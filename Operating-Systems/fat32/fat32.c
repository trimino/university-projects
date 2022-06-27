
// The MIT License (MIT)
// 
// Copyright (c) 2020 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_NUM_ARGUMENTS 4
#define NUM_ENTRIES 16
#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size


// BPB: BIOS Parmeter Block  - located in the first sector of the reserved sectors
char    BS_OEMName[8];
char    BS_VolLab[11];
int8_t  BPB_SecPerClus;
int8_t  BPB_NumFATs;

int16_t BPB_RootEntCnt;
int16_t BPB_BytesPerSec;
int16_t BPB_RsvdSecCnt;

int32_t BPB_FATSz32;
int32_t BPB_RootClus;
int32_t RootDirSectors = 0;
int32_t FirstDataSector = 0;
int32_t FirstSectorofCluster = 0;

FILE *fp;
int file_open = 0;

// Each record can be represented by the struct below
struct __attribute__((__packed__)) DirectoryEntry{
    char        DIR_Name[11];
    uint8_t     DIR_Attr;
    uint8_t     Unused1[8];
    uint8_t     Unused2[4];
    uint16_t    DIR_FirstClusterHigh;
    uint16_t    DIR_FirstClusterLow;
    uint32_t    DIR_FileSize;
};
struct DirectoryEntry dir[16];


/*
*Function       : LBAToOffset
*Parameters     : The current sector number that points to a block of data
*Returns        : The value of the address for that block of data
*Description    : Finds the starting address of  a block of data given the sector number corresponding to that data block  
*/
int LBAToOffset(int32_t sector)
{
    return ( (sector - 2) * BPB_BytesPerSec ) + (BPB_BytesPerSec * BPB_RsvdSecCnt) + (BPB_NumFATs * BPB_FATSz32 * BPB_BytesPerSec);
}


/*
Name: NextLB
Parameters: Given a logical block address, look up into the first FAT and return the logical block address of the block in the file. If there is no futher 
blocks then return -1;
*/
int16_t NextLB(uint32_t sector)
{
    uint32_t    FATAddress = (BPB_BytesPerSec * BPB_RsvdSecCnt) + (sector * 4);
    int16_t     val;
    
    fseek( fp, FATAddress, SEEK_SET);
    fread( &val, 2, 1, fp);
    return val;
}


int compare(char *userString, char *directoryString)
{
    char *dotdot = "..";

    if (strncmp(dotdot, userString, 2) == 0)
    {
        if (strncmp(userString, directoryString, 2) == 0)
        {
        return 1;
        }
        return 0;
    }

    char IMG_Name[12];

    strncpy(IMG_Name, directoryString, 11);
    IMG_Name[11] = '\0';

    char input[11];
    memset(input, 0, 11);
    strncpy(input, userString, strlen(userString));

    char expanded_name[12];
    memset(expanded_name, ' ', 12);

    char *token = strtok(input, ".");

    strncpy(expanded_name, token, strlen(token));

    token = strtok(NULL, ".");

    if (token)
    {
        strncpy((char *)(expanded_name + 8), token, strlen(token));
    }

    expanded_name[11] = '\0';

    int i;
    for (i = 0; i < 11; i++)
    {
        expanded_name[i] = toupper(expanded_name[i]);
    }

    if (strncmp(expanded_name, IMG_Name, 11) == 0)
    {
        return 1;
    }
    return 0;
}


/* 
*Name       : info
*Parameters : None
*Returns    : int
*Description: prints the informatin about BPB
*/
int info()
{
    printf("BPB_BytsPerSec: %d\nBPB_BytsPerSec: %.4x\n", BPB_BytesPerSec, BPB_BytesPerSec); //512
    printf("BPB_SecPerClus: %d\nBPB_SecPerClus: %.4x\n", BPB_SecPerClus, BPB_FATSz32);    //1
    printf("BPB_RsvdSecCnt: %d\nBPB_RsvdSecCnt: %.4x\n", BPB_RsvdSecCnt, BPB_FATSz32);    //32
    printf("BPB_NumFATs: %d\nBPB_NumFATs: %.4x\n", BPB_NumFATs, BPB_FATSz32);
    printf("BPB_FATSz32: %d\nBPB_FATSz32: %.4x\n", BPB_FATSz32, BPB_FATSz32);
    return 0;
}


