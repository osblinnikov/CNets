

#ifndef runnablesContainer_cnets_osblinnikov_github_com_H
#define runnablesContainer_cnets_osblinnikov_github_com_H

#include "github.com/osblinnikov/cnets/types/types.h"
#include <pthread.h>

typedef struct RunnableStoppable{
  void *target;
  char *name;
  void (*onStart)(void* target);
  struct arrayObject (*getReaders)(void *target);
  void (*setReadData)(void *target, bufferReadData *readData);
  void (*run)(void* target);
  void (*onStop)(void* target);
}RunnableStoppable;

#define RunnableStoppable_create(_NAME_,_target, fullName)\
    RunnableStoppable _NAME_;\
    _NAME_.name = #fullName; \
    _NAME_.target = (void*)_target;\
    _NAME_.onStart = fullName##_onStart;\
    _NAME_.run = fullName##_run;\
    _NAME_.onStop = fullName##_onStop;\
    _NAME_.getReaders = fullName##_getReaders;\
    _NAME_.setReadData = fullName##_setReadData;

typedef struct runnablesContainer_cnets_osblinnikov_github_com_Kernel{
  RunnableStoppable objectToRun;
  BOOL isSeparateThread;
  volatile BOOL isRunning;
  pthread_spinlock_t isRunningLock;
  volatile BOOL stopFlag;
  pthread_spinlock_t stopFlagLock;
  pthread_t kernelThread;

  pthread_mutex_t     isRunning_cv_mutex;
  pthread_cond_t      isRunning_cv;

  void (*launch)(struct runnablesContainer_cnets_osblinnikov_github_com_Kernel* that, RunnableStoppable objectToRun, BOOL lockLaunch);
  void (*stopThread)(struct runnablesContainer_cnets_osblinnikov_github_com_Kernel* that);
}runnablesContainer_cnets_osblinnikov_github_com_Kernel;

#undef runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(RUNNABLESCONTAINER_CNETS_OSBLINNIKOV_GITHUB_COM_STATIC)
  #ifdef runnablesContainer_cnets_osblinnikov_github_com_EXPORT
    #define runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

struct runnablesContainer_cnets_osblinnikov_github_com;

runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API
void runnablesContainer_cnets_osblinnikov_github_com_init(struct runnablesContainer_cnets_osblinnikov_github_com *that);

runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API
void runnablesContainer_cnets_osblinnikov_github_com_deinit(struct runnablesContainer_cnets_osblinnikov_github_com *that);

typedef struct runnablesContainer_cnets_osblinnikov_github_com{
  struct runnablesContainer_cnets_osblinnikov_github_com_Kernel kernel;
  struct runnablesContainer_cnets_osblinnikov_github_com *containers;
  int containers_size;
  struct RunnableStoppable target;
  unsigned spawnMode;
  void (*setContainers)(struct runnablesContainer_cnets_osblinnikov_github_com *that, arrayObject containers);
  void (*setCore)(struct runnablesContainer_cnets_osblinnikov_github_com *that, RunnableStoppable target, unsigned spawnMode);
  void (*launch)(struct runnablesContainer_cnets_osblinnikov_github_com *that, BOOL lockLastElement);
  void (*stop)(struct runnablesContainer_cnets_osblinnikov_github_com *that);
}runnablesContainer_cnets_osblinnikov_github_com;

runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API
  void RunnableStoppable_init(struct RunnableStoppable* that);

runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API
  void runnablesContainer_cnets_osblinnikov_github_com_Kernel_create(
    runnablesContainer_cnets_osblinnikov_github_com_Kernel* that
  );

runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API
  void runnablesContainer_cnets_osblinnikov_github_com_Kernel_destroy(
    runnablesContainer_cnets_osblinnikov_github_com_Kernel* that
  );

#endif /* runnablesContainer_cnets_osblinnikov_github_com_H */
