
// Shell starter file
// You may make any changes to any part of this file.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/limits.h>
#include <errno.h>
#include <signal.h>

#define COMMAND_LENGTH 1024
#define NUM_TOKENS (COMMAND_LENGTH / 2 + 1)
#define HISTORY_DEPTH 10

char history[HISTORY_DEPTH][COMMAND_LENGTH];
int history_count = 0; //keep track of history command number
int global; 
pid_t childpid; /* variable to store the child's pid */
int retval;     /* child process: user-provided return code */
int status;     /* parent process: child's exit status */
char cwd[PATH_MAX]; //for get working directory //https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
bool my_val = true;
bool n_val = false;

/**
 * Command Input and Processing
 */
  /*
	History Commands:
 */
 // Add command to history, 
void add_history(char *hist_buff ){

	char hist_num[50];
	int i = history_count % 10; //we are wrapping around rather than shifting, using modulus
	history_count++;
	strcpy(history[i], hist_buff);
	sprintf(hist_num,"here %d\t%s \n", history_count, history[i]);
	//write(STDOUT_FILENO, hist_num, strlen(hist_num));

	//for debuggin
	//write(STDOUT_FILENO, "adding to history\n\n", strlen("adding to history\n\n"));

	memset(hist_num,0,50);// reset array, idk if this is needed
	//check: Can't you just free the array as it is redeclared every time the function is called?

}

 // Retrieve command (copy into buffer, likely),
/*
char * retrieve_history_cmd(){
	return;
}
*/
 // Printing the last ten commands to the screen.
 void print_history(){
	 char hist_num[50];
	 int temp_hist_count= 1; //dont want to touch actual history count, this is for printing
	 int i = (history_count+10) % 10;  // which string to print. it will wrap around

	if(history_count <= 10){ //start at begginning if less than 10 
		temp_hist_count = 1;
		i =0;
	}
	else{ //most of the cases, above 10 commands
		temp_hist_count = history_count-9;
	}
	while(temp_hist_count-1 != history_count){ //while we dont reach recent command
		sprintf(hist_num," %d \t%s\n", temp_hist_count, history[i]);
		write(STDOUT_FILENO, hist_num, strlen(hist_num));
	
		temp_hist_count++;
		memset(hist_num,0,50);
		i++;
		i = i% 10; //remember to wrap around using modulus
	}

 }

 void handle_SIGINT(){

 		my_val = false;
 		write(STDOUT_FILENO, "\n", strlen("\n"));
 		print_history();

  }

/*
 * Tokenize the string in 'buff' into 'tokens'.
 * buff: Character array containing string to tokenize.
 *       Will be modified: all whitespace replaced with '\0'
 * tokens: array of pointers of size at least COMMAND_LENGTH/2 + 1.
 *       Will be modified so tokens[i] points to the i'th token
 *       in the string buff. All returned tokens will be non-empty.
 *       NOTE: pointers in tokens[] will all point into buff!
 *       Ends with a null pointer.
 * returns: number of tokens.
 */
int tokenize_command(char *buff, char *tokens[])
{
	int token_count = 0;
	_Bool in_token = false;
	int num_chars = strnlen(buff, COMMAND_LENGTH);
	for (int i = 0; i < num_chars; i++) {
		switch (buff[i]) {
		// Handle token delimiters (ends):
		case ' ':
		case '\t':
		case '\n':
			buff[i] = '\0';
			in_token = false;
			break;

		// Handle other characters (may be start)
		default:
			if (!in_token) {
				tokens[token_count] = &buff[i];
				token_count++;
				in_token = true;
			}
		}
	}
	tokens[token_count] = NULL;
	return token_count;
}

/**
 * Read a command from the keyboard into the buffer 'buff' and tokenize it
 * such that 'tokens[i]' points into 'buff' to the i'th token in the command.
 * buff: Buffer allocated by the calling code. Must be at least
 *       COMMAND_LENGTH bytes long.
 * tokens[]: Array of character pointers which point into 'buff'. Must be at
 *       least NUM_TOKENS long. Will strip out up to one final '&' token.
 *       tokens will be NULL terminated (a NULL pointer indicates end of tokens).
 * in_background: pointer to a boolean variable. Set to true if user entered
 *       an & as their last token; otherwise set to false.
 */


