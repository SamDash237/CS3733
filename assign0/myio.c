#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "myio.h"

char *ReadInput(int fd) {
   char buf[BUFSIZ];
   int i;
   char *input;
   int r, rt, x;

   i = 1;
   r = 0;
   rt = 1;

   input = calloc(BUFSIZ, sizeof(char));

   while (rt > 0) {
      rt = read(fd, &buf, BUFSIZ);
    
      for (x = 0; x < BUFSIZ; x++) {
         if (buf[x] == '\n' || buf[x] == EOF) {
            rt = -1;
            break;
         }
         input[x*i] = buf[x];
         r++;
      }
    
      i++;
    
      if (rt != -1)
         input = realloc(input, BUFSIZ*i);
   }

   if (r == 0)
      return NULL;

   input[r] = '\0';
   input = realloc(input, r+1);

   return(input);
}

int ReadInteger() {
   char *input;
   int g, n, x;
   g = 0;

   do {
      g = 0;
    
      printf("Input an integer\n");
      input = ReadInput(STDIN_FILENO);
      for (x = 0; x < INT_MAX; x++) {
         if (x == 0 && input[x] == '-')
            continue;
         if (input[x] == 0)
            break;
         else if (input[x] > '9' || input[x] < '0') {
            g = 1;
            printf("Improper input\n");
            break;
         }
     }
   } while (g == 1);

   n = atoi(input);
   free(input);

   return n;
}

double ReadDouble(void) {
   int d, e;
   char *input;
   int g;
   double n;
   int x;

   do {
      g = 0;
      d = 0;
      e = 0;
    
      printf("Input a double\n");
      input = ReadInput(STDIN_FILENO);
      for (x = 0; x < INT_MAX; x++) {
         if (x == 0 && input[x] == '-')
            continue;
         if (input[x] == 0)
            break;
         else if (input[x] == '.' && d == 0)
            d = 1;
         else if (x != 0 && (input[x] == 'e' || input[x] == 'E') && e == 0) {
            d = 1;
            e = 1;
         }
         else if (input[x] > '9' || input[x] < '0') {
            g = 1;
            printf("Improper input\n");
            break;
         }
      }
   } while (g == 1);

   n = strtod(input, NULL);
   free(input);

   return n;
}

char *ReadLine(void) {
   printf("Input a line\n");
   return(ReadInput(STDIN_FILENO));
}

char *ReadLineFile(FILE *infile) {
  char *i = calloc(BUFSIZ, sizeof(char));
  int x;
  if(fgets(i, BUFSIZ, infile)) {
    for(x = 0; x < BUFSIZ && i[x] != '\0'; x++)
      if(i[x] == '\n')
        break;
      i[x] = '\0';
      return i;
    }
      else {
        return NULL;
    }
}