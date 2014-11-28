#define SPINCOUNT 100

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../include/mapBuffer.h"

void* com_github_airutech_cnets_mapBuffer_readNext(bufferKernelParams *params, int waitThreshold);
bufferReadData com_github_airutech_cnets_mapBuffer_readNextWithMeta(bufferKernelParams *params, int waitThreshold);
int com_github_airutech_cnets_mapBuffer_readFinished(bufferKernelParams *params);
void* com_github_airutech_cnets_mapBuffer_writeNext(bufferKernelParams *params, int waitThreshold);
int com_github_airutech_cnets_mapBuffer_writeFinished(bufferKernelParams *params);
int com_github_airutech_cnets_mapBuffer_size(bufferKernelParams *params);
int64_t com_github_airutech_cnets_mapBuffer_timeout(bufferKernelParams *params);
int com_github_airutech_cnets_mapBuffer_gridSize(bufferKernelParams *params);
int com_github_airutech_cnets_mapBuffer_uniqueId(bufferKernelParams *params);
int com_github_airutech_cnets_mapBuffer_addSelector(bufferKernelParams *params, void* selectorContainer);
void com_github_airutech_cnets_mapBuffer_onCreate(com_github_airutech_cnets_mapBuffer *that);
void com_github_airutech_cnets_mapBuffer_onDestroy(com_github_airutech_cnets_mapBuffer *that);

reader com_github_airutech_cnets_mapBuffer_getReader(com_github_airutech_cnets_mapBuffer *that, void* container, int gridId){
  bufferKernelParams_create(params, that, gridId, container,com_github_airutech_cnets_mapBuffer_)
  reader_create(res,params)
  return res;
}

writer com_github_airutech_cnets_mapBuffer_getWriter(com_github_airutech_cnets_mapBuffer *that, void* container, int gridId){
  bufferKernelParams_create(params, that, gridId, container,com_github_airutech_cnets_mapBuffer_)
  writer_create(res,params)
  return res;
}

void com_github_airutech_cnets_mapBuffer_initialize(com_github_airutech_cnets_mapBuffer *that){
  com_github_airutech_cnets_mapBuffer_onCreate(that);
}

void com_github_airutech_cnets_mapBuffer_deinitialize(struct com_github_airutech_cnets_mapBuffer *that){
  com_github_airutech_cnets_mapBuffer_onDestroy(that);
}
/*[[[end]]] (checksum: 8bc4baab7ebd65a97dcd5dd7dc03af56)*/

#include <assert.h>

void com_github_airutech_cnets_mapBuffer_onCreate(com_github_airutech_cnets_mapBuffer *that){
  int res;
  int i;
  for(i = 0; i < (int)that->buffers.length; i++){
    res = that->free_buffers.enqueue(&that->free_buffers,i, 0, 0);
    assert(res == TRUE);
    that->buffers_to_read[i] = 0;  
    res = pthread_rwlock_init(&that->buffers_to_read_lock[i], 0);
    assert(!res);
  }

  res = pthread_rwlock_init(&that->rwLock,NULL);
  assert(!res);

  that->uniqueId = statsCollectorStatic_getNextLocalId();

  that->selectorContainers = NULL;
  return;
}

void com_github_airutech_cnets_mapBuffer_onDestroy(com_github_airutech_cnets_mapBuffer *that){
  int res;
  int i;
  for(i = 0; i < (int)that->buffers.length; i++){  
    res = pthread_rwlock_destroy(&that->buffers_to_read_lock[i]);
    assert(!res);
  }

  res = pthread_rwlock_destroy(&that->rwLock);
  assert(!res);
  return;
}

void* com_github_airutech_cnets_mapBuffer_readNext(bufferKernelParams *params, int waitThreshold) {
  bufferReadData res = com_github_airutech_cnets_mapBuffer_readNextWithMeta(params, waitThreshold);
  return res.data;
}

bufferReadData com_github_airutech_cnets_mapBuffer_readNextWithMeta(bufferKernelParams *params, int waitThreshold) {
  bufferReadData res;
  res.data = NULL;
  if(params == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer readNextWithMeta: params is NULL\n");
    return res;
  }
  com_github_airutech_cnets_mapBuffer *that = (com_github_airutech_cnets_mapBuffer*)params->target;
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer readNextWithMeta: Some Input parameters are wrong\n");
    return res;
  }
  uint32_t milisec = waitThreshold < 0? that->timeout_milisec : waitThreshold;
  /*find the reader's queue*/
  com_github_airutech_cnets_queue *grid_queue = &that->grid[params->grid_id];

  /*write id of buffer to params->internalId variable or NULL if no one buffer available*/
  if(!grid_queue->dequeue(grid_queue, &params->internalId, milisec, SPINCOUNT)){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_readNextWithMeta: dequeue is failed: %d  %u\n", params->internalId, milisec);
  }else{
    if(params->internalId >= (unsigned)0 && params->internalId < that->buffers.length ){
      res.data = (void*)&((char*)that->buffers.array)[params->internalId*that->buffers.itemSize];
      pthread_rwlock_rdlock(&that->buffers_to_read_lock[params->internalId]);
      res.writer_grid_id = that->buffers_grid_ids[params->internalId];
      pthread_rwlock_unlock(&that->buffers_to_read_lock[params->internalId]);
      res.nested_buffer_id = 0;
    }
  }
  return res;
}

