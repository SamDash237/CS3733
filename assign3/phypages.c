#include <stdlib.h>
#include "phypages.h"

int* inFrames(int** frms, int sz) {
      *frms = (int *)malloc(sz * sizeof(int));
      
      (*frms)[0] = OS;
      
      int x;
      for (x = 1; x < sz; x++) {
         (*frms)[x] = NONE;
      }
      
      return *frms;
}

int fdOpen(int** frms, int sz) {
      int f = -1;
      
      int x;
      for (x = 1; x < sz; x++) {
         if ((*frms)[x] == -1) {
            f = x;
            break;
         }
      }
      
      return f;
}

int* rvMap(int** frms, int frame, int pg) {
      (*frms)[frame] = pg;
      
      return *frms;
}