/* 
*Name       : ls
*Parameters : None
*Returns    : int
*Description: List contents in the directory execept for deleted and system files
*/
int ls()
{
    int i ;
    for(i = 0; i < NUM_ENTRIES; i++)
    {
        char filename[12];
        strncpy(filename, dir[i].DIR_Name, 11);
        // Do not list deleted files or system volme names
        if((dir[i].DIR_Attr == 0x01 || dir[i].DIR_Attr == 0x10 || dir[i].DIR_Attr == 0x20 ) && filename[0] != 0xffffffe5)
        {
            printf("%s\n",filename);
        }
    }
    return 0;
}


/*
*Name       : readfile
*Parameters : filename, requested off set, requested bytes
*Returns    : Outputs the bytes in hexadecimal
*Description: Reads from a given file at the position (in bytes) specified by the position parameter and output the number of bytes specified. 
*/
int readfile(char *filename, int requestedOffset, int requestedBytes)
{
    int i;
    int found = 0;
    int bytesRemainingToRead = requestedBytes;

    if (requestedOffset < 0)
    {
        printf("Error: Offset is less than zero");
    }

    for (i = 0; i < NUM_ENTRIES; i++)
    {
        if (compare(filename, dir[i].DIR_Name))
        {
            int cluster = dir[i].DIR_FirstClusterLow;

            found = 1;

            int searchSize = requestedOffset;

            while (searchSize >= BPB_BytesPerSec)
            {
                cluster = NextLB(cluster);
                searchSize = searchSize - BPB_BytesPerSec;
            }

            int offset = LBAToOffset(cluster);
            int byteOffset = (requestedOffset % BPB_BytesPerSec);
            fseek(fp, offset + byteOffset, SEEK_SET);

            unsigned char buffer[BPB_BytesPerSec];

            int firstblockbytes = BPB_BytesPerSec - requestedOffset;
            fread(buffer, 1, firstblockbytes, fp);

            for (i = 0; i < firstblockbytes; i++)
            {
                printf("%x ", buffer[i]);
            }

            bytesRemainingToRead = bytesRemainingToRead - firstblockbytes;

            while (bytesRemainingToRead >= 512)
            {
                cluster = NextLB(cluster);
                offset = LBAToOffset(cluster);
                fseek(fp, offset, SEEK_SET);
                fread(buffer, 1, BPB_BytesPerSec, fp);

                for (i = 0; i < BPB_BytesPerSec; i++)
                {
                    printf("%x ", buffer[i]);
                }
                bytesRemainingToRead = bytesRemainingToRead - BPB_BytesPerSec;
            }

            if (bytesRemainingToRead)
            {
                cluster = NextLB(cluster);
                offset = LBAToOffset(cluster);
                fseek(fp, offset, SEEK_SET);
                fread(buffer, 1, BPB_BytesPerSec, fp);

                for (i = 0; i < bytesRemainingToRead; i++)
                {
                    printf("%x ", buffer[i]);
                }
            }
            printf("\n");
        }
    }

    if (!found)
    {
        printf("Error: File was not Found\n");
        return -1;
    }

    return 0;
}


