/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../topology.h"
#include <stdlib.h>

void topology_replicator_cnets_osblinnikov_github_com_run(void *that);
void topology_replicator_cnets_osblinnikov_github_com_onStart(void *that);
void topology_replicator_cnets_osblinnikov_github_com_onStop(void *that);
void topology_replicator_cnets_osblinnikov_github_com_onCreate(struct topology_replicator_cnets_osblinnikov_github_com *that);
void topology_replicator_cnets_osblinnikov_github_com_onDestroy(struct topology_replicator_cnets_osblinnikov_github_com *that);
void topology_replicator_cnets_osblinnikov_github_com_onKernels(struct topology_replicator_cnets_osblinnikov_github_com *that);
struct arrayObject topology_replicator_cnets_osblinnikov_github_com_getReaders(void *t);

struct runnablesContainer_cnets_osblinnikov_github_com topology_replicator_cnets_osblinnikov_github_com_getRunnables(struct topology_replicator_cnets_osblinnikov_github_com *that){
  return that->_runnables;
}

struct arrayObject topology_replicator_cnets_osblinnikov_github_com_getReaders(void *t){
  struct topology_replicator_cnets_osblinnikov_github_com *that = (struct topology_replicator_cnets_osblinnikov_github_com*)t;
  return arrayObjectNULL();
}


void topology_replicator_cnets_osblinnikov_github_com_init(struct topology_replicator_cnets_osblinnikov_github_com *that,
    runnablesContainer_cnets_osblinnikov_github_com* _parent,
    uint32_t _maxNumberOfKernelsPerThread,
    uint32_t _countOfThreads,
    char* _bindTo){
  
  that->parent = _parent;
  that->maxNumberOfKernelsPerThread = _maxNumberOfKernelsPerThread;
  that->countOfThreads = _countOfThreads;
  that->bindTo = _bindTo;
  
  topology_replicator_cnets_osblinnikov_github_com_onKernels(that);
  
  that->kernel0 = (dispatchKernel_cnets_osblinnikov_github_com*)malloc(sizeof(dispatchKernel_cnets_osblinnikov_github_com)*that->countOfThreads);
  int _kernel0_i;
  for(_kernel0_i=0;_kernel0_i<(int)that->countOfThreads;_kernel0_i++){
    dispatchKernel_cnets_osblinnikov_github_com_init(&that->kernel0[_kernel0_i],that->parent,that->maxNumberOfKernelsPerThread,_kernel0_i,that->countOfThreads);
  }
  that->arrContainers = (runnablesContainer_cnets_osblinnikov_github_com*)malloc(sizeof(runnablesContainer_cnets_osblinnikov_github_com)*(0+that->countOfThreads));
  that->getRunnables = topology_replicator_cnets_osblinnikov_github_com_getRunnables;
  
    runnablesContainer_cnets_osblinnikov_github_com_init(&that->_runnables);
    
    int j;
    for(j=0;j<(int)that->countOfThreads;j++){
      that->arrContainers[0+j] = that->kernel0[j].getRunnables(&that->kernel0[j]);
    }

    arrayObject arr;
    arr.array = (void*)that->arrContainers;
    arr.length = 0+that->countOfThreads;
    arr.itemSize = sizeof(runnablesContainer_cnets_osblinnikov_github_com);
    that->_runnables.setContainers(&that->_runnables,arr);
    /*set core to call onStart/onStop from runnablesContainer*/
    RunnableStoppable_create(runnableStoppableObj,that, topology_replicator_cnets_osblinnikov_github_com)
    that->_runnables.setCore(&that->_runnables,runnableStoppableObj, (unsigned)-1);
  topology_replicator_cnets_osblinnikov_github_com_onCreate(that);
}

void topology_replicator_cnets_osblinnikov_github_com_deinit(struct topology_replicator_cnets_osblinnikov_github_com *that){
  topology_replicator_cnets_osblinnikov_github_com_onDestroy(that);
  
  int _kernel0_i;
  for(_kernel0_i=0;_kernel0_i<(int)that->countOfThreads;_kernel0_i++){
    dispatchKernel_cnets_osblinnikov_github_com_deinit(&that->kernel0[_kernel0_i]);
  }
  free((void*)that->kernel0);
  free((void*)that->arrContainers);
}

/*[[[end]]] (checksum: c09b538244cbd355313b9e25a385a0e9)*/

void topology_replicator_cnets_osblinnikov_github_com_run(void *t){
  /*struct topology_replicator_cnets_osblinnikov_github_com *that = (struct topology_replicator_cnets_osblinnikov_github_com*)t;*/
}

void topology_replicator_cnets_osblinnikov_github_com_onStart(void *t){
  /*struct topology_replicator_cnets_osblinnikov_github_com *that = (struct topology_replicator_cnets_osblinnikov_github_com*)t;*/
}

void topology_replicator_cnets_osblinnikov_github_com_onStop(void *t){
  /*struct topology_replicator_cnets_osblinnikov_github_com *that = (struct topology_replicator_cnets_osblinnikov_github_com*)t;*/
}

void topology_replicator_cnets_osblinnikov_github_com_onCreate(struct topology_replicator_cnets_osblinnikov_github_com *that){
  
  return;
}

void topology_replicator_cnets_osblinnikov_github_com_onDestroy(struct topology_replicator_cnets_osblinnikov_github_com *that){
  
  return;
}

void topology_replicator_cnets_osblinnikov_github_com_onKernels(struct topology_replicator_cnets_osblinnikov_github_com *that){
  
  return;
}
