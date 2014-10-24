#ifndef com_github_airutech_cnets_runnablesContainer_Kernel_H
#define com_github_airutech_cnets_runnablesContainer_Kernel_H

#undef com_github_airutech_cnets_runnablesContainer_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(com_github_airutech_cnets_runnablesContainer_STATIC)
  #ifdef com_github_airutech_cnets_runnablesContainer_EXPORT
    #define com_github_airutech_cnets_runnablesContainer_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_airutech_cnets_runnablesContainer_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_airutech_cnets_runnablesContainer_EXPORT_API extern
#endif

#include "github.com/airutech/cnets/types/c/include/types.h"
#include "./RunnableStoppable.h"
#include <pthread.h>

typedef struct com_github_airutech_cnets_runnablesContainer_Kernel{
  RunnableStoppable objectToRun;
  BOOL isSeparateThread;
  BOOL isRunning;
  pthread_spinlock_t isRunningLock;
  BOOL stopFlag;
  pthread_spinlock_t stopFlagLock;
  pthread_t kernelThread;
  void (*launch)(struct com_github_airutech_cnets_runnablesContainer_Kernel* that, RunnableStoppable objectToRun, BOOL lockLaunch);
  void (*stopThread)(struct com_github_airutech_cnets_runnablesContainer_Kernel* that);
}com_github_airutech_cnets_runnablesContainer_Kernel;

com_github_airutech_cnets_runnablesContainer_EXPORT_API
  void com_github_airutech_cnets_runnablesContainer_Kernel_create(
    com_github_airutech_cnets_runnablesContainer_Kernel* that
  );

com_github_airutech_cnets_runnablesContainer_EXPORT_API
  void com_github_airutech_cnets_runnablesContainer_Kernel_destroy(
    com_github_airutech_cnets_runnablesContainer_Kernel* that
  );

#endif /* com_github_airutech_cnets_runnablesContainer_Kernel_H */