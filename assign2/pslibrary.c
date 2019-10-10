#include <stdio.h>
#include <string.h>

#define READY  0
#define RUNNING  1
#define WAITING  2
#define DONE  3

static char stateChars[] = {'r','R','w',0};

/* 1) handle state changes:
         running process completes CPU burst
         running process has quantum expire
         IO complete
   2) do context switch if necessary
         both ready
         one ready and CPU free
   3) append appropriate characters to character arrays
         avoid putting in multiple string terminators
*/
/* assume s1 and s2 point to buffers with enough space to hold the result */
/* assume that the int parameters are strictly greater than 0 */

void part0(char *s1, char *s2) {
    char *p0string1 = "RRwwwwwRRRRRRRRR";
    char *p0string2 = "rrRRRRwwwwwwwwrrRRRRRRR";

    memcpy(s1, p0string1, 17);
    memcpy(s2, p0string2, 24);

    return;
}
void display(char *heading, char *s1, char *s2) {
   int length;
   int l1, l2;
   int r1, r2;
   int toR; 
   int x;
   
   printf("\n%s", heading);
   printf("%s\n", s1);
   printf("%s\n", s2);
   
   l1 = 0;
   l2 = 0;
   r1 = 0;
   r2 = 0;
   toR = 0;
   
   x = 0;
   while (s1[x] != '\0') {
      if (s1[x] == 'r')
         r1++;
      else if (s1[x] == 'R')
         toR++;
      l1++;
      
      x++;
   }
   
   x = 0;
   while (s2[x] != '\0') {
      if (s2[x] == 'r')
         r2++;
      else if (s2[x] == 'R')
         toR++;
      l2++;
      
      x++;
   }
   
   if (l1 > l2)
      length = l1;
   else
      length = l2;
   
   printf("%d\n", r1);
   printf("%d\n", r2);
   printf("%.1f\n", (double)(r1+r2)/2);
   printf("%.5f\n", (double)toR/length);
}

void insert(char *s, int p, char r) {
  int x;
  int len;
  if(s == NULL)
    printf("Passing NULL to strlen\n");
  len = strlen(s);
  
  for(x = len; x >= p; x--)
    s[x+1] = s[x];
  s[p] = r;
}

void fcfsa(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
  int x;
  int s1length, s2length;
  
  s1length = x1+y1+z1;
  s2length = x1+x2+y2+z2;
   
  x = 0;
  while(x != -1) {
    if(x1 != 0) {
      s1[x] = 'R';
      s2[x] = 'r';
      x1--;
      }
  else {
    if(y1 != 0) {
      s1[x] = 'w';
      y1--;
      }
    else if(z1 != 0) {
      s1[x] = 'R';
      z1--;
      }
    else if(z2 == 0)
      x = -2;
         
    if(x2 != 0) {
      s2[x] = 'R';
      x2--;
      }
    else if(y2 != 0) {
      s2[x] = 'w';
      y2--;
      }
    else if(z2 != 0) {
      s2[x] = 'R';
      z2--;
      }
    else if(z1 == 0)
      x = -2;
      }   
      x++;
   }
   
   s1[s1length] = '\0';
   s2[s2length] = '\0';
   
   x = 0;
   while(s1[x] != '\0' && s2[x] != '\0') {
         if(s1[x] == 'R' && s2[x] == 'R') {
            if(s2[x] == s2[x-1])
               insert(s1, x, 'r');
            else
               insert(s2, x, 'r');
         }
         x++;
     }
}

void fcfs(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
  int i;                                      /* next string position (time) */
  int state1 = READY;                               /* start with both ready */
  int state2 = READY;
  int cL1 = x1;                               /* P1 next CPU burst remaining */
  int cL2 = x2;                               /* P2 next CPU burst remaining */
  int iL1 = y1;               /* P1 next IO burst remaining, 0 if no more IO */
  int iL2 = y2;               /* P2 next IO burst remaining, 0 if no more IO */
  
  for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                
      if ((state1 == RUNNING) && (cL1== 0)) {
         if (iL1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];           
         }
         else
            state1 = WAITING;
      }  
      else if ((state2 == RUNNING) && (cL2 == 0) ) {
         if (iL2 == 0) {
            state2 = DONE;
            s2[i] = stateChars[state2];
         }
         else
            state2 = WAITING;
      }  
                                                    
      if ((state1 == WAITING) && (iL1 == 0)) {
         state1 = READY;
         cL1 = z1;
      }  
      if ((state2 == WAITING) && (iL2 == 0)) {
         state2 = READY;
         cL2 = z2;
      }  
                                    
      if ( (state1 == READY) && (state2 == READY)) {
         state1 = RUNNING;
      }  
                                     
      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
      }  
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
      }  

      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];
                                                        
      if (state1 == RUNNING)
         cL1--;
      if (state1 == WAITING)
         iL1--;
      if (state2 == RUNNING)
         cL2--;
      if (state2 == WAITING)
         iL2--;
   }                                               
}

void sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
  int i;                                      /* next string position (time) */
  int state1 = READY;                               /* start with both ready */
  int state2 = READY;
  int cL1 = x1;                               /* P1 next CPU burst remaining */
  int cL2 = x2;                               /* P2 next CPU burst remaining */
  int iL1 = y1;               /* P1 next IO burst remaining, 0 if no more IO */
  int iL2 = y2;               /* P2 next IO burst remaining, 0 if no more IO */       
   
   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                
      if ((state1 == RUNNING) && (cL1== 0)) {
         if (iL1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];            
         }
         else
            state1 = WAITING;
      }  
      else if ((state2 == RUNNING) && (cL2 == 0) ) {
         if (iL2 == 0) {
            state2 = DONE;
            s2[i] = stateChars[state2];
         }
         else
            state2 = WAITING;
      }  
                                                     
      if ((state1 == WAITING) && (iL1 == 0)) {
         state1 = READY;
         cL1 = z1;
      }  
      if ((state2 == WAITING) && (iL2 == 0)) {
         state2 = READY;
         cL2 = z2;
      }  
                                    
      if ( (state1 == READY) && (state2 == READY)) {
         if (cL1 <= cL2)
            state1 = RUNNING;
         else
            state2 = RUNNING;
      }  
                                    
      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
      }  
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
      }  

      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];

      if (state1 == RUNNING)
         cL1--;
      if (state1 == WAITING)
         iL1--;
      if (state2 == RUNNING)
         cL2--;
      if (state2 == WAITING)
         iL2--;
   }
}

void psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
  int i;                                      /* next string position (time) */
  int state1 = READY;                               /* start with both ready */
  int state2 = READY;
  int cL1 = x1;                               /* P1 next CPU burst remaining */
  int cL2 = x2;                               /* P2 next CPU burst remaining */
  int iL1 = y1;               /* P1 next IO burst remaining, 0 if no more IO */
  int iL2 = y2;               /* P2 next IO burst remaining, 0 if no more IO */
   
   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
 
      if ((state1 == RUNNING) && (cL1== 0)) {
         if (iL1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];
         }
         else
            state1 = WAITING;
      }  
      else if ((state2 == RUNNING) && (cL2 == 0) ) {
         if (iL2 == 0) {
            state2 = DONE;
            s2[i] = stateChars[state2];
         }
         else
            state2 = WAITING;
      }  

      if ((state1 == WAITING) && (iL1 == 0)) {
         state1 = READY;
         cL1 = z1;
      }  
      if ((state2 == WAITING) && (iL2 == 0)) {
         state2 = READY;
         cL2 = z2;
      }  

      if ( (state1 == READY) && (state2 == READY)) {
         if (cL1 <= cL2)
            state1 = RUNNING;
         else
            state2 = RUNNING;
      }

      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
      }  
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
      }

      else if ( (state1 == READY) && (cL1 < cL2)) {
         state2 = READY;
         state1 = RUNNING;
      }
      else if ( (state2 == READY) && (cL2 < cL1)) {
         state1 = READY;
         state2 = RUNNING;
      }

      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];

      if (state1 == RUNNING)
         cL1--;
      if (state1 == WAITING)
         iL1--;
      if (state2 == RUNNING)
         cL2--;
      if (state2 == WAITING)
         iL2--;
   }
}

void rr(char *s1, char *s2, int q, int x1, int y1, int z1, int x2, int y2, int z2) {
  int i;                                      /* next string position (time) */
  int state1 = READY;                               /* start with both ready */
  int state2 = READY;
  int cL1 = x1;                               /* P1 next CPU burst remaining */
  int cL2 = x2;                               /* P2 next CPU burst remaining */
  int iL1 = y1;               /* P1 next IO burst remaining, 0 if no more IO */
  int iL2 = y2;               /* P2 next IO burst remaining, 0 if no more IO */
  int qL;                                               /* quantum remaining */

   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {

      if ((state1 == RUNNING) && (cL1== 0)) {
         if (iL1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];
         }
         else
            state1 = WAITING;
      }  
      else if ((state2 == RUNNING) && (cL2 == 0) ) {
         if (iL2 == 0) {
            state2 = DONE;
            s2[i] = stateChars[state2];
         }
         else
            state2 = WAITING;
      }  

      if ((state1 == RUNNING) && (qL == 0) ) {
         state1 = READY;
         qL = q;
         if (state2 == READY)
            state2 = RUNNING;
      }  
      if ((state2 == RUNNING) && (qL == 0) ) {
         state2 = READY;
         qL = q;
         if (state1 == READY)
            state1 = RUNNING;
      }  

      if ((state1 == WAITING) && (iL1 == 0)) {
         state1 = READY;
         cL1 = z1;
      }  
      if ((state2 == WAITING) && (iL2 == 0)) {
         state2 = READY;
         cL2 = z2;
      }  

      if ( (state1 == READY) && (state2 == READY)) {
         state1 = RUNNING;
         qL = q;
      }  

      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
         qL = q;
      }  
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
         qL = q;
      }  

      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];

      qL--;
      if (state1 == RUNNING)
         cL1--;
      if (state1 == WAITING)
         iL1--;
      if (state2 == RUNNING)
         cL2--;
      if (state2 == WAITING)
         iL2--;
   }
}