
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../mapBuffer.h"
/*[[[end]]] (c8758e660135eca590d877f4dbe24d53) (c8758e660135eca590d877f4dbe24d53)*/

const int countToSend = 3000000;

BOOL checkTotal(int total){
  return total >= countToSend;
}

int testWrite(writer* w){
  void* res = w->writeNext(w, -1);
  if(res != NULL){
    *(unsigned*)res = 1;
    return w->writeFinished(w);
  }else{
    printf("writeNext is NULL\n");
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

void *writeKernel(void* inTarget){
  int cnt = 0;
  int total = 0;
  uint64_t nextTime = 0;
  while(TRUE){
    uint64_t curTime = curTimeMilisec();
    if(curTime>nextTime){
      printf("writer: %d %d\n",cnt, total);
      cnt = 0;
      nextTime = curTime + 1000L;
    }
    if(0<=testWrite((writer*)inTarget)){
      ++cnt;
      ++total;//it's because we actually have 2 writers
      if (checkTotal(++total))
        break;
    }
  }
  return NULL;
}

void *readKernel(void* inTarget){
  int total = 0;
  int cnt = 0;
  uint64_t nextTime = 0;
  while(TRUE){
    uint64_t curTime = curTimeMilisec();
    if(curTime>nextTime){
      printf("reader: %d %d\n",cnt, total);
      cnt = 0;
      nextTime = curTime + 1000L;
    }
    if(0<=testRead((reader*)inTarget)){
      ++cnt;
      if (checkTotal(++total))
        break;
    }
  }
  return NULL;
}

int main(int argc, char* argv[]){
  arrayObject_create(arrBufs,unsigned,100)
  com_github_osblinnikov_cnets_mapBuffer_create(classObj,arrBufs,1000,2)
  com_github_osblinnikov_cnets_mapBuffer_createReader(classObjR0,&classObj,0)
  com_github_osblinnikov_cnets_mapBuffer_createReader(classObjR1,&classObj,1)
  com_github_osblinnikov_cnets_mapBuffer_createWriter(classObjW0,&classObj,0)
  com_github_osblinnikov_cnets_mapBuffer_createWriter(classObjW1,&classObj,1)

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

  pthread_t threadW0, threadW1, threadR0, threadR1;
  pthread_create(&threadW0, NULL, writeKernel, (void *)&classObjW0);
  pthread_create(&threadW1, NULL, writeKernel, (void *)&classObjW1);
  pthread_create(&threadR0, NULL, readKernel, (void *)&classObjR0);
  pthread_create(&threadR1, NULL, readKernel, (void *)&classObjR1);
  // readKernel((void *)&classObjR1);
  // taskDelay(5000000000L);
  pthread_join(threadW0, NULL);pthread_join(threadW1, NULL);pthread_join(threadR0, NULL);pthread_join(threadR1, NULL);

  // com_github_osblinnikov_cnets_mapBuffer_deinitialize(&classObj);
  return 0;
}