/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../include/queue.h"
void com_github_airutech_cnets_queue_onCreate(com_github_airutech_cnets_queue *that);
void com_github_airutech_cnets_queue_onDestroy(com_github_airutech_cnets_queue *that);
void com_github_airutech_cnets_queue_initialize(com_github_airutech_cnets_queue *that){
  com_github_airutech_cnets_queue_onCreate(that);
}

void com_github_airutech_cnets_queue_deinitialize(struct com_github_airutech_cnets_queue *that){
  com_github_airutech_cnets_queue_onDestroy(that);
}
/*[[[end]]] (checksum: cd2c58ec7c94a8d384711e7ccb284a23)*/

BOOL com_github_airutech_cnets_queue_isEmpty(com_github_airutech_cnets_queue *that) {
  return that->tail == that->head;
}

BOOL com_github_airutech_cnets_queue_isFull(com_github_airutech_cnets_queue *that) {
  long headMin = that->tail - (long)that->capacity;
  if(headMin < 0){
    headMin = that->maxIndex + headMin;
  }
  return (headMin == that->head);
}

BOOL com_github_airutech_cnets_queue_enqueue(com_github_airutech_cnets_queue *that,unsigned obj){
  if(com_github_airutech_cnets_queue_isFull(that)){
    return FALSE;
  }else{
    that->tail++;
    if(that->tail >= that->maxIndex){that->tail = 0;}
    ((unsigned*)that->data.array)[(int)(that->tail % that->capacity)] = obj;
    return TRUE;
  }
}

BOOL com_github_airutech_cnets_queue_dequeue(com_github_airutech_cnets_queue *that,unsigned *obj){
  if(com_github_airutech_cnets_queue_isEmpty(that)){
    return FALSE;
  }else{
    that->head++;
    if(that->head >= that->maxIndex){that->head = 0;}
    *obj = ((unsigned*)that->data.array)[(int)(that->head % that->capacity)];
    return TRUE;
  }
}

int com_github_airutech_cnets_queue_length(com_github_airutech_cnets_queue *that){
  int res;
  if(that->head <= that->tail){
    return (int)(that->tail - that->head);
  }else{
    res = (int)(that->maxIndex - that->head);
    res += that->tail;
    return res;
  }
}
void com_github_airutech_cnets_queue_clear(com_github_airutech_cnets_queue *that){
  that->head = that->tail = that->maxIndex - 5;
}

void com_github_airutech_cnets_queue_onCreate(com_github_airutech_cnets_queue *that){
  unsigned maxInteger = 0;
  maxInteger--;
  if(that->capacity > 0){
    that->maxIndex = (unsigned)(maxInteger/(unsigned)that->capacity)*(unsigned)that->capacity;
  }else{
    that->maxIndex = 5;
  }
  that->head = that->tail = that->maxIndex - 5;
  that->isEmpty = com_github_airutech_cnets_queue_isEmpty;
  that->isFull = com_github_airutech_cnets_queue_isFull;
  that->enqueue = com_github_airutech_cnets_queue_enqueue;
  that->dequeue = com_github_airutech_cnets_queue_dequeue;
  that->length = com_github_airutech_cnets_queue_length;
  that->clear = com_github_airutech_cnets_queue_clear;

  return;
}

void com_github_airutech_cnets_queue_onDestroy(com_github_airutech_cnets_queue *that){
  
  return;
}

void com_github_airutech_cnets_queue_onKernels(com_github_airutech_cnets_queue *that){
  
  return;
}


