#ifndef __hash__
#define __hash__

#define HASH_SIZE 997
/*
Header da Tabela Hash, autoria de Marcelo Johann 2018
*/

typedef struct hash_node{
  int type;
  char* text;
  struct hash_node* next;
}HASH;

void hashInit(void);
int hashAddress(char* text);
HASH* hashInsert(int type, char* text);
HASH * hashFind(char* text);
void hashPrint(void);


#endif
