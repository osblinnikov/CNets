

#ifndef dispatchBuffer_cnets_osblinnikov_github_com_H
#define dispatchBuffer_cnets_osblinnikov_github_com_H

#include <pthread.h>

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/readerWriter/readerWriter.h"
#include "github.com/osblinnikov/cnets/types/types.h"
#include "github.com/osblinnikov/cnets/vector/vector.h"

#undef dispatchBuffer_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(DISPATCHBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_STATIC)
  #ifdef dispatchBuffer_cnets_osblinnikov_github_com_EXPORT
    #define dispatchBuffer_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define dispatchBuffer_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define dispatchBuffer_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

struct dispatchBuffer_cnets_osblinnikov_github_com;

dispatchBuffer_cnets_osblinnikov_github_com_EXPORT_API
void dispatchBuffer_cnets_osblinnikov_github_com_init(struct dispatchBuffer_cnets_osblinnikov_github_com *that,
    arrayObject _buffers,
    int64_t _timeout_milisec,
    int32_t _readers_grid_size);

dispatchBuffer_cnets_osblinnikov_github_com_EXPORT_API
void dispatchBuffer_cnets_osblinnikov_github_com_deinit(struct dispatchBuffer_cnets_osblinnikov_github_com *that);

dispatchBuffer_cnets_osblinnikov_github_com_EXPORT_API
reader dispatchBuffer_cnets_osblinnikov_github_com_createReader(struct dispatchBuffer_cnets_osblinnikov_github_com *that, int gridId);

dispatchBuffer_cnets_osblinnikov_github_com_EXPORT_API
writer dispatchBuffer_cnets_osblinnikov_github_com_createWriter(struct dispatchBuffer_cnets_osblinnikov_github_com *that, int gridId);

typedef struct dispatchBuffer_cnets_osblinnikov_github_com{
  void *_readerIds_, *_writerIds_;
  void (*readerIdsDestructor)(void*);
  void (*writerIdsDestructor)(void*);
  arrayObject buffers;
  int64_t timeout_milisec;
  int32_t readers_grid_size;
  arrayObject messagesInMailbox;
  arrayObject dispatchedKernels;
  arrayObject messagesSpawnTime;
  arrayObject spawnedArray;

  
/*[[[end]]] (checksum: 6d0b0262e946f6ae9b974f9ee978779a)*/
  unsigned char volatile * isSpawned;
  uint32_t volatile * inMailbox;
  uint64_t volatile * spawnTime;
  pthread_spinlock_t * spawnedSpinLocks;
  pthread_mutex_t     cv_mutex;
  pthread_cond_t      cv;
  struct formula_dispatchBuffer_cnets_osblinnikov_github_com{
    uint32_t (*formula)(dispatchBuffer_cnets_osblinnikov_github_com* that,bufferKernelParams *params, uint64_t curTime, uint32_t cntInMailBox, uint32_t readerId);
    size_t (*getIdsLength)(dispatchBuffer_cnets_osblinnikov_github_com* that, bufferKernelParams *params);
    uint32_t* (*getIds)(dispatchBuffer_cnets_osblinnikov_github_com* that, bufferKernelParams *params);
    void* context;
  }formula;
}dispatchBuffer_cnets_osblinnikov_github_com;

#endif /* dispatchBuffer_cnets_osblinnikov_github_com_H */
