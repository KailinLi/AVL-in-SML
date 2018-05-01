#include "avl.h"

int height(AVLNodePtr T) {
    return T ? T->height : -1;
}
int maxH(int lhs, int rhs) {
    if (lhs > rhs) return lhs;
    else return rhs;
}
AVLNodePtr rotateLeft(AVLNodePtr rt) {
    AVLNodePtr newRoot = rt->left;
    rt->left = newRoot->right;
    newRoot->right = rt;
    rt->height = maxH(height(rt->left), height(rt->right)) + 1;
    newRoot->height = maxH(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}
AVLNodePtr rotateRight(AVLNodePtr rt) {
    AVLNodePtr newRoot = rt->right;
    rt->right = newRoot->left;
    newRoot->left = rt;
    rt->height = maxH(height(rt->left), height(rt->right)) + 1;
    newRoot->height = maxH(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}
AVLNodePtr doubleRotateLeft(AVLNodePtr rt) {
    rt->left = rotateRight(rt->left);
    return rotateLeft(rt);
}
AVLNodePtr doubleRotateRight(AVLNodePtr rt) {
    rt->right = rotateLeft(rt->right);
    return rotateRight(rt);
}
AVLNodePtr balance(AVLNodePtr rt) {
    if (!rt) return NULL;
    if (height(rt->left) - height(rt->right) > 1) {
        if (height(rt->left->left) >= height(rt->left->right))
            rt = rotateLeft(rt);
        else
            rt = doubleRotateLeft(rt);
    }
    else if (height(rt->right) - height(rt->left) > 1) {
        if (height(rt->right->right) >= height(rt->right->left))
            rt = rotateRight(rt);
        else
            rt = doubleRotateRight(rt);
    }
    rt->height = maxH(height(rt->left), height(rt->right)) + 1;
    return rt;
}
AVLNodePtr insertTreeNode(AVLNodePtr rt, long data) {
    if (!rt) {
        rt = (AVLNodePtr)malloc(sizeof(struct avlNode));
        // printf("new avl tree node\n");
        rt->data = data;
        rt->left = NULL;
        rt->right = NULL;
        rt->height = 0;
    }
    if (rt->data > data) {
        rt->left = insertTreeNode(rt->left, data);
    }
    else if (rt->data < data) {
        rt->right = insertTreeNode(rt->right, data);
    }
    return balance(rt);
}
AVLNodePtr insertTree(AVL * T, long data) {
    if (!T) return NULL;
    T->root = insertTreeNode(T->root, data);
    return T->root;
}
AVLNodePtr searchTreeNode(AVLNodePtr rt, long data) {
    if (!rt) return NULL;
    if (rt->data == data) return rt;
    else if (rt->data > data) return searchTreeNode(rt->left, data);
    else return searchTreeNode(rt->right, data);
}
AVLNodePtr searchTree(AVL * T, long data) {
    if (!T) return NULL;
    return searchTreeNode(T->root, data);
}