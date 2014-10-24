#ifndef com_github_airutech_cnets_readerWriter_linkedContainer_H
#define com_github_airutech_cnets_readerWriter_linkedContainer_H

#include "./writer.h"

typedef struct linkedContainer{
  struct linkedContainer *next;
  struct linkedContainer *prev;
  struct writer w;
  void (*add)(struct linkedContainer *that, struct linkedContainer *added);
  void (*remove)(struct linkedContainer *that);
  void (*call)(struct linkedContainer *that);
}linkedContainer;

com_github_airutech_cnets_readerWriter_EXPORT_API
void linkedContainer_init(struct linkedContainer *that, struct writer w);

#define linkedContainer_create(_NAME_,_writer_)\
    linkedContainer _NAME_;\
    linkedContainer_init(&_NAME_,_writer_);

#endif /* com_github_airutech_cnets_readerWriter_linkedContainer_H */