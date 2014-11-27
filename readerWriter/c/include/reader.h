#ifndef com_github_airutech_cnets_readerWriter_reader_H
#define com_github_airutech_cnets_readerWriter_reader_H

#include "./linkedContainer.h"

typedef struct reader{
  unsigned packetsCounter, bytesCounter;
  uint64_t statsTime;
  struct bufferKernelParams statsWriterParams;
  struct bufferKernelParams params;
  bufferReadData (*readNextWithMeta)(struct reader *that, int waitThreshold);
  void* (*readNext)(struct reader *that, int waitThreshold);
  int (*readFinished)(struct reader *that);
  int (*size)(struct reader *that);
  int (*timeout)(struct reader *that);
  int (*gridSize)(struct reader *that);
  int (*uniqueId)(struct reader *that);
  void (*incrementBytesCounter)(struct reader *that, int bytesCounter);
  int (*addSelector)(struct reader *that, linkedContainer *selectorContainer);
}reader;

com_github_airutech_cnets_readerWriter_EXPORT_API
void reader_init(struct reader *that, bufferKernelParams params);

#define reader_create(_NAME_,params)\
    reader _NAME_;\
    reader_init(&_NAME_,params);

com_github_airutech_cnets_readerWriter_EXPORT_API
  reader readerNULL();

#endif /* com_github_airutech_cnets_readerWriter_reader_H */