/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../queue.h"
void com_github_osblinnikov_cnets_queue_onCreate(com_github_osblinnikov_cnets_queue *that);
void com_github_osblinnikov_cnets_queue_onDestroy(com_github_osblinnikov_cnets_queue *that);
void com_github_osblinnikov_cnets_queue_init(struct com_github_osblinnikov_cnets_queue *that,
    int _capacity){
  
  that->capacity = _capacity;
  that->data = arrayObject_init_dynamic(sizeof(uint32_t), that->capacity);
  com_github_osblinnikov_cnets_queue_onKernels(that);
  com_github_osblinnikov_cnets_queue_onCreate(that);
}

void com_github_osblinnikov_cnets_queue_deinit(struct com_github_osblinnikov_cnets_queue *that){
  com_github_osblinnikov_cnets_queue_onDestroy(that);
}
/*[[[end]]] (f92a71cdb77b79091e16d271b40f9d6f) (cd2c58ec7c94a8d384711e7ccb284a23)*/

BOOL com_github_osblinnikov_cnets_queue_isEmpty(com_github_osblinnikov_cnets_queue *that) {
  return that->tail == that->head;
}

BOOL com_github_osblinnikov_cnets_queue_isFull(com_github_osblinnikov_cnets_queue *that) {
  int64_t headMin = (int64_t)that->tail - (int64_t)that->capacity;
  if(headMin < 0){
    headMin = that->maxIndex + headMin;
  }
  return (headMin == (int64_t)that->head);
}

BOOL com_github_osblinnikov_cnets_queue_enqueue(com_github_osblinnikov_cnets_queue *that,uint32_t obj){
  if(com_github_osblinnikov_cnets_queue_isFull(that)){
    return FALSE;
  }else{
    that->tail++;
    if(that->tail >= that->maxIndex){that->tail = 0;}
    ((uint32_t*)that->data.array)[(uint32_t)(that->tail % that->capacity)] = obj;
    return TRUE;
  }
}

BOOL com_github_osblinnikov_cnets_queue_dequeue(com_github_osblinnikov_cnets_queue *that,uint32_t *obj){
  if(com_github_osblinnikov_cnets_queue_isEmpty(that)){
    return FALSE;
  }else{
    that->head++;
    if(that->head >= that->maxIndex){that->head = 0;}
    *obj = ((uint32_t*)that->data.array)[(uint32_t)(that->head % that->capacity)];
    return TRUE;
  }
}

uint32_t com_github_osblinnikov_cnets_queue_length(com_github_osblinnikov_cnets_queue *that){
  uint32_t res;
  if(that->head <= that->tail){
    return (uint32_t)(that->tail - that->head);
  }else{
    res = (uint32_t)(that->maxIndex - that->head);
    res += that->tail;
    return res;
  }
}
void com_github_osblinnikov_cnets_queue_clear(com_github_osblinnikov_cnets_queue *that){
  that->head = that->tail = that->maxIndex - 5;
}

void com_github_osblinnikov_cnets_queue_onCreate(com_github_osblinnikov_cnets_queue *that){
  uint32_t maxInteger = 0;
  maxInteger--;
  if(that->capacity > 0){
    that->maxIndex = (uint32_t)(maxInteger/(uint32_t)that->capacity)*(uint32_t)that->capacity;
  }else{
    that->maxIndex = 5;
  }
  that->head = that->tail = that->maxIndex - 5;
  that->isEmpty = com_github_osblinnikov_cnets_queue_isEmpty;
  that->isFull = com_github_osblinnikov_cnets_queue_isFull;
  that->enqueue = com_github_osblinnikov_cnets_queue_enqueue;
  that->dequeue = com_github_osblinnikov_cnets_queue_dequeue;
  that->length = com_github_osblinnikov_cnets_queue_length;
  that->clear = com_github_osblinnikov_cnets_queue_clear;

  return;
}

void com_github_osblinnikov_cnets_queue_onDestroy(com_github_osblinnikov_cnets_queue *that){
  
  return;
}

void com_github_osblinnikov_cnets_queue_onKernels(com_github_osblinnikov_cnets_queue *that){
  
  return;
}


