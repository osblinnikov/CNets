#include "../readerWriter.h"

/*********WRITER FUNCTIONS**********/

writer writerNULL(){
  writer w;
  bufferKernelParams params;
  params.target = NULL;
  writer_init(&w,params);
  return w;
}

void idsDestructor(void* ids){
  vector_cnets_osblinnikov_github_com* vec = (vector_cnets_osblinnikov_github_com*)ids;
  vector_cnets_osblinnikov_github_com_deinit(vec);
  free(vec);
}

vector_cnets_osblinnikov_github_com* getVectorFromParams(bufferKernelParams* params, BOOL isReader){
  vector_cnets_osblinnikov_github_com* vec = (vector_cnets_osblinnikov_github_com*)params->getKernelIds(params, isReader);
  if(vec == 0){
    vec = (vector_cnets_osblinnikov_github_com*)malloc(sizeof(vector_cnets_osblinnikov_github_com));
    if(vec == 0){
      printf("ERROR: writer_cnets_osblinnikov_github_com_getVectorFromParams: unable to allocate memory for vector_cnets_osblinnikov_github_com");
      return 0;
    }
    vector_cnets_osblinnikov_github_com_init(vec);
    params->setKernelIds(params, isReader, vec, idsDestructor);
  }
  return vec;
}

void writer_cnets_osblinnikov_github_com_setKernelId(writer *that, unsigned id){
  if(that == NULL || that->params.target == NULL){return;}
  vector_cnets_osblinnikov_github_com* vec = getVectorFromParams(&that->params, FALSE);
  if(vec != 0){
    vector_cnets_osblinnikov_github_com_add(vec, (void*)id);
  }
  that->kernelId = id;
}

void reader_cnets_osblinnikov_github_com_setKernelId(reader *that, unsigned id){
  if(that == NULL || that->params.target == NULL){return;}
  vector_cnets_osblinnikov_github_com* vec = getVectorFromParams(&that->params, TRUE);
  if(vec != 0){
    vector_cnets_osblinnikov_github_com_add(vec, (void*)id);
  }
  that->kernelId = id;
}

void* readerWriter_cnets_osblinnikov_github_com_writeNext(writer *that, int waitThreshold) {
  if(that == NULL || that->params.target == NULL || that->hasWriteNext){return NULL;}
  /*todo: add here special code for debuging data flow*/
  void* res = that->params.writeNext(&that->params, waitThreshold);
  if(res != NULL){
      that->hasWriteNext = TRUE;
  }
  return res;
}

#define dispatchesAndStats(that,isReader)\
{\
  if (that->interval > 0 && that->statsWriterParams.target != 0) { \
    that->packetsCounter++; \
    uint64_t curTime = curTimeMilisec(); \
    if (curTime - that->statsTime > that->interval) { \
      types_cnets_osblinnikov_github_com_statsLocalProtocol* p; \
      p = (types_cnets_osblinnikov_github_com_statsLocalProtocol*) that->statsWriterParams.writeNext(&that->statsWriterParams,0); \
      if (p != 0) { \
        p->writer = FALSE; \
        p->uniqueId = that->uniqueId(that); \
        p->gridId = that->params.grid_id; \
        p->packets = that->packetsCounter; \
        p->bytes = that->bytesCounter; \
        that->statsWriterParams.writeFinished(&that->statsWriterParams); \
        that->statsTime = curTime; \
        that->packetsCounter = 0; \
        that->bytesCounter = 0; \
      } \
    } \
  } \
  vector_cnets_osblinnikov_github_com* ids = (vector_cnets_osblinnikov_github_com*)that->params.getKernelIds(& that->params, isReader); \
  if (ids != 0 && vector_cnets_osblinnikov_github_com_total(ids) > 0){ \
    if (that->dispatchWriterParams.target != 0){ \
      vector_cnets_osblinnikov_github_com* dispatchables = (vector_cnets_osblinnikov_github_com*)that->dispatchWriterParams.writeNext(&that->dispatchWriterParams,-1); \
      if (dispatchables != 0){ \
        *dispatchables = *ids; \
        that->dispatchWriterParams.writeFinished(&that->dispatchWriterParams); \
      }else{ \
        printf("ERROR: readerWriter_cnets_osblinnikov_github_com_dispatchesAndStats: writeNext: dispatchables is NULL\n"); \
      } \
    } \
  } \
} \


int readerWriter_cnets_osblinnikov_github_com_writeFinished(writer *that) {
  if(that == NULL || that->params.target == NULL || !that->hasWriteNext){return -1;}

  that->hasWriteNext = FALSE;

  int res = that->params.writeFinished(&that->params);

  if(res == 0)
    dispatchesAndStats(that,FALSE);

  return res;
}

int readerWriter_cnets_osblinnikov_github_com_sizeW(writer *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.size(&that->params);
}

int readerWriter_cnets_osblinnikov_github_com_timeoutW(writer *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.timeout(&that->params);
}

int readerWriter_cnets_osblinnikov_github_com_gridSizeW(writer *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.gridSize(&that->params); 
}

int readerWriter_cnets_osblinnikov_github_com_uniqueIdW(writer *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.uniqueId(&that->params);
}

void readerWriter_cnets_osblinnikov_github_com_incrementBytesCounterW(writer *that, int bytesCounter) {
  if (that->interval > 0) {
    that->bytesCounter += bytesCounter;
  }
}

/*********READER FUNCTIONS**********/

reader readerNULL(){
  reader r;
  bufferKernelParams params;
  params.target = NULL;
  reader_init(&r,params);
  return r;
}

bufferReadData readerWriter_cnets_osblinnikov_github_com_readNextWithMeta(reader *that, int waitThreshold) {
  bufferReadData res;
  res.data = NULL;
  if(that == NULL || that->params.target == NULL || that->hasReadNext){return res;}
  /*todo: add here special code for debuging data flow*/
  res = that->params.readNextWithMeta(&that->params, waitThreshold);
  that->hasReadNext = (res.data != NULL);
  return res;
}

void* readerWriter_cnets_osblinnikov_github_com_readNext(reader *that, int waitThreshold) {
  if(that == NULL || that->params.target == NULL || that->hasReadNext){return NULL;}
  /*todo: add here special code for debuging data flow*/
  void* res = that->params.readNext(&that->params, waitThreshold);
  that->hasReadNext = (res != NULL);
  return res;
}

int readerWriter_cnets_osblinnikov_github_com_readFinished(reader *that) {
  if(that == NULL || that->params.target == NULL || !that->hasReadNext){return -1;}
  /*todo: add here special code for debuging data flow*/

  that->hasReadNext = FALSE;

  int res = that->params.readFinished(&that->params);

  if(res == 0)
    dispatchesAndStats(that,TRUE);

  return res;
}

int readerWriter_cnets_osblinnikov_github_com_sizeR(reader *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.size(&that->params);
}

int readerWriter_cnets_osblinnikov_github_com_timeoutR(reader *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.timeout(&that->params);
}

int readerWriter_cnets_osblinnikov_github_com_gridSizeR(reader *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.gridSize(&that->params); 
}

int readerWriter_cnets_osblinnikov_github_com_uniqueIdR(reader *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.uniqueId(&that->params);
}

void readerWriter_cnets_osblinnikov_github_com_incrementBytesCounterR(reader *that, int bytesCounter) {
  if (that->interval > 0) {
    that->bytesCounter += bytesCounter;
  }
}

int readerWriter_cnets_osblinnikov_github_com_addSelector(reader *that,linkedContainer *container){
  if(that == NULL || that->params.target == NULL){return -1;}
  return that->params.addSelector(&that->params, (void*)container);
} 

/****STRUCTURES INITIALIZATIONS***/

void writer_init(writer *that, bufferKernelParams params){
  if(that == NULL){
    printf("writer_init 'that' is NULL\n");
    return;
  }
  that->hasWriteNext = FALSE;
  that->packetsCounter = 0;
  that->bytesCounter = 0;
  that->statsTime = 0;
  that->kernelId = (unsigned)-1;
  that->interval = statsCollectorStatic_getStatsInterval();
  that->statsWriterParams = (statsCollectorStatic_getWriter()).params;
  that->dispatchWriterParams = (dispatcherCollector_getWriter()).params;
  that->params = params;
  that->writeNext = readerWriter_cnets_osblinnikov_github_com_writeNext;
  that->writeFinished = readerWriter_cnets_osblinnikov_github_com_writeFinished;
  that->size = readerWriter_cnets_osblinnikov_github_com_sizeW;
  that->timeout = readerWriter_cnets_osblinnikov_github_com_timeoutW;
  that->gridSize = readerWriter_cnets_osblinnikov_github_com_gridSizeW;
  that->uniqueId = readerWriter_cnets_osblinnikov_github_com_uniqueIdW;
  that->incrementBytesCounter = readerWriter_cnets_osblinnikov_github_com_incrementBytesCounterW;
  that->setKernelId = writer_cnets_osblinnikov_github_com_setKernelId;
  return;
}

void reader_init(reader *that, bufferKernelParams params){
  if(that == NULL){
    printf("reader_init 'that' is NULL\n");
    return;
  }
  that->hasReadNext = FALSE;
  that->packetsCounter = 0;
  that->bytesCounter = 0;
  that->statsTime = 0;
  that->kernelId = (unsigned)-1;
  that->interval = statsCollectorStatic_getStatsInterval();
  that->statsWriterParams = (statsCollectorStatic_getWriter()).params;
  that->dispatchWriterParams = (dispatcherCollector_getWriter()).params;
  that->params = params;
  that->readNextWithMeta = readerWriter_cnets_osblinnikov_github_com_readNextWithMeta;
  that->readNext = readerWriter_cnets_osblinnikov_github_com_readNext;
  that->readFinished = readerWriter_cnets_osblinnikov_github_com_readFinished;
  that->size = readerWriter_cnets_osblinnikov_github_com_sizeR;
  that->timeout = readerWriter_cnets_osblinnikov_github_com_timeoutR;
  that->gridSize = readerWriter_cnets_osblinnikov_github_com_gridSizeR;
  that->uniqueId = readerWriter_cnets_osblinnikov_github_com_uniqueIdR;
  that->incrementBytesCounter = readerWriter_cnets_osblinnikov_github_com_incrementBytesCounterR;
  that->addSelector = readerWriter_cnets_osblinnikov_github_com_addSelector;
  that->setKernelId = reader_cnets_osblinnikov_github_com_setKernelId;
  return;
}

void readerWriter_cnets_osblinnikov_github_com_addContainer(struct linkedContainer *that, struct linkedContainer *added){
  if(that == NULL){
    printf("readerWriter_cnets_osblinnikov_github_com_addContainer that is NULL\n");
    return;
  }
  if(that->next != NULL){
    that->next->add(that->next,added);
  }else{
    that->next = added;
    added->prev = that;
  }
}

void readerWriter_cnets_osblinnikov_github_com_removeContainer(struct linkedContainer *that){
  if(that == NULL){
    printf("readerWriter_cnets_osblinnikov_github_com_removeContainer that is NULL\n");
    return;
  }
  if(that->prev != NULL){
    that->prev->next = that->next;
  }
  if(that->next != NULL){        
    that->next->prev = that->prev;
  }
}

void readerWriter_cnets_osblinnikov_github_com_callContainer(struct linkedContainer *that){
  if(that == NULL){
    printf("readerWriter_cnets_osblinnikov_github_com_callContainer that is NULL\n");
    return;
  }
//  that->w.writeNext(&that->w, -1);//will not cause anithing, but makes writer work consistent
  that->w.hasWriteNext = TRUE;
  that->w.writeFinished(&that->w);
  if(that->next != NULL){
    that->next->call(that->next);
  }
}

void linkedContainer_init(struct linkedContainer *that, struct writer w){
  if(that == NULL){
    printf("linkedContainer_init that is NULL\n");
    return;
  }
  that->next = NULL;
  that->prev = NULL;
  that->w = w;
  that->add = readerWriter_cnets_osblinnikov_github_com_addContainer;
  that->remove = readerWriter_cnets_osblinnikov_github_com_removeContainer;
  that->call = readerWriter_cnets_osblinnikov_github_com_callContainer;
}
