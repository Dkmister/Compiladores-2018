#include "semantic.h"
/*
Vilmar: Diego, ao inves de hash_pointer o sor usava symbol no codigo
Tem nas fotos que te passei, da uma olhada.
To meio confuso, mas essa vai ser minha contribuicao, se for util de alguma forma.

*/
void set_declarations(AST *node){
  if (!node) return;
  
  if (node->type == AST_VARDEC)
  {
    if(node->symbol->type != SYMBOL_ID)
      {
        fprintf(stderr,"Semantic Error >>> Symbol %s already declared :(",node->hash_pointer->type);
        //exit(4) tem que ser feito no main para futuro debugging e especeficaco
      }
      else
        node->hash_pointer->type = SYMBOL_VARDEC;
  }
  if (node->type == AST_FUNC)
    {
    if(node->symbol->type != SYMBOL_ID)
      {
        fprintf(stderr,"Semantic Error >>> Symbol %s already declared :(",node->hash_pointer->type);
                              //exit(4) tem que ser feito no main para futuro debugging e especeficaco
       }
     else
       node->hash_pointer->type = SYMBOL_FUNCTION;
    }

}
