/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../include/types.h"
void com_github_osblinnikov_cnets_types_onCreate(com_github_osblinnikov_cnets_types *that);
void com_github_osblinnikov_cnets_types_onDestroy(com_github_osblinnikov_cnets_types *that);
void com_github_osblinnikov_cnets_types_initialize(com_github_osblinnikov_cnets_types *that){
  com_github_osblinnikov_cnets_types_onCreate(that);
}

void com_github_osblinnikov_cnets_types_deinitialize(struct com_github_osblinnikov_cnets_types *that){
  com_github_osblinnikov_cnets_types_onDestroy(that);
}
/*[[[end]]] (checksum: b7292e67d88346f9c8a24afbe1bed6f1) (71c5424b19c94ae035119a62d5086f81)*/

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