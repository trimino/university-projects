/*
  Name: David Trimino
  ID:   1001659459
*/
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define ALIGN4(s)         (((((s) - 1) >> 2) << 2) + 4)
#define BLOCK_DATA(b)      ((b) + 1)
#define BLOCK_HEADER(ptr)   ((struct _block *)(ptr) - 1)


static int atexit_registered = 0;
static int num_mallocs       = 0;
static int num_frees         = 0;
static int num_reuses        = 0;
static int num_grows         = 0;
static int num_splits        = 0;
static int num_coalesces     = 0;
static int num_blocks        = 0;
static int num_requested     = 0;
static int max_heap          = 0;
struct _block *head = NULL;
struct _block *heapList = NULL; /* Free list to track the _blocks available */

/*
 *  \brief printStatistics
 *
 *  \param none
 *
 *  Prints the heap statistics upon process exit.  Registered
 *  via atexit()
 *
 *  \return none
 */
void printStatistics( void )
{

  printf("\nheap management statistics\n");
  printf("mallocs:\t%d\n", num_mallocs );
  printf("frees:\t\t%d\n", num_frees );
  printf("reuses:\t\t%d\n", num_reuses );
  printf("grows:\t\t%d\n", num_grows );
  printf("splits:\t\t%d\n", num_splits );
  printf("coalesces:\t%d\n", num_coalesces );
  printf("blocks:\t\t%d\n", num_blocks );
  printf("requested:\t%d\n", num_requested );
  printf("max heap:\t%d\n", max_heap );
}

struct _block 
{
   size_t  size;         /* Size of the allocated _block of memory in bytes */
   struct _block *prev;  /* Pointer to the previous _block of allcated memory   */
   struct _block *next;  /* Pointer to the next _block of allcated memory   */
   bool   free;          /* Is this _block free?                     */
   char   padding[3];
};



/*
 * \brief findFreeBlock
 *
 * \param last pointer to the linked list of free _blocks
 * \param size size of the _block needed in bytes 
 *
 * \return a _block that fits the request or NULL if no free _block matches
 */
struct _block *findFreeBlock(struct _block **last, size_t size) 
{
   struct _block *curr = heapList;
   
#if defined FIT && FIT == 0
   /* First fit */
   while (curr && !(curr->free && curr->size >= size)) 
   {
      *last = curr;
      curr  = curr->next;
   }
#endif

#if defined BEST && BEST == 0

   size_t smallest = 0;
  
   struct _block *trackerr = NULL;
   
      while (curr) 
      {
         *last = curr;
         if(curr->free  && curr->size > size)
         {
            if(smallest == 0) // make smallest the first diff in the free block its find
             {
                smallest = curr->size - size;
                trackerr = curr;
             }
             else if( (curr->size - size ) < smallest) // if the next diff in smaller than smallest
            {
               trackerr = curr;
               smallest = curr->size - size ; // make new diff the new smallest
            }
         }
         curr  = curr->next;
      }
      
      curr = trackerr;
#endif

#if defined WORST && WORST == 0

   size_t biggest = 0;
   struct _block *trackerr = NULL;
   
      while (curr) 
      {
         *last = curr;
         if(curr->free  && curr->size > size)
         {
            if(biggest == 0) // make biggest the first diff in the free block its find
             {
                biggest = curr->size - size;
                trackerr = curr;
             }            
            else if( (curr->size - size ) > biggest ) // if the next left over diff is bigger than biggest
            {
               biggest = curr->size - size ; // make new diff the new biggest
               trackerr = curr;
            }
         }
         curr  = curr->next;
      }
      curr = trackerr;
#endif

#if defined NEXT && NEXT == 0

   if(head != NULL)
   {
      curr = head;
   }
   else if(head == NULL)
   {
      curr=*last;
   }
   while (curr && !(curr->free && curr->size >= size)) 
   {
      *last = curr;
      curr  = curr->next;
   }
   head = curr;
   
#endif
   
   return curr;
}

/*
 * \brief growheap
 *
 * Given a requested size of memory, use sbrk() to dynamically 
 * increase the data segment of the calling process.  Updates
 * the free list with the newly allocated memory.
 *
 * \param last tail of the free _block list
 * \param size size in bytes to request from the OS
 *
 * \return returns the newly allocated _block of NULL if failed
 */
