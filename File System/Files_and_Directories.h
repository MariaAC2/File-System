/*Chirnogeanu Maria Andreea - Grupa 315CB*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE 200
#define MAX_WORD 51

typedef struct Root Root;
typedef struct FolderNode FolderNode;
typedef struct FileNode FileNode;

struct Root {
    FolderNode* root;
};

struct FileNode {
    FolderNode *parent;
    char *name;
    FileNode *left, *right;
};

struct FolderNode {
    FolderNode *parent;
    char *name;
    FileNode *files;
    FolderNode *subdirs;
    FolderNode *left, *right;
};

Root createRoot();
FolderNode *createFolderNode(FolderNode *, char *);
FolderNode *createFolderTree(FolderNode *, char *);
FileNode *createFileNode(FolderNode *, char *);
void PrintFolder(FolderNode *);