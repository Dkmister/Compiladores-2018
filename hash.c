#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
HASH* Table[HASH_SIZE];

void hashInit(void)
{
  int i ;

  for (i=0;i<HASH_SIZE;++i)
     Table[i] = 0 ;
}



int hashAddress(char *text){

  int address = 1;

  int i ;

  for(i=0;i<strlen(text);i++)
     address = ( address * text[i] ) % HASH_SIZE + 1 ;

  return address - 1;
}



HASH* hashInsert(int type, char *text)
{
  int address;

  HASH *newnode = 0;

  address = hashAddress(text);

  newnode = (HASH*) calloc(1,sizeof(HASH));

  newnode->text = calloc(strlen(text)+1,sizeof(char));

  strcpy(newnode->text,text);

  newnode->type = type;

  newnode->next = Table[address];

  Table[address] = newnode;

  return newnode;

}


HASH *hashFind(char *text){

  int address;

  HASH *node = 0;

  address = hashAddress(text);
  for(node = Table[address];node;node = node->next)
    if(!strcmp(text,node->text))
      return node;

  return 0;
}


void hashPrint(void)
{
  int i;

  HASH *node;

  for(i=0;i<HASH_SIZE;i++)
    for(node = Table[i];node;node = node->next)
      printf("Table [%d] has %s\n",i,node->text);
}
