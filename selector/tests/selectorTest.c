
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../selector.h"
/*[[[end]]] (cd59c4015188742c1e7808ded68d3506) (cd59c4015188742c1e7808ded68d3506)*/

int testWrite(writer* w){
  void* res = w->writeNext(w, -1);
  if(res != NULL){
    *(unsigned*)res = 1;
    return w->writeFinished(w);
  }else{
    return -1;
  }
}

int testRead(reader* r, unsigned expectedBufferId, unsigned expectedWriterId){
  bufferReadData res = r->readNextWithMeta(r, -1);
  if(res.data != NULL){
    BOOL rs = *(unsigned*)res.data == 1 
      && r->readFinished(r) == 0 
      && res.nested_buffer_id == expectedBufferId 
      && res.writer_grid_id == expectedWriterId;
    return rs?0:-1;
  }else{
    return -1;
  }
}


int main(int argc, char* argv[]){
  arrayObject_create(arrBufs0,unsigned,100)
  com_github_osblinnikov_cnets_mapBuffer_create(mbObj0,arrBufs0,1000,1)
  com_github_osblinnikov_cnets_mapBuffer_createReader(mbObj0R0,&mbObj0,0)
  com_github_osblinnikov_cnets_mapBuffer_createWriter(mbObj0W0,&mbObj0,0)

  arrayObject_create(arrBufs1,unsigned,100)
  com_github_osblinnikov_cnets_mapBuffer_create(mbObj1,arrBufs1,1000,1)
  com_github_osblinnikov_cnets_mapBuffer_createReader(mbObj1R0,&mbObj1,0)
  com_github_osblinnikov_cnets_mapBuffer_createWriter(mbObj1W0,&mbObj1,0)

  arrayObject_create(readersObj, reader, 2)
  reader* arr = (reader*)readersObj.array;
  arr[0] = mbObj0R0;
  arr[1] = mbObj1R0;
  com_github_osblinnikov_cnets_selector_create(selectorObj,readersObj);
  com_github_osblinnikov_cnets_selector_createReader(selectorObjR0,&selectorObj,0,-1)

  if(testWrite(&mbObj0W0) < 0){
    printf("testWrite: res < 0 should be 0\n");
    return -1;
  }

  if(testWrite(&mbObj1W0) < 0){
    printf("testWrite: res < 0 should be 0\n");
    return -1;
  }

  if(testRead(&selectorObjR0, 0, 0) < 0){
    printf("testRead: res < 0 should be 0\n");
    return -1;
  }

  if(testRead(&selectorObjR0, 1, 0) < 0){
    printf("testRead: res < 0 should be 0\n");
    return -1;
  }
  com_github_osblinnikov_cnets_mapBuffer_deinitialize(&mbObj0);
  com_github_osblinnikov_cnets_mapBuffer_deinitialize(&mbObj1);
  com_github_osblinnikov_cnets_selector_deinitialize(&selectorObj);
  return 0;
}