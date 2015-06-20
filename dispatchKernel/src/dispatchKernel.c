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
  struct dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatchKernel_cnets_osblinnikov_github_com*)t;
  that->_readData = readData;
}


void dispatchKernel_cnets_osblinnikov_github_com_init(struct dispatchKernel_cnets_osblinnikov_github_com *that,
    runnablesContainer_cnets_osblinnikov_github_com* _parent,
    uint32_t _maxNumberOfKernels,
    uint32_t _threadId){
  that->_readData = NULL;
  
  that->parent = _parent;
  that->maxNumberOfKernels = _maxNumberOfKernels;
  that->threadId = _threadId;
  that->readers = arrayObject_init_dynamic(sizeof(reader), 1);
  int readers_i_ = 0;
  for(readers_i_=0;readers_i_<1;readers_i_++){
    reader_init(&((reader*)that->readers.array)[readers_i_]);
  }
  reader_init(&that->readerSelector);
  that->kernels = arrayObject_init_dynamic(sizeof(RunnableStoppable), 1);
  int kernels_i_ = 0;
  for(kernels_i_=0;kernels_i_<1;kernels_i_++){
    RunnableStoppable_init(&((RunnableStoppable*)that->kernels.array)[kernels_i_]);
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

/*[[[end]]] (checksum: 7e41523b72b38980530beb833f41ad8c)*/


void dispatchKernel_cnets_osblinnikov_github_com_run(void *t){
  struct dispatchKernel_cnets_osblinnikov_github_com *that = (struct dispatchKernel_cnets_osblinnikov_github_com*)t;
  if(!that->readerSelector.params.target){return;}
  bufferReadData res = that->readerSelector.readNextWithMeta(&that->readerSelector,-1);
  if(res.data == NULL){
    printf("WARN: dispatchKernel_cnets_osblinnikov_github_com_run: data is NULL\n");
    return;
  }
  RunnableStoppable* rs = &((RunnableStoppable*)that->kernels.array)[res.nested_buffer_id];
  rs->setReadData(rs->target, &res);
  rs->run(rs->target);
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
      return FALSE;
    }
    if(parent->spawnMode != 0){
      return TRUE;
    }
    if(that->maxNumberOfKernels == 0 || *count >= that->maxNumberOfKernels*that->threadId){
      struct arrayObject readers = parent->target.getReaders(&parent->target.target);
      if(fillReaders){
        for(int i=0; i<readers.length; i++){
          ((reader*)that->readers.array)[that->readers.length++] =  ((reader*)readers.array)[i];
          ((RunnableStoppable*)that->kernels.array)[that->kernels.length++] =  parent->target;/*need to find the kernel very fast*/
        }
      }else{
        *countReaders += readers.length;
      }
    }
    *count += 1;
  }
  return TRUE;
}

void freeDynamic(struct dispatchKernel_cnets_osblinnikov_github_com* ptr){
  if(ptr->readers.array){
    arrayObject_free_dynamic(ptr->readers);
    ptr->readers.array = 0;
    ptr->readers.length = 0;
  }
  if(ptr->kernels.array){
    arrayObject_free_dynamic(ptr->kernels);
    ptr->kernels.array = 0;
    ptr->kernels.length = 0;
  }
}

void dispatchKernel_cnets_osblinnikov_github_com_onStart(void *t){
  struct dispatchKernel_cnets_osblinnikov_github_com *ptr = (struct dispatchKernel_cnets_osblinnikov_github_com*)t;
  freeDynamic(ptr);

  unsigned countReaders = 0, count = 0;
  countKernels(ptr, ptr->parent, &count, &countReaders, FALSE);

  if(count > 0 && countReaders > 0){
    ptr->readers = arrayObject_init_dynamic(sizeof(reader),countReaders);
    ptr->kernels = arrayObject_init_dynamic(sizeof(RunnableStoppable),countReaders);
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