void read_command(char *buff, char *tokens[], _Bool *in_background)
{
	*in_background = false;

	// Read input
	int length = read(STDIN_FILENO, buff, COMMAND_LENGTH-1);
	
	if ( (length < 0) && (errno != EINTR) ) {
		perror("Unable to read command. Terminating.\n");
		exit(-1); //terminate with error
	}

	// Null terminate and strip \n.
	buff[length] = '\0';
	if (buff[strlen(buff) - 1] == '\n') {
		buff[strlen(buff) - 1] = '\0';
	}

	n_val = true;

	// ******retrieve and add history stuff **********//check
	/*
	I was thinking putting all this code inside the retrieve function.
	that function can return the retrieved buff into the buff here.
	for error handling i was thinking replacing buff with key words
	then when the key word is read in the main while loop we print the
	error ..........
	*/
	char justNum[50];
	int i= 0;
	if(buff[0]=='!' && buff[1] == '!'){	//run prev command
		
		if(history_count >= 1){
			i = (history_count+9) % 10;
			strcpy(buff, history[i]);
			write(STDOUT_FILENO, buff, strlen(buff));
			write(STDOUT_FILENO, "\n", strlen("\n")); //new buff is pulled from history
			add_history(buff); 
		}
		else{
			//check : error handling
		}
	}

	else if(buff[0]== '!'){
		
		
		strcpy(justNum, &buff[1]);
		int run_prev = atoi(justNum); //get the number to run

		if(run_prev<= history_count && run_prev>0){
			//run_prev--;
			i = (run_prev +9) % 10;
			strcpy(buff, history[i]);
			write(STDOUT_FILENO, buff, strlen(buff));
			write(STDOUT_FILENO, "\n", strlen("\n")); //pullng new command from history
			add_history(buff);
		}
		else{
			//check: error handling
		}
	}

	else{ //regular case
		//add command to history
		if(my_val){
		add_history(buff);
		} //check had to put it here cause after it gets messed up
	}
	
	// Tokenize (saving original command string)
	int token_count = tokenize_command(buff, tokens);
	if (token_count == 0) {
		return;
	}

	// Extract if running in background:
	if (token_count > 0 && strcmp(tokens[token_count - 1], "&") == 0) {
		*in_background = true;
		tokens[token_count - 1] = 0;
	}
}

/**
 * Main and Execute Commands
 
*/
int main(int argc, char* argv[])
{
	char input_buffer[COMMAND_LENGTH];
	char *tokens[NUM_TOKENS];
	while (true) {

		// Get command
		// Use write because we need to use read() to work with
		// signals, and read() is incompatible with printf().
		if(getcwd(cwd, sizeof(cwd)) != NULL){
			write(STDOUT_FILENO, cwd, strlen(cwd));

		}

		write(STDOUT_FILENO, "> ", strlen("> "));
		_Bool in_background = false;

		signal(SIGINT, handle_SIGINT);//look up man signal for more info

		if(getchar() == '\n' && !n_val){ //checks for enter before reading into buffer
			n_val = true;
			continue;
		}

		read_command(input_buffer, tokens, &in_background);


		if(!my_val){
			my_val = true;
			continue;
		}

		if(!strcmp(tokens[0],"exit")){
			
			exit(0);

		}
		
		else if(!strcmp(tokens[0],"pwd")){
		
			if(getcwd(cwd, sizeof(cwd)) != NULL){
				write(STDOUT_FILENO, cwd, strlen(cwd));
				write(STDOUT_FILENO, "\n", strlen("\n"));
			}

			else{
				write(STDOUT_FILENO, "pwd failed\n", strlen("pwd failed\n"));
			}
		}

		else if(!strcmp(tokens[0],"cd")){
		
			if(chdir(tokens[1]) != 0){
				write(STDOUT_FILENO, "No such file or directory.\n", strlen("No such file or directory.\n"));
			}
		}
		
		else if(!strcmp(tokens[0],"history")){
				print_history();
		}	
		
		else{
 
			childpid = fork();
			
			if(childpid >= 0){ //fork successful
				
				if(childpid == 0){
					//this is child

					if(execvp(tokens[0], tokens) == -1){
						char unknown[100];
						sprintf(unknown, "%s: Unknown command\n", tokens[0]);
						write(STDOUT_FILENO, unknown, strlen(unknown));
					}

					exit(0);
				}

				else{
					//this is parent
					
					if(in_background){
						//do not wait for child to end and continue other tasks
					}

					else{
						//wait for for child to end
						waitpid(childpid,&status, 0); //check : option 0 waits fo any child process 
					}
				}
			}

			else{
				write(STDOUT_FILENO, "fork failed\n", strlen("fork failed\n"));
				exit(0);
			}
		}

			

	}
	return 0;
}