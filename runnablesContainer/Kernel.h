#ifndef runnablesContainer_cnets_osblinnikov_github_com_Kernel_H
#define runnablesContainer_cnets_osblinnikov_github_com_Kernel_H

#undef runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(COM_GITHUB_AIRUTECH_CNETS_RUNNABLESCONTAINER_STATIC)
  #ifdef runnablesContainer_cnets_osblinnikov_github_com_EXPORT
    #define runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

#include "github.com/osblinnikov/cnets/types/types.h"
#include "./RunnableStoppable.h"
#include <pthread.h>

typedef struct runnablesContainer_cnets_osblinnikov_github_com_Kernel{
  RunnableStoppable objectToRun;
  BOOL isSeparateThread;
  BOOL isRunning;
  pthread_spinlock_t isRunningLock;
  BOOL stopFlag;
  pthread_spinlock_t stopFlagLock;
  pthread_t kernelThread;

  pthread_mutex_t     isRunning_cv_mutex;
  pthread_cond_t      isRunning_cv;

  void (*launch)(struct runnablesContainer_cnets_osblinnikov_github_com_Kernel* that, RunnableStoppable objectToRun, BOOL lockLaunch);
  void (*stopThread)(struct runnablesContainer_cnets_osblinnikov_github_com_Kernel* that);
}runnablesContainer_cnets_osblinnikov_github_com_Kernel;

runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API
  void runnablesContainer_cnets_osblinnikov_github_com_Kernel_create(
    runnablesContainer_cnets_osblinnikov_github_com_Kernel* that
  );

runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API
  void runnablesContainer_cnets_osblinnikov_github_com_Kernel_destroy(
    runnablesContainer_cnets_osblinnikov_github_com_Kernel* that
  );

#endif /* runnablesContainer_cnets_osblinnikov_github_com_Kernel_H */