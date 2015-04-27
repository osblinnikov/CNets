/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../mapBuffer.h"

void* mapBuffer_cnets_osblinnikov_github_com_readNext(bufferKernelParams *params, int waitThreshold);
bufferReadData mapBuffer_cnets_osblinnikov_github_com_readNextWithMeta(bufferKernelParams *params, int waitThreshold);
int mapBuffer_cnets_osblinnikov_github_com_readFinished(bufferKernelParams *params);
void* mapBuffer_cnets_osblinnikov_github_com_writeNext(bufferKernelParams *params, int waitThreshold);
int mapBuffer_cnets_osblinnikov_github_com_writeFinished(bufferKernelParams *params);
int mapBuffer_cnets_osblinnikov_github_com_size(bufferKernelParams *params);
int64_t mapBuffer_cnets_osblinnikov_github_com_timeout(bufferKernelParams *params);
int mapBuffer_cnets_osblinnikov_github_com_gridSize(bufferKernelParams *params);
int mapBuffer_cnets_osblinnikov_github_com_uniqueId(bufferKernelParams *params);
int mapBuffer_cnets_osblinnikov_github_com_addSelector(bufferKernelParams *params, void* selectorContainer);
void mapBuffer_cnets_osblinnikov_github_com_onCreate(mapBuffer_cnets_osblinnikov_github_com *that);
void mapBuffer_cnets_osblinnikov_github_com_onDestroy(mapBuffer_cnets_osblinnikov_github_com *that);

reader mapBuffer_cnets_osblinnikov_github_com_createReader(mapBuffer_cnets_osblinnikov_github_com *that, int gridId){
  bufferKernelParams_create(params, that, gridId, mapBuffer_cnets_osblinnikov_github_com_)
  reader_create(res,params)
  return res;
}

writer mapBuffer_cnets_osblinnikov_github_com_createWriter(mapBuffer_cnets_osblinnikov_github_com *that, int gridId){
  bufferKernelParams_create(params, that, gridId, mapBuffer_cnets_osblinnikov_github_com_)
  writer_create(res,params)
  return res;
}

void mapBuffer_cnets_osblinnikov_github_com_init(struct mapBuffer_cnets_osblinnikov_github_com *that,
    arrayObject _buffers,
    int64_t _timeout_milisec,
    int32_t _readers_grid_size){
  
  that->buffers = _buffers;
  that->timeout_milisec = _timeout_milisec;
  that->readers_grid_size = _readers_grid_size;
  mapBuffer_cnets_osblinnikov_github_com_onCreate(that);
}

void mapBuffer_cnets_osblinnikov_github_com_deinit(struct mapBuffer_cnets_osblinnikov_github_com *that){
  mapBuffer_cnets_osblinnikov_github_com_onDestroy(that);
  
}
/*[[[end]]] (checksum: 4589e7f84eb8649b23c0092b8f663d63)*/

#include <assert.h>

void mapBuffer_cnets_osblinnikov_github_com_onCreate(mapBuffer_cnets_osblinnikov_github_com *that){

  that->buffers_grid_ids = (unsigned*)malloc(sizeof(unsigned)*that->buffers.length);
  that->buffers_to_read = (int*)malloc(sizeof(int)* that->buffers.length);
  that->buffers_to_read_lock = (pthread_spinlock_t*)malloc(sizeof(pthread_spinlock_t)*that->buffers.length);
  that->grid = queue_cnets_osblinnikov_github_com_createGrid_dynamic(that->readers_grid_size, that->buffers.length);
  that->grid_mutex = (pthread_spinlock_t*)malloc(sizeof(pthread_spinlock_t)*that->readers_grid_size);
  that->free_buffers = queue_cnets_osblinnikov_github_com_create_dynamic(that->buffers.length);

  int res;
  int i;
  for(i=0; i < that->readers_grid_size; i++){
    res = pthread_spin_init(&that->grid_mutex[i], 0);
    assert(!res);
  }
  for(i = 0; i < (int)that->buffers.length; i++){
    res = that->free_buffers.enqueue(&that->free_buffers,i);
    assert(res == TRUE);
    that->buffers_to_read[i] = 0;  
    res = pthread_spin_init(&that->buffers_to_read_lock[i], 0);
    assert(!res);
  }
  res = pthread_mutex_init(&that->switch_cv_ow_mutex, NULL);
  assert(!res);
  res = pthread_mutex_init(&that->switch_cv_mutex, NULL);
  assert(!res);
  res = pthread_cond_init (&that->switch_cv, NULL);
  assert(!res);

  res = pthread_mutex_init(&that->free_buffers_cv_ow_mutex, NULL);
  assert(!res);
  res = pthread_mutex_init(&that->free_buffers_cv_mutex, NULL);
  assert(!res);
  res = pthread_cond_init (&that->free_buffers_cv, NULL);
  assert(!res);

  res = pthread_rwlock_init(&that->rwLock,NULL);
  assert(!res);

  that->uniqueId = statsCollectorStatic_getNextLocalId();

  that->selectorContainers = NULL;
  return;
}

