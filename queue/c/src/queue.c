#define SPINCOUNT 500

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

BOOL enqueue(struct lfds611QUEUE_queue_state *qs, uint32_t obj){
  return lfds611QUEUE_queue_enqueue(qs, (void *)(intptr_t) obj);
}

BOOL dequeue(struct lfds611QUEUE_queue_state *qs,uint32_t *obj){
  void* user_data;
  if(lfds611QUEUE_queue_dequeue(qs, (void *) &user_data)){
    *obj = (uint32_t)(intptr_t)user_data;
    return TRUE;
  }
  return FALSE;
}

BOOL com_github_airutech_cnets_queue_enqueue(com_github_airutech_cnets_queue *that,uint32_t obj, uint32_t timeout_milisec, int spinCount){
  BOOL res = FALSE;
  int i=0;
  do{
    res = enqueue(that->qs,obj);
  }while(!res && ++i<spinCount && timeout_milisec);
  if(!res && timeout_milisec){
    struct timespec wait_timespec = getTimespecDelay((uint64_t)timeout_milisec*(uint64_t)1000000L);
    pthread_mutex_lock(&that->switch_cv_read_mutex);
    if(!(res = enqueue(that->qs,obj))){
      do{
        if(ETIMEDOUT == pthread_cond_timedwait(&that->switch_cv_read, &that->switch_cv_read_mutex, &wait_timespec)){
          printf("WARN: com_github_airutech_cnets_queue_enqueue: wait timeout\n");
        }else{
          res = enqueue(that->qs,obj);
          if(res == TRUE)
            break;
        }
      }while(compareTimespec(&wait_timespec)<0);
    }
    pthread_mutex_unlock(&that->switch_cv_read_mutex);
  }
  if(res){
    pthread_mutex_lock(&that->switch_cv_write_mutex);
      pthread_cond_broadcast(&that->switch_cv_write);
    pthread_mutex_unlock(&that->switch_cv_write_mutex);  
  }
  return res;
}

BOOL com_github_airutech_cnets_queue_dequeue(com_github_airutech_cnets_queue *that,uint32_t *obj, uint32_t timeout_milisec, int spinCount){
  BOOL res = FALSE;
  int i=0;
  do{
    res = dequeue(that->qs,obj);
  }while(!res && ++i<spinCount && timeout_milisec);
  if(!res && timeout_milisec){
    struct timespec wait_timespec = getTimespecDelay((uint64_t)timeout_milisec*(uint64_t)1000000L);
    pthread_mutex_lock(&that->switch_cv_write_mutex);
    if(!(res = dequeue(that->qs,obj))){
      do{
        if(ETIMEDOUT == pthread_cond_timedwait(&that->switch_cv_write, &that->switch_cv_write_mutex, &wait_timespec)){
          printf("WARN: com_github_airutech_cnets_queue_dequeue: wait timeout\n");
        }else{
          res = dequeue(that->qs,obj);
          if(res == TRUE)
            break;
        }
      }while(compareTimespec(&wait_timespec)<0);
    }
    pthread_mutex_unlock(&that->switch_cv_write_mutex);
  }
  if(res){
    pthread_mutex_lock(&that->switch_cv_read_mutex);
      pthread_cond_broadcast(&that->switch_cv_read);
    pthread_mutex_unlock(&that->switch_cv_read_mutex);  
  }
  return res;
}

void com_github_airutech_cnets_queue_clear(com_github_airutech_cnets_queue *that){
  lfds611QUEUE_atom_t *user_data;
  while( lfds611QUEUE_queue_dequeue(that->qs, (void *) &user_data) )
    ;
  pthread_mutex_lock(&that->switch_cv_read_mutex);
    pthread_cond_broadcast(&that->switch_cv_read);
  pthread_mutex_unlock(&that->switch_cv_read_mutex);  
}

void com_github_airutech_cnets_queue_onCreate(com_github_airutech_cnets_queue *that){
  int res;
  lfds611QUEUE_queue_new( &that->qs, that->capacity );
  res = pthread_mutex_init(&that->switch_cv_write_mutex, NULL);
  assert(!res);
  res = pthread_cond_init (&that->switch_cv_write, NULL);
  assert(!res);
  res = pthread_mutex_init(&that->switch_cv_read_mutex, NULL);
  assert(!res);
  res = pthread_cond_init (&that->switch_cv_read, NULL);
  assert(!res);  
  that->enqueue = com_github_airutech_cnets_queue_enqueue;
  that->dequeue = com_github_airutech_cnets_queue_dequeue;
  that->clear = com_github_airutech_cnets_queue_clear;
  return;
}

void com_github_airutech_cnets_queue_onDestroy(com_github_airutech_cnets_queue *that){
  int res;
  lfds611QUEUE_queue_delete( that->qs, NULL, NULL );
  res = pthread_mutex_destroy(&that->switch_cv_write_mutex);
  assert(!res);
  res = pthread_cond_destroy(&that->switch_cv_write);
  assert(!res);
  res = pthread_mutex_destroy(&that->switch_cv_read_mutex);
  assert(!res);
  res = pthread_cond_destroy(&that->switch_cv_read);
  assert(!res);  
  return;
}

void com_github_airutech_cnets_queue_onKernels(com_github_airutech_cnets_queue *that){
  
  return;
}


