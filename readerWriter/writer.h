#ifndef readerWriter_cnets_osblinnikov_github_com_writer_H
#define readerWriter_cnets_osblinnikov_github_com_writer_H

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

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  void writer_init(struct writer *that, bufferKernelParams params);

#define writer_create(_NAME_,params)\
    writer _NAME_;\
    writer_init(&_NAME_,params);

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  writer writerNULL();

#endif /* readerWriter_cnets_osblinnikov_github_com_writer_H */