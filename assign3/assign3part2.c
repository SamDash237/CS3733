#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "pagetable.h"
#include "phypages.h"

struct node {
   int pgnum;
   struct node* up;
   struct node* down;
};
typedef struct node node;

void push(int pg, node** top);
int pop(node** top);
int seek(node** top);
int search(int pg, node** top);
int cut(int pg, node** top);
void trstack(node** top);
void frstack(node** top);

int main(int argc, char *argv[]) {
   int **addrt, flts, fdi, fdo, f, *frms, lru, nodes;
   unsigned long ofst, pg, physar, virtar;
   node* top;
   
   if (argc != 2) {
      printf("Usage: %s <SEQUENCE FILE>\n", argv[0]);
      exit(1);
   }
   
   if ((fdi = open(argv[1], O_RDONLY)) == -1) {
      perror("Main failed to open sequence file");
      exit(2);
   }
   
   if ((fdo = open("output-part2", O_WRONLY | O_CREAT, 0600)) == -1) {
      perror("Main failed to open output file");
      close(fdi);
      exit(2);
   }
   
   addrt = inTable(&addrt, 32);
   frms = inFrames(&frms, 8);
   flts = 0;
   nodes = 0;
   top = NULL;
   
   while (read(fdi, &virtar, sizeof(virtar)) > 0) {
      printf("Virtual address: %#lx\n", virtar);
      
      ofst = virtar & 0x7F;
      printf("Offset: %#lx\n", ofst);
      
      pg = virtar >> 7;
      
      if (nodes < 7 && search(pg, &top) == -1) {
         flts++;
         push(pg, &top);
         nodes++;
      }
      else if (nodes >= 7 && search(pg, &top) > -1) {
         cut(pg, &top);
         push(pg, &top);
      }
      else if (search(pg, &top) == -1) {
         lru = cut(-1, &top);
         push(pg, &top);
      }
      
      printf("Virtual page: %#lx\n", pg);
      
      if (addrt[pg][1] == virt)
         f = addrt[pg][0];
      else {
         f = fdOpen(&frms, 8);
         if (f == -1) {
            printf("Page fault\n");
            flts++;
            f = addrt[lru][0];
            addrt[lru][0] = -1;
            addrt[lru][1] = i;
         }
      }
      
      addrt = ptPage(&addrt, pg, f);
      frms = rvMap(&frms, f, pg);
      pg = addrt[pg][0];
      printf("Physical frame: %#lx\n", pg);
      physar = pg << 7;
      printf("Shifted frame: %#lx\n", physar);
      physar += ofst;
      printf("Physical address: %#lx\n", physar);
      trstack(&top);
      
      if (write(fdo, &physar, sizeof(physar)) == -1) {
         perror("Main failed to write to output file");
         frTable(&addrt, 32);
         free(frms);
         frstack(&top);
         close(fdi);
         close(fdo);
         exit(3);
      }
   }
   
   printf("Total page faults: %d\n", flts);
   
   frTable(&addrt, 32);
   free(frms);
   frstack(&top);
   close(fdi);
   close(fdo);
   
   return 0;
}

void push(int pg, node** top) {
   if (*top == NULL) {
      *top = malloc(sizeof(node));
      (*top) -> pgnum = pg;
      (*top) -> up = NULL;
      (*top) -> down = NULL;
      
      return;
   }
   
   node* lower = *top;
   *top = malloc(sizeof(node));
   (*top) -> pgnum = pg;
   (*top) -> up = NULL;
   (*top) -> down = lower;
   lower -> up = *top;
}

int pop(node** top) {
   if (*top == NULL)
      return -1;
   
   int num = (*top) -> pgnum;
   
   if ((*top) -> down == NULL) {
      free(*top);
      return num;
   }
   
   node* temp = *top;
   *top = (*top) -> down;
   (*top) -> up = NULL;
   free(temp);
   
   return num;
}

int seek(node** top) {
      return (*top) -> pgnum;
}

int search(int pg, node** top) {
   node* current = *top;
   int ret = -1;
   
   if (*top == NULL)
      return ret;
   
   do {
      if (current -> pgnum == pg) {
         ret = current -> pgnum;
         break;
      }
      
      current = current -> down;
   } while (current != NULL);
   
   return ret;
}

int cut(int pg, node** top) {
   node* current = *top;
   int val;
   
   while (current != NULL) {
      if (pg == -1 && current -> down == NULL) {
         val = current -> pgnum;
         current -> up -> down = NULL;
         free(current);
         return val;
      }
      if (current -> pgnum == pg) {
         val = current -> pgnum;
         if (current == *top) {
            pop(top);
            return val;
         }
         if (current -> down != NULL)
            current -> down -> up = current -> up;
         if (current -> up != NULL)
            current -> up -> down = current -> down;
         
         free(current);
         break;
      }
      
      current = current -> down;
   }
   
   return val;
}

void trstack(node** top) {
   node* current = *top;
   
   printf("[ ");
   
   while (current != NULL) {
      printf("%d ", current -> pgnum);
      current = current -> down;
   }
   
   printf("]\n");
}

void frstack(node** top) {
      node* next;
      
      while (*top != NULL) {
         next = (*top) -> down;
         pop(top);
         *top = next;
      }
}