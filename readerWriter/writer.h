#ifndef com_github_osblinnikov_cnets_readerWriter_writer_H
#define com_github_osblinnikov_cnets_readerWriter_writer_H

typedef struct writer{
  unsigned packetsCounter, bytesCounter;
  uint64_t statsTime;
  struct bufferKernelParams statsWriterParams;
  struct bufferKernelParams params;
  void* (*writeNext)(struct writer *that, int waitThreshold);
  int (*writeFinished)(struct writer *that);
  int (*size)(struct writer *that);
  int (*timeout)(struct writer *that);
  int (*gridSize)(struct writer *that);
  int (*uniqueId)(struct writer *that);
  void (*incrementBytesCounter)(struct writer *that, int bytesCounter);
}writer;

com_github_osblinnikov_cnets_readerWriter_EXPORT_API
  void writer_init(struct writer *that, bufferKernelParams params);

#define writer_create(_NAME_,params)\
    writer _NAME_;\
    writer_init(&_NAME_,params);

com_github_osblinnikov_cnets_readerWriter_EXPORT_API
  writer writerNULL();

#endif /* com_github_osblinnikov_cnets_readerWriter_writer_H */