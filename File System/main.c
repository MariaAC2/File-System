/*Chirnogeanu Maria-Andreea - Grupa 315CB*/

#include "Files_and_Directories.h"

#define LINE_MAX_LEN 1000
#define TOKEN_MAX_LEN 300

#define TOUCH "touch"
#define MKDIR "mkdir"
#define LS "ls"
#define RM "rm"
#define RMDIR "rmdir"
#define CD "cd"
#define PWD "pwd"
#define FIND "find"

void process_command(
    char commands[3][TOKEN_MAX_LEN],
    int token_idx) {
    
    if (!strcmp(commands[0], TOUCH)) {
        printf("touch");
    } else if (!strcmp(commands[0], MKDIR)) {
        printf("mkdir");
    } else if (!strcmp(commands[0], LS)) {
        printf("ls");
    }    if (!strcmp(commands[0], RM)) {
        printf("rm");
    }    if (!strcmp(commands[0], RMDIR)) {
        printf("rmdir");
    }    if (!strcmp(commands[0], CD)) {
        printf("cd");
    }    if (!strcmp(commands[0], PWD)) {
        printf("pwd");
    }    if (!strcmp(commands[0], FIND)) {
        printf("find");
    }
    printf("\n");
}

int main() {
    char line[LINE_MAX_LEN];
    char cmd[3][TOKEN_MAX_LEN];
    char *token;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        line[strlen(line)-1] = 0;

        cmd[0][0] = cmd[1][0] = cmd[2][0] = 0;

        int token_idx = 0;
        token = strtok(line, " ");
        while (token) {
            strcpy(cmd[token_idx], token);
            ++token_idx;

            token = strtok(NULL, " ");
            process_command(cmd, token_idx);
        }
    }

    return 0;
}
