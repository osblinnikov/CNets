
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../include/mapBuffer.h"
/*[[[end]]] (checksum: c8758e660135eca590d877f4dbe24d53)*/


int testWrite(writer* w){
  void* res = w->writeNext(w, -1);
  if(res != NULL){
    *(unsigned*)res = 1;
    return w->writeFinished(w);
  }else{
    return -1;
  }
}

int testRead(reader* r){
  void* res = r->readNext(r, -1);
  if(res != NULL){
    BOOL rs = *(unsigned*)res == 1 && r->readFinished(r) == 0;
    return rs?0:-1;
  }else{
    return -1;
  }
}

int main(int argc, char* argv[]){
  arrayObject_create(arrBufs,unsigned,100)
  com_github_airutech_cnets_mapBuffer_create(classObj,arrBufs,1000,2)
  com_github_airutech_cnets_mapBuffer_createReader(classObjR0,&classObj,0)
  com_github_airutech_cnets_mapBuffer_createReader(classObjR1,&classObj,1)
  com_github_airutech_cnets_mapBuffer_createWriter(classObjW0,&classObj,0)
  com_github_airutech_cnets_mapBuffer_createWriter(classObjW1,&classObj,1)

  if(testWrite(&classObjW0) < 0){
    printf("testWrite: res < 0 should be 0\n");
    return -1;
  }
  printf("testWrite 1\n");

  if(testWrite(&classObjW1) < 0){
    printf("testWrite: res < 0 should be 0\n");
    return -1;
  }

  printf("testWrite 2\n");

  if(testRead(&classObjR0) < 0){
    printf("testRead: res < 0 should be 0\n");
    return -1;
  }
  printf("testRead 1\n");


  if(testRead(&classObjR0) < 0){
    printf("testRead: res < 0 should be 0\n");
    return -1;
  }
  printf("testRead 2\n");

  if(testRead(&classObjR1) < 0){
    printf("testRead: res < 0 should be 0\n");
    return -1;
  }
  printf("testRead 3\n");


  if(testRead(&classObjR1) < 0){
    printf("testRead: res < 0 should be 0\n");
    return -1;
  }
  printf("testRead 4\n");

  if(testRead(&classObjR0) >= 0){
    printf("testRead: res >= 0 should be < 0\n");
    return -1;
  }
  printf("testRead 5\n");

  com_github_airutech_cnets_mapBuffer_deinitialize(&classObj);
  return 0;
}