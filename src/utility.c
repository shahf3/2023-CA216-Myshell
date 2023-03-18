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

#define MAX_COMMAND_LENGTH 1024
//extern char **eviron;

// function for implementing cd command
void cd(char* arg) {
    if (arg == NULL) {
        char* cwd = getcwd(NULL, 0);
        printf("%s\n", cwd);
        free(cwd);
    } else {
        if (chdir(arg) == -1) {
            printf("Error: Directory '%s' not found\n", arg);
        } else {
            char* cwd = getcwd(NULL, 0);
            setenv("PWD", cwd, 1);
            free(cwd);
        }
    }
}
// function for implementing clear command
void clearfunction() {
    system("clear");
}
// function for implementing dir command
void dir(char* arg) {
    if (arg == NULL) {
        arg = ".";
    }
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(arg)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent->d_name);
        }
        closedir(dir);
    } else {
        printf("Error: Directory '%s' not found\n", arg);
    }
}
// function for implementing environ command
void environfunction() {
    extern char **environ;
    char **envp = environ;
    while (*envp != NULL) {
        printf("%s\n", *envp);
        envp++;
    }
}
// function for implementing echo command
void echo(char *message) {
    printf("%s\n", message);
}
// function for implementing help command
void help() {
    char *filename = "README.md";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen() error");
    } else {
        char line[MAX_COMMAND_LENGTH];
        while (fgets(line, MAX_COMMAND_LENGTH, file) != NULL) {
            printf("%s", line);
        }
        fclose(file);
    }
}
// function for implementing pause command
void pause_shell() {
    printf("Press Enter to continue...");
    getchar();
}
// function for implementing quit command
void quit()
{
    exit(0);
}

