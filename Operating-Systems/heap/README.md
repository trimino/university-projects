# Heap Management 


## Summary

This mini operating systems project is to build and implement a custom malloc and free function. In this project I needed to implement a library that interacts with the operating system to perform heap management on behalf of a user process. 





## Program Requirements

* [x] Implemented a splitting and coalescing of free blocks. If two blocks are adjacent then combine them. If a free block is larger than the requested size then split the block into two
* [x] Implemented a three additional heap management strategies: Next-Fit, Worst-Fit, Best-Fit, and First-Fit
* [x] Counters:
	* Count number of times the user calls malloc successfully
	* Count number of times the user calls free successfully
	* Count number of times we reuse an existing block 
	* Count number of times we request a new block
	* Count number of times we split a block 
	* Count number of times we coalesce blocks
	* Count number of times blocks in free list
	* Count total amount of memory requested
	* Maximum size of the heap
* [x] Code will print these statistics (THESE STAT ARE FAKE):
	* mallocs:	8
	* freees:	8
	* reuses:	1
	* grows:	5
	* splits:	1
	* coalesces:	1
	* blocks:	5
	* requested:	7298
	* max heap:	4096
* [x] Four test programs are provided to help debug your code. Located in the tests directory
* [x] Implement realloc and calloc
	
	
	
## Building and Running the Code
	* The code compiles into four shared libraries and six test programs. To build the code to your top level directory and type:
		$ make

	* Once you have the library, you can use it to override the existing malloc by using LD_PRELOAD:
			$ env LD_PRELOAD=lib/libmalloc-ff.so cat README.md
		or
			$ env LD_PRELOAD=lib/libmalloc-ff.so tests/test 1


	* Best-Fit: libmalloc-bf.so
	* First-Fit: libmalloc-ff.so
	* Next-Fit: libmalloc-nf.so
	* Worst-Fit: libmalloc-wf.so
