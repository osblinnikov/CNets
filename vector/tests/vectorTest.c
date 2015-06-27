
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../vector.h"
/*[[[end]]] (checksum: 29138986b5083a979a4e0706be38903c)*/

#include <stdio.h>

int main(int argc, char* argv[]){
  int i;

  vector_cnets_osblinnikov_github_com v;
  vector_cnets_osblinnikov_github_com_init(&v);

  vector_cnets_osblinnikov_github_com_add(&v, 1);
  vector_cnets_osblinnikov_github_com_add(&v, 2);
  vector_cnets_osblinnikov_github_com_add(&v, 3);
  vector_cnets_osblinnikov_github_com_add(&v, 4);

  for (i = 0; i < vector_cnets_osblinnikov_github_com_total(&v); i++)
      printf("%d ", vector_cnets_osblinnikov_github_com_get(&v, i));
  printf("\n");

  vector_cnets_osblinnikov_github_com_delete(&v, 3);
  vector_cnets_osblinnikov_github_com_delete(&v, 2);
  vector_cnets_osblinnikov_github_com_delete(&v, 1);

  vector_cnets_osblinnikov_github_com_set(&v, 0, 5);
  vector_cnets_osblinnikov_github_com_add(&v, 6);

  for (i = 0; i < vector_cnets_osblinnikov_github_com_total(&v); i++)
      printf("%d ", vector_cnets_osblinnikov_github_com_get(&v, i));
  printf("\n");

  vector_cnets_osblinnikov_github_com_deinit(&v);
  return 0;
}
