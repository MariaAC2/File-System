/*Chirnogeanu Maria Andreea - Grupa 315CB*/

#include "Files_and_Directories.h"
 
DTree InitRoot() {
    DTree root = (DTree)malloc(sizeof(DNode));
    if (root == NULL) {
        return NULL;
    }
    root->name = "root";
    root->parent = NULL;
    root->files = NULL;
    root->subdirs = NULL;
    root->left = NULL;
    root->right = NULL;

    return root;
}

DTree DLeaf(DTree curr_dir, char* name) {
    DTree dir = (DTree)malloc(sizeof(DNode));
    if (dir == NULL) {
        return NULL;
    }
    dir->name = (char *)malloc(51 * sizeof(char));
    if (dir->name == NULL) {
        free(dir);
        return NULL;
    }
    strcpy(dir->name, name);
    dir->parent = curr_dir;
    dir->files = NULL;
    dir->subdirs = NULL;
    dir->left = NULL;
    dir->right = NULL;

    return dir;
}

FTree FLeaf(DTree curr_dir, char* name) {
    FTree file = (FTree)malloc(sizeof(FNode));
    if (file == NULL) {
        return NULL;
    }
    file->name = (char *)malloc(51 * sizeof(char));
    if (file->name == NULL) {
        free(file);
        return NULL;
    }
    strcpy(file->name, name);

    file->parent = curr_dir;
    file->left = NULL;
    file->right = NULL;

    return file;
}

FTree CreateFileTree(FTree file, DTree curr_dir, char *name) {
    if (SearchDirs(curr_dir->subdirs, name) == 1) {
        printf("Directory %s already exists!\n", name);
        return file;
    }
    if (file == NULL) {
        return FLeaf(curr_dir, name);
    } else if (strcmp(name, file->name) < 0) {
        file->left = CreateFileTree(file->left, curr_dir, name);
    } else if (strcmp(name, file->name) > 0) {
        file->right = CreateFileTree(file->right, curr_dir, name);
    } else {
        printf("File %s already exists!\n", name);
    }
    return file;
}

DTree CreateDirTree(DTree dir, DTree curr_dir, char *name) {
    if (SearchFiles(curr_dir->files, name) == 1) {
        printf("File %s already exists!\n", name);
        return dir;
    }
    if (dir == NULL) {
        return DLeaf(curr_dir, name);
    } else if (strcmp(name, dir->name) < 0) {
        dir->left = CreateDirTree(dir->left, curr_dir, name);
    } else if (strcmp(name, dir->name) > 0) {
        dir->right = CreateDirTree(dir->right, curr_dir, name);
    } else {
        printf("Directory %s already exists!\n", name);
    }
    return dir;
}

int SearchFiles(FTree file, char* elem) {
    if (file == NULL) {
        return 0;
    }
    if (strcmp(elem, file->name) == 0) {
        return 1;
    } else if (strcmp(elem, file->name) < 0) {
        SearchFiles(file->left, elem);
    } else {
        SearchFiles(file->right, elem);
    }
}

int SearchDirs(DTree file, char* elem) {
    if (file == NULL) {
        return 0;
    }
    if (strcmp(elem, file->name) < 0) {
        return SearchDirs(file->left, elem);
    } else if (strcmp(elem, file->name) > 0) {
        return SearchDirs(file->right, elem);
    } else {
        return 1;
    }
}

DTree FindDir(DTree file, char* elem) {
    if (file == NULL) {
        return NULL;
    }
    if (strcmp(elem, file->name) == 0) {
        return file;
    } else if (strcmp(elem, file->name) < 0) {
        FindDir(file->left, elem);
    } else {
        FindDir(file->right, elem);
    }
}

void ShowPath(DTree curr_dir) {
    if (curr_dir == NULL) {
        return;
    }
    ShowPath(curr_dir->parent);
    printf("/%s", curr_dir->name);
}

