#include <stdlib.h>
#include "pagetable.h"

int** inTable(int*** table, int sz) {
      *table = (int **)malloc(sz * sizeof(int*));
      
      int x;
      for (x = 0; x < sz; x++) {
         (*table)[x] = (int *)malloc(2 * sizeof(int));
         (*table)[x][0] = NONE;
         (*table)[x][1] = i;
      }
      
      return *table;
}

int** ptPage(int*** table, int vp, int pf) {
      (*table)[vp][0] = pf;
      (*table)[vp][1] = virt;
      
      return *table;
}

void frTable(int*** table, int sz) {
   int x;
   for (x = 0; x < sz; x++)
      free((*table)[x]);
   
   free(*table);
}