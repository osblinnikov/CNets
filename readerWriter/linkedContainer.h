#ifndef readerWriter_cnets_osblinnikov_github_com_linkedContainer_H
#define readerWriter_cnets_osblinnikov_github_com_linkedContainer_H

#include "./writer.h"

typedef struct linkedContainer{
  struct linkedContainer *next;
  struct linkedContainer *prev;
  struct writer w;
  void (*add)(struct linkedContainer *that, struct linkedContainer *added);
  void (*remove)(struct linkedContainer *that);
  void (*call)(struct linkedContainer *that);
}linkedContainer;

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
void linkedContainer_init(struct linkedContainer *that, struct writer w);

#define linkedContainer_create(_NAME_,_writer_)\
    linkedContainer _NAME_;\
    linkedContainer_init(&_NAME_,_writer_);

#endif /* readerWriter_cnets_osblinnikov_github_com_linkedContainer_H */