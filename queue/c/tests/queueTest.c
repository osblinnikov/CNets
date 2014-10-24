
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../include/queue.h"
/*[[[end]]] (checksum: 2ba1e92af3ca8c0c65c29ed3201f817b)*/
int main(int argc, char* argv[]){
  com_github_airutech_cnets_queue_create(classObj,1);
  com_github_airutech_cnets_queue_createGrid(classObjGrid,10,100);
  return 0;
}