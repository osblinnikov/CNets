
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../include/mapBuffer.h"
/*[[[end]]] (checksum: c8758e660135eca590d877f4dbe24d53)*/
int main(int argc, char* argv[]){
  arrayObject_create(arrBufs,unsigned,100)
  com_github_airutech_cnets_mapBuffer_create(classObj,arrBufs,0,0)
  com_github_airutech_cnets_mapBuffer_deinitialize(&classObj);
  return 0;
}