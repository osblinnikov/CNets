#include "../include/Kernel.h"
#include <assert.h>

void *com_github_airutech_cnets_runnablesContainer_Kernel_run(void* inTarget){
  com_github_airutech_cnets_runnablesContainer_Kernel* that = (com_github_airutech_cnets_runnablesContainer_Kernel* )inTarget;
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_runnablesContainer_Kernel_run: that is NULL\n");
    return NULL;
  }
  pthread_spin_lock(&that->stopFlagLock);
  while(!that->stopFlag){
    pthread_spin_unlock(&that->stopFlagLock);
    that->objectToRun.run(that->objectToRun.target);
    pthread_spin_lock(&that->stopFlagLock);
  }
  pthread_spin_unlock(&that->stopFlagLock);

  pthread_spin_lock(&that->isRunningLock);
  that->isRunning = FALSE;
  pthread_spin_unlock(&that->isRunningLock);
  return NULL;
}

void com_github_airutech_cnets_runnablesContainer_Kernel_launch(
  struct com_github_airutech_cnets_runnablesContainer_Kernel* that, 
  RunnableStoppable objectToRun, 
  BOOL lockLaunch
){
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_runnablesContainer_Kernel_launch: that is NULL\n");
    return;
  }
  if(objectToRun.target == NULL){
    printf("ERROR: com_github_airutech_cnets_runnablesContainer_Kernel_launch: objectToRun.target is NULL\n");
    return;
  }
  pthread_spin_lock(&that->stopFlagLock);
  that->stopFlag = FALSE;
  pthread_spin_unlock(&that->stopFlagLock);
  pthread_spin_lock(&that->isRunningLock);
  if(!that->isRunning){
    that->isRunning = TRUE;
    pthread_spin_unlock(&that->isRunningLock);
    that->objectToRun = objectToRun;
    that->objectToRun.onStart(that->objectToRun.target);
    if(lockLaunch){
      that->isSeparateThread = FALSE;
      com_github_airutech_cnets_runnablesContainer_Kernel_run((void*)that);
    }else{
      that->isSeparateThread = TRUE;
      if(pthread_create(&that->kernelThread, NULL, com_github_airutech_cnets_runnablesContainer_Kernel_run, (void *)that)){
        printf("ERROR com_github_airutech_cnets_runnablesContainer_Kernel_launch: return code from pthread_create() != 0\n");
        pthread_spin_lock(&that->isRunningLock);
        that->isRunning = FALSE;
        pthread_spin_unlock(&that->isRunningLock);
      }
    }
  }else{
    pthread_spin_unlock(&that->isRunningLock);
  }
}

void com_github_airutech_cnets_runnablesContainer_Kernel_stopThread(
  struct com_github_airutech_cnets_runnablesContainer_Kernel* that
){
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_runnablesContainer_Kernel_stopThread: that is NULL\n");
    return;
  }
  if(that->objectToRun.target == NULL) {
    printf("ERROR: com_github_airutech_cnets_runnablesContainer_Kernel_stopThread: objectToRun.target is NULL\n");
    return;
  }

  pthread_spin_lock(&that->stopFlagLock);
  that->stopFlag = TRUE;
  pthread_spin_unlock(&that->stopFlagLock);
  // if(that->isSeparateThread) {
  //    this.interrupt();
  // }
  pthread_spin_lock(&that->isRunningLock);
  while(that->isRunning){
    pthread_spin_unlock(&that->isRunningLock);
    /*make sure that nobody will start the kernel before we finish the waiting*/
    pthread_spin_lock(&that->stopFlagLock);
    that->stopFlag = TRUE;
    pthread_spin_unlock(&that->stopFlagLock);
    taskDelay(1000000L);
    pthread_spin_lock(&that->isRunningLock);
  }
  pthread_spin_unlock(&that->isRunningLock);
  // if (that->isSeparateThread) {
  //   this.join();
  // }
  that->objectToRun.onStop(that->objectToRun.target);
  that->objectToRun.target = NULL;
}

void com_github_airutech_cnets_runnablesContainer_Kernel_create(
  com_github_airutech_cnets_runnablesContainer_Kernel* that
){
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_runnablesContainer_Kernel_create: that is NULL\n");
    return;
  }
  int res;
  that->objectToRun.target = NULL;
  that->isSeparateThread = FALSE;
  that->isRunning = FALSE;
  res = pthread_spin_init(&that->isRunningLock, 0);
  assert(!res);
  that->stopFlag = FALSE;
  res = pthread_spin_init(&that->stopFlagLock, 0);
  assert(!res);
  that->launch = com_github_airutech_cnets_runnablesContainer_Kernel_launch;
  that->stopThread = com_github_airutech_cnets_runnablesContainer_Kernel_stopThread;
  return;
}

void com_github_airutech_cnets_runnablesContainer_Kernel_destroy(
  com_github_airutech_cnets_runnablesContainer_Kernel* that
){
  if(that == NULL){
    printf("ERROR: com_github_airutech_cnets_runnablesContainer_Kernel_destroy: that is NULL\n");
    return;
  }
  int res = pthread_spin_destroy(&that->isRunningLock);
  assert(!res);
  res = pthread_spin_destroy(&that->stopFlagLock);
  assert(!res);
}