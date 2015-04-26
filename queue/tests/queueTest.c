
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../queue.h"
/*[[[end]]] (checksum: f98e009465bc52ac8d0d53699bfa8cd0)*/

int testQueue(queue_cnets_osblinnikov_github_com *classObj){
  unsigned obj = 1;
  if(!classObj->enqueue(classObj,obj)){
    printf("!classObj->enqueue(classObj,obj)\n");
    return -1;
  }
  if(classObj->enqueue(classObj,obj)){
    printf("classObj->enqueue(classObj,obj), should be false\n");
    return -1;
  }
  obj = 0;
  if(!classObj->dequeue(classObj,&obj) || obj != 1){
    printf("!classObj->dequeue(classObj,&obj)\n");
    return -1;
  }
  return 0;
}

int main(int argc, char* argv[]){
  queue_cnets_osblinnikov_github_com_create(classObj,1);
  if(testQueue(&classObj)<0){return -1;}

  queue_cnets_osblinnikov_github_com_createGrid(classObjGrid,10,1);
  if(testQueue(&classObjGrid[0])<0){return -1;}
  if(testQueue(&classObjGrid[9])<0){return -1;}
  return 0;
}