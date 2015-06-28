/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../selector.h"

void* selector_cnets_osblinnikov_github_com_readNext(bufferKernelParams *params, int waitThreshold);
bufferReadData selector_cnets_osblinnikov_github_com_readNextWithMeta(bufferKernelParams *params, int waitThreshold);
int selector_cnets_osblinnikov_github_com_readFinished(bufferKernelParams *params);
void* selector_cnets_osblinnikov_github_com_writeNext(bufferKernelParams *params, int waitThreshold);
int selector_cnets_osblinnikov_github_com_writeFinished(bufferKernelParams *params);
int selector_cnets_osblinnikov_github_com_writeFinishedWithMeta(bufferKernelParams *params, bufferWriteData writeData);
int selector_cnets_osblinnikov_github_com_size(bufferKernelParams *params);
int64_t selector_cnets_osblinnikov_github_com_timeout(bufferKernelParams *params);
int selector_cnets_osblinnikov_github_com_gridSize(bufferKernelParams *params);
int selector_cnets_osblinnikov_github_com_uniqueId(bufferKernelParams *params);
int selector_cnets_osblinnikov_github_com_addSelector(bufferKernelParams *params, void* selectorContainer);
void selector_cnets_osblinnikov_github_com_onCreate(selector_cnets_osblinnikov_github_com *that);
void selector_cnets_osblinnikov_github_com_onDestroy(selector_cnets_osblinnikov_github_com *that);
void selector_cnets_osblinnikov_github_com_setKernelIds(bufferKernelParams *params, short isReader, void* ids, void (*idsDestructor)(void*));
void* selector_cnets_osblinnikov_github_com_getKernelIds(bufferKernelParams *params, short isReader);
void selector_cnets_osblinnikov_github_com_enable(bufferKernelParams *params, short isEnabled);

reader selector_cnets_osblinnikov_github_com_createReader(selector_cnets_osblinnikov_github_com *that, int gridId){
  bufferKernelParams_create(params, that, gridId, selector_cnets_osblinnikov_github_com_)
  reader_create(res,params)
  return res;
}

writer selector_cnets_osblinnikov_github_com_createWriter(selector_cnets_osblinnikov_github_com *that, int gridId){
  bufferKernelParams_create(params, that, gridId, selector_cnets_osblinnikov_github_com_)
  writer_create(res,params)
  return res;
}

void selector_cnets_osblinnikov_github_com_init(struct selector_cnets_osblinnikov_github_com *that,
    arrayObject _reducableReaders){
  that->_readerIds_ = 0;
  that->_writerIds_ = 0;
  
  that->reducableReaders = _reducableReaders;
  selector_cnets_osblinnikov_github_com_onCreate(that);
}

void selector_cnets_osblinnikov_github_com_deinit(struct selector_cnets_osblinnikov_github_com *that){
  selector_cnets_osblinnikov_github_com_onDestroy(that);
  
  if(that->_readerIds_ && that->readerIdsDestructor){
    that->readerIdsDestructor(that->_readerIds_);
    that->_readerIds_ = 0;
  }
  if(that->_writerIds_ && that->writerIdsDestructor){
    that->writerIdsDestructor(that->_writerIds_);
    that->_writerIds_ = 0;
  }
}


void selector_cnets_osblinnikov_github_com_setKernelIds(bufferKernelParams *params, short isReader, void* ids, void (*idsDestructor)(void*)) {
  if(params == NULL){
    fprintf(stderr,"ERROR: selector_cnets_osblinnikov_github_com setKernelIds: params is NULL\n");
    return;
  }
  selector_cnets_osblinnikov_github_com *that = (selector_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    fprintf(stderr,"ERROR: selector_cnets_osblinnikov_github_com setKernelIds: Some Input parameters are wrong\n");
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

void* selector_cnets_osblinnikov_github_com_getKernelIds(bufferKernelParams *params, short isReader) {
  if(params == NULL){
    fprintf(stderr,"ERROR: selector_cnets_osblinnikov_github_com setKernelIds: params is NULL\n");
    return 0;
  }
  selector_cnets_osblinnikov_github_com *that = (selector_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    fprintf(stderr,"ERROR: selector_cnets_osblinnikov_github_com setKernelIds: Some Input parameters are wrong\n");
    return 0;
  };
  if(isReader){
    return that->_readerIds_;
  }else{
    return that->_writerIds_;
  }
}
/*[[[end]]] (checksum: be5ebb8555f03c823f9b1d4a82c9cb86)*/

#include <assert.h>

void selector_cnets_osblinnikov_github_com_onCreate(selector_cnets_osblinnikov_github_com *that){

  that->allContainers = (linkedContainer*)malloc(sizeof(linkedContainer)*that->reducableReaders.length);
  that->writesToContainers = (uint32_t*)malloc(sizeof(uint32_t)*that->reducableReaders.length);
  
  that->timeout_milisec = -1;
  that->lastReadId = -1;
  that->sumWrites = 0;
  int res;
  int i;
  res = pthread_mutex_init(&that->switch_cv_lock, NULL);
  assert(!res);
  res = pthread_cond_init (&that->switch_cv, NULL);
  assert(!res);
  for(i=0; i<(int)that->reducableReaders.length; i++){
    that->writesToContainers[i] = 0;
    reader* rdReaderItem = &((reader*)that->reducableReaders.array)[i];
    if(rdReaderItem == NULL || rdReaderItem->params.target == NULL){
      that->allContainers[i].add = NULL;
      continue;
    }
    linkedContainer_init(&that->allContainers[i], selector_cnets_osblinnikov_github_com_createWriter(that, i));
    if(0!=rdReaderItem->addSelector(rdReaderItem,&that->allContainers[i]) ) {
      printf("ERROR: selector_cnets_osblinnikov_github_com_onCreate addSelector failed\n");
    }
    int64_t to = rdReaderItem->timeout(rdReaderItem);
    if( to >= 0 && (that->timeout_milisec < 0 || that->timeout_milisec > to) ){
      that->timeout_milisec = to;
    }
  }
  that->selectorContainers = NULL;
  return;
}

void selector_cnets_osblinnikov_github_com_onDestroy(selector_cnets_osblinnikov_github_com *that){
  free(that->allContainers);/* = (linkedContainer*)malloc(sizeof(linkedContainer)*that->reducableReaders.length);*/
  free(that->writesToContainers); /* = (uint32_t*)malloc(sizeof(uint32_t)*that->reducableReaders.length);*/

  int i;
  for(i=0; i<(int)that->reducableReaders.length; i++){
    if(that->allContainers[i].add != NULL) {
      that->allContainers[i].remove(&that->allContainers[i]);
    }
  }

  int res;
  res = pthread_mutex_destroy(&that->switch_cv_lock);
  assert(!res);
  res = pthread_cond_destroy (&that->switch_cv);
  assert(!res);
  return;
}

void* selector_cnets_osblinnikov_github_com_readNext(bufferKernelParams *params, int waitThreshold) {
  bufferReadData res = selector_cnets_osblinnikov_github_com_readNextWithMeta(params, waitThreshold);
  return res.data;
}

bufferReadData selector_cnets_osblinnikov_github_com_readNextWithMeta(bufferKernelParams *params, int waitThreshold) {
  bufferReadData res;
  res.data = NULL;
  if(params == NULL){
    fprintf(stderr,"ERROR: selector_cnets_osblinnikov_github_com readNextWithMeta: params is NULL\n");
    return res;
  }
  selector_cnets_osblinnikov_github_com *that = (selector_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    fprintf(stderr,"ERROR: selector_cnets_osblinnikov_github_com readNextWithMeta: Some Input parameters are wrong\n");
    return res;
  }
  BOOL r = FALSE;
  uint64_t nanosec = waitThreshold < 0? (uint64_t)that->timeout_milisec : (uint64_t)waitThreshold;

  pthread_mutex_lock(&that->switch_cv_lock);
  if(that->sumWrites <= 0 && nanosec > 0){
    struct timespec wait_timespec;
    wait_timespec = getTimespecDelay(nanosec*(uint64_t)1000000L);
    do{
      if(ETIMEDOUT == pthread_cond_timedwait(&that->switch_cv, &that->switch_cv_lock, &wait_timespec)){
        printf("WARN: selector_cnets_osblinnikov_github_com_readNextWithMeta: wait timeout, params->grid_id='%d'\n",params->grid_id);
      }
      if(that->sumWrites > 0){
        break;
      }else if(!(r = compareTimespec(&wait_timespec)<0) ){
        pthread_mutex_unlock(&that->switch_cv_lock);
        return res;
      }
    }while(r);
  }
  do{
    ++that->lastReadId;
    if(that->lastReadId >= (int)that->reducableReaders.length){that->lastReadId = 0;}
  }while(that->writesToContainers[that->lastReadId] == 0);
  that->sumWrites--;
  that->writesToContainers[that->lastReadId]--;
  pthread_mutex_unlock(&that->switch_cv_lock);
  reader* rdReaderItem = &((reader*)that->reducableReaders.array)[that->lastReadId];

  if(params->readNested > 0){
    res = rdReaderItem->readNextWithMeta(rdReaderItem,0);
  }else{
    res.data = (void*)rdReaderItem;
  }
  if(res.data != NULL){
    res.nested_buffer_id = that->lastReadId;
    params->bufferId = that->lastReadId;
  }
  return res;
}

int selector_cnets_osblinnikov_github_com_readFinished(bufferKernelParams *params) {
  int res = -1;
  if(params == NULL){
    printf("ERROR: selector_cnets_osblinnikov_github_com readFinished: params is NULL\n");
    return res;
  }
  selector_cnets_osblinnikov_github_com *that = (selector_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: selector_cnets_osblinnikov_github_com readFinished: Some Input parameters are wrong\n");
    return res;
  }
  if(params->bufferId >=0 && params->bufferId < (int)that->reducableReaders.length){
    if(params->readNested > 0){
      reader* rdReaderItem = &((reader*)that->reducableReaders.array)[params->bufferId];
      res = rdReaderItem->readFinished(rdReaderItem);
    }
    params->bufferId = -1;
  }else{
    printf("ERROR: selector_cnets_osblinnikov_github_com readFinished: some params are wrong\n");
  }
  return res;
}

void* selector_cnets_osblinnikov_github_com_writeNext(bufferKernelParams *params, int waitThreshold) {
  if(params == NULL){
    printf("ERROR: selector_cnets_osblinnikov_github_com writeNext: params is NULL\n");
    return NULL;
  }
  selector_cnets_osblinnikov_github_com *that = (selector_cnets_osblinnikov_github_com*)params->target;
  void* res = NULL;
  if(that == NULL){
    printf("ERROR: selector_cnets_osblinnikov_github_com writeNext: Some Input parameters are wrong\n");
    return res;
  }
//  printf("ERROR: selector_cnets_osblinnikov_github_com writeNext is not allowed\n");
  return res;
}



int selector_cnets_osblinnikov_github_com_writeFinished(bufferKernelParams *params) {
  bufferWriteData writeData;
//  writeData.grid_ids = 0;
//  writeData.isLocalOnly = 0;
  return selector_cnets_osblinnikov_github_com_writeFinishedWithMeta(params, writeData);
}

int selector_cnets_osblinnikov_github_com_writeFinishedWithMeta(bufferKernelParams *params, bufferWriteData writeData){
  if(params == NULL){
    printf("ERROR: selector_cnets_osblinnikov_github_com_writeFinishedWithMeta: params is NULL\n");
    return -1;
  }
  selector_cnets_osblinnikov_github_com *that = (selector_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: selector_cnets_osblinnikov_github_com_writeFinishedWithMeta: Some Input parameters are wrong\n");
    return -1;
  };
  pthread_mutex_lock(&that->switch_cv_lock);
  ++that->sumWrites;
  ++that->writesToContainers[params->grid_id];
  pthread_cond_broadcast(&that->switch_cv);
  pthread_mutex_unlock(&that->switch_cv_lock);

  linkedContainer * tmp = (linkedContainer *) that->selectorContainers; //removing volatile pointer
  if(tmp != NULL){
    tmp->call(tmp);
  }

  return 0;
}

int selector_cnets_osblinnikov_github_com_size(bufferKernelParams *params){
  if(params == NULL){
    printf("ERROR: selector_cnets_osblinnikov_github_com size: params is NULL\n");
    return -1;
  }
  selector_cnets_osblinnikov_github_com *that = (selector_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: selector_cnets_osblinnikov_github_com size: Some Input parameters are wrong\n");
    return -1;
  };
  if(params->bufferId <0 || params->bufferId >= (int)that->reducableReaders.length){
    return -1;
  }
  reader* rdReaderItem = &((reader*)that->reducableReaders.array)[params->bufferId];
  return rdReaderItem->size(rdReaderItem);
}

int64_t selector_cnets_osblinnikov_github_com_timeout(bufferKernelParams *params){
  if(params == NULL){
    printf("ERROR: selector_cnets_osblinnikov_github_com timeout: params is NULL\n");
    return -1;
  }
  selector_cnets_osblinnikov_github_com *that = (selector_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: selector_cnets_osblinnikov_github_com timeout: Some Input parameters are wrong\n");
    return -1;
  };
  return that->timeout_milisec;
}

int selector_cnets_osblinnikov_github_com_gridSize(bufferKernelParams *params){
  return 1;/*only one selector allowed to listen*/
}

int selector_cnets_osblinnikov_github_com_uniqueId(bufferKernelParams *params){
  return -1;/*it is unnecessary to have unique id*/
}

int selector_cnets_osblinnikov_github_com_addSelector(bufferKernelParams *params, void* selectorContainer) {
  selector_cnets_osblinnikov_github_com *that;
#ifdef _DEBUG
  if(params == NULL){
    fprintf(stderr,"ERROR: selector_cnets_osblinnikov_github_com: params is NULL\n");
    return -1;
  }
  that = (selector_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    fprintf(stderr,"ERROR: selector_cnets_osblinnikov_github_com: Some Input parameters are wrong\n");
    return -1;
  };
#endif
  that = (selector_cnets_osblinnikov_github_com*)params->target;
  linkedContainer *sContainer = (linkedContainer*)selectorContainer;
  if(that->selectorContainers == NULL){
      that->selectorContainers = sContainer;
  }else{
      linkedContainer * tmp = (linkedContainer *) that->selectorContainers; //removing volatile pointer
      tmp->add(tmp, sContainer);
  }
  return 0;
}

void selector_cnets_osblinnikov_github_com_enable(bufferKernelParams *params, short isEnabled){
  return;
}

