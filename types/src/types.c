/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../types.h"
void com_github_osblinnikov_cnets_types_onCreate(com_github_osblinnikov_cnets_types *that);
void com_github_osblinnikov_cnets_types_onDestroy(com_github_osblinnikov_cnets_types *that);
void com_github_osblinnikov_cnets_types_init(struct com_github_osblinnikov_cnets_types *that){
  
  com_github_osblinnikov_cnets_types_onKernels(that);
  com_github_osblinnikov_cnets_types_onCreate(that);
}

void com_github_osblinnikov_cnets_types_deinit(struct com_github_osblinnikov_cnets_types *that){
  com_github_osblinnikov_cnets_types_onDestroy(that);
}
/*[[[end]]] (checksum: e20117ea76f34832a75cb111c3e9e273) (71c5424b19c94ae035119a62d5086f81)*/

void com_github_osblinnikov_cnets_types_onCreate(com_github_osblinnikov_cnets_types *that){
  
  return;
}

void com_github_osblinnikov_cnets_types_onDestroy(com_github_osblinnikov_cnets_types *that){
  
  return;
}


void com_github_osblinnikov_cnets_types_onKernels(com_github_osblinnikov_cnets_types *that){
  
  return;
}

struct arrayObject arrayObjectNULL(){
  struct arrayObject res;
  res.array = NULL;
  res.length = 0;
  res.itemSize = 0;
  return res;
}

struct arrayObject arrayObject_init_dynamic(unsigned itemSize, unsigned capacity){
  struct arrayObject res;
  res.array = (void*)malloc(itemSize*capacity);
  if(res.array == NULL){
    printf("MALLOC FAILED %dx%d\n", itemSize, capacity);
    res.length = 0;
    res.itemSize = 0;
  }else{
    res.length = capacity;
    res.itemSize = itemSize;
  }
  return res;
}

void arrayObject_free_dynamic(struct arrayObject res){
  if(res.array != NULL){
    free(res.array);
  }
}