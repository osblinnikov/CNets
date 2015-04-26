/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../runnablesContainer.h"
void com_github_osblinnikov_cnets_runnablesContainer_onCreate(com_github_osblinnikov_cnets_runnablesContainer *that);
void com_github_osblinnikov_cnets_runnablesContainer_onDestroy(com_github_osblinnikov_cnets_runnablesContainer *that);
void com_github_osblinnikov_cnets_runnablesContainer_init(struct com_github_osblinnikov_cnets_runnablesContainer *that){
  
  com_github_osblinnikov_cnets_runnablesContainer_onKernels(that);
  com_github_osblinnikov_cnets_runnablesContainer_onCreate(that);
}

void com_github_osblinnikov_cnets_runnablesContainer_deinit(struct com_github_osblinnikov_cnets_runnablesContainer *that){
  com_github_osblinnikov_cnets_runnablesContainer_onDestroy(that);
}
/*[[[end]]] (checksum: 78f41246454b2956a57ce0c15321b732) (451c3cc5739926ae03ed7689ce57110e)*/

void com_github_osblinnikov_cnets_runnablesContainer_setContainers(
  struct com_github_osblinnikov_cnets_runnablesContainer *that,
  arrayObject containers
){
  that->containers = (com_github_osblinnikov_cnets_runnablesContainer *)containers.array;
  that->containers_size = containers.length;
}

void com_github_osblinnikov_cnets_runnablesContainer_setCore(
  struct com_github_osblinnikov_cnets_runnablesContainer *that, 
  RunnableStoppable target
){
  that->target = target;
}

void com_github_osblinnikov_cnets_runnablesContainer_launch(
  struct com_github_osblinnikov_cnets_runnablesContainer *that, 
  BOOL lockLastElement
){
  if(that->target.target != NULL){
    that->kernel.launch(&that->kernel, that->target, lockLastElement);
  }else if(that->containers != NULL){
    int i;
    for(i=0; i< that->containers_size - 1; i++){
      that->containers[i].launch(&that->containers[i], FALSE);
    }
    i = that->containers_size - 1;
    that->containers[i].launch(&that->containers[i], lockLastElement);
  }
}

void com_github_osblinnikov_cnets_runnablesContainer_stop(
  struct com_github_osblinnikov_cnets_runnablesContainer *that
){
  if(that->target.target != NULL){
    that->kernel.stopThread(&that->kernel);
  }else if(that->containers != NULL){
    int i;
    for(i=that->containers_size; i>=0; i--){
      that->containers[i].stop(&that->containers[i]);
    }
  }
}

void com_github_osblinnikov_cnets_runnablesContainer_onCreate(com_github_osblinnikov_cnets_runnablesContainer *that){
  com_github_osblinnikov_cnets_runnablesContainer_Kernel_create(&that->kernel);
  that->containers = NULL;
  that->containers_size = 0;
  that->target.target = NULL;
  that->setContainers = com_github_osblinnikov_cnets_runnablesContainer_setContainers;
  that->setCore = com_github_osblinnikov_cnets_runnablesContainer_setCore;
  that->launch = com_github_osblinnikov_cnets_runnablesContainer_launch;
  that->stop = com_github_osblinnikov_cnets_runnablesContainer_stop;
  return;
}

void com_github_osblinnikov_cnets_runnablesContainer_onDestroy(com_github_osblinnikov_cnets_runnablesContainer *that){
  com_github_osblinnikov_cnets_runnablesContainer_stop(that);
  com_github_osblinnikov_cnets_runnablesContainer_Kernel_destroy(&that->kernel);
  return;
}

void com_github_osblinnikov_cnets_runnablesContainer_onKernels(com_github_osblinnikov_cnets_runnablesContainer *that){
  
  return;
}