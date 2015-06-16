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
    int32_t _readers_grid_size){
  that->_readerIds_ = 0;
  that->_writerIds_ = 0;
  
  that->buffers = _buffers;
  that->timeout_milisec = _timeout_milisec;
  that->readers_grid_size = _readers_grid_size;
  that->requiredToRespawn = arrayObject_init_dynamic(sizeof(char), that->readers_grid_size);
  that->messagesInMailbox = arrayObject_init_dynamic(sizeof(uint32_t), that->buffers.length);
  dispatchBuffer_cnets_osblinnikov_github_com_onCreate(that);
}

void dispatchBuffer_cnets_osblinnikov_github_com_deinit(struct dispatchBuffer_cnets_osblinnikov_github_com *that){
  dispatchBuffer_cnets_osblinnikov_github_com_onDestroy(that);
  
  arrayObject_free_dynamic(that->requiredToRespawn);
  arrayObject_free_dynamic(that->messagesInMailbox);
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
    printf("ERROR: dispatchBuffer_cnets_osblinnikov_github_com setKernelIds: params is NULL\n");
    return;
  }
  dispatchBuffer_cnets_osblinnikov_github_com *that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: dispatchBuffer_cnets_osblinnikov_github_com setKernelIds: Some Input parameters are wrong\n");
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
    printf("ERROR: dispatchBuffer_cnets_osblinnikov_github_com setKernelIds: params is NULL\n");
    return 0;
  }
  dispatchBuffer_cnets_osblinnikov_github_com *that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: dispatchBuffer_cnets_osblinnikov_github_com setKernelIds: Some Input parameters are wrong\n");
    return 0;
  };
  if(isReader){
    return that->_readerIds_;
  }else{
    return that->_writerIds_;
  }
}
/*[[[end]]] (checksum: 0bfba302c3fbb1549c32e52e778f79d7)*/

void dispatchBuffer_cnets_osblinnikov_github_com_onCreate(dispatchBuffer_cnets_osblinnikov_github_com *that){
  
  return;
}

void dispatchBuffer_cnets_osblinnikov_github_com_onDestroy(dispatchBuffer_cnets_osblinnikov_github_com *that){
  
  return;
}

void* dispatchBuffer_cnets_osblinnikov_github_com_readNext(bufferKernelParams *params, int waitTimeout) {
  bufferReadData res = dispatchBuffer_cnets_osblinnikov_github_com_readNextWithMeta(params, waitTimeout);
  return res.data;
}

bufferReadData dispatchBuffer_cnets_osblinnikov_github_com_readNextWithMeta(bufferKernelParams *params, int waitTimeout) {
  bufferReadData res;
  res.data = NULL;
  if(params == NULL){
    printf("ERROR: dispatchBuffer_cnets_osblinnikov_github_com readNextWithMeta: params is NULL\n");
    return res;
  }
  dispatchBuffer_cnets_osblinnikov_github_com *that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: dispatchBuffer_cnets_osblinnikov_github_com readNextWithMeta: Some Input parameters are wrong\n");
    return res;
  }
  /*TODO:IMPLEMENTATION GOES HERE*/
  return res;
}

int dispatchBuffer_cnets_osblinnikov_github_com_readFinished(bufferKernelParams *params) {
  if(params == NULL){
    printf("ERROR: dispatchBuffer_cnets_osblinnikov_github_com readFinished: params is NULL\n");
    return -1;
  }
  dispatchBuffer_cnets_osblinnikov_github_com *that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: dispatchBuffer_cnets_osblinnikov_github_com readFinished: Some Input parameters are wrong\n");
    return -1;
  }
  /*TODO:IMPLEMENTATION GOES HERE*/
  return 0;
}

void* dispatchBuffer_cnets_osblinnikov_github_com_writeNext(bufferKernelParams *params, int waitTimeout) {
  if(params == NULL){
    printf("ERROR: dispatchBuffer_cnets_osblinnikov_github_com writeNext: params is NULL\n");
    return NULL;
  }
  dispatchBuffer_cnets_osblinnikov_github_com *that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  void* res = NULL;
  if(that == NULL){
    printf("ERROR: dispatchBuffer_cnets_osblinnikov_github_com writeNext: Some Input parameters are wrong\n");
    return res;
  }
  /*TODO:IMPLEMENTATION GOES HERE*/
  return res;
}

int dispatchBuffer_cnets_osblinnikov_github_com_writeFinished(bufferKernelParams *params) {
  if(params == NULL){
    printf("ERROR: dispatchBuffer_cnets_osblinnikov_github_com writeFinished: params is NULL\n");
    return -1;
  }
  dispatchBuffer_cnets_osblinnikov_github_com *that = (dispatchBuffer_cnets_osblinnikov_github_com*)params->target;
  if(that == NULL){
    printf("ERROR: dispatchBuffer_cnets_osblinnikov_github_com writeFinished: Some Input parameters are wrong\n");
    return -1;
  };
  /*TODO:IMPLEMENTATION GOES HERE*/
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
