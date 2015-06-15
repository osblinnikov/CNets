
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../dispatchBuffer.h"
/*[[[end]]] (checksum: 2357e788fd3a687cdfc08ba8dee81d0a)*/

int dispatchIds(writer* w, vector_cnets_osblinnikov_github_com *ids){
  vector_cnets_osblinnikov_github_com* data = (vector_cnets_osblinnikov_github_com*)w->writeNext(w,-1);
  if(data == 0){
    printf("ERROR: test: dispatchIds: w->writeNext returns NULL\n");
    return -1;
  }

  *data = *ids;

  if( w->writeFinished(w) != 0 ){
    printf("ERROR: test: dispatchIds: w->writeFinished returns non-0 status\n");
    return -1;
  }

  return 0;
}

int dequeueAllDifferentIdsTest(reader* r, int countToRead){
  unsigned readTmp[countToRead];
  for(int i=0; i<countToRead; i++){
    unsigned id = (unsigned) r->readNext(r, -1);
    if(id == (unsigned)-1){
      printf("dequeueAllDifferentIds: readNext returns -1\n");
      return -1;
    }
    readTmp[i] = id;
    if(r->readFinished(r) != 0){
      printf("dequeueAllDifferentIds: readFinished returns non-0 status\n");
      return -1;
    }
    for(int j=0; j<i; j++){
      if(readTmp[j] == id) {
        printf("dequeueAllDifferentIds: %d at index %d already occurs at position %d\n", id, i, j);
        return -1;
      }
    }
  }
  return 0;
}



int main(int argc, char* argv[]){

  const uint64_t timeoutMilisec = 1000;
  const unsigned numberOfKernels = 100000;
  const unsigned threadPoolSize = 4;
  vector_cnets_osblinnikov_github_com ids0;
  vector_cnets_osblinnikov_github_com_init(&ids0);
  /*starting from the 2nd kernel, because we're emulating first kernel as writer*/
  vector_cnets_osblinnikov_github_com_resize(&ids0, numberOfKernels-1);
  for(unsigned i=1; i<numberOfKernels; i++){
    vector_cnets_osblinnikov_github_com_add(&ids0, (void*)i);
  }

  arrayObject arr = arrayObject_init_dynamic(sizeof(vector_cnets_osblinnikov_github_com), numberOfKernels);
  if(arr.array == NULL){
    printf("ERROR: test: array is NULL\n");
    return -1;
  }
  for(unsigned i=0; i<numberOfKernels; i++){
    ((vector_cnets_osblinnikov_github_com*)arr.array)[i].items = NULL;
  }
  dispatchBuffer_cnets_osblinnikov_github_com classObj;

  dispatchBuffer_cnets_osblinnikov_github_com_init(&classObj, arr, timeoutMilisec, threadPoolSize);
  writer w = dispatchBuffer_cnets_osblinnikov_github_com_createWriter(&classObj, 0);
  reader r[threadPoolSize];
  for(unsigned i=0; i<threadPoolSize; i++){
   r[i] = dispatchBuffer_cnets_osblinnikov_github_com_createReader(&classObj, i);
  }
  /*now we can globally set writer, and initialize all other readers/writers with the provided dispatcher*/
  dispatcherCollector_setWriter(w);

  /*should be totally fine to dispatch more kernels than array length, because internally dispatchBuffer is not a queue, but a hash*/
  for(unsigned i=0; i<numberOfKernels*2; i++){
    if(dispatchIds(&w, &ids0) != 0){
      return -1;
    }
  }
  /*should be totally fine to dequeue numberOfKernels*2 * (numberOfKernels-1)  because we have numberOfKernels-1 kernels each was dispatched numberOfKernels*2 times(see for-loop above) */
  /*we will read buffers in the emulated threadpool*/
  for(unsigned thr=0; thr<threadPoolSize; thr++){
    for(unsigned j=0; j<numberOfKernels*2/threadPoolSize; j++ ){
      if(dequeueAllDifferentIdsTest(&r[thr], numberOfKernels-1) != 0){
        return -1;
      }
    }
  }

  dispatchBuffer_cnets_osblinnikov_github_com_deinit(&classObj);
  arrayObject_free_dynamic(arr);
  return 0;
}
