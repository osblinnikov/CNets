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
struct arrayObject dispatchKernel_cnets_osblinnikov_github_com_getReaders(void *t);
void dispatchKernel_cnets_osblinnikov_github_com_setReadData(void *t, bufferReadData *readData);

struct runnablesContainer_cnets_osblinnikov_github_com dispatchKernel_cnets_osblinnikov_github_com_getRunnables(struct dispatchKernel_cnets_osblinnikov_github_com *that){
  return that->_runnables;
}

struct arrayObject dispatchKernel_cnets_osblinnikov_github_com_getReaders(void *t){
  struct dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatchKernel_cnets_osblinnikov_github_com*)t;
  return arrayObjectNULL();
}


void dispatchKernel_cnets_osblinnikov_github_com_setReadData(void *t, bufferReadData *readData){
  if(t == NULL || readData == NULL){return;}
  struct dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatchKernel_cnets_osblinnikov_github_com*)t;
  
}


void dispatchKernel_cnets_osblinnikov_github_com_init(struct dispatchKernel_cnets_osblinnikov_github_com *that,
    runnablesContainer_cnets_osblinnikov_github_com* _parent,
    uint32_t _maxNumberOfKernels,
    uint32_t _threadId,
    uint32_t _countOfThreads){
  
  that->parent = _parent;
  that->maxNumberOfKernels = _maxNumberOfKernels;
  that->threadId = _threadId;
  that->countOfThreads = _countOfThreads;
  that->readers = arrayObject_init_dynamic(sizeof(reader), 1);
  int readers_i_ = 0;
  for(readers_i_=0;readers_i_<1;readers_i_++){
    reader_init(&((reader*)that->readers.array)[readers_i_]);
  }
  reader_init(&that->readerSelector);
  that->kernels = arrayObject_init_dynamic(sizeof(runnables_dispatchKernel_cnets_osblinnikov_github_com), 1);
  int kernels_i_ = 0;
  for(kernels_i_=0;kernels_i_<1;kernels_i_++){
    runnables_dispatchKernel_cnets_osblinnikov_github_com_init(&((runnables_dispatchKernel_cnets_osblinnikov_github_com*)that->kernels.array)[kernels_i_]);
  }
  
  dispatchKernel_cnets_osblinnikov_github_com_onKernels(that);
  
  that->getRunnables = dispatchKernel_cnets_osblinnikov_github_com_getRunnables;
  
    runnablesContainer_cnets_osblinnikov_github_com_init(&that->_runnables);
    RunnableStoppable_create(runnableStoppableObj,that, dispatchKernel_cnets_osblinnikov_github_com)
    that->_runnables.setCore(&that->_runnables,runnableStoppableObj, 1);
  dispatchKernel_cnets_osblinnikov_github_com_onCreate(that);
}

void dispatchKernel_cnets_osblinnikov_github_com_deinit(struct dispatchKernel_cnets_osblinnikov_github_com *that){
  dispatchKernel_cnets_osblinnikov_github_com_onDestroy(that);
  
  arrayObject_free_dynamic(that->readers);
  arrayObject_free_dynamic(that->kernels);
}

/*[[[end]]] (checksum: 2c2e7e0101a8f9bf3d87a690a4b1e519)*/


void runnables_dispatchKernel_cnets_osblinnikov_github_com_init(runnables_dispatchKernel_cnets_osblinnikov_github_com* that){
  if(that == NULL){return;}
  RunnableStoppable_init(&that->r);
  that->startNumber = 0;
}


void dispatchKernel_cnets_osblinnikov_github_com_run(void *t){
  struct dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatchKernel_cnets_osblinnikov_github_com*)t;
  if(!that->readerSelector.params.target){taskDelayMilisec(1000L);return;}
  bufferReadData res = that->readerSelector.readNextWithMeta(&that->readerSelector,-1);

  if(res.data == NULL){
    printf("WARN: dispatchKernel_cnets_osblinnikov_github_com_run: timeout: %d %d %d \n", that->threadId, that->countOfThreads, that->readers.length);
    return;
  }
  runnables_dispatchKernel_cnets_osblinnikov_github_com* rs = &((runnables_dispatchKernel_cnets_osblinnikov_github_com*)that->kernels.array)[res.nested_buffer_id];

  res.nested_buffer_id -= rs->startNumber;
  rs->r.setReadData(rs->r.target, &res);
  rs->r.run(rs->r.target);
  that->readerSelector.readFinished(&that->readerSelector);
}

