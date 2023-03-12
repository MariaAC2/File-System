/*Chirnogeanu Maria-Andreea - Grupa 315CB*/

#include "Files_and_Directories.h"

int main() {

    char** words = malloc(MAX_LINE * sizeof(char*));
    int i;
    for (i = 0; i < MAX_LINE; i++) {
        words[i] = malloc(MAX_WORD * sizeof(char));
    }
    int number_words = 0;

    char buffer[MAX_LINE];
    char *ptr = NULL;
    while (fgets(buffer, MAX_LINE, stdin)) {
        ptr = strtok(buffer, " \n");
        while (ptr != NULL) {
            snprintf(words[number_words++], MAX_LINE, "%s", ptr);
            ptr = strtok(NULL, " \n");
        }
    }

    DTree root = InitRoot();
    DTree curr_dir = root;
    for (int i = 0; i < number_words; i++) {
        if (strcmp(words[i], "touch") == 0) {
            curr_dir->files = CreateFileTree(curr_dir->files, curr_dir, words[i + 1]);
        } else if (strcmp(words[i], "mkdir") == 0) {
            curr_dir->subdirs = CreateDirTree(curr_dir->subdirs, curr_dir, words[i + 1]);
        } else if (strcmp(words[i], "ls") == 0) {
            PrintDir(curr_dir->subdirs);
            PrintFile(curr_dir->files);
            printf("\n");
        } else if (strcmp(words[i], "rm") == 0) {
            curr_dir->files = DeleteFile(curr_dir->files, words[i + 1]);
        } else if (strcmp(words[i], "rmdir") == 0) {
            curr_dir->subdirs = DeleteDir(curr_dir->subdirs, words[i + 1]);
        } else if (strcmp(words[i], "cd") == 0) {
            DTree temp;
            if (strcmp(words[i + 1], "..") == 0) {
                temp = curr_dir->parent;
                if (temp != NULL) {
                    curr_dir = temp;
                }
            } else {
                temp = FindDir(curr_dir->subdirs, words[i + 1]);
                if (temp == NULL) {
                    printf("Directory not found!\n");
                } else {
                    curr_dir = temp;
                }
            }
        } else if (strcmp(words[i], "pwd") == 0) {
            ShowPath(curr_dir);
            printf("\n");
        } else if (strcmp(words[i], "quit") == 0) {
            FreeRoot(root);
        }
    }
    for (i = 0; i < MAX_LINE; i++) {
        free(words[i]);
    }
    free(words);
    return 0;
}
