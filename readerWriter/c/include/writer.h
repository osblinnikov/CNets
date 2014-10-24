#ifndef com_github_airutech_cnets_readerWriter_writer_H
#define com_github_airutech_cnets_readerWriter_writer_H

typedef struct writer{
  bufferKernelParams params;
  void* (*writeNext)(struct writer *that, BOOL make_timeout);
  int (*writeFinished)(struct writer *that);
  int (*size)(struct writer *that);
  int (*timeout)(struct writer *that);
  int (*gridSize)(struct writer *that);
  int (*uniqueId)(struct writer *that);
}writer;

com_github_airutech_cnets_readerWriter_EXPORT_API
  void writer_init(struct writer *that, bufferKernelParams params);

#define writer_create(_NAME_,params)\
    writer _NAME_;\
    writer_init(&_NAME_,params);

com_github_airutech_cnets_readerWriter_EXPORT_API
  writer writerNULL();

#endif /* com_github_airutech_cnets_readerWriter_writer_H */