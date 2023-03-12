# File-System
### Chirnogeanu Maria-Andreea, Grupa 315CB

For this homework we have to implement Linux commands on binary search trees.\
In the main file, I implemented a parser which executes each command corresponding with the command names.\
At the start of the parser, I initiated the root directory and a variable called curr_dir, that holds the information for the current directory.

I use two structures: FTree and DTree. These are the names for the binary search trees for the files and for the directories.\
Each one is created similarly. For each one, I created a function that initiates a leaf for the BST that we need, then I used a recursive function that adds the file or the directory lexicographically.\
The functions for the leaf all initiate the parent of the file and the directory as the current directory. In the main function, I added the files incurr_dir->files, meaning that there is a direct link between the current directory and its files.\
The same process is applied at curr_dir->subdirs, which means that a directory has files and subdirectories and its files and subdirectories have as a parent the current directory.

For **touch**, I created an additional function that searches in the directory tree to check if a directory with that name already exists. If it exists, it will not be added into the file tree. Then, I used a recursive function to add in order the files into the file tree.

For **mkdir**, I applied a similar process with touch. but I implemented a function that searches in the file tree.

For **ls**, I printed the content of the files and subdirs form the current directory.

For **rm**, I implemented a recursive function that deletes a file from the binary search tree. The process of deletion is the following:
 * if the file with the given name is not found, we print a message and thenwe return the tree.
 * if the file with the given name is found, we take three different cases: if the node is a leaf(*doesn't have any children*), if it has *one child* and
if it has *both children*.

In the case of *no children*, we free the memory used for the node and we give it a NULL value, to make sure that the memory is properly freed.\
In the case of *one child*, I decided if left child or the right child exists, then I put the left or the right value into a temporary node and frees the memory from the node that needs to be deleted.\
If the node has *two children*, I used an additional function, that finds the file with the minimum value in the file tree. I used this function for finding the minimum value from the subtree from the right side. I stocked the result into a temporary node, I give its name to the node, then I continue the search on the right side of the tree. Finally, I returned the modified tree.

For **rmdir** I applied the same process, but for the subdirectory tree.

For **cd [name of dir]**, I used a functions that returns the node from a directory tree with the name of the directory that needs going into. I use this function to search into the subdirectories for the current directory. The result of the search is stocked into a temporary node and I verified if the node exists or not. The function returns NULL if the directory is not in the tree.\
In this case, it is printed a message. If not, the current directory becomes the temp node, which means that the current directory is moved to the directory with the name given. For **cd ..**, I also used a temporary variable which stores the parent of the current directory. if it is not null, the current directory becomes the temp, which means that the current directory is moved back.

For **pwd**, I used a recursive function that prints where the directory is located and its path. I set the beginning condition and then I went back to the parent. Finally, I print the current directory's name.
