/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../runnablesContainer.h"
void runnablesContainer_cnets_osblinnikov_github_com_onCreate(runnablesContainer_cnets_osblinnikov_github_com *that);
void runnablesContainer_cnets_osblinnikov_github_com_onDestroy(runnablesContainer_cnets_osblinnikov_github_com *that);
void runnablesContainer_cnets_osblinnikov_github_com_init(struct runnablesContainer_cnets_osblinnikov_github_com *that){
  
  runnablesContainer_cnets_osblinnikov_github_com_onCreate(that);
}

void runnablesContainer_cnets_osblinnikov_github_com_deinit(struct runnablesContainer_cnets_osblinnikov_github_com *that){
  runnablesContainer_cnets_osblinnikov_github_com_onDestroy(that);
  
}
/*[[[end]]] (checksum: 0e47c22eafea6baea3212690d3ddb0a4)*/

void RunnableStoppable_init(struct RunnableStoppable* that){
  that->onStart = NULL;
  that->run = NULL;
  that->getReaders = NULL;
  that->onStop = NULL;
  that->target = NULL;
}

void runnablesContainer_cnets_osblinnikov_github_com_launch(
  struct runnablesContainer_cnets_osblinnikov_github_com *that, 
  BOOL lockLastElement
){
  if(that->containers != NULL && that->containers_size > 0){
    int i;
    for(i=0; i< that->containers_size; i++){
      if(that->target.target != NULL){
        printf("=> launch: %s mode=%d\n",that->target.name,that->spawnMode);
        that->target.onStart(that->target.target);
      }
      that->containers[i].launch(&that->containers[i], (lockLastElement && i == that->containers_size - 1) );
    }
  }else if(that->target.target != NULL){
    printf("=> launch: %s mode=%d\n",that->target.name,that->spawnMode);
    if(that->spawnMode == 1){
      that->kernel.launch(&that->kernel, that->target, lockLastElement);
    }else{
      that->target.onStart(that->target.target);
    }

  }else {
    printf("===> runnablesContainer_cnets_osblinnikov_github_com_launch NULL\n");
  }
}

void runnablesContainer_cnets_osblinnikov_github_com_stop(
  struct runnablesContainer_cnets_osblinnikov_github_com *that
){
  if(that->containers != NULL && that->containers_size > 0){
    int i;
    for(i=that->containers_size -1; i>=0; i--){
      that->containers[i].stop(&that->containers[i]);
      if(that->target.target != NULL){
        that->target.onStop(that->target.target);
      }
    }
  }else if(that->target.target != NULL){
    if(that->spawnMode == 1){
      that->kernel.stopThread(&that->kernel);
    }else{
      that->target.onStop(&that->target.target);
    }
  }else{
    printf("===> runnablesContainer_cnets_osblinnikov_github_com_stop NULL\n");
  }
}

void runnablesContainer_cnets_osblinnikov_github_com_setContainers(
  struct runnablesContainer_cnets_osblinnikov_github_com *that,
  arrayObject containers
){
  that->containers = (runnablesContainer_cnets_osblinnikov_github_com *)containers.array;
  that->containers_size = containers.length;
}

void runnablesContainer_cnets_osblinnikov_github_com_setCore(
  struct runnablesContainer_cnets_osblinnikov_github_com *that, 
  RunnableStoppable target,
  unsigned spawnMode
){
  that->target = target;
  that->spawnMode = spawnMode;
}

void runnablesContainer_cnets_osblinnikov_github_com_onCreate(runnablesContainer_cnets_osblinnikov_github_com *that){
  runnablesContainer_cnets_osblinnikov_github_com_Kernel_create(&that->kernel);
  that->containers = NULL;
  that->spawnMode = 0;
  that->containers_size = 0;
  that->target.target = NULL;
  that->setContainers = runnablesContainer_cnets_osblinnikov_github_com_setContainers;
  that->setCore = runnablesContainer_cnets_osblinnikov_github_com_setCore;
  that->launch = runnablesContainer_cnets_osblinnikov_github_com_launch;
  that->stop = runnablesContainer_cnets_osblinnikov_github_com_stop;
  return;
}

void runnablesContainer_cnets_osblinnikov_github_com_onDestroy(runnablesContainer_cnets_osblinnikov_github_com *that){
  runnablesContainer_cnets_osblinnikov_github_com_stop(that);
  runnablesContainer_cnets_osblinnikov_github_com_Kernel_destroy(&that->kernel);
  return;
}
