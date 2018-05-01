#include <iostream>
#include <ctime>
#include <stdlib.h>
int main () {
    int i_cnt = 20000;
    int r_cnt = 10000;
    FILE * smlF = fopen("input.sml", "w");
    FILE * ccF = fopen("input.txt", "w");
    fprintf(ccF, "%d", i_cnt);
    fprintf(smlF, "val input = [");
    for (int i = 0; i < i_cnt; ++i) {
        fprintf(ccF, ",%d", i);
        if (!i) fprintf(smlF, "%d", i);
        else fprintf(smlF, ",%d", i);
    }
    fprintf(ccF, "\n%d", r_cnt);
    fprintf(smlF, "];\nval searchData = [");
    for (int i = 0; i < r_cnt; ++i) {
        int tmp = rand() % (i_cnt << 1);
        fprintf(ccF, ",%d", tmp);
        if (!i) fprintf(smlF, "%d", tmp);
        else fprintf(smlF, ",%d", tmp);
    }
    fprintf(ccF, "\n");
    fprintf(smlF, "];\n");
    fclose(ccF);
    fclose(smlF);
}