/**************************************************************
* Class:  CSC-415-03 Fall 2022
* Name: Mark Kim
* Student ID: 918204214
* GitHub ID: mkim797
* Project: Assignment 3 – Simple Shell
*
* File: Kim_Mark_HW3_main.c
*
* Description:
* This is a simple shell that runs on top of the regular command-
* line interpreter for Linux.
*
**************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE  123

int main(int argc, char *argv[]) {
    // Buffer, shell arguments, and tokens
    char buf[BUFFER_SIZE];
    int sh_argc;
    char *sh_argv[BUFFER_SIZE/2];
    char *token;
    char *prompt;

    // Child status and process id
    int c_stat;
    pid_t c_pid;

    // This changes the prompt to whatever is provided as a command
    // line argument or ">" as default. (Requirement #8 in Requirements.md)
    if (argc > 1) {
        prompt = argv[1];
    } else {
        prompt = ">";
    }
    
    while(1) {
        printf("%s", prompt);  // The prompt for the shell

        // Takes in user input and writes it to buffer.
        // As specified in linux man page documentation, NULL is returned
        // if EOF is reached from fgets, hence shell will exit gracefully per
        // requirements (Error Handling #2 in Requirements.md)
        if(fgets(buf, BUFFER_SIZE, stdin) == NULL) {
            printf("\nThank you for using my command shell.\n");
            return 0;
        }

        // In the chance that user input exceeds the buffer size
        // the buffer is cleared by iterating through the rest of
        // standard input with fgetc() until a new line is reached.
        // 
        if (strlen(buf) >= BUFFER_SIZE - 1) {
            while(fgetc(stdin) != '\n');
        }
    
        // We tokenize the buffer and enter all the tokens into
        // the shell argument vector all the while incrementing
        // the argument count. A NULL is placed at the end of the array
        // per man page specifications for execvp.
        // (Requirements #4 & #6 in Requirements.md)
        token = strtok(buf, " \n\t");
        sh_argc = 0;
        while (token != NULL) {
            sh_argv[sh_argc++] = token;
            printf("Token: '%s'\n", token);
            token = strtok(NULL, " \n\t");
        }
        sh_argv[sh_argc++] = NULL;

        // sh_argv[0] will be NULL when a user inputs empty lines
        // or lines of whitespace are entered. As specified,
        // an error is reported and a new line of input is fetched,
        // (Error Handling #3 in Requirements.md)
        if (sh_argv[0] == NULL) {
            perror("Error: An empty line was entered. Please try again.");
            continue;
        } 
        // The exit command shall terminate the shell, so a strcmp
        // is used to check if the first argument in the argument vector
        // is exit. (Requirement #7 in Requirements.md)
        else if(!strcmp(sh_argv[0], "exit")) {
            printf("\nThank you for using my command shell.\n");
            return 0;
        } else {
            // Per man page specification, fork() returns -1 if it failed,
            // 0 if this is the child process, or the child process id 
            // if this is the parent process. execvp() is called in the child
            // process per specifications. (Requirement #1 & #3 in
            // Requirements.md)
            c_pid = fork();
            if ( c_pid < 0 ) {
                perror("Fork failed: exiting");
                return (-1);
            } else if ( c_pid == 0 ) {
                // Child process.
                // Per man page specification, execvp() returns -1 if it fails
                // this handles that case while executing execvp().
                if(execvp(sh_argv[0], sh_argv) < 0) {
                    perror("Execvp failed: exiting");
                    return (-1);
                }
            } else {
                // Parent process:
                // Per specification, the shell waits for child process to
                // complete, then prints the child PID and the result from
                // the child process. (Requirement #2 in Requirements.md)
                wait(&c_stat);
                printf("Child %d, exited with %d\n", c_pid, WEXITSTATUS(c_stat));
            }
        }
    }
    return 0;
}
