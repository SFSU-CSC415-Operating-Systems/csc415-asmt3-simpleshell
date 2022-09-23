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
    char buf[BUFFER_SIZE];
    int sh_argc;
    char *sh_argv[BUFFER_SIZE/2];
    char *token;
    char *prompt;
    int c_stat;
    pid_t c_pid;

    if (argc > 1) {
        prompt = argv[1];
    } else {
        prompt = ">";
    }
    
    while(1) {
        printf("%s", prompt);

        if(fgets(buf, BUFFER_SIZE, stdin) == NULL) {
            printf("\nThank you for using my command shell.\n");
            return 0;
        }

        // printf("strlen(buf): %lu\n",strlen(buf));

        if (strlen(buf) >= BUFFER_SIZE - 1) {
            while(fgetc(stdin) != '\n');
        }

        // printf("Buffer: '%s'\tBuffer size: %lu\n", buf, sizeof(buf));
    
        token = strtok(buf, " \n");

        sh_argc = 0;

        while (token != NULL) {
            sh_argv[sh_argc++] = token;
            printf("Token: '%s'\n", token);
            token = strtok(NULL, " \n");
        }

        sh_argv[sh_argc++] = NULL;

        // printf("sh_argc: %d\n", sh_argc);

        if (sh_argv[0] == NULL) {
            perror("An empty line was entered. Please try again.");
            continue;
        } else if(!strcmp(sh_argv[0], "exit")) {
            printf("\nThank you for using my command shell.\n");
            return 0;
        } else {
            for (int i = 0; i < sh_argc; i++) {
                printf("sh_argv[%d]: '%s'\n", i, sh_argv[i]);
            }

            c_pid = fork();

            if ( c_pid < 0 ) {
                perror("Fork failed: exiting");
                return (-1);
            } else if ( c_pid == 0 ) {
                if(execvp(sh_argv[0], sh_argv) < 0) {
                    perror("Execvp failed: exiting");
                    return (-1);
                }
            } else {
                wait(&c_stat);
                printf("Child %d, exited with %d\n", c_pid, WEXITSTATUS(c_stat));
            }
        }
        
    }

    return 0;
}
