#include "../Kernel.h"
#include <assert.h>

void *com_github_osblinnikov_cnets_runnablesContainer_Kernel_run(void* inTarget){
  com_github_osblinnikov_cnets_runnablesContainer_Kernel* that = (com_github_osblinnikov_cnets_runnablesContainer_Kernel* )inTarget;
  if(that == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_runnablesContainer_Kernel_run: that is NULL\n");
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

  pthread_mutex_lock(&that->isRunning_cv_mutex);
  pthread_cond_broadcast(&that->isRunning_cv);
  pthread_mutex_unlock(&that->isRunning_cv_mutex);

  return NULL;
}

void com_github_osblinnikov_cnets_runnablesContainer_Kernel_launch(
  struct com_github_osblinnikov_cnets_runnablesContainer_Kernel* that, 
  RunnableStoppable objectToRun, 
  BOOL lockLaunch
){
  if(that == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_runnablesContainer_Kernel_launch: that is NULL\n");
    return;
  }
  if(objectToRun.target == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_runnablesContainer_Kernel_launch: objectToRun.target is NULL\n");
    return;
  }
  pthread_spin_lock(&that->stopFlagLock);
  that->stopFlag = FALSE;
  pthread_spin_unlock(&that->stopFlagLock);
  pthread_spin_lock(&that->isRunningLock);
  if(!that->isRunning){
    that->isRunning = TRUE;
    pthread_spin_unlock(&that->isRunningLock);

    pthread_mutex_lock(&that->isRunning_cv_mutex);
    pthread_cond_broadcast(&that->isRunning_cv);
    pthread_mutex_unlock(&that->isRunning_cv_mutex);

    that->objectToRun = objectToRun;
    that->objectToRun.onStart(that->objectToRun.target);
    if(lockLaunch){
      that->isSeparateThread = FALSE;
      com_github_osblinnikov_cnets_runnablesContainer_Kernel_run((void*)that);
    }else{
      that->isSeparateThread = TRUE;
      if(pthread_create(&that->kernelThread, NULL, com_github_osblinnikov_cnets_runnablesContainer_Kernel_run, (void *)that)){
        printf("ERROR com_github_osblinnikov_cnets_runnablesContainer_Kernel_launch: return code from pthread_create() != 0\n");
        pthread_spin_lock(&that->isRunningLock);
        that->isRunning = FALSE;
        pthread_spin_unlock(&that->isRunningLock);
      }
    }
  }else{
    pthread_spin_unlock(&that->isRunningLock);
  }
}

void com_github_osblinnikov_cnets_runnablesContainer_Kernel_stopThread(
  struct com_github_osblinnikov_cnets_runnablesContainer_Kernel* that
){
  if(that == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_runnablesContainer_Kernel_stopThread: that is NULL\n");
    return;
  }
  if(that->objectToRun.target == NULL) {
    printf("ERROR: com_github_osblinnikov_cnets_runnablesContainer_Kernel_stopThread: objectToRun.target is NULL\n");
    return;
  }

  pthread_spin_lock(&that->stopFlagLock);
  that->stopFlag = TRUE;
  pthread_spin_unlock(&that->stopFlagLock);
  // if(that->isSeparateThread) {
  //    this.interrupt();
  // }
  pthread_spin_lock(&that->isRunningLock);

  struct timespec wait_timespec = getTimespecDelay((uint64_t)1000*(uint64_t)1000000);

  while(that->isRunning){
    pthread_spin_unlock(&that->isRunningLock);
    /*make sure that nobody will start the kernel before we finish the waiting*/
    pthread_spin_lock(&that->stopFlagLock);
    that->stopFlag = TRUE;
    pthread_spin_unlock(&that->stopFlagLock);
    //taskDelay(1000000L);
    pthread_mutex_lock(&that->isRunning_cv_mutex);
    if(ETIMEDOUT == pthread_cond_timedwait(&that->isRunning_cv, &that->isRunning_cv_mutex, &wait_timespec)){
      printf("ERROR: com_github_osblinnikov_cnets_runnablesContainer_Kernel_stopThread: wait timeout\n");
    }
    pthread_mutex_unlock(&that->isRunning_cv_mutex);
    pthread_spin_lock(&that->isRunningLock);
  }
  pthread_spin_unlock(&that->isRunningLock);
  // if (that->isSeparateThread) {
  //   this.join();
  // }
  that->objectToRun.onStop(that->objectToRun.target);
  that->objectToRun.target = NULL;
}

void com_github_osblinnikov_cnets_runnablesContainer_Kernel_create(
  com_github_osblinnikov_cnets_runnablesContainer_Kernel* that
){
  if(that == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_runnablesContainer_Kernel_create: that is NULL\n");
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
  res = pthread_mutex_init(&that->isRunning_cv_mutex, 0);
  assert(!res);
  res = pthread_cond_init(&that->isRunning_cv, 0);
  assert(!res);

  that->launch = com_github_osblinnikov_cnets_runnablesContainer_Kernel_launch;
  that->stopThread = com_github_osblinnikov_cnets_runnablesContainer_Kernel_stopThread;
  return;
}

void com_github_osblinnikov_cnets_runnablesContainer_Kernel_destroy(
  com_github_osblinnikov_cnets_runnablesContainer_Kernel* that
){
  if(that == NULL){
    printf("ERROR: com_github_osblinnikov_cnets_runnablesContainer_Kernel_destroy: that is NULL\n");
    return;
  }
  int res = pthread_spin_destroy(&that->isRunningLock);
  assert(!res);
  res = pthread_spin_destroy(&that->stopFlagLock);
  assert(!res);
  res = pthread_mutex_destroy(&that->isRunning_cv_mutex);
  assert(!res);
  res = pthread_cond_destroy(&that->isRunning_cv);
  assert(!res);
}