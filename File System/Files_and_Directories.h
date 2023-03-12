/*Chirnogeanu Maria Andreea - Grupa 315CB*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE 200
#define MAX_WORD 51

typedef struct file { // file struct
    char *name;
    struct directory *parent;
    struct file *left, *right;
} FNode, *FTree;

typedef struct directory { // directory struct
    char *name;
    struct directory* parent;
    struct file* files;
    struct directory* subdirs;
    struct directory *left, *right;
} DNode, *DTree;


DTree InitRoot();
DTree DLeaf(DTree curr_dir, char* name);
FTree FLeaf(DTree curr_dir, char* name);
FTree CreateFileTree(FTree file, DTree curr_dir, char *name);
DTree CreateDirTree(DTree dir, DTree curr_dir, char *name);
void PrintFile(FTree);
void PrintDir(DTree);
int SearchFiles(FTree, char*);
int SearchDirs(DTree, char*);
FTree MinFile(FTree file);
FTree DeleteFile(FTree file, char *name);
DTree MinDir(DTree dir);
DTree DeleteDir(DTree dir, char *name);
void FreeDir(DTree dir);
void FreeFile(FTree file);
void FreeRoot(DTree root);
DTree FindDir(DTree file, char* elem);
void GoBack(DTree curr_dir);
void FindDirr(DTree dir);
int SearchDirsss(DTree file, char* elem);
void ShowPath(DTree curr_dir);
