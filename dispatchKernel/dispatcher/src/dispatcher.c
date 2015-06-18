/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../dispatcher.h"
#include <stdlib.h>

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_run(void *that);
void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onStart(void *that);
void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onStop(void *that);
void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onCreate(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that);
void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onDestroy(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that);
void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onKernels(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that);

struct runnablesContainer_cnets_osblinnikov_github_com dispatcher_dispatchKernel_cnets_osblinnikov_github_com_getRunnables(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that){
  return that->_runnables;
}

struct runnablesContainer_cnets_osblinnikov_github_com dispatcher_dispatchKernel_cnets_osblinnikov_github_com_getRunnablesForInterface(struct RunnablesInterface *ptr){
  struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com*)ptr->target;
  return that->_runnables;
}

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_init(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that,
    RunnablesInterface _parent,
    uint32_t _threadId,
    reader _rids0){
  
  that->parent = _parent;
  that->threadId = _threadId;
  that->_kernelId = dispatcherCollector_getNextLocalId();
  that->rids0 = _rids0;
  that->rids0.setKernelId(&that->rids0, that->_kernelId);
  
  dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onKernels(that);
  
  that->getRunnables = dispatcher_dispatchKernel_cnets_osblinnikov_github_com_getRunnables;
  
    runnablesContainer_cnets_osblinnikov_github_com_init(&that->_runnables);
    RunnableStoppable_create(runnableStoppableObj,that, dispatcher_dispatchKernel_cnets_osblinnikov_github_com_)
    that->_runnables.setCore(&that->_runnables,runnableStoppableObj, that->_kernelId, 0);
  dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onCreate(that);
}

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_deinit(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that){
  dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onDestroy(that);
  
}

/*[[[end]]] (checksum: 5c5db3f8bf83d6c07732714a8f5939ca)*/

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_run(void *t){
  /*struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com*)t;*/
}

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onStart(void *t){
  /*struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com*)t;*/
}

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onStop(void *that){
  /*struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com*)t;*/
}

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onCreate(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that){
  that->rids0.dispatchWriter = NULL;
  return;
}

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onDestroy(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that){
  
  return;
}

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onKernels(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that){
  
  return;
}
