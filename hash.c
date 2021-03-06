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

int hashAddress(char* text){

  int address = 1;

  int i ;

  for(i=0;i<strlen(text);i++)
     address = ( address * text[i] ) % HASH_SIZE + 1 ;

  return address - 1;
}

HASH* hashInsert(int type, char* text)
{

  if(hashFind(text) != 0)
    return hashFind(text);

  int address;

  HASH* newnode = 0;

  address = hashAddress(text);

  newnode = (HASH*) calloc(1,sizeof(HASH));

  newnode->text = calloc(strlen(text)+1,sizeof(char));

  strcpy(newnode->text,text);

  newnode->type = type;

  newnode->data_type = 0;

  newnode->scoped = 0;

  newnode->next = Table[address];

  Table[address] = newnode;

  return newnode;

}


HASH* hashFind(char* text){

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

  HASH* node;

  for(i=0;i<HASH_SIZE;i++)
    for(node = Table[i];node;node = node->next)
      printf("Table [%d] has %s, type: %d \n",i,node->text, node->type);
}

void hashUnscope(void)
{
  int i;

  HASH* node;

  for(i=0;i<HASH_SIZE;i++)
    for(node = Table[i];node;node = node->next)
    {
      if (node->scoped == 1)
      {
        node->type = LT_IDENT;
        node->data_type = 0;
        node->scoped = 0;
      }
    }
}

HASH* makeTemp(void)
{
  static int serialNumber = 0;
  static char buffer[64];
  
  sprintf(buffer,"%d",serialNumber++);
  hashInsert(LT_INT,buffer);

}


PARAM* new_param(int type)
{
  PARAM* new_param = 0;
  new_param = (PARAM*) calloc(1,sizeof(PARAM));
  new_param->type = type;
  new_param->next = NULL;
  return new_param;
}

