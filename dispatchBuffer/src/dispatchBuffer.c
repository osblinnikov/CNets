#include <assert.h>

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../dispatchBuffer.h"

void* dispatchBuffer_cnets_osblinnikov_github_com_readNext(bufferKernelParams *params, int waitThreshold);
bufferReadData dispatchBuffer_cnets_osblinnikov_github_com_readNextWithMeta(bufferKernelParams *params, int waitThreshold);
int dispatchBuffer_cnets_osblinnikov_github_com_readFinished(bufferKernelParams *params);
void* dispatchBuffer_cnets_osblinnikov_github_com_writeNext(bufferKernelParams *params, int waitThreshold);
int dispatchBuffer_cnets_osblinnikov_github_com_writeFinished(bufferKernelParams *params);
int dispatchBuffer_cnets_osblinnikov_github_com_size(bufferKernelParams *params);
int64_t dispatchBuffer_cnets_osblinnikov_github_com_timeout(bufferKernelParams *params);
int dispatchBuffer_cnets_osblinnikov_github_com_gridSize(bufferKernelParams *params);
int dispatchBuffer_cnets_osblinnikov_github_com_uniqueId(bufferKernelParams *params);
int dispatchBuffer_cnets_osblinnikov_github_com_addSelector(bufferKernelParams *params, void* selectorContainer);
void dispatchBuffer_cnets_osblinnikov_github_com_onCreate(dispatchBuffer_cnets_osblinnikov_github_com *that);
void dispatchBuffer_cnets_osblinnikov_github_com_onDestroy(dispatchBuffer_cnets_osblinnikov_github_com *that);
void dispatchBuffer_cnets_osblinnikov_github_com_setKernelIds(bufferKernelParams *params, short isReader, void* ids, void (*idsDestructor)(void*));
void* dispatchBuffer_cnets_osblinnikov_github_com_getKernelIds(bufferKernelParams *params, short isReader);

reader dispatchBuffer_cnets_osblinnikov_github_com_createReader(dispatchBuffer_cnets_osblinnikov_github_com *that, int gridId){
  bufferKernelParams_create(params, that, gridId, dispatchBuffer_cnets_osblinnikov_github_com_)
  reader_create(res,params)
  return res;
}

writer dispatchBuffer_cnets_osblinnikov_github_com_createWriter(dispatchBuffer_cnets_osblinnikov_github_com *that, int gridId){
  bufferKernelParams_create(params, that, gridId, dispatchBuffer_cnets_osblinnikov_github_com_)
  writer_create(res,params)
  return res;
}

void dispatchBuffer_cnets_osblinnikov_github_com_init(struct dispatchBuffer_cnets_osblinnikov_github_com *that,
    arrayObject _buffers,
    int64_t _timeout_milisec,
    uint32_t _startKernelId,
    int32_t _readers_grid_size){
  that->_readerIds_ = 0;
  that->_writerIds_ = 0;
  
  that->buffers = _buffers;
  that->timeout_milisec = _timeout_milisec;
  that->startKernelId = _startKernelId;
  that->readers_grid_size = _readers_grid_size;
  that->messagesInMailbox = arrayObject_init_dynamic(sizeof(uint32_t), that->buffers.length);
  that->dispatchedKernels = arrayObject_init_dynamic(sizeof(uint32_t), that->readers_grid_size);
  that->messagesSpawnTime = arrayObject_init_dynamic(sizeof(uint64_t), that->buffers.length);
  that->spawnedArray = arrayObject_init_dynamic(sizeof(char), that->buffers.length);
  dispatchBuffer_cnets_osblinnikov_github_com_onCreate(that);
}

void dispatchBuffer_cnets_osblinnikov_github_com_deinit(struct dispatchBuffer_cnets_osblinnikov_github_com *that){
  dispatchBuffer_cnets_osblinnikov_github_com_onDestroy(that);
  
  arrayObject_free_dynamic(that->messagesInMailbox);
  arrayObject_free_dynamic(that->dispatchedKernels);
  arrayObject_free_dynamic(that->messagesSpawnTime);
  arrayObject_free_dynamic(that->spawnedArray);
  if(that->_readerIds_ && that->readerIdsDestructor){
    that->readerIdsDestructor(that->_readerIds_);
    that->_readerIds_ = 0;
  }
  if(that->_writerIds_ && that->writerIdsDestructor){
    that->writerIdsDestructor(that->_writerIds_);
    that->_writerIds_ = 0;
  }
}


void dispatchBuffer_cnets_osblinnikov_github_com_setKernelIds(bufferKernelParams *params, short isReader, void* ids, void (*idsDestructor)(void*)) {
  if(params == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com setKernelIds: params is NULL\n");
    return;
  }
  dispatchBuffer_cnets_osblinnikov_github_com *that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com setKernelIds: Some Input parameters are wrong\n");
    return;
  };
  if(isReader){
    that->_readerIds_ = ids;
    that->readerIdsDestructor = idsDestructor;
  }else{
    that->_writerIds_ = ids;
    that->writerIdsDestructor = idsDestructor;
  }
}

void* dispatchBuffer_cnets_osblinnikov_github_com_getKernelIds(bufferKernelParams *params, short isReader) {
  if(params == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com setKernelIds: params is NULL\n");
    return 0;
  }
  dispatchBuffer_cnets_osblinnikov_github_com *that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com setKernelIds: Some Input parameters are wrong\n");
    return 0;
  };
  if(isReader){
    return that->_readerIds_;
  }else{
    return that->_writerIds_;
  }
}
/*[[[end]]] (checksum: 9e9c0f6a4e6b90f95b0465e880cf0ae0)*/

uint32_t defaultFormula(dispatchBuffer_cnets_osblinnikov_github_com* that,bufferKernelParams *params, uint64_t curTime, uint32_t inMailBox, uint32_t index){
  /*each 10 miliseconds will add 1 to the mailbox raiting*/
  return inMailBox+(uint32_t)(curTime - that->spawnTime[index])/10;
}

void dispatchBuffer_cnets_osblinnikov_github_com_onCreate(dispatchBuffer_cnets_osblinnikov_github_com *that){
  that->inMailbox = (uint32_t volatile * )that->messagesInMailbox.array;
  that->spawnTime = (uint64_t volatile * )that->messagesSpawnTime.array;
  that->isSpawned = (unsigned char volatile *)that->spawnedArray.array;
  that->spawnedSpinLocks = (pthread_spinlock_t*)malloc(sizeof(pthread_spinlock_t)*that->buffers.length);
  if(that->spawnedSpinLocks == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com_onCreate: spawnedSpinLocks==NULL\n");
  }
  int res;
  for(size_t i = 0; i<that->buffers.length; i++){
    that->isSpawned[i] = 0;
    that->inMailbox[i] = 0;
    that->spawnTime[i] = 0;
    res = pthread_spin_init(&that->spawnedSpinLocks[i], 0);
    assert(!res);
  }
  res = pthread_mutex_init(&that->cv_mutex, NULL);
  assert(!res);
  res = pthread_cond_init (&that->cv, NULL);
  assert(!res);
  that->formula.context = NULL;
  that->formula.getIds = NULL;
  that->formula.getIdsLength = NULL;
  that->formula.formula = defaultFormula;
  return;
}

void dispatchBuffer_cnets_osblinnikov_github_com_onDestroy(dispatchBuffer_cnets_osblinnikov_github_com *that){
  int res;
  for(size_t i = 0; i<that->buffers.length; i++){
    res = pthread_spin_destroy(&that->spawnedSpinLocks[i]);
    assert(!res);
  }
  free((void*)that->spawnedSpinLocks);
  res = pthread_mutex_destroy(&that->cv_mutex);
  assert(!res);
  res = pthread_cond_destroy(&that->cv);
  assert(!res);
  return;
}

void* dispatchBuffer_cnets_osblinnikov_github_com_readNext(bufferKernelParams *params, int waitTimeout) {
  bufferReadData res = dispatchBuffer_cnets_osblinnikov_github_com_readNextWithMeta(params, waitTimeout);
  return res.data;
}

int dispatchBuffer_cnets_osblinnikov_github_com_waitNext(dispatchBuffer_cnets_osblinnikov_github_com *that, struct timespec* wait_timespec){
  int res = 0;
  pthread_mutex_lock(&that->cv_mutex);
  if(ETIMEDOUT == pthread_cond_timedwait(&that->cv, &that->cv_mutex, wait_timespec)){
    res = 1;
  }
  pthread_mutex_unlock(&that->cv_mutex);
  return res;
}

void dispatchBuffer_cnets_osblinnikov_github_com_waitBroadcast(dispatchBuffer_cnets_osblinnikov_github_com *that){
  pthread_mutex_lock(&that->cv_mutex);
  pthread_cond_broadcast(&that->cv);
  pthread_mutex_unlock(&that->cv_mutex);
}

bufferReadData dispatchBuffer_cnets_osblinnikov_github_com_readNextWithMeta(bufferKernelParams *params, int waitThreshold) {
  bufferReadData res;
  res.data = NULL;
  dispatchBuffer_cnets_osblinnikov_github_com *that;
#ifdef _DEBUG
  if(params == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com readNextWithMeta: params is NULL\n");
    return res;
  }
  that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com readNextWithMeta: Some Input parameters are wrong\n");
    return res;
  }
  if(that->readers_grid_size <= params->grid_id){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com readNextWithMeta: that->readers_grid_size <= params->grid_id\n");
    return res;
  }
#endif
  that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  struct timespec wait_timespec = {0,0};
  uint64_t curTime = curTimeMilisec();
  uint32_t maxId, maxI;
  uint32_t maxFormula = 0;
  size_t idsLength;
  uint32_t* ids;

  if(that->formula.getIdsLength == NULL || that->formula.getIds == NULL){
    idsLength = that->buffers.length;
    ids = NULL;
  }else{
    idsLength = that->formula.getIdsLength(that,params);
    ids = that->formula.getIds(that,params);
  }

  do{
    /*selection of the most relevant kernelId for the current grid_id*/
    for(uint32_t j = 0; j<idsLength; j++){
      uint32_t i, id;
      if(ids != NULL){
        id = ids[j];
        i = id - that->startKernelId;
      }else{
        id = i = j;
      }
      uint32_t inMailbox = that->inMailbox[i];
      if(!that->isSpawned[i] && inMailbox > 0){
        uint32_t newFormula = that->formula.formula(that, params, curTime, inMailbox, i);
        if(maxFormula<newFormula){
          maxFormula = newFormula;
          maxId = id;
          maxI = i;
        }
      }
    }
    if(maxFormula == 0){
      if(wait_timespec.tv_nsec == 0 && wait_timespec.tv_sec == 0){
        uint64_t nanosec = waitThreshold < 0? (uint64_t)that->timeout_milisec : (uint64_t)waitThreshold;
        wait_timespec = getTimespecDelay(nanosec*(uint64_t)1000000L);
      }
      if(dispatchBuffer_cnets_osblinnikov_github_com_waitNext(that, &wait_timespec)){
        return res;
      }else{
        curTime = curTimeMilisec();
        continue;
      }
    }
    pthread_spin_lock(&that->spawnedSpinLocks[maxI]);
  }while(that->isSpawned[maxI]);
  that->isSpawned[maxI] = 1;
  --that->inMailbox[maxI];
  pthread_spin_unlock(&that->spawnedSpinLocks[maxI]);


  /*res.nested_buffer_id = 0;
  res.writer_grid_id = 0;*/
  params->internalId = maxI;
  res.data = (void*)&((uint32_t*)that->dispatchedKernels.array)[params->grid_id];
  *(uint32_t*)res.data = maxId;
  return res;
}

int dispatchBuffer_cnets_osblinnikov_github_com_readFinished(bufferKernelParams *params) {
  dispatchBuffer_cnets_osblinnikov_github_com *that;
#ifdef _DEBUG
  if(params == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com readFinished: params is NULL\n");
    return -1;
  }
  that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com readFinished: Some Input parameters are wrong\n");
    return -1;
  }
#endif
  that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  that->isSpawned[params->internalId] = 0;
  return 0;
}

void* dispatchBuffer_cnets_osblinnikov_github_com_writeNext(bufferKernelParams *params, int waitTimeout) {
  dispatchBuffer_cnets_osblinnikov_github_com *that;
#ifdef _DEBUG
  if(params == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com writeNext: params is NULL\n");
    return NULL;
  }
  that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com writeNext: Some Input parameters are wrong\n");
    return NULL;
  }
  if(that->buffers.length <= params->grid_id){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com writeNext: that->buffers.length <= params->grid_id\n");
    return NULL;
  }
#endif
  that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  return (void*)&((vector_cnets_osblinnikov_github_com*)that->buffers.array)[params->grid_id];
}


int dispatchBuffer_cnets_osblinnikov_github_com_writeFinished(bufferKernelParams *params) {
  dispatchBuffer_cnets_osblinnikov_github_com *that;
#ifdef _DEBUG
  if(params == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com writeFinished: params is NULL\n");
    return -1;
  }
  that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    fprintf(stderr,"ERROR: dispatchBuffer_cnets_osblinnikov_github_com writeFinished: Some Input parameters are wrong\n");
    return -1;
  };
#endif
  that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  vector_cnets_osblinnikov_github_com* ids = &((vector_cnets_osblinnikov_github_com*)that->buffers.array)[params->grid_id];
  uint64_t curTime = curTimeMilisec();
  for(size_t i = 0; i < ids->total; i++){
    uint32_t id = (uint32_t)(unsigned long long)ids->items[i];
    i = id - that->startKernelId;
    that->spawnTime[i] = curTime;
    pthread_spin_lock(&that->spawnedSpinLocks[i]);
    ++that->inMailbox[i];
    pthread_spin_unlock(&that->spawnedSpinLocksi);
  }
  dispatchBuffer_cnets_osblinnikov_github_com_waitBroadcast(that);
  return 0;
}

int dispatchBuffer_cnets_osblinnikov_github_com_size(bufferKernelParams *params){
  return 0;
}

int64_t dispatchBuffer_cnets_osblinnikov_github_com_timeout(bufferKernelParams *params){
  return 0;
}

int dispatchBuffer_cnets_osblinnikov_github_com_gridSize(bufferKernelParams *params){
  return 0;
}

int dispatchBuffer_cnets_osblinnikov_github_com_uniqueId(bufferKernelParams *params){
  return 0;
}

int dispatchBuffer_cnets_osblinnikov_github_com_addSelector(bufferKernelParams *params, void* selectorContainer) {
  return 0;
}
