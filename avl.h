#ifndef AVL_H
#define AVL_H
#include <stdio.h>
#include <stdlib.h>

typedef struct avlNode {
    int height;
    long data;
    struct avlNode *left;
    struct avlNode *right;
} *AVLNodePtr;

typedef struct avl {
    AVLNodePtr root;
} AVL;

AVLNodePtr insertTree(AVL * T, long data);
AVLNodePtr searchTree(AVL * T, long data);

#endif // AVL_H