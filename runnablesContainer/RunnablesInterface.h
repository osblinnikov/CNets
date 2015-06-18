#ifndef runnablesContainer_cnets_osblinnikov_github_com_RunnablesInterface_H
#define runnablesContainer_cnets_osblinnikov_github_com_RunnablesInterface_H

#include "./runnablesContainer.h"


typedef struct runnablesContainer_cnets_osblinnikov_github_com (*getRunnablesFunc)(struct RunnablesInterface *params);

typedef struct RunnablesInterface{
  void* target;
  getRunnablesFunc getRunnables;
}RunnablesInterface;

void RunnablesInterface_init(struct RunnablesInterface* that){
  that->target = NULL;
  that->getRunnables = NULL;
}

void RunnablesInterface_set(struct RunnablesInterface* that, void* target, getRunnablesFunc func ){
  that->target = target;
  that->getRunnables = func;
}

#endif /* runnablesContainer_cnets_osblinnikov_github_com_RunnablesInterface_H */