/* 
*Name       : cd
*Parameters : Directory the user chooses to go into
*Returns    : 0 upon success and -1 upon failure
*Description: Command that will change the working directory to the given directory. (Supports cd ../name)
*/
int cd(char *directoryName)
{
    int i;
    int found = 0;
    for (i = 0; i < NUM_ENTRIES; i++)
    {
        if (compare(directoryName, dir[i].DIR_Name))
        {
            int cluster = dir[i].DIR_FirstClusterLow;

            if (cluster == 0)
            {
                cluster = 2;
            }

            int offset = LBAToOffset(cluster);
            fseek(fp, offset, SEEK_SET);
            fread(dir, sizeof(struct DirectoryEntry), NUM_ENTRIES, fp);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Error Directory Wasn't found\n");
        return -1;
    }
    return 0;
}



int main()
{

    char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );

    while( 1 )
    {
        // Print out the mfs prompt
        printf ("mfs> ");

        // Read the command from the commandline.  The
        // maximum command that will be read is MAX_COMMAND_SIZE
        // This while command will wait here until the user
        // inputs something since fgets returns NULL when there
        // is no input
        while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );

        /* Parse input */
        char *token[MAX_NUM_ARGUMENTS];

        int   token_count = 0;                                 
                                                            
        // Pointer to point to the token
        // parsed by strsep
        char *arg_ptr;                                         
                                                            
        char *working_str  = strdup( cmd_str );                

        // we are going to move the working_str pointer so
        // keep track of its original value so we can deallocate
        // the correct amount at the end
        char *working_root = working_str;

        // Tokenize the input stringswith whitespace used as the delimiter
        while ( ( (arg_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && 
                (token_count<MAX_NUM_ARGUMENTS))
        {
        token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );
        if( strlen( token[token_count] ) == 0 )
        {
            token[token_count] = NULL;
        }
            token_count++;
        }

        // CODE TO HELP WITH DEUBG - prints tokenized input
        int token_index  = 0;
        for( token_index = 0; token_index < token_count; token_index ++ ) 
        {
          printf("token[%d] = %s\n", token_index, token[token_index] );  
        }
        free( working_root );

        // Catch NULL inputs (when user presses enter)
        if (token[0] == NULL && token[1] == NULL)
        {
            int a = 0;  // trival assignment
        }

        else if (strcmp( token[0], "open" ) == 0)
        {
            // Condition if the user opens a file that is already opened
            if (file_open)
            {
                printf("The file is already opened\n");
            }
            else
            {
                if (access(token[1], F_OK) == 0)
                {
                    // Open the fat32.img
                    fp = fopen( token[1], "r");
                    file_open = 1;

                    if (file_open)
                    {
                        // seek set move from the beginning of the file
                        // seek cur move from where we currently are
                        // seek end move from the end of the file toward the head of the file

                        fseek(fp,11,SEEK_SET);
                        fread(&BPB_BytesPerSec,2,1,fp);

                        fseek(fp,13,SEEK_SET);
                        fread(&BPB_SecPerClus,1,1,fp);

                        fseek(fp,14,SEEK_SET);
                        fread(&BPB_RsvdSecCnt,2,1,fp);

                        fseek(fp,16,SEEK_SET);
                        fread(&BPB_NumFATs,1,1,fp);

                        fseek(fp,36,SEEK_SET);
                        fread(&BPB_FATSz32,4,1,fp);

                        RootDirSectors = (BPB_NumFATs * BPB_FATSz32 * BPB_BytesPerSec) +(BPB_RsvdSecCnt * BPB_BytesPerSec);

                        fseek(fp,RootDirSectors,SEEK_SET);
                        fread(dir, 16, sizeof(struct DirectoryEntry), fp);
                    }
                    else
                    {
                        printf("ERROR: file system not found\n");
                    }
                }
                else
                {
                    printf("Could not find file image: %s\n", token[1]);
                }
            }

        }


        else if (strcmp( token[0], "stat" ) == 0)
        {
            // Code for stat command
        }


        else if(strcmp( token[0], "cd" ) == 0)
        {
            if (file_open)
            {
                cd( token[1] );
            }  
            else
            {
                printf("ERROR: File Image Not Open\n");
            }    
        }


        else if (strcmp(token[0], "ls" ) == 0)
        {
            if (fp)
            {
                ls();
            }
            else
            {
                printf("ERROR: File Image Not Open\n");
            }   
        }


        else if (strcmp( token[0], "get" ) == 0)
        {
            if (file_open)
            {
                // Function call for get
            }
            else
            {
                printf("ERROR: File Image Not Open\n");
            }
        }


        else if (strcmp( token[0], "read" ) == 0)
        {
            if (file_open)
            {
                if (token[2] && token[3])
                {
                    readfile( token[1], atoi(token[2]), atoi(token[3]) );
                }
                else
                {
                    printf("ERROR: Please use right format <filename> <position> <number of bytes>\n");
                }
            }
            else
            {
                printf("ERROR: File Image Not Open\n");
            }
        }


        else if (strcmp( token[0], "close" ) == 0)
        {
            if (file_open)
            {
                fclose(fp);
                file_open = 0;
            }
            else
            {
                printf("ERROR: File has not been opened\n");
            }
        }


        else if (strcmp( token[0], "bpb" ) == 0)
        {
            if (fp)
            {
                info();
            }
            else
            {
                printf("ERROR: File Image Not Open\n");
            }
            
        }


        else if (strcmp( token[0], "quit" ) == 0)
        {
            free(working_root);
            if (file_open)
                fclose(fp);
            return 0;
        }


        else 
        {
            if(fp)
            printf("Command not found ! \n");
            else
            printf("Error: First system image must be opened first\n");
        }
    }
  return 0;
}