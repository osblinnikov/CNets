#include "../readerWriter.h"

/*********WRITER FUNCTIONS**********/

writer writerNULL(){
  writer w;
  bufferKernelParams params;
  params.target = NULL;
  writer_init_with_params(&w,params);
  return w;
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
} \


int readerWriter_cnets_osblinnikov_github_com_writeFinished(writer *that) {
  if(that == NULL || that->params.target == NULL || !that->hasWriteNext){return -1;}

  that->hasWriteNext = FALSE;

  int res = that->params.writeFinished(&that->params);

  if(res == 0)
    dispatchesAndStats(that,FALSE);
}

int readerWriter_cnets_osblinnikov_github_com_writeFinishedWithMeta(writer *that, bufferWriteData writeData){
  if(that == NULL || that->params.target == NULL || !that->hasWriteNext){return -1;}

  that->hasWriteNext = FALSE;

  int res = that->params.writeFinishedWithMeta(&that->params, writeData);

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
  reader_init_with_params(&r,params);
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

  int res = that->params.readFinished(&that->params);

  if(res == 0)
    dispatchesAndStats(that,TRUE);

  that->hasReadNext = FALSE;

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

void readerWriter_cnets_osblinnikov_github_com_setReadNested(struct reader *that, BOOL readNested){
  if(that == NULL){
    printf("readerWriter_cnets_osblinnikov_github_com_setReadNested 'that' is NULL\n");
    return;
  }
  that->params.readNested = readNested;
}

void readerWriter_cnets_osblinnikov_github_com_enable(struct reader *that, BOOL isEnabled){
  if(that == NULL || that->params.target == NULL){return;}
  return that->params.enable(&that->params, isEnabled);
}

/****STRUCTURES INITIALIZATIONS***/

void writer_init(writer *that){
  bufferKernelParams params;
  writer_init_with_params(that, params);
  that->params.target = NULL;
}


void writer_init_with_params(writer *that, bufferKernelParams params){
  if(that == NULL){
    printf("writer_init 'that' is NULL\n");
    return;
  }
  that->hasWriteNext = FALSE;
  that->packetsCounter = 0;
  that->bytesCounter = 0;
  that->statsTime = 0;
  that->interval = statsCollectorStatic_getStatsInterval();
  that->statsWriterParams = (statsCollectorStatic_getWriter()).params;
  that->params = params;
  that->writeNext = readerWriter_cnets_osblinnikov_github_com_writeNext;
  that->writeFinished = readerWriter_cnets_osblinnikov_github_com_writeFinished;
  that->writeFinishedWithMeta = readerWriter_cnets_osblinnikov_github_com_writeFinishedWithMeta;
  that->size = readerWriter_cnets_osblinnikov_github_com_sizeW;
  that->timeout = readerWriter_cnets_osblinnikov_github_com_timeoutW;
  that->gridSize = readerWriter_cnets_osblinnikov_github_com_gridSizeW;
  that->uniqueId = readerWriter_cnets_osblinnikov_github_com_uniqueIdW;
  that->incrementBytesCounter = readerWriter_cnets_osblinnikov_github_com_incrementBytesCounterW;
  return;
}

void reader_init(reader *that){
  bufferKernelParams params;
  that->params.target = NULL;
  reader_init_with_params(that, params);
}

void reader_init_with_params(reader *that, bufferKernelParams params){
  if(that == NULL){
    printf("reader_init 'that' is NULL\n");
    return;
  }
  that->params.readNested = TRUE;
  that->hasReadNext = FALSE;
  that->packetsCounter = 0;
  that->bytesCounter = 0;
  that->statsTime = 0;
  that->interval = statsCollectorStatic_getStatsInterval();
  that->statsWriterParams = (statsCollectorStatic_getWriter()).params;
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
  that->setReadNested = readerWriter_cnets_osblinnikov_github_com_setReadNested;
  that->enable = readerWriter_cnets_osblinnikov_github_com_enable;
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