int com_github_airutech_cnets_mapBuffer_readFinished(bufferKernelParams *params) {
  if(params == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer readFinished: params is NULL\n");
    return -1;
  }
  com_github_airutech_cnets_mapBuffer *that = (com_github_airutech_cnets_mapBuffer*)params->target;
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer readFinished: Some Input parameters are wrong\n");
    return -1;
  }
  pthread_rwlock_wrlock(&that->buffers_to_read_lock[params->internalId]);
  int btr = --that->buffers_to_read[params->internalId];
  pthread_rwlock_unlock(&that->buffers_to_read_lock[params->internalId]);
  if(btr){return 0;}
  /*here, we are only in case if read everything*/
  if(!that->free_buffers.enqueue(&that->free_buffers, params->internalId, 0, 0)){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_readFinished: enqueue %d failed\n", params->internalId);
  }
  return 0;
}

void* com_github_airutech_cnets_mapBuffer_writeNext(bufferKernelParams *params, int waitThreshold) {
  if(params == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer writeNext: params is NULL\n");
    return NULL;
  }
  com_github_airutech_cnets_mapBuffer *that = (com_github_airutech_cnets_mapBuffer*)params->target;
  void* res = NULL;
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer writeNext: Some Input parameters are wrong\n");
    return res;
  }
  uint32_t milisec = waitThreshold < 0? that->timeout_milisec : waitThreshold;
  if(!that->free_buffers.dequeue(&that->free_buffers, &params->internalId, milisec, SPINCOUNT)){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_writeNext: dequeue is failed: %d %u\n", params->internalId, milisec);
  }else{
    res = (void*)&((char*)that->buffers.array)[params->internalId*that->buffers.itemSize];
  }
  return res;
}

int com_github_airutech_cnets_mapBuffer_writeFinished(bufferKernelParams *params) {
  if(params == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_writeFinished: params is NULL\n");
    return -1;
  }
  com_github_airutech_cnets_mapBuffer *that = (com_github_airutech_cnets_mapBuffer*)params->target;
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_writeFinished: Some Input parameters are wrong\n");
    return -1;
  };

  int i = 0;

  pthread_rwlock_wrlock(&that->buffers_to_read_lock[params->internalId]);
  if(that->buffers_to_read[params->internalId]){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_writeFinished: ERROR not all readers read buffer %d, there are %d remain!\n",params->internalId, that->buffers_to_read[params->internalId]);
    pthread_rwlock_unlock(&that->buffers_to_read_lock[params->internalId]);
    return -1;
  }
  that->buffers_to_read[params->internalId] = that->readers_grid_size;
  that->buffers_grid_ids[params->internalId] = params->grid_id;
  pthread_rwlock_unlock(&that->buffers_to_read_lock[params->internalId]);

  /*foreach reader push new buffer id*/
  for(i=0; i<(int)that->readers_grid_size; ++i){
    if(!that->grid[i].enqueue(&that->grid[i], params->internalId, 0, 0)){
      printf("ERROR: com_github_airutech_cnets_mapBuffer_writeFinished: enqueue %d failed\n", params->internalId);
    }
  }

  pthread_rwlock_rdlock(&that->rwLock);
  if(that->selectorContainers != NULL){
    that->selectorContainers->call(that->selectorContainers);
  }
  pthread_rwlock_unlock(&that->rwLock);
  return 0;
}

int com_github_airutech_cnets_mapBuffer_size(bufferKernelParams *params){
  if(params == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_size: params is NULL\n");
    return -1;
  }
  com_github_airutech_cnets_mapBuffer *that = (com_github_airutech_cnets_mapBuffer*)params->target;
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_size: Some Input parameters are wrong\n");
    return -1;
  };
  return that->buffers.length;
}

int64_t com_github_airutech_cnets_mapBuffer_timeout(bufferKernelParams *params){
  if(params == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_timeout: params is NULL\n");
    return -1;
  }
  com_github_airutech_cnets_mapBuffer *that = (com_github_airutech_cnets_mapBuffer*)params->target;
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_timeout: Some Input parameters are wrong\n");
    return -1;
  };
  return that->timeout_milisec;
}

int com_github_airutech_cnets_mapBuffer_gridSize(bufferKernelParams *params){
  if(params == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_gridSize: params is NULL\n");
    return -1;
  }
  com_github_airutech_cnets_mapBuffer *that = (com_github_airutech_cnets_mapBuffer*)params->target;
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_gridSize: Some Input parameters are wrong\n");
    return -1;
  };
  return that->readers_grid_size;
}

int com_github_airutech_cnets_mapBuffer_uniqueId(bufferKernelParams *params){
  if(params == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_uniqueId: params is NULL\n");
    return -1;
  }
  com_github_airutech_cnets_mapBuffer *that = (com_github_airutech_cnets_mapBuffer*)params->target;
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_uniqueId: Some Input parameters are wrong\n");
    return -1;
  };
  return that->uniqueId;
}

int com_github_airutech_cnets_mapBuffer_addSelector(bufferKernelParams *params, void* selectorContainer) {
  if(params == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_addSelector: params is NULL\n");
    return -1;
  }
  com_github_airutech_cnets_mapBuffer *that = (com_github_airutech_cnets_mapBuffer*)params->target;
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_addSelector: Some Input parameters are wrong\n");
    return -1;
  };
  linkedContainer *sContainer = (linkedContainer*)selectorContainer;
  pthread_rwlock_wrlock(&that->rwLock);
  if(that->selectorContainers == NULL){that->selectorContainers = sContainer;}
  else{that->selectorContainers->add(that->selectorContainers, sContainer);}
  pthread_rwlock_unlock(&that->rwLock);
  return 0;
}

void com_github_airutech_cnets_mapBuffer_onKernels(com_github_airutech_cnets_mapBuffer *that){
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_mapBuffer_onKernels: Some Input parameters are wrong\n");
    return;
  };
  return;
}