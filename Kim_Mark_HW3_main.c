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

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE  123

int main(int argc, char *argv[]) {
    char buf[BUFFER_SIZE];
    int sh_argc;
    char *sh_argv[BUFFER_SIZE];
    char *token;
    char prompt[1] = ">";

    if(argc > 1) {
        printf("Argument: %s\t%lu\n", argv[1], strlen(argv[1]));
    };
    
    while(1) {
        printf("%s", prompt);
        if(fgets(buf, BUFFER_SIZE, stdin) = NULL) {
            break;
        }
        buf[strlen(buf) - 1] = '\0';
        token = strtok(buf, " ");
        sh_argc = 0;
        while (token != NULL) {
            sh_argv[sh_argc++] = token;
            token = strtok(NULL, " ");
        }
        if(strcmp(sh_argv[0], "exit")) {
            printf("\nThank you for using my command shell.\n");
            return 0;
        }

        for (int i = 0; i < sh_argc; i++) {
            printf("%s", sh_argv[i]);
        }

    }
}