#ifndef __hash__
#define __hash__

#define HASH_SIZE 997

#define LT_INT		1
#define LT_FLOAT	2
#define LT_CHAR		3
#define LT_STRING	4
#define LT_IDENT	5
#define VAR_S		6
#define VAR_V		7
#define VAR_F		8

typedef struct hash_node{
  int type;
  int data_type;
  char* text;
  struct hash_node* next;
}HASH;

void hashInit(void);
int hashAddress(char* text);
HASH* hashInsert(int type, char* text);
HASH* hashFind(char* text);
void hashPrint(void);


#endif
