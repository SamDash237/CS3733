#define virt 1
#define i 0
#define NONE -1

int** inTable(int*** table, int sz);
int** ptPage(int*** table, int vp, int pf);
void frTable(int*** table, int sz);
