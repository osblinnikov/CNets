#ifndef com_github_osblinnikov_cnets_runnablesContainer_RunnableStoppable_H
#define com_github_osblinnikov_cnets_runnablesContainer_RunnableStoppable_H

#include "github.com/osblinnikov/cnets/types/types.h"

typedef struct RunnableStoppable{
  void *target;
  void (*onStart)(void* target);
  void (*run)(void* target);
  void (*onStop)(void* target);
}RunnableStoppable;

#define RunnableStoppable_create(_NAME_,_target, fullName_)\
    RunnableStoppable _NAME_;\
    _NAME_.target = (void*)_target;\
    _NAME_.onStart = fullName_##onStart;\
    _NAME_.run = fullName_##run;\
    _NAME_.onStop = fullName_##onStop;

#endif /* com_github_osblinnikov_cnets_runnablesContainer_RunnableStoppable_H */