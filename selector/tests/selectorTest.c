
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../selector.h"
/*[[[end]]] (checksum: bc4be62c4d98a1460d8cf7e511d751c8)*/

int testWrite(writer* w){
  void* res = w->writeNext(w, -1);
  if(res != NULL){
    *(unsigned*)res = 1;
      printf("data is written\n");
    return w->writeFinished(w);
  }else{
      printf("No data to write\n");
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
      printf("No data to read\n");
    return -1;
  }
}


int main(int argc, char* argv[]){
  arrayObject_create(arrBufs0,unsigned,100)
  mapBuffer_cnets_osblinnikov_github_com mbObj0, mbObj1;
  mapBuffer_cnets_osblinnikov_github_com_init(&mbObj0,arrBufs0,1000,1);
  reader mbObj0R0 = mapBuffer_cnets_osblinnikov_github_com_createReader(&mbObj0,0);
  writer mbObj0W0 = mapBuffer_cnets_osblinnikov_github_com_createWriter(&mbObj0,0);

  arrayObject_create(arrBufs1,unsigned,100)
  mapBuffer_cnets_osblinnikov_github_com_init(&mbObj1,arrBufs1,1000,1);
  reader mbObj1R0 = mapBuffer_cnets_osblinnikov_github_com_createReader(&mbObj1,0);
  writer mbObj1W0 = mapBuffer_cnets_osblinnikov_github_com_createWriter(&mbObj1,0);

  arrayObject_create(readersObj, reader, 2)
  reader* arr = (reader*)readersObj.array;
  arr[0] = mbObj0R0;
  arr[1] = mbObj1R0;
  selector_cnets_osblinnikov_github_com selectorObj;
  selector_cnets_osblinnikov_github_com_init(&selectorObj,readersObj);
  reader selectorObjR0 = selector_cnets_osblinnikov_github_com_createReader(&selectorObj,0);

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
  mapBuffer_cnets_osblinnikov_github_com_deinit(&mbObj0);
  mapBuffer_cnets_osblinnikov_github_com_deinit(&mbObj1);
  selector_cnets_osblinnikov_github_com_deinit(&selectorObj);
  printf("--- selectorTest OK\n");
  return 0;
}
