

#ifndef queue_cnets_osblinnikov_github_com_H
#define queue_cnets_osblinnikov_github_com_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/types/types.h"

#undef queue_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(QUEUE_CNETS_OSBLINNIKOV_GITHUB_COM_STATIC)
  #ifdef queue_cnets_osblinnikov_github_com_EXPORT
    #define queue_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define queue_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define queue_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

struct queue_cnets_osblinnikov_github_com;

queue_cnets_osblinnikov_github_com_EXPORT_API
void queue_cnets_osblinnikov_github_com_init(struct queue_cnets_osblinnikov_github_com *that,
    int32_t _capacity);

queue_cnets_osblinnikov_github_com_EXPORT_API
void queue_cnets_osblinnikov_github_com_deinit(struct queue_cnets_osblinnikov_github_com *that);

typedef struct queue_cnets_osblinnikov_github_com{
    int32_t capacity;
  arrayObject data;
  uint32_t maxIndex;
  uint32_t head;
  uint32_t tail;

  
/*[[[end]]] (checksum: e83423cfd890a32e04989bd8ad23c1e4)*/
  BOOL (*isEmpty)(struct queue_cnets_osblinnikov_github_com *that);
  BOOL (*isFull)(struct queue_cnets_osblinnikov_github_com *that);
  BOOL (*dequeue)(struct queue_cnets_osblinnikov_github_com *that,uint32_t *obj);
  BOOL (*enqueue)(struct queue_cnets_osblinnikov_github_com *that,uint32_t obj);
  uint32_t (*length)(struct queue_cnets_osblinnikov_github_com *that);
  void (*clear)(struct queue_cnets_osblinnikov_github_com *that);
}queue_cnets_osblinnikov_github_com;

queue_cnets_osblinnikov_github_com_EXPORT_API
struct queue_cnets_osblinnikov_github_com* queue_cnets_osblinnikov_github_com_createGrid_dynamic(
    int32_t count,
    int32_t _capacity);

queue_cnets_osblinnikov_github_com_EXPORT_API
void queue_cnets_osblinnikov_github_com_freeGrid_dynamic(struct queue_cnets_osblinnikov_github_com* res, int32_t count);

queue_cnets_osblinnikov_github_com_EXPORT_API
struct queue_cnets_osblinnikov_github_com queue_cnets_osblinnikov_github_com_create_dynamic(int32_t _capacity);

queue_cnets_osblinnikov_github_com_EXPORT_API
void queue_cnets_osblinnikov_github_com_free_dynamic(struct queue_cnets_osblinnikov_github_com that);

#endif /* queue_cnets_osblinnikov_github_com_H */