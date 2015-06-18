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
    uint32_t _numberOfKernels,
    uint32_t _startLocalId,
    reader _rids0){
  
  that->parent = _parent;
  that->threadId = _threadId;
  that->numberOfKernels = _numberOfKernels;
  that->startLocalId = _startLocalId;
  that->_kernelId = dispatcherCollector_getNextLocalId();
  that->runObjects = arrayObject_init_dynamic(sizeof(RunnableStoppable), that->numberOfKernels);
  int runObjects_i_ = 0;
  for(runObjects_i_=0;runObjects_i_<that->numberOfKernels;runObjects_i_++){
    RunnableStoppable_init(&((RunnableStoppable*)that->runObjects.array)[runObjects_i_]);
  }
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
  
  arrayObject_free_dynamic(that->runObjects);
}

/*[[[end]]] (checksum: d6b739241f342ce4b6da72767199b30d)*/

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_run(void *t){
  struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com*)t;
  uint32_t* idPtr = (uint32_t*)that->rids0.readNext(&that->rids0, -1);
  if(idPtr){
    uint32_t id = *idPtr;
    unsigned index = id - that->startLocalId;
    if(index >= that->numberOfKernels){
      fprintf(stderr, "ERROR: dispatcher_dispatchKernel_cnets_osblinnikov_github_com_run: index >= that->numberOfKernels: id=%d startLocalId=%d\n",id,that->startLocalId);
    }else{
#ifdef _DEBUG
      if(!((RunnableStoppable*)that->runObjects.array)[index].run || !((RunnableStoppable*)that->runObjects.array)[index].target){
        fprintf(stderr, "ERROR: dispatcher_dispatchKernel_cnets_osblinnikov_github_com_run: !((RunnableStoppable*)that->runObjects.array)[index].run || !((RunnableStoppable*)that->runObjects.array)[index].target: id=%d startLocalId=%d\n",id,that->startLocalId);
      }
#endif
      ((RunnableStoppable*)that->runObjects.array)[index].run(((RunnableStoppable*)that->runObjects.array)[index].target);
    }
    that->rids0.readFinished(&that->rids0);
  }
}

void callRunnableObjects(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that,
                         struct runnablesContainer_cnets_osblinnikov_github_com *runnables,
                         BOOL doStart,
                         BOOL doStop,
                         BOOL doFill){
  if(runnables->containers != NULL && runnables->containers_size > 0){
    int i;
    for(i=0; i< runnables->containers_size; i++){
      callRunnableObjects(that, &runnables->containers[i],doStart,doStop,doFill);
    }
  }else if(runnables->target.target != NULL){
    if(runnables->spawnMode == 0
       && runnables->id >= that->startLocalId
       && runnables->id < that->numberOfKernels+that->startLocalId
    ){
      if(doStart){
        runnables->target.onStart(runnables->target.target);
      }else if(doStop){
        runnables->target.onStop(runnables->target.target);
      }else if(doFill){
        unsigned index = runnables->id - that->startLocalId;
        if(index >= that->numberOfKernels){
          fprintf(stderr, "ERROR: callRunnableObjects: index >= that->numberOfKernels: id=%d startLocalId=%d\n",id,that->startLocalId);
        }else{
#ifdef _DEBUG
          printf("DEBUG: callRunnableObjects: numberOfKernels=%d: index=%d <-> id=%d\n", that->numberOfKernels, index, runnables->id);
#endif
          ((RunnableStoppable*)that->runObjects.array)[index] = runnables->target;
        }
      }
    }
  }else{
    fprintf(stderr, "ERROR: callRunnableObjects: no containers and no target found in runnable\n");
  }
}

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onStart(void *t){
  /*struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com*)t;*/
  struct runnablesContainer_cnets_osblinnikov_github_com runnables = that->parent.getRunnables(&that->parent);
  callRunnableObjects(that,&runnables, TRUE, FALSE, TRUE);
}

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onStop(void *that){
  /*struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com*)t;*/
  struct runnablesContainer_cnets_osblinnikov_github_com runnables = that->parent.getRunnables(&that->parent);
  callRunnableObjects(that,&runnables, FALSE, TRUE, FALSE);
}

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onCreate(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that){
  that->rids0.dispatchWriter = NULL;
  that->rids0.params.grid_id = that->threadId;
  return;
}

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onDestroy(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that){
  
  return;
}

void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_onKernels(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that){
  
  return;
}
