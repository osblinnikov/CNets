

#ifndef com_github_airutech_cnets_queue_H
#define com_github_airutech_cnets_queue_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/airutech/cnets/types/c/include/types.h"

#undef com_github_airutech_cnets_queue_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(com_github_airutech_cnets_queue_STATIC)
  #ifdef com_github_airutech_cnets_queue_EXPORT
    #define com_github_airutech_cnets_queue_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_airutech_cnets_queue_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_airutech_cnets_queue_EXPORT_API extern
#endif

struct com_github_airutech_cnets_queue;

com_github_airutech_cnets_queue_EXPORT_API
void com_github_airutech_cnets_queue_initialize(struct com_github_airutech_cnets_queue *that);

com_github_airutech_cnets_queue_EXPORT_API
void com_github_airutech_cnets_queue_deinitialize(struct com_github_airutech_cnets_queue *that);

com_github_airutech_cnets_queue_EXPORT_API
void com_github_airutech_cnets_queue_onKernels(struct com_github_airutech_cnets_queue *that);

#undef com_github_airutech_cnets_queue_onCreateMacro
#define com_github_airutech_cnets_queue_onCreateMacro(_NAME_) /**/

#define com_github_airutech_cnets_queue_create(_NAME_,_capacity)\
    com_github_airutech_cnets_queue _NAME_;\
    _NAME_.capacity = _capacity;\
    com_github_airutech_cnets_queue_onCreateMacro(_NAME_)\
    arrayObject_create(_NAME_##_data_, unsigned, _capacity)\
    _NAME_.data = _NAME_##_data_;\
    com_github_airutech_cnets_queue_initialize(&_NAME_);\
    com_github_airutech_cnets_queue_onKernels(&_NAME_);

typedef struct com_github_airutech_cnets_queue{
    int32_t capacity;arrayObject data;uint32_t maxIndex;uint32_t head;uint32_t tail;

  
  void (*run)(void *that);
/*[[[end]]] (checksum: 23ebdc90a7a3cdb465882a41fbec2718)*/
  BOOL (*isEmpty)(struct com_github_airutech_cnets_queue *that);
  BOOL (*isFull)(struct com_github_airutech_cnets_queue *that);
  BOOL (*dequeue)(struct com_github_airutech_cnets_queue *that,unsigned *obj);
  BOOL (*enqueue)(struct com_github_airutech_cnets_queue *that,unsigned obj);
  int (*length)(struct com_github_airutech_cnets_queue *that);
  void (*clear)(struct com_github_airutech_cnets_queue *that);
}com_github_airutech_cnets_queue;


#define com_github_airutech_cnets_queue_createGrid(_NAME_,_count,_capacity)\
  com_github_airutech_cnets_queue _NAME_[_count];\
  arrayObject_create(_NAME_##_data_, unsigned, _count*_capacity)\
  int _NAME_##i;\
  for(_NAME_##i=0;_NAME_##i<_count;_NAME_##i++){\
    _NAME_[_NAME_##i].capacity = _capacity;\
    _NAME_[_NAME_##i].data.array = (void*)&((unsigned*)_NAME_##_data_.array)[_capacity * _NAME_##i];\
    _NAME_[_NAME_##i].data.length = _capacity;\
    _NAME_[_NAME_##i].data.itemSize = sizeof(unsigned);\
    com_github_airutech_cnets_queue_initialize(&_NAME_[_NAME_##i]);\
    com_github_airutech_cnets_queue_onKernels(&_NAME_[_NAME_##i]);\
  }


#endif /* com_github_airutech_cnets_queue_H */