
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../include/queue.h"
/*[[[end]]] (checksum: 2ba1e92af3ca8c0c65c29ed3201f817b)*/

int testQueue(com_github_airutech_cnets_queue *classObj){
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
  com_github_airutech_cnets_queue_create(classObj,1);
  if(testQueue(&classObj)<0){return -1;}

  com_github_airutech_cnets_queue_createGrid(classObjGrid,10,1);
  if(testQueue(&classObjGrid[0])<0){return -1;}
  if(testQueue(&classObjGrid[9])<0){return -1;}
  return 0;
}