FTree MinFile(FTree file) {
    FTree current = file;
    while (current != NULL && current->left != NULL) {
        current = current->left;
    }
    return current;
}

FTree DeleteFile(FTree file, char *name) {
    if (file == NULL) {
        printf("File %s doesn't exist!\n", name);
        return file;
    }
    if (strcmp(name, file->name) < 0) {
        file->left = DeleteFile(file->left, name);
    } else if (strcmp(name, file->name) > 0) {
        file->right = DeleteFile(file->right, name);
    } else {
        if (file->left == NULL && file->right == NULL) {
            if (file->name != NULL) {
                free(file->name);
            }
            free(file);
            return NULL;
        } else if (file->left == NULL) {
            FTree temp = file->right;
            if (file->name != NULL) {
                free(file->name);
            }
            free(file);
            return temp;
        } else if (file->right == NULL) {
            FTree temp = file->left;
            if (file->name != NULL) {
                free(file->name);
            }
            free(file);
            return temp;
        }
        FTree temp = MinFile(file->right);
        strncpy(file->name, temp->name, strlen(temp->name) + 1);
        file->right = DeleteFile(file->right, temp->name);

    }
    return file;
}

DTree MinDir(DTree dir) {
    DTree current = dir;
    while (current != NULL && current->left != NULL) {
        current = current->left;
    }
    return current;
}

DTree DeleteDir(DTree dir, char *name) {
    if (dir == NULL) {
        printf("Directory %s doesn't exist!\n", name);
        return dir;
    }
    if (strcmp(name, dir->name) < 0) {
        dir->left = DeleteDir(dir->left, name);
    } else if (strcmp(name, dir->name) > 0) {
        dir->right = DeleteDir(dir->right, name);
    } else {
        if (dir->left == NULL && dir->right == NULL) {
            if (dir->name != NULL) {
                free(dir->name);
                dir->name = NULL;
            }
            if (dir != NULL) {
                free(dir);
                dir = NULL;
            }
        } else if (dir->left == NULL) {
            DTree temp = dir;
            dir = dir->right;
            if (temp->name != NULL) {
                free(temp->name);
                temp->name = NULL;
            }
            if (temp != NULL) {
                free(temp);
                temp = NULL;
            }
        } else if (dir->right == NULL) {
            DTree temp = dir;
            dir = dir->left;
            if (temp->name != NULL) {
                free(temp->name);
                temp->name = NULL;
            }
            if (temp != NULL) {
                free(temp);
                temp = NULL;
            }
        } else {
            DTree temp = MinDir(dir->right);
            strncpy(dir->name, temp->name, strlen(temp->name) + 1);
            dir->right = DeleteDir(dir->right, temp->name);
        }
    }
    return dir;
}

void PrintFile(FTree file) {
    if (file == NULL) {
        return;
    }
    PrintFile(file->left);
    printf("%s ", file->name);
    PrintFile(file->right);
}

void PrintDir(DTree dir) {
    if (dir == NULL) {
        return;
    }
    PrintDir(dir->left);
    printf("%s ", dir->name);
    PrintDir(dir->right);
}

void FreeFile(FTree file) {
    if (file == NULL) {
        return;
    }
    FreeFile(file->left);
    FreeFile(file->right);
    free(file->name);
    free(file);
}

void FreeFTree(FTree *file) {
    if ((*file) == NULL) {
        return;
    }
    FreeFile(*file);
    *file = NULL;
}

void FreeDTree(DTree *dir) {
    if ((*dir) == NULL) {
        return;
    }
    FreeDir(*dir);
    *dir = NULL;
}

void FreeDir(DTree dir) {
    if (dir == NULL) {
        return;
    }
    FreeDir(dir->left);
    FreeDir(dir->right);
    free(dir->name);
    free(dir);
}

void FreeRoot(DTree root) {
    if (root == NULL) {
        return;
    }
    FreeDTree(&root->subdirs);
    FreeFTree(&root->files);
    free(root);
}