void mapBuffer_cnets_osblinnikov_github_com_onDestroy(mapBuffer_cnets_osblinnikov_github_com *that){
  free((void*)that->buffers_grid_ids);/* = (unsigned*)malloc(sizeof(unsigned)*that->buffers.length);*/
  free((void*)that->buffers_to_read);/* = (int*)malloc(sizeof(int)* that->buffers.length);*/
  free((void*)that->buffers_to_read_lock);/* = (pthread_spinlock_t*)malloc(sizeof(pthread_spinlock_t)*that->buffers.length);*/
  queue_cnets_osblinnikov_github_com_freeGrid_dynamic(that->grid, that->readers_grid_size);
  free((void*)that->grid_mutex);/* = (pthread_spinlock_t*)malloc(sizeof(pthread_spinlock_t)*that->readers_grid_size);*/
  queue_cnets_osblinnikov_github_com_free_dynamic(that->free_buffers);


  int res;
  int i;
  for(i = 0; i < (int)that->buffers.length; i++){  
    res = pthread_spin_destroy(&that->buffers_to_read_lock[i]);
    assert(!res);
  }
  for(i=0; i < that->readers_grid_size; i++){
    res = pthread_spin_destroy(&that->grid_mutex[i]);
    assert(!res);
  }
  res = pthread_mutex_destroy(&that->switch_cv_ow_mutex);
  assert(!res);
  res = pthread_mutex_destroy(&that->switch_cv_mutex);
  assert(!res);
  res = pthread_cond_destroy(&that->switch_cv);
  assert(!res);

  res = pthread_mutex_destroy(&that->free_buffers_cv_ow_mutex);
  assert(!res);

  res = pthread_mutex_destroy(&that->free_buffers_cv_mutex);
  assert(!res);

  res = pthread_cond_destroy(&that->free_buffers_cv);
  assert(!res);

  res = pthread_rwlock_destroy(&that->rwLock);
  assert(!res);
  return;
}

void* mapBuffer_cnets_osblinnikov_github_com_readNext(bufferKernelParams *params, int waitThreshold) {
  bufferReadData res = mapBuffer_cnets_osblinnikov_github_com_readNextWithMeta(params, waitThreshold);
  return res.data;
}

bufferReadData mapBuffer_cnets_osblinnikov_github_com_readNextWithMeta(bufferKernelParams *params, int waitThreshold) {
  bufferReadData res;
  res.data = NULL;
  if(params == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com readNextWithMeta: params is NULL\n");
    return res;
  }
  mapBuffer_cnets_osblinnikov_github_com *that = (mapBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com readNextWithMeta: Some Input parameters are wrong\n");
    return res;
  }
  uint64_t nanosec = waitThreshold < 0? (uint64_t)that->timeout_milisec : (uint64_t)waitThreshold;
  struct timespec wait_timespec;
  wait_timespec = getTimespecDelay(nanosec*(uint64_t)1000000L);
  /*find the reader's queue*/
  queue_cnets_osblinnikov_github_com *grid_queue = &that->grid[params->grid_id];
  pthread_spinlock_t              *grid_mutex = &that->grid_mutex[params->grid_id];
  /*Lock `wrote` dqueue for the Reader "params->grid_id"*/
  pthread_spin_lock(grid_mutex);

  /*if number of wrote dqueue elements = 0*/
  if(nanosec && grid_queue->isEmpty(grid_queue)){
    /*wait until cond variable of wrote buffer with "Lock `wrote` dqueue" mutex*/
    pthread_spin_unlock(grid_mutex);
    pthread_mutex_lock(&that->switch_cv_mutex);
    pthread_spin_lock(grid_mutex);
    if(grid_queue->isEmpty(grid_queue)){
      do{
        pthread_spin_unlock(grid_mutex);
        if(ETIMEDOUT == pthread_cond_timedwait(&that->switch_cv, &that->switch_cv_mutex, &wait_timespec)){
          printf("WARN: mapBuffer_cnets_osblinnikov_github_com_readNextWithMeta: wait timeout, params->grid_id='%d'\n",params->grid_id);
        }
        pthread_spin_lock(grid_mutex);
        if(!grid_queue->isEmpty(grid_queue)){
          break;
        }
      }while(compareTimespec(&wait_timespec)<0);
    }
    pthread_mutex_unlock(&that->switch_cv_mutex);
  }
  if(!grid_queue->isEmpty(grid_queue)){
    /*write id of buffer to params->internalId variable or NULL if no one buffer available*/
    if(!grid_queue->dequeue(grid_queue, &params->internalId)){
      printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_readNextWithMeta: dequeue is failed: %d\n", params->internalId);
    }else{
      if(params->internalId >= (unsigned)0 && params->internalId < that->buffers.length ){
        res.data = (void*)&((char*)that->buffers.array)[params->internalId*that->buffers.itemSize];
        res.writer_grid_id = that->buffers_grid_ids[params->internalId];
        res.nested_buffer_id = 0;
      }
    }
  }
  /*Unlock `wrote` dqueue for the Reader "params->grid_id"*/
  pthread_spin_unlock(grid_mutex);
  return res;
}

int mapBuffer_cnets_osblinnikov_github_com_readFinished(bufferKernelParams *params) {
  if(params == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com readFinished: params is NULL\n");
    return -1;
  }
  mapBuffer_cnets_osblinnikov_github_com *that = (mapBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com readFinished: Some Input parameters are wrong\n");
    return -1;
  }
  int btr;
  pthread_spin_lock(&that->buffers_to_read_lock[params->internalId]);
  btr = --that->buffers_to_read[params->internalId];
  pthread_spin_unlock(&that->buffers_to_read_lock[params->internalId]);
  if(btr){return 0;}
  /*here, we are only in case if read everything*/
  pthread_mutex_lock(&that->free_buffers_cv_mutex);
  if(!that->free_buffers.enqueue(&that->free_buffers, params->internalId)){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_readFinished: enqueue %d failed\n", params->internalId);
  }
  pthread_cond_signal(&that->free_buffers_cv);
  pthread_mutex_unlock(&that->free_buffers_cv_mutex);
  return 0;
}

void* mapBuffer_cnets_osblinnikov_github_com_writeNext(bufferKernelParams *params, int waitThreshold) {
  if(params == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com writeNext: params is NULL\n");
    return NULL;
  }
  mapBuffer_cnets_osblinnikov_github_com *that = (mapBuffer_cnets_osblinnikov_github_com*)params->target;
  void* res = NULL;
  if(that == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com writeNext: Some Input parameters are wrong\n");
    return res;
  }
  uint64_t nanosec = waitThreshold < 0? (uint64_t)that->timeout_milisec : (uint64_t)waitThreshold;
  struct timespec wait_timespec;
  wait_timespec = getTimespecDelay(nanosec*(uint64_t)1000000L);
  pthread_mutex_lock(&that->free_buffers_cv_ow_mutex);
  pthread_mutex_lock(&that->free_buffers_cv_mutex);
  if(nanosec && that->free_buffers.isEmpty(&that->free_buffers)){
    /*Lock uniq Publisher - only one Publisher will wait for condition variable
    wait until cond variable of free buffer with "Lock `free` stack" mutex*/
    if(ETIMEDOUT == pthread_cond_timedwait(&that->free_buffers_cv, &that->free_buffers_cv_mutex, &wait_timespec)){
      printf("WARN: mapBuffer_cnets_osblinnikov_github_com_writeNext: wait timeout, params->grid_id='%d'\n",params->grid_id);
    }
  }
  if(!that->free_buffers.isEmpty(&that->free_buffers)){
    if(!that->free_buffers.dequeue(&that->free_buffers, &params->internalId)){
      printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_writeNext: dequeue is failed: %d\n", params->internalId);
    }else{
      res = (void*)&((char*)that->buffers.array)[params->internalId*that->buffers.itemSize];
    }
  }
  pthread_mutex_unlock(&that->free_buffers_cv_mutex);
  pthread_mutex_unlock(&that->free_buffers_cv_ow_mutex);
  return res;
}

int mapBuffer_cnets_osblinnikov_github_com_writeFinished(bufferKernelParams *params) {
  if(params == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_writeFinished: params is NULL\n");
    return -1;
  }
  mapBuffer_cnets_osblinnikov_github_com *that = (mapBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_writeFinished: Some Input parameters are wrong\n");
    return -1;
  };

  int i = 0;

  pthread_spin_lock(&that->buffers_to_read_lock[params->internalId]);
  if(that->buffers_to_read[params->internalId]){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_writeFinished: ERROR not all readers read buffer %d, there are %d remain!\n",params->internalId, that->buffers_to_read[params->internalId]);
    pthread_spin_unlock(&that->buffers_to_read_lock[params->internalId]);
    return -1;
  }
  that->buffers_to_read[params->internalId] = that->readers_grid_size;
  pthread_spin_unlock(&that->buffers_to_read_lock[params->internalId]);
  /*foreach reader push new buffer id*/
  for(i=0; i<(int)that->readers_grid_size; ++i){
    pthread_spin_lock( &that->grid_mutex[i] );
    if(!that->grid[i].enqueue(&that->grid[i], params->internalId)){
      printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_writeFinished: enqueue %d failed\n", params->internalId);
    }
    that->buffers_grid_ids[params->internalId] = params->grid_id;
    pthread_spin_unlock(&that->grid_mutex[i]);
  }

  pthread_mutex_lock(&that->switch_cv_mutex);
    pthread_cond_broadcast(&that->switch_cv);
  pthread_mutex_unlock(&that->switch_cv_mutex);

  pthread_rwlock_rdlock(&that->rwLock);
  if(that->selectorContainers != NULL){
    that->selectorContainers->call(that->selectorContainers);
  }
  pthread_rwlock_unlock(&that->rwLock);
  return 0;
}

int mapBuffer_cnets_osblinnikov_github_com_size(bufferKernelParams *params){
  if(params == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_size: params is NULL\n");
    return -1;
  }
  mapBuffer_cnets_osblinnikov_github_com *that = (mapBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_size: Some Input parameters are wrong\n");
    return -1;
  };
  return that->buffers.length;
}

int64_t mapBuffer_cnets_osblinnikov_github_com_timeout(bufferKernelParams *params){
  if(params == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_timeout: params is NULL\n");
    return -1;
  }
  mapBuffer_cnets_osblinnikov_github_com *that = (mapBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_timeout: Some Input parameters are wrong\n");
    return -1;
  };
  return that->timeout_milisec;
}

int mapBuffer_cnets_osblinnikov_github_com_gridSize(bufferKernelParams *params){
  if(params == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_gridSize: params is NULL\n");
    return -1;
  }
  mapBuffer_cnets_osblinnikov_github_com *that = (mapBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_gridSize: Some Input parameters are wrong\n");
    return -1;
  };
  return that->readers_grid_size;
}

int mapBuffer_cnets_osblinnikov_github_com_uniqueId(bufferKernelParams *params){
  if(params == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_uniqueId: params is NULL\n");
    return -1;
  }
  mapBuffer_cnets_osblinnikov_github_com *that = (mapBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_uniqueId: Some Input parameters are wrong\n");
    return -1;
  };
  return that->uniqueId;
}

int mapBuffer_cnets_osblinnikov_github_com_addSelector(bufferKernelParams *params, void* selectorContainer) {
  if(params == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_addSelector: params is NULL\n");
    return -1;
  }
  mapBuffer_cnets_osblinnikov_github_com *that = (mapBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: mapBuffer_cnets_osblinnikov_github_com_addSelector: Some Input parameters are wrong\n");
    return -1;
  };
  linkedContainer *sContainer = (linkedContainer*)selectorContainer;
  pthread_rwlock_wrlock(&that->rwLock);
  if(that->selectorContainers == NULL){that->selectorContainers = sContainer;}
  else{that->selectorContainers->add(that->selectorContainers, sContainer);}
  pthread_rwlock_unlock(&that->rwLock);
  return 0;
}