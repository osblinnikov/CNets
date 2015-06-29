#ifndef readerWriter_cnets_osblinnikov_github_com_linkedContainer_H
#define readerWriter_cnets_osblinnikov_github_com_linkedContainer_H

#include "./writer.h"
#include "./reader.h"

typedef struct linkedContainer{
  struct linkedContainer *next;
  struct linkedContainer *prev;
  struct writer w;
  struct reader r;
  void (*add)(struct linkedContainer *that, struct linkedContainer *added);
  void (*remove)(struct linkedContainer *that);
  void (*call)(struct linkedContainer *that);
  void (*reverseCall)(struct linkedContainer *that);
}linkedContainer;

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
void linkedContainer_init(struct linkedContainer *that, struct writer w, struct reader r);

#define linkedContainer_create(_NAME_,_writer_,_reader_)\
    linkedContainer _NAME_;\
    linkedContainer_init(&_NAME_,_writer_,_reader_);

#endif /* readerWriter_cnets_osblinnikov_github_com_linkedContainer_H */
