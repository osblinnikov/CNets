/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../include/readerWriter.h"
void com_github_airutech_cnets_readerWriter_onCreate(com_github_airutech_cnets_readerWriter *that);
void com_github_airutech_cnets_readerWriter_onDestroy(com_github_airutech_cnets_readerWriter *that);
void com_github_airutech_cnets_readerWriter_initialize(com_github_airutech_cnets_readerWriter *that){
  com_github_airutech_cnets_readerWriter_onCreate(that);
}

void com_github_airutech_cnets_readerWriter_deinitialize(struct com_github_airutech_cnets_readerWriter *that){
  com_github_airutech_cnets_readerWriter_onDestroy(that);
}
/*[[[end]]] (checksum: ab7daffd3cfb8978936159bd8c620083)*/

void com_github_airutech_cnets_readerWriter_onCreate(com_github_airutech_cnets_readerWriter *that){
  
  return;
}

void com_github_airutech_cnets_readerWriter_onDestroy(com_github_airutech_cnets_readerWriter *that){
  
  return;
}

void com_github_airutech_cnets_readerWriter_onKernels(com_github_airutech_cnets_readerWriter *that){
  
  return;
}

/*********WRITER FUNCTIONS**********/

writer writerNULL(){
  writer r;
  r.params.target = NULL;
  return r;
}

void* com_github_airutech_cnets_readerWriter_writeNext(writer *that, int waitThreshold) {
  if(that == NULL || that->params.target == NULL){return 0;}
  /*todo: add here special code for debuging data flow*/
  return that->params.writeNext(&that->params, waitThreshold);
}

int com_github_airutech_cnets_readerWriter_writeFinished(writer *that) {
  if(that == NULL || that->params.target == NULL){return 0;}
  /*todo: add here special code for debuging data flow*/
  uint64_t interval = statsCollectorStatic_getStatsInterval();
  if(interval > 0) {
    if (that->statsWriterParams.target == 0) {
      that->statsWriterParams = (statsCollectorStatic_getWriter()).params;
    }
    struct writer statsWriter;
    writer_init(&statsWriter, that->statsWriterParams);
    if (statsWriter.params.target != 0 && statsWriter.uniqueId(&statsWriter) != that->uniqueId(that)) {
      that->packetsCounter++;
      uint64_t curTime = curTimeMilisec();
      if (curTime - that->statsTime > interval) {
        com_github_airutech_cnets_types_statsLocalProtocol* p;
        p = (com_github_airutech_cnets_types_statsLocalProtocol*) statsWriter.writeNext(&statsWriter,0);
        if (p != 0) {
          p->writer = TRUE;
          p->uniqueId = that->uniqueId(that);
          p->gridId = that->params.grid_id;
          p->packets = that->packetsCounter;
          p->bytes = that->bytesCounter;
          statsWriter.writeFinished(&statsWriter);
          that->statsTime = curTime;
          that->packetsCounter = 0;
          that->bytesCounter = 0;
        }
      }
    }
  }
  return that->params.writeFinished(&that->params);
}

int com_github_airutech_cnets_readerWriter_sizeW(writer *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.size(&that->params);
}

int com_github_airutech_cnets_readerWriter_timeoutW(writer *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.timeout(&that->params);
}

int com_github_airutech_cnets_readerWriter_gridSizeW(writer *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.gridSize(&that->params); 
}

int com_github_airutech_cnets_readerWriter_uniqueIdW(writer *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.uniqueId(&that->params);
}

void com_github_airutech_cnets_readerWriter_incrementBytesCounterW(writer *that, int bytesCounter) {
  if (statsCollectorStatic_getStatsInterval() > 0) {
    that->bytesCounter += bytesCounter;
  }
}

/*********READER FUNCTIONS**********/

reader readerNULL(){
  reader r;
  r.params.target = NULL;
  return r;
}

bufferReadData com_github_airutech_cnets_readerWriter_readNextWithMeta(reader *that, int waitThreshold) {
  bufferReadData res;
  res.data = NULL;
  if(that == NULL || that->params.target == NULL){return res;}
  /*todo: add here special code for debuging data flow*/
  return that->params.readNextWithMeta(&that->params, waitThreshold);
}

void* com_github_airutech_cnets_readerWriter_readNext(reader *that, int waitThreshold) {
  if(that == NULL || that->params.target == NULL){return 0;}
  /*todo: add here special code for debuging data flow*/
  return that->params.readNext(&that->params, waitThreshold);
}

int com_github_airutech_cnets_readerWriter_readFinished(reader *that) {
  if(that == NULL || that->params.target == NULL){return 0;}
  /*todo: add here special code for debuging data flow*/
  uint64_t interval = statsCollectorStatic_getStatsInterval();
  if(interval > 0) {
    if (that->statsWriterParams.target == 0) {
      that->statsWriterParams = (statsCollectorStatic_getWriter()).params;
    }
    struct writer statsWriter;
    writer_init(&statsWriter, that->statsWriterParams);
    if (statsWriter.params.target != 0 && statsWriter.uniqueId(&statsWriter) != that->uniqueId(that)) {
      that->packetsCounter++;
      uint64_t curTime = curTimeMilisec();
      if (curTime - that->statsTime > interval) {
        com_github_airutech_cnets_types_statsLocalProtocol* p;
        p = (com_github_airutech_cnets_types_statsLocalProtocol*) statsWriter.writeNext(&statsWriter,0);
        if (p != 0) {
          p->writer = FALSE;
          p->uniqueId = that->uniqueId(that);
          p->gridId = that->params.grid_id;
          p->packets = that->packetsCounter;
          p->bytes = that->bytesCounter;
          statsWriter.writeFinished(&statsWriter);
          that->statsTime = curTime;
          that->packetsCounter = 0;
          that->bytesCounter = 0;
        }
      }
    }
  }
  return that->params.readFinished(&that->params);
}

int com_github_airutech_cnets_readerWriter_sizeR(reader *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.size(&that->params);
}

int com_github_airutech_cnets_readerWriter_timeoutR(reader *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.timeout(&that->params);
}

int com_github_airutech_cnets_readerWriter_gridSizeR(reader *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.gridSize(&that->params); 
}

int com_github_airutech_cnets_readerWriter_uniqueIdR(reader *that){
  if(that == NULL || that->params.target == NULL){return 0;}
  return that->params.uniqueId(&that->params);
}

void com_github_airutech_cnets_readerWriter_incrementBytesCounterR(reader *that, int bytesCounter) {
  if (statsCollectorStatic_getStatsInterval() > 0) {
    that->bytesCounter += bytesCounter;
  }
}

int com_github_airutech_cnets_readerWriter_addSelector(reader *that,linkedContainer *container){
  if(that == NULL || that->params.target == NULL){return -1;}
  return that->params.addSelector(&that->params, (void*)container);
} 

/****STRUCTURES INITIALIZATIONS***/

void writer_init(writer *that, bufferKernelParams params){
  if(that == NULL || params.target == NULL){
    printf("writer_init that or params->target is NULL\n");
    return;
  }
  that->packetsCounter = 0;
  that->bytesCounter = 0;
  that->statsTime = 0;
  that->statsWriterParams.target = 0;
  that->params = params;
  that->writeNext = com_github_airutech_cnets_readerWriter_writeNext;
  that->writeFinished = com_github_airutech_cnets_readerWriter_writeFinished;
  that->size = com_github_airutech_cnets_readerWriter_sizeW;
  that->timeout = com_github_airutech_cnets_readerWriter_timeoutW;
  that->gridSize = com_github_airutech_cnets_readerWriter_gridSizeW;
  that->uniqueId = com_github_airutech_cnets_readerWriter_uniqueIdW;
  that->incrementBytesCounter = com_github_airutech_cnets_readerWriter_incrementBytesCounterW;
  return;
}

void reader_init(reader *that, bufferKernelParams params){
  if(that == NULL || params.target == NULL){
    printf("reader_init that or params->target is NULL\n");
    return;
  }
  that->packetsCounter = 0;
  that->bytesCounter = 0;
  that->statsTime = 0;
  that->statsWriterParams.target = 0;
  that->params = params;
  that->readNextWithMeta = com_github_airutech_cnets_readerWriter_readNextWithMeta;
  that->readNext = com_github_airutech_cnets_readerWriter_readNext;
  that->readFinished = com_github_airutech_cnets_readerWriter_readFinished;
  that->size = com_github_airutech_cnets_readerWriter_sizeR;
  that->timeout = com_github_airutech_cnets_readerWriter_timeoutR;
  that->gridSize = com_github_airutech_cnets_readerWriter_gridSizeR;
  that->uniqueId = com_github_airutech_cnets_readerWriter_uniqueIdR;
  that->incrementBytesCounter = com_github_airutech_cnets_readerWriter_incrementBytesCounterR;
  that->addSelector = com_github_airutech_cnets_readerWriter_addSelector;
  return;
}

void com_github_airutech_cnets_readerWriter_addContainer(struct linkedContainer *that, struct linkedContainer *added){
  if(that == NULL){
    printf("com_github_airutech_cnets_readerWriter_addContainer that is NULL\n");
    return;
  }
  if(that->next != NULL){
    that->next->add(that->next,added);
  }else{
    that->next = added;
    added->prev = that;
  }
}

void com_github_airutech_cnets_readerWriter_removeContainer(struct linkedContainer *that){
  if(that == NULL){
    printf("com_github_airutech_cnets_readerWriter_removeContainer that is NULL\n");
    return;
  }
  if(that->prev != NULL){
    that->prev->next = that->next;
  }
  if(that->next != NULL){        
    that->next->prev = that->prev;
  }
}

void com_github_airutech_cnets_readerWriter_callContainer(struct linkedContainer *that){
  if(that == NULL){
    printf("com_github_airutech_cnets_readerWriter_callContainer that is NULL\n");
    return;
  }
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
  that->add = com_github_airutech_cnets_readerWriter_addContainer;
  that->remove = com_github_airutech_cnets_readerWriter_removeContainer;
  that->call = com_github_airutech_cnets_readerWriter_callContainer;
}