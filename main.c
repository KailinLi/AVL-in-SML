#include "avl.h"
int main () {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    AVL data = {.root = NULL};
    int cnt, i;
    scanf("%d", &cnt);
    while (cnt--) {
        scanf(",%d", &i);
        insertTree(&data, i);
    }
    scanf("%d", &cnt);
    while (cnt--) {
        scanf(",%d", &i);
        if (searchTree(&data, i)) printf("1\n");
        else printf("0\n");
    }
}