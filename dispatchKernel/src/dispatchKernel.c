/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../dispatchKernel.h"
#include <stdlib.h>

void dispatchKernel_cnets_osblinnikov_github_com_run(void *that);
void dispatchKernel_cnets_osblinnikov_github_com_onStart(void *that);
void dispatchKernel_cnets_osblinnikov_github_com_onStop(void *that);
void dispatchKernel_cnets_osblinnikov_github_com_onCreate(struct dispatchKernel_cnets_osblinnikov_github_com *that);
void dispatchKernel_cnets_osblinnikov_github_com_onDestroy(struct dispatchKernel_cnets_osblinnikov_github_com *that);
void dispatchKernel_cnets_osblinnikov_github_com_onKernels(struct dispatchKernel_cnets_osblinnikov_github_com *that);

struct runnablesContainer_cnets_osblinnikov_github_com dispatchKernel_cnets_osblinnikov_github_com_getRunnables(struct dispatchKernel_cnets_osblinnikov_github_com *that){
  return that->_runnables;
}

struct runnablesContainer_cnets_osblinnikov_github_com dispatchKernel_cnets_osblinnikov_github_com_getRunnablesForInterface(struct RunnablesInterface *ptr){
  struct dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatchKernel_cnets_osblinnikov_github_com*)ptr->target;
  return that->_runnables;
}

void dispatchKernel_cnets_osblinnikov_github_com_init(struct dispatchKernel_cnets_osblinnikov_github_com *that,
    RunnablesInterface _parent,
    uint32_t _threads,
    int64_t _timeout){
  
  that->parent = _parent;
  that->threads = _threads;
  that->timeout = _timeout;
  that->numberOfKernels = dispatcherCollector_getLocalId()-dispatcherCollector_getStartLocalId();
  that->buffersArr = arrayObject_init_dynamic(sizeof(vector_cnets_osblinnikov_github_com), that->numberOfKernels);
  int buffersArr_i_ = 0;
  for(buffersArr_i_=0;buffersArr_i_<that->numberOfKernels;buffersArr_i_++){
    vector_cnets_osblinnikov_github_com_init(&((vector_cnets_osblinnikov_github_com*)that->buffersArr.array)[buffersArr_i_]);
  }
  
  dispatchBuffer_cnets_osblinnikov_github_com_init(&that->ids,that->buffersArr,that->timeout,dispatcherCollector_getStartLocalId(),that->threads);
  reader idsr0_0 = dispatchBuffer_cnets_osblinnikov_github_com_createReader(&that->ids,0);
  dispatchKernel_cnets_osblinnikov_github_com_onKernels(that);
  
  that->kernel0 = (dispatcher_dispatchKernel_cnets_osblinnikov_github_com*)malloc(sizeof(dispatcher_dispatchKernel_cnets_osblinnikov_github_com)*that->threads);
  int _kernel0_i;
  for(_kernel0_i=0;_kernel0_i<(int)that->threads;_kernel0_i++){
    dispatcher_dispatchKernel_cnets_osblinnikov_github_com_init(&that->kernel0[_kernel0_i],that->parent,_kernel0_i,idsr0_0);
  }
  that->arrContainers = (runnablesContainer_cnets_osblinnikov_github_com*)malloc(sizeof(runnablesContainer_cnets_osblinnikov_github_com)*(0+that->threads));
  that->getRunnables = dispatchKernel_cnets_osblinnikov_github_com_getRunnables;
  
    runnablesContainer_cnets_osblinnikov_github_com_init(&that->_runnables);
    
    int j;
    for(j=0;j<(int)that->threads;j++){
      that->arrContainers[0+j] = that->kernel0[j].getRunnables(&that->kernel0[j]);
    }

    arrayObject arr;
    arr.array = (void*)that->arrContainers;
    arr.length = 0+that->threads;
    arr.itemSize = sizeof(runnablesContainer_cnets_osblinnikov_github_com);
    that->_runnables.setContainers(&that->_runnables,arr);
    /*set core to call onStart/onStop from runnablesContainer*/
    RunnableStoppable_create(runnableStoppableObj,that, dispatchKernel_cnets_osblinnikov_github_com_)
    that->_runnables.setCore(&that->_runnables,runnableStoppableObj, (unsigned)-1, -1);
  dispatchKernel_cnets_osblinnikov_github_com_onCreate(that);
}

void dispatchKernel_cnets_osblinnikov_github_com_deinit(struct dispatchKernel_cnets_osblinnikov_github_com *that){
  dispatchKernel_cnets_osblinnikov_github_com_onDestroy(that);
  
  arrayObject_free_dynamic(that->buffersArr);
  dispatchBuffer_cnets_osblinnikov_github_com_deinit(&that->ids);
  int _kernel0_i;
  for(_kernel0_i=0;_kernel0_i<(int)that->threads;_kernel0_i++){
    dispatcher_dispatchKernel_cnets_osblinnikov_github_com_deinit(&that->kernel0[_kernel0_i]);
  }
  free((void*)that->kernel0);
  free((void*)that->arrContainers);
}

/*[[[end]]] (checksum: 7d224c418479fad85d9a7b5ebe3bcc28)*/

void dispatchKernel_cnets_osblinnikov_github_com_run(void *t){
  /*struct dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatchKernel_cnets_osblinnikov_github_com*)t;*/
}

void dispatchKernel_cnets_osblinnikov_github_com_onStart(void *t){
  /*struct dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatchKernel_cnets_osblinnikov_github_com*)t;*/
}

void dispatchKernel_cnets_osblinnikov_github_com_onStop(void *that){
  /*struct dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatchKernel_cnets_osblinnikov_github_com*)t;*/
}

void dispatchKernel_cnets_osblinnikov_github_com_onCreate(struct dispatchKernel_cnets_osblinnikov_github_com *that){
  dispatcherCollector_tagAsStartLocalId();
  dispatcherCollector_addWriter(dispatchBuffer_cnets_osblinnikov_github_com_createWriter(&that->dispatcher, 0));
}

void dispatchKernel_cnets_osblinnikov_github_com_onDestroy(struct dispatchKernel_cnets_osblinnikov_github_com *that){
  
  return;
}

void dispatchKernel_cnets_osblinnikov_github_com_onKernels(struct dispatchKernel_cnets_osblinnikov_github_com *that){
  
  return;
}