BOOL countKernels(struct dispatchKernel_cnets_osblinnikov_github_com* that,
                  struct runnablesContainer_cnets_osblinnikov_github_com* parent,
                  unsigned *count,
                  unsigned *countReaders,
                  BOOL fillReaders
){
  if(parent == NULL){return FALSE;}
  if(parent->containers != NULL && parent->containers_size > 0){
    for(int i=0; i< parent->containers_size; i++){
      if(!countKernels(that, &parent->containers[i], count, countReaders, fillReaders)){
        return FALSE;
      }
    }
  }else if(parent->target.target != NULL){
    if(that->maxNumberOfKernels != 0 && *count >= that->maxNumberOfKernels*(that->threadId+1)){
      if(that->countOfThreads == that->threadId+1){
        fprintf(stderr,"ERROR: dispatchKernel_cnets_osblinnikov_github_com %d: countKernels: count=%d exceeds maximum number of dispatching kernels %d\n", that->threadId, *count+1, that->maxNumberOfKernels*that->countOfThreads);
      }
      return FALSE;
    }
    if(parent->spawnMode != 0){
      return TRUE;
    }
    if(that->maxNumberOfKernels == 0 || *count >= that->maxNumberOfKernels*that->threadId){
      printf("id=%d: %d of limit %d\n",that->threadId,*count, that->maxNumberOfKernels*that->threadId);
      struct arrayObject readers = parent->target.getReaders(parent->target.target);
      if(fillReaders){
        unsigned startNumber = *countReaders;
        for(int i=0; i<readers.length; i++){
          ((reader*)that->readers.array)[*countReaders] =  ((reader*)readers.array)[i];
          runnables_dispatchKernel_cnets_osblinnikov_github_com *tmp = &((runnables_dispatchKernel_cnets_osblinnikov_github_com*)that->kernels.array)[(*countReaders)++];
          tmp->r =  parent->target;/*need to find the kernel very fast*/
          tmp->startNumber = startNumber;
        }
      }else{
        (*countReaders) += readers.length;
      }
    }
    *count += 1;
  }
  return TRUE;
}

void freeDynamic(struct dispatchKernel_cnets_osblinnikov_github_com* ptr){
  if(ptr->readers.array){
    arrayObject_free_dynamic(ptr->readers);
  }
  ptr->readers.array = 0;
  ptr->readers.length = 0;
  if(ptr->kernels.array){
    arrayObject_free_dynamic(ptr->kernels);
  }
  ptr->kernels.array = 0;
  ptr->kernels.length = 0;
}

void dispatchKernel_cnets_osblinnikov_github_com_onStart(void *t){
  struct dispatchKernel_cnets_osblinnikov_github_com *ptr = (struct dispatchKernel_cnets_osblinnikov_github_com*)t;
  freeDynamic(ptr);

  unsigned countReaders = 0, count = 0;
  if( ptr->maxNumberOfKernels != 0 || ptr->threadId == 0 ){
    countKernels(ptr, ptr->parent, &count, &countReaders, FALSE);
  }
  if(count > 0 && countReaders > 0){
    ptr->readers = arrayObject_init_dynamic(sizeof(reader),countReaders);
    ptr->kernels = arrayObject_init_dynamic(sizeof(runnables_dispatchKernel_cnets_osblinnikov_github_com),countReaders);
    countReaders = count = 0;
    countKernels(ptr, ptr->parent, &count, &countReaders, TRUE);
  }
  if(ptr->readers.length > 0){
    printf("dispatchKernel_cnets_osblinnikov_github_com_onStart: init %d\n", ptr->readers.length );
    selector_cnets_osblinnikov_github_com_init(&ptr->selector, ptr->readers);
    ptr->readerSelector = selector_cnets_osblinnikov_github_com_createReader(&ptr->selector, 0);
  }else{
    printf("WARN: dispatchKernel_cnets_osblinnikov_github_com_onStart: readerSelector was not initialized, because readers are 0\n");
    ptr->readerSelector.params.target = NULL;
  }
}

void dispatchKernel_cnets_osblinnikov_github_com_onStop(void *t){
/*  struct dispatchKernel_cnets_osblinnikov_github_com *ptr = (struct dispatchKernel_cnets_osblinnikov_github_com*)t;*/
}

void dispatchKernel_cnets_osblinnikov_github_com_onCreate(struct dispatchKernel_cnets_osblinnikov_github_com *that){

}

void dispatchKernel_cnets_osblinnikov_github_com_onDestroy(struct dispatchKernel_cnets_osblinnikov_github_com *that){
  
  return;
}

void dispatchKernel_cnets_osblinnikov_github_com_onKernels(struct dispatchKernel_cnets_osblinnikov_github_com *that){
  
  return;
}
