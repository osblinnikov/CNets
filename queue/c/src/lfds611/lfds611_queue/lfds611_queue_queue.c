#include "lfds611_queue_internal.h"





/****************************************************************************/
int lfds611QUEUE_queue_enqueue( struct lfds611QUEUE_queue_state *qs, void *user_data )
{
  LFDS611QUEUE_ALIGN(LFDS611QUEUE_ALIGN_DOUBLE_POINTER) struct lfds611QUEUE_queue_element
    *qe[LFDS611QUEUE_QUEUE_PAC_SIZE];

  assert( qs != NULL );
  // TRD : user_data can be NULL

  lfds611QUEUE_queue_internal_new_element_from_freelist( qs, qe, user_data );

  if( qe[LFDS611QUEUE_QUEUE_POINTER] == NULL )
    return( 0 );

  lfds611QUEUE_queue_internal_queue( qs, qe );

  return( 1 );
}





/****************************************************************************/
int lfds611QUEUE_queue_guaranteed_enqueue( struct lfds611QUEUE_queue_state *qs, void *user_data )
{
  LFDS611QUEUE_ALIGN(LFDS611QUEUE_ALIGN_DOUBLE_POINTER) struct lfds611QUEUE_queue_element
    *qe[LFDS611QUEUE_QUEUE_PAC_SIZE];

  assert( qs != NULL );
  // TRD : user_data can be NULL

  lfds611QUEUE_queue_internal_guaranteed_new_element_from_freelist( qs, qe, user_data );

  if( qe[LFDS611QUEUE_QUEUE_POINTER] == NULL )
    return( 0 );

  lfds611QUEUE_queue_internal_queue( qs, qe );

  return( 1 );
}





/****************************************************************************/
void lfds611QUEUE_queue_internal_queue( struct lfds611QUEUE_queue_state *qs, struct lfds611QUEUE_queue_element *qe[LFDS611QUEUE_QUEUE_PAC_SIZE] )
{
  LFDS611QUEUE_ALIGN(LFDS611QUEUE_ALIGN_DOUBLE_POINTER) struct lfds611QUEUE_queue_element
    *enqueue[LFDS611QUEUE_QUEUE_PAC_SIZE],
    *next[LFDS611QUEUE_QUEUE_PAC_SIZE];

  unsigned char
    cas_result = 0;

  assert( qs != NULL );
  assert( qe != NULL );

  // TRD : the DCAS operation issues a read and write barrier, so we don't need a read barrier in the do() loop

  LFDS611QUEUE_BARRIER_LOAD;

  do
  {
    enqueue[LFDS611QUEUE_QUEUE_POINTER] = qs->enqueue[LFDS611QUEUE_QUEUE_POINTER];
    enqueue[LFDS611QUEUE_QUEUE_COUNTER] = qs->enqueue[LFDS611QUEUE_QUEUE_COUNTER];

    next[LFDS611QUEUE_QUEUE_POINTER] = enqueue[LFDS611QUEUE_QUEUE_POINTER]->next[LFDS611QUEUE_QUEUE_POINTER];
    next[LFDS611QUEUE_QUEUE_COUNTER] = enqueue[LFDS611QUEUE_QUEUE_POINTER]->next[LFDS611QUEUE_QUEUE_COUNTER];

    /* TRD : this if() ensures that the next we read, just above,
             really is from qs->enqueue (which we copied into enqueue)
    */

    LFDS611QUEUE_BARRIER_LOAD;

    if( qs->enqueue[LFDS611QUEUE_QUEUE_POINTER] == enqueue[LFDS611QUEUE_QUEUE_POINTER] and qs->enqueue[LFDS611QUEUE_QUEUE_COUNTER] == enqueue[LFDS611QUEUE_QUEUE_COUNTER] )
    {
      if( next[LFDS611QUEUE_QUEUE_POINTER] == NULL )
      {
        qe[LFDS611QUEUE_QUEUE_COUNTER] = next[LFDS611QUEUE_QUEUE_COUNTER] + 1;
        cas_result = lfds611QUEUE_abstraction_dcas( (volatile lfds611QUEUE_atom_t *) enqueue[LFDS611QUEUE_QUEUE_POINTER]->next, (lfds611QUEUE_atom_t *) qe, (lfds611QUEUE_atom_t *) next );
      }
      else
      {
        next[LFDS611QUEUE_QUEUE_COUNTER] = enqueue[LFDS611QUEUE_QUEUE_COUNTER] + 1;
        lfds611QUEUE_abstraction_dcas( (volatile lfds611QUEUE_atom_t *) qs->enqueue, (lfds611QUEUE_atom_t *) next, (lfds611QUEUE_atom_t *) enqueue );
      }
    }
  }
  while( cas_result == 0 );

  qe[LFDS611QUEUE_QUEUE_COUNTER] = enqueue[LFDS611QUEUE_QUEUE_COUNTER] + 1;
  lfds611QUEUE_abstraction_dcas( (volatile lfds611QUEUE_atom_t *) qs->enqueue, (lfds611QUEUE_atom_t *) qe, (lfds611QUEUE_atom_t *) enqueue );

  return;
}





/****************************************************************************/
int lfds611QUEUE_queue_dequeue( struct lfds611QUEUE_queue_state *qs, void **user_data )
{
  LFDS611QUEUE_ALIGN(LFDS611QUEUE_ALIGN_DOUBLE_POINTER) struct lfds611QUEUE_queue_element
    *enqueue[LFDS611QUEUE_QUEUE_PAC_SIZE],
    *dequeue[LFDS611QUEUE_QUEUE_PAC_SIZE],
    *next[LFDS611QUEUE_QUEUE_PAC_SIZE];

  unsigned char
    cas_result = 0;

  int
    rv = 1,
    state = LFDS611QUEUE_QUEUE_STATE_UNKNOWN,
    finished_flag = LOWERED;

  assert( qs != NULL );
  assert( user_data != NULL );

  // TRD : the DCAS operation issues a read and write barrier, so we don't need a read barrier in the do() loop

  LFDS611QUEUE_BARRIER_LOAD;

  do
  {
    dequeue[LFDS611QUEUE_QUEUE_POINTER] = qs->dequeue[LFDS611QUEUE_QUEUE_POINTER];
    dequeue[LFDS611QUEUE_QUEUE_COUNTER] = qs->dequeue[LFDS611QUEUE_QUEUE_COUNTER];

    enqueue[LFDS611QUEUE_QUEUE_POINTER] = qs->enqueue[LFDS611QUEUE_QUEUE_POINTER];
    enqueue[LFDS611QUEUE_QUEUE_COUNTER] = qs->enqueue[LFDS611QUEUE_QUEUE_COUNTER];

    next[LFDS611QUEUE_QUEUE_POINTER] = dequeue[LFDS611QUEUE_QUEUE_POINTER]->next[LFDS611QUEUE_QUEUE_POINTER];
    next[LFDS611QUEUE_QUEUE_COUNTER] = dequeue[LFDS611QUEUE_QUEUE_POINTER]->next[LFDS611QUEUE_QUEUE_COUNTER];

    /* TRD : confirm that dequeue didn't move between reading it
             and reading its next pointer
    */

    LFDS611QUEUE_BARRIER_LOAD;

    if( dequeue[LFDS611QUEUE_QUEUE_POINTER] == qs->dequeue[LFDS611QUEUE_QUEUE_POINTER] and dequeue[LFDS611QUEUE_QUEUE_COUNTER] == qs->dequeue[LFDS611QUEUE_QUEUE_COUNTER] )
    {
      if( enqueue[LFDS611QUEUE_QUEUE_POINTER] == dequeue[LFDS611QUEUE_QUEUE_POINTER] and next[LFDS611QUEUE_QUEUE_POINTER] == NULL )
        state = LFDS611QUEUE_QUEUE_STATE_EMPTY;

      if( enqueue[LFDS611QUEUE_QUEUE_POINTER] == dequeue[LFDS611QUEUE_QUEUE_POINTER] and next[LFDS611QUEUE_QUEUE_POINTER] != NULL )
        state = LFDS611QUEUE_QUEUE_STATE_ENQUEUE_OUT_OF_PLACE;

      if( enqueue[LFDS611QUEUE_QUEUE_POINTER] != dequeue[LFDS611QUEUE_QUEUE_POINTER] )
        state = LFDS611QUEUE_QUEUE_STATE_ATTEMPT_DELFDS611QUEUE_QUEUE;

      switch( state )
      {
        case LFDS611QUEUE_QUEUE_STATE_EMPTY:
          *user_data = NULL;
          rv = 0;
          finished_flag = RAISED;
        break;

        case LFDS611QUEUE_QUEUE_STATE_ENQUEUE_OUT_OF_PLACE:
          next[LFDS611QUEUE_QUEUE_COUNTER] = enqueue[LFDS611QUEUE_QUEUE_COUNTER] + 1;
          lfds611QUEUE_abstraction_dcas( (volatile lfds611QUEUE_atom_t *) qs->enqueue, (lfds611QUEUE_atom_t *) next, (lfds611QUEUE_atom_t *) enqueue );
        break;

        case LFDS611QUEUE_QUEUE_STATE_ATTEMPT_DELFDS611QUEUE_QUEUE:
          *user_data = next[LFDS611QUEUE_QUEUE_POINTER]->user_data;

          next[LFDS611QUEUE_QUEUE_COUNTER] = dequeue[LFDS611QUEUE_QUEUE_COUNTER] + 1;
          cas_result = lfds611QUEUE_abstraction_dcas( (volatile lfds611QUEUE_atom_t *) qs->dequeue, (lfds611QUEUE_atom_t *) next, (lfds611QUEUE_atom_t *) dequeue );

          if( cas_result == 1 )
            finished_flag = RAISED;
        break;
      }
    }
  }
  while( finished_flag == LOWERED );

  if( cas_result == 1 )
    lfds611QUEUE_freelist_push( qs->fs, dequeue[LFDS611QUEUE_QUEUE_POINTER]->fe );

  return( rv );
}

