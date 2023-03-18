/*Authour = Faizan ali shah
student id = 21319001

DCU Academic Integrity Declaration: 

I understand that the University regards breaches of academic integrity and plagiarism as grave and serious.

I have read and understood the DCU Academic Integrity and Plagiarism Policy. 

I accept the  penalties that may be imposed should I engage in practice or practices that breach this policy.
I have identified and included the source of all facts, ideas, opinions and viewpoints of others in the assignment references. 

Direct quotations, paraphrasing, discussion of ideas from books, journal articles, internet sources, module text, or any other source whatsoever are acknowledged and the sources cited are identified in the assignment references.
I declare that this material, which I now submit for assessment, is entirely my own work and has not been taken from the work of others save and to the extent that such work has been cited and acknowledged within the text of my work.*/

#include "myshell.h"
//#include "utility.c"

// Global variables
char* shell_path;

int main(int argc, char *argv[])
{
    // Get the full path of the shell executable
    shell_path = realpath("./myshell", NULL);
    setenv("shell", shell_path, 1);

    // Main loop
    char* line;
    char* args[100];
    char* token;
    int status = 1;
    do
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s $", cwd);
        }
        else
        {
            perror("getcwd() error");
            return 1;
        }
        fflush(stdout);
        // Read the input line
        line = NULL;
        size_t bufsize = 0;
        getline(&line, &bufsize, stdin);
        // Token the input line
        int i = 0;
        //int background = 0;
        char *token = strtok(line, " \n");
        while (token != NULL) 
        {
            args[i] = token;
            i++;
            token = strtok(NULL, " \n");
        }
        //args[i] = NULL;
        int background = 0;
        for (i=0; args[i] != NULL; i++)
        {
            if (strcmp(args[i], "&") == 0)
            {
                args[i] = NULL;
                background = 1;
                break;
            }
        }
        //checking for o redirection requested
        char *output_file = NULL;
        int output_fd = -1;
        for (int i = 0; args[i] != NULL; i++) 
        {
            if (strcmp(args[i], ">") == 0) 
            {
                output_file = args[i+1];
                output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                args[i] = NULL;
                break;
            } 
            else if (strcmp(args[i], ">>") == 0) 
            {
                output_file = args[i+1];
                output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                args[i] = NULL;
                break;
            }
        }

        // Check if input redirection is requested
        char *input_file = NULL;
        //int *input_fd = NULL;
        int input_fd = -1;
        for (int i = 0; args[i] != NULL; i++) 
        {
            if (strcmp(args[i], "<") == 0) {
                input_file = args[i+1];
                int input_fd = open(input_file, O_RDONLY);
                args[i] = NULL;
                break;
            }
        }
        // Check if the command is an internal command
        if(strcmp(args[0], "cd") == 0) 
        {
            cd(args[1]);
        } 
        else if(strcmp(args[0], "clr") == 0) 
        {
            clearfunction();
        }
        else if(strcmp(args[0], "dir") == 0) 
        {
            dir(args[1]);
        }
        else if(strcmp(args[0], "environ") == 0) 
        {
            environfunction();
        }
        else if(strcmp(args[0], "echo") == 0) 
        {
            for(int i = 1; args[i] != NULL; i++) 
            {
                printf("%s ", args[i]);
            }
            printf("\n");
        }

        else if(strcmp(args[0], "help") == 0) 
        {
            help();
        } 
        else if(strcmp(args[0], "pause") == 0) 
        {
            pause_shell();
        } 
        else if(strcmp(args[0], "quit") == 0) 
        {
            quit();
            status = 0;
        }
        else // Execute external command
        {
            pid_t pid = fork();
            if (pid == 0) {
                // Child process
                execvp(args[0], args);
                // If execvp() returns, there was an error
                printf("Unknown command: %s\n", args[0]);
                exit(1);
            } else if (pid < 0) {
            // Error forking
            printf("Error forking\n");
            } else {
                // Parent process
                wait(NULL);
            }
        }
        free(line);
    } 
    while(status);
    free(shell_path);
    return 0;
}
