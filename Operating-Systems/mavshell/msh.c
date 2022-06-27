/*
 * Name: David Trimino
 * ID: 1001659459
 */



#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 5     // Mav shell only supports five arguments

int main()
{
  // Count will help keep track of commands 	
  int count = 0;
  char* commands[15];
  int i;
  for(i = 0; i < 15; i++)
    commands[i] = malloc(sizeof(char) * 255 );
  
  // pids_count will help keep track of the last 15 pids 
  int pid_count = 0;
  int pids[15];


  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );

  while( 1 )
  {
    // Print out the msh prompt
    printf ("msh> ");

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
    char *argument_ptr;                                         
    
    char *working_str  = strdup( cmd_str );                
    
    // we are going to move the working_str pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *working_root = working_str;
    
    // Tokenize the input stringswith whitespace used as the delimiter
    while ( ( (argument_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && 
              (token_count<MAX_NUM_ARGUMENTS)) {
      token[token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    
    // Set up variables
    int status;
    int i;

    pid_t process = -1;
    char* PATH[4]= {"./", "/usr/local/bin/", "/usr/bin/", "/bin/"};
    
    // Helps us keep track of the last 15 command counts (valid and not valid) 
    if( token[0] != NULL ) {
      if ( count < 15 ) count++;
      for(i = count - 1; i > -1; i--){
        strcpy( commands[i+1], commands[i] );
      }

      // Get the length of the command
      int space = 0;
      for(i = 0; i < token_count - 1 && token[i] != NULL; i++){
        space = space + strlen( token[i] ) + 1;
      }

      // Copy contents to a char* 
      char* temp = malloc(sizeof(char) * space);		
      strcpy( temp, token[0] );
      for(i =1; i < token_count - 1 && token[i] != NULL; i++){
        strcat(temp, " " );
	strcat(temp, token[i] );
      }
     
      strcpy(commands[0], temp);
      free( temp );
    }

    
    // Check for an input that could result in a seg fault (NULL) or if user wants to exit program
    if( token[0] == NULL ) process = -1;
    else if( strcmp(token[0], "quit") == 0 || strcmp(token[0], "exit") == 0 ){
      break;
    }

    // Child process will not affect parent process 
    // Check for a command that needs to be run by the parent process
    // process = -1 
    else if( strcmp(token[0], "cd") == 0 ){
      chdir( token[1] );
    }
    else if ( strcmp(token[0], "showpids") == 0 ){
      for(i = 0; i < pid_count; i++)
	printf("[%d]: %d\n", i, pids[i]); 
    }
    else if( strcmp(token[0], "history") == 0 ){
      for(i = 0; i < count; i++)
        printf("[%d]: %s\n", i+1, commands[i]);
    }
    else if( token[0][0] == '!' ){
      // In ASCI Code digits start at 48 
      int index = (int) token[0][1] - 48;
      char* temp;
      token_count = 0;
      while( (temp = strsep(&commands[index], WHITESPACE)) != NULL ){
        token[token_count] = strndup( temp, strlen(temp) + 1 );
	token_count++;
      }
     
      process = fork();     
    }

    // if the command is not a built-in command then create a fork 
    // to be executed by the child 
    else{
        process = fork();
    }
    

    // Run user specified commands only for the child process
    // execvpe() used because it helps us meet the PATH requirements to find a specific command
    // PATH REQUIREMENTS:
    // 1. current working directory
    // 2. /usr/local/bin/
    // 3. /usr/bin/
    // 4. /bin
    if( process == 0 ){    
      
      if( execvpe(token[0], token, PATH) == -1 ){
        char* error = token[0];
	strcat(error, " : Command not found\n");
	perror(error);
        exit(EXIT_FAILURE);
      }

      exit(EXIT_SUCCESS);
    }
    else if( process > 0){
      // Force the parent process to wait until child is finished
      waitpid(process, &status, 0);
      if( pid_count < 15 ) pid_count++;
      for(i = pid_count - 1; i > -1; i--)
        pids[i+1] = pids[i];

      pids[0] = process;
      fflush(NULL);
    } 

     

/*
    // Code to help debug user input
    int token_index  = 0;
    for( token_index = 0; token_index < token_count; token_index ++ ) 
    {
      printf("token[%d] = %s\n", token_index, token[token_index] );  
    }
*/    
    free( working_root );
  
  }
  
  
  for(i = 0; i < 15; i++){
    free( commands[i] );
  }
  return 0;
}
