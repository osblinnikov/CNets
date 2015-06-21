#ifndef readerWriter_cnets_osblinnikov_github_com_reader_H
#define readerWriter_cnets_osblinnikov_github_com_reader_H

#include "./linkedContainer.h"
#include "./Exports.h"

typedef struct reader{
  struct bufferReadData *readData;
  BOOL hasReadNext;
  unsigned packetsCounter, bytesCounter;
  uint64_t statsTime, interval;
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
  void (*setReadData)(struct reader *that, struct bufferReadData *readData);
}reader;

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
void reader_init_with_params(struct reader *that, bufferKernelParams params);

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
void reader_init(reader *that);

#define reader_create(_NAME_,params)\
    reader _NAME_;\
    reader_init_with_params(&_NAME_,params);

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  reader readerNULL();

#endif /* readerWriter_cnets_osblinnikov_github_com_reader_H */
