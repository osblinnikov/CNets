/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../queue.h"
void queue_cnets_osblinnikov_github_com_onCreate(queue_cnets_osblinnikov_github_com *that);
void queue_cnets_osblinnikov_github_com_onDestroy(queue_cnets_osblinnikov_github_com *that);
void queue_cnets_osblinnikov_github_com_init(struct queue_cnets_osblinnikov_github_com *that,
    int32_t _capacity){
  
  that->capacity = _capacity;
  that->data = arrayObject_init_dynamic(sizeof(uint32_t), that->capacity);
  queue_cnets_osblinnikov_github_com_onCreate(that);
}

void queue_cnets_osblinnikov_github_com_deinit(struct queue_cnets_osblinnikov_github_com *that){
  queue_cnets_osblinnikov_github_com_onDestroy(that);
  
  arrayObject_free_dynamic(that->data);
}
/*[[[end]]] (checksum: 74e5943c4184a5f29613864b620987fa)*/

BOOL queue_cnets_osblinnikov_github_com_isEmpty(queue_cnets_osblinnikov_github_com *that) {
  return that->tail == that->head;
}

BOOL queue_cnets_osblinnikov_github_com_isFull(queue_cnets_osblinnikov_github_com *that) {
  int64_t headMin = (int64_t)that->tail - (int64_t)that->capacity;
  if(headMin < 0){
    headMin = that->maxIndex + headMin;
  }
  return (headMin == (int64_t)that->head);
}

BOOL queue_cnets_osblinnikov_github_com_enqueue(queue_cnets_osblinnikov_github_com *that,uint32_t obj){
  if(queue_cnets_osblinnikov_github_com_isFull(that)){
    return FALSE;
  }else{
    that->tail++;
    if(that->tail >= that->maxIndex){that->tail = 0;}
    ((uint32_t*)that->data.array)[(uint32_t)(that->tail % that->capacity)] = obj;
    return TRUE;
  }
}

BOOL queue_cnets_osblinnikov_github_com_dequeue(queue_cnets_osblinnikov_github_com *that,uint32_t *obj){
  if(queue_cnets_osblinnikov_github_com_isEmpty(that)){
    return FALSE;
  }else{
    that->head++;
    if(that->head >= that->maxIndex){that->head = 0;}
    *obj = ((uint32_t*)that->data.array)[(uint32_t)(that->head % that->capacity)];
    return TRUE;
  }
}

uint32_t queue_cnets_osblinnikov_github_com_length(queue_cnets_osblinnikov_github_com *that){
  uint32_t res;
  if(that->head <= that->tail){
    return (uint32_t)(that->tail - that->head);
  }else{
    res = (uint32_t)(that->maxIndex - that->head);
    res += that->tail;
    return res;
  }
}
void queue_cnets_osblinnikov_github_com_clear(queue_cnets_osblinnikov_github_com *that){
  that->head = that->tail = that->maxIndex - 5;
}

void queue_cnets_osblinnikov_github_com_onCreate(queue_cnets_osblinnikov_github_com *that){
  uint32_t maxInteger = 0;
  maxInteger--;
  if(that->capacity > 0){
    that->maxIndex = (uint32_t)(maxInteger/(uint32_t)that->capacity)*(uint32_t)that->capacity;
  }else{
    that->maxIndex = 5;
  }
  that->head = that->tail = that->maxIndex - 5;
  that->isEmpty = queue_cnets_osblinnikov_github_com_isEmpty;
  that->isFull = queue_cnets_osblinnikov_github_com_isFull;
  that->enqueue = queue_cnets_osblinnikov_github_com_enqueue;
  that->dequeue = queue_cnets_osblinnikov_github_com_dequeue;
  that->length = queue_cnets_osblinnikov_github_com_length;
  that->clear = queue_cnets_osblinnikov_github_com_clear;

  return;
}

void queue_cnets_osblinnikov_github_com_onDestroy(queue_cnets_osblinnikov_github_com *that){
  
  return;
}

struct queue_cnets_osblinnikov_github_com* queue_cnets_osblinnikov_github_com_createGrid_dynamic(
    int32_t count,
    int32_t _capacity){
  queue_cnets_osblinnikov_github_com* res = (queue_cnets_osblinnikov_github_com*)malloc(
    sizeof(queue_cnets_osblinnikov_github_com)*count);
  int i;
  for(i=0;i<count;i++){
    res[i] = queue_cnets_osblinnikov_github_com_create_dynamic(_capacity);
  }
  return res;
}

void queue_cnets_osblinnikov_github_com_freeGrid_dynamic(struct queue_cnets_osblinnikov_github_com* res, int32_t count){
  int i;
  for(i=0;i<count;i++){
    queue_cnets_osblinnikov_github_com_free_dynamic(res[i]);
  }
  free(res);
}

struct queue_cnets_osblinnikov_github_com queue_cnets_osblinnikov_github_com_create_dynamic(int32_t _capacity){
  queue_cnets_osblinnikov_github_com res;
  queue_cnets_osblinnikov_github_com_init(&res, _capacity);
  return res;
}

void queue_cnets_osblinnikov_github_com_free_dynamic(struct queue_cnets_osblinnikov_github_com res){
  queue_cnets_osblinnikov_github_com_deinit(&res);
}