struct _block *growHeap(struct _block *last, size_t size) 
{
   /* Request more space from OS */
   struct _block *curr = (struct _block *)sbrk(0);
   struct _block *prev = (struct _block *)sbrk(sizeof(struct _block) + size);
   
   assert(curr == prev);

   /* OS allocation failed */
   if (curr == (struct _block *)-1) 
   {
      
      return NULL;
   }

   /* Update heapList if not set */
   if (heapList == NULL) 
   {   
      heapList = curr;
   }

   /* Attach new _block to prev _block */
   if (last) 
   {
      
      last->next = curr;
   }
   
   /* Update _block metadata */
   curr->size = size;
   curr->next = NULL;
   curr->free = false;
  
   num_grows ++;
   
   //max_heap = num_requested * num_mallocs;   
   return curr;
}

/*
 * \brief malloc
 *
 * finds a free _block of heap memory for the calling process.
 * if there is no free _block that satisfies the request then grows the 
 * heap and returns a new _block
 *
 * \param size size of the requested memory in bytes
 *
 * \return returns the requested memory allocation to the calling process 
 * or NULL if failed
 */
void *malloc(size_t size) 
{
    
   num_requested += size;
   num_mallocs++;
   if( atexit_registered == 0 )
   {
      atexit_registered = 1;
      atexit( printStatistics );
   }

   /* Align to multiple of 4 */
   size = ALIGN4(size);

   /* Handle 0 size */
   if (size == 0) 
   {
      return NULL;
   }

   /* Look for free _block */
   struct _block *last = heapList;
   struct _block *next = findFreeBlock(&last, size);
   const int block_size = sizeof(struct _block);
   

   
   if(next){
   
      if( (next->size - size) > sizeof(struct _block))
      {
         num_splits++;
         num_blocks++;
         int old_size = next->size;
         struct _block * old_next = next->next;
         uint8_t * ptr = (uint8_t*) next;
         next->size = size + next->size + block_size;
         next->next = (struct _block*)(ptr + size + sizeof(struct _block));
         next->size = size;
         next->next->free = 1;
         next->next->size = old_size-size-block_size;
         next->next->next = old_next;  
      }
   }
   /* Could not find free _block, so grow heap */
   if (next == NULL) 
   { 
      next = growHeap(last, size);
      num_reuses++;
      max_heap += size; 
   }
   
 

   /* Could not find free _block or grow heap, so just return NULL */
   if (next == NULL) 
   {
      
      return NULL;
   }
   
   /* Mark _block as in use */
   
   next->free = false;
   
   /* Return data address associated with _block */
   return BLOCK_DATA(next);
}

/*
 * \brief free
 *
 * frees the memory _block pointed to by pointer. if the _block is adjacent
 * to another _block then coalesces (combines) them
 *
 * \param ptr the heap memory to free
 *
 * \return none
 */
void free(void *ptr) 
{
   if (ptr == NULL) 
   {
      return;
   }

   /* Make _block as free */
   struct _block *currr = BLOCK_HEADER(ptr);
   assert(currr->free == 0);
   currr->free = true;
   //num_requested = max_heap + currr->size ;

   
   num_frees++;
   struct _block* curr = heapList;
  
      if( curr && curr->next )
         {
            if( curr->free  && curr->next->free  )
               {
                  num_coalesces ++; 
                  num_blocks --;
                  curr->size = curr->size + curr->next->size + sizeof(struct _block);
                  if(curr->next->next  )
                  {
                     curr->next = curr->next->next;
                  }
                  else
                  {
                     curr->next = NULL;
                  }
               }
         }

}
void *realloc(void *ptr, size_t size)
{
   if (size == 0) 
   {
      free(ptr);
      return NULL;
   }
   else
   {
      struct _block *new = malloc(size);
      memcpy(new,ptr,sizeof(void*));
      return BLOCK_DATA(new);
   }
  
}
void *calloc(size_t nmemb, size_t size )
{
   if (size == 0) 
   {
      return NULL;
   }
   size_t block_size = nmemb*size;
   struct _block *new  = malloc(block_size);
   if(new == NULL)
   {
      return NULL;
   }
   else
   {
      memset(new,'\0',block_size);
   }
   return BLOCK_DATA(new);

}

/* vim: set expandtab sts=3 sw=3 ts=6 ft=cpp: --------------------------------*/