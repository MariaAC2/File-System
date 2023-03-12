/*Chirnogeanu Maria Andreea - Grupa 315CB*/

#include "Files_and_Directories.h"

Root createRoot(char *name) {
    Root root;
    root.root = createFolderNode();
    return root;
}

FolderNode *createFolderNode(FolderNode *currentFolder, char *name) {
    FolderNode *folderNode = (FolderNode *)malloc(sizeof(FolderNode));

    if (folderNode == NULL) {
        free(folderNode);
        return NULL;
    }

    folderNode->parent = currentFolder;
    folderNode->name = name;
    folderNode->files = NULL;
    folderNode->subdirs = NULL;
    folderNode->left = NULL;
    folderNode->right = NULL;

    return folderNode;
}

FolderNode *createFolderTree(FolderNode *currentFolder, char *name) {
    FolderNode *folderNode = currentFolder->subdirs;

    if (folderNode == NULL) {
        return createFolderNode(currentFolder->subdirs, name);
    }

    if (strcmp(name, folderNode->name) < 0) {
        return createFolderTree(folderNode->left, name);
    } else if (strcmp(name, folderNode->name) > 0) {
        return createFolderTree(folderNode->right, name);
    } else {
        printf("Directory %s already exists!\n", name);
    }
    return folderNode;
}

// void mkdir(FolderNode *currentFolder, char *name) {

// }

FileNode *createFileNode(FolderNode *currentFolder, char *name) {
    FileNode *fileNode = (FileNode *)malloc(sizeof(FileNode));

    if (fileNode == NULL) {
        free(fileNode);
        return NULL;
    }

    fileNode->parent = currentFolder;
    fileNode->name = name;
    fileNode->left = NULL;
    fileNode->right = NULL;

    return fileNode;
}

void PrintFolder(FolderNode *currentFolder) {
    if (currentFolder->subdirs == NULL) {
        return;
    }
    PrintDir(currentFolder->subdirs->left);
    printf("%s ", currentFolder->subdirs->name);
    PrintDir(currentFolder->subdirs->right);
}