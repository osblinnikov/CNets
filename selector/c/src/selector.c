/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../include/selector.h"

void* com_github_osblinnikov_cnets_selector_readNext(bufferKernelParams *params, BOOL make_timeout);
bufferReadData com_github_osblinnikov_cnets_selector_readNextWithMeta(bufferKernelParams *params, BOOL make_timeout);
int com_github_osblinnikov_cnets_selector_readFinished(bufferKernelParams *params);
void* com_github_osblinnikov_cnets_selector_writeNext(bufferKernelParams *params, BOOL make_timeout);
int com_github_osblinnikov_cnets_selector_writeFinished(bufferKernelParams *params);
int com_github_osblinnikov_cnets_selector_size(bufferKernelParams *params);
int com_github_osblinnikov_cnets_selector_timeout(bufferKernelParams *params);
int com_github_osblinnikov_cnets_selector_gridSize(bufferKernelParams *params);
int com_github_osblinnikov_cnets_selector_uniqueId(bufferKernelParams *params);
int com_github_osblinnikov_cnets_selector_addSelector(bufferKernelParams *params, void* selectorContainer);
void com_github_osblinnikov_cnets_selector_onCreate(com_github_osblinnikov_cnets_selector *that);
void com_github_osblinnikov_cnets_selector_onDestroy(com_github_osblinnikov_cnets_selector *that);

reader com_github_osblinnikov_cnets_selector_getReader(com_github_osblinnikov_cnets_selector *that, void* container, int gridId){
  bufferKernelParams_create(params, that, gridId, container,com_github_osblinnikov_cnets_selector_)
  reader_create(res,params)
  return res;
}

writer com_github_osblinnikov_cnets_selector_getWriter(com_github_osblinnikov_cnets_selector *that, void* container, int gridId){
  bufferKernelParams_create(params, that, gridId, container,com_github_osblinnikov_cnets_selector_)
  writer_create(res,params)
  return res;
}

void com_github_osblinnikov_cnets_selector_initialize(com_github_osblinnikov_cnets_selector *that){
  com_github_osblinnikov_cnets_selector_onCreate(that);
}

void com_github_osblinnikov_cnets_selector_deinitialize(struct com_github_osblinnikov_cnets_selector *that){
  com_github_osblinnikov_cnets_selector_onDestroy(that);
}
/*[[[end]]] (checksum: 91486a3dfc81208487ff66a14daa5a67) (150173e19f1ff97a45ede3dbd6d1cf50) */

#include <assert.h>

void com_github_osblinnikov_cnets_selector_onCreate(com_github_osblinnikov_cnets_selector *that){
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
    reader* rdReaderItem = (reader*)&((char*)that->reducableReaders.array)[i * that->reducableReaders.itemSize];
    if(rdReaderItem == NULL){
      that->allContainers[i].add = NULL;
      continue;
    }
    linkedContainer_create(_linkedContainer_,com_github_osblinnikov_cnets_selector_getWriter(that, NULL, i))
    that->allContainers[i] = _linkedContainer_;
    if(0!=rdReaderItem->addSelector(rdReaderItem,&that->allContainers[i]) ) {
      printf("ERROR: com_github_osblinnikov_cnets_selector_onCreate addSelector failed\n");
    }
    int64_t to = rdReaderItem->timeout(rdReaderItem);
    if( to >= 0 && (that->timeout_milisec < 0 || that->timeout_milisec > to) ){
      that->timeout_milisec = to;
    }
  }
  return;
}

void com_github_osblinnikov_cnets_selector_onDestroy(com_github_osblinnikov_cnets_selector *that){
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

void* com_github_osblinnikov_cnets_selector_readNext(bufferKernelParams *params, int waitThreshold) {
  bufferReadData res = com_github_osblinnikov_cnets_selector_readNextWithMeta(params, waitThreshold);
  return res.data;
}

bufferReadData com_github_osblinnikov_cnets_selector_readNextWithMeta(bufferKernelParams *params, int waitThreshold) {
  bufferReadData res;
  res.data = NULL;
  if(params == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_selector readNextWithMeta: params is NULL\n");
    return res;
  }
  com_github_osblinnikov_cnets_selector *that = (com_github_osblinnikov_cnets_selector*)params->target;
  if(that == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_selector readNextWithMeta: Some Input parameters are wrong\n");
    return res;
  }
  BOOL r = FALSE;
  uint64_t nanosec = waitThreshold < 0? (uint64_t)that->timeout_milisec : (uint64_t)waitThreshold;
  struct timespec wait_timespec;
  wait_timespec = getTimespecDelay(nanosec*(uint64_t)1000000L);

  pthread_mutex_lock(&that->switch_cv_lock);
  if(that->sumWrites <= 0 && nanosec > 0){
    do{
      if(ETIMEDOUT == pthread_cond_timedwait(&that->switch_cv, &that->switch_cv_lock, &wait_timespec)){
        printf("ERROR: com_github_osblinnikov_cnets_selector_readNextWithMeta: wait timeout, params->grid_id='%d'\n",params->grid_id);
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
  reader* rdReaderItem = (reader*)&((char*)that->reducableReaders.array)[that->lastReadId * that->reducableReaders.itemSize];
  res = rdReaderItem->readNextWithMeta(rdReaderItem,FALSE);
  if(res.data != NULL){
    res.nested_buffer_id = that->lastReadId;
    com_github_osblinnikov_cnets_selector_container *container = (com_github_osblinnikov_cnets_selector_container*)params->additionalData;
    if(container != NULL){
      container->bufferId = that->lastReadId;
    }
  }
  return res;
}

int com_github_osblinnikov_cnets_selector_readFinished(bufferKernelParams *params) {
  int res = -1;
  if(params == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_selector readFinished: params is NULL\n");
    return res;
  }
  com_github_osblinnikov_cnets_selector *that = (com_github_osblinnikov_cnets_selector*)params->target;
  if(that == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_selector readFinished: Some Input parameters are wrong\n");
    return res;
  }
  com_github_osblinnikov_cnets_selector_container *container = (com_github_osblinnikov_cnets_selector_container *)params->additionalData;
  if(container != NULL && container->bufferId >=0 && container->bufferId < (int)that->reducableReaders.length){
    reader* rdReaderItem = (reader*)&((char*)that->reducableReaders.array)[container->bufferId * that->reducableReaders.itemSize];
    res = rdReaderItem->readFinished(rdReaderItem);
    container->bufferId = -1;
  }else{
    printf("ERROR: com_github_osblinnikov_cnets_selector readFinished: some params are wrong\n");
  }
  return res;
}

void* com_github_osblinnikov_cnets_selector_writeNext(bufferKernelParams *params, int waitThreshold) {
  if(params == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_selector writeNext: params is NULL\n");
    return NULL;
  }
  com_github_osblinnikov_cnets_selector *that = (com_github_osblinnikov_cnets_selector*)params->target;
  void* res = NULL;
  if(that == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_selector writeNext: Some Input parameters are wrong\n");
    return res;
  }
  printf("ERROR: com_github_osblinnikov_cnets_selector writeNext is not allowed\n");
  return res;
}

int com_github_osblinnikov_cnets_selector_writeFinished(bufferKernelParams *params) {
  if(params == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_selector writeFinished: params is NULL\n");
    return -1;
  }
  com_github_osblinnikov_cnets_selector *that = (com_github_osblinnikov_cnets_selector*)params->target;
  if(that == NULL){
    printf("ERROR: selector writeFinished: Some Input parameters are wrong\n");
    return -1;
  };
  pthread_mutex_lock(&that->switch_cv_lock);
  ++that->sumWrites;
  ++that->writesToContainers[params->grid_id];
  pthread_cond_broadcast(&that->switch_cv);
  pthread_mutex_unlock(&that->switch_cv_lock);
  return 0;
}

int com_github_osblinnikov_cnets_selector_size(bufferKernelParams *params){
  if(params == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_selector size: params is NULL\n");
    return -1;
  }
  com_github_osblinnikov_cnets_selector *that = (com_github_osblinnikov_cnets_selector*)params->target;
  if(that == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_selector size: Some Input parameters are wrong\n");
    return -1;
  };
  com_github_osblinnikov_cnets_selector_container *container = (com_github_osblinnikov_cnets_selector_container *)params->additionalData;
  if(container == NULL || container->bufferId <0 || container->bufferId >= (int)that->reducableReaders.length){
    return -1;
  }
  reader* rdReaderItem = (reader*)&((char*)that->reducableReaders.array)[container->bufferId * that->reducableReaders.itemSize];
  return rdReaderItem->size(rdReaderItem);
}

int64_t com_github_osblinnikov_cnets_selector_timeout(bufferKernelParams *params){
  if(params == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_selector timeout: params is NULL\n");
    return -1;
  }
  com_github_osblinnikov_cnets_selector *that = (com_github_osblinnikov_cnets_selector*)params->target;
  if(that == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_selector timeout: Some Input parameters are wrong\n");
    return -1;
  };
  return that->timeout_milisec;
}

int com_github_osblinnikov_cnets_selector_gridSize(bufferKernelParams *params){
  return 1;/*only one selector allowed to listen*/
}

int com_github_osblinnikov_cnets_selector_uniqueId(bufferKernelParams *params){
  return -1;/*it is unnecessary to have unique id*/
}

int com_github_osblinnikov_cnets_selector_addSelector(bufferKernelParams *params, void* selectorContainer) {
  printf("ERROR: com_github_osblinnikov_cnets_selector addSelector is not allowed: nested selectors look ambiguous\n");
  return -1;
}

void com_github_osblinnikov_cnets_selector_onKernels(com_github_osblinnikov_cnets_selector *that){
  /*do nothing*/
  return;
}