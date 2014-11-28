#ifndef __LIBLFDS611QUEUE_H

  /***** library header *****/
  #define LFDS611QUEUE_RELEASE_NUMBER_STRING  "6.1.1"




  /***** lfds611QUEUE_abstraction *****/

  /***** defines *****/
  #if (defined _WIN64 && defined _MSC_VER && !defined WIN_KERNEL_BUILD)
    // TRD : 64-bit Windows user-mode with the Microsoft C compiler, any CPU
    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <windows.h>
    #include <intrin.h>
    typedef unsigned __int64                 lfds611QUEUE_atom_t;
    #define LFDS611QUEUE_INLINE                   __forceinline
    #define LFDS611QUEUE_ALIGN(alignment)         __declspec( align(alignment) )
    #define LFDS611QUEUE_ALIGN_SINGLE_POINTER     8
    #define LFDS611QUEUE_ALIGN_DOUBLE_POINTER     16
    #define LFDS611QUEUE_BARRIER_COMPILER_LOAD    _ReadBarrier()
    #define LFDS611QUEUE_BARRIER_COMPILER_STORE   _WriteBarrier()
    #define LFDS611QUEUE_BARRIER_COMPILER_FULL    _ReadWriteBarrier()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_LOAD   _mm_lfence()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_STORE  _mm_sfence()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_FULL   _mm_mfence()
  #endif

  #if (!defined _WIN64 && defined _WIN32 && defined _MSC_VER && !defined WIN_KERNEL_BUILD)
    // TRD : 32-bit Windows user-mode with the Microsoft C compiler, any CPU
    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <windows.h>
    #include <intrin.h>
    typedef unsigned long int                lfds611QUEUE_atom_t;
    #define LFDS611QUEUE_INLINE                   __forceinline
    #define LFDS611QUEUE_ALIGN(alignment)         __declspec( align(alignment) )
    #define LFDS611QUEUE_ALIGN_SINGLE_POINTER     4
    #define LFDS611QUEUE_ALIGN_DOUBLE_POINTER     8
    #define LFDS611QUEUE_BARRIER_COMPILER_LOAD    _ReadBarrier()
    #define LFDS611QUEUE_BARRIER_COMPILER_STORE   _WriteBarrier()
    #define LFDS611QUEUE_BARRIER_COMPILER_FULL    _ReadWriteBarrier()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_LOAD   _mm_lfence()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_STORE  _mm_sfence()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_FULL   _mm_mfence()

    // TRD : this define is documented but missing in Microsoft Platform SDK v7.0
    #define _InterlockedCompareExchangePointer(destination, exchange, compare) _InterlockedCompareExchange((volatile long *) destination, (long) exchange, (long) compare)
  #endif

  #if (defined _WIN64 && defined _MSC_VER && defined WIN_KERNEL_BUILD)
    // TRD : 64-bit Windows kernel with the Microsoft C compiler, any CPU
    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <wdm.h>
    typedef unsigned __int64                 lfds611QUEUE_atom_t;
    #define LFDS611QUEUE_INLINE                   __forceinline
    #define LFDS611QUEUE_ALIGN(alignment)         __declspec( align(alignment) )
    #define LFDS611QUEUE_ALIGN_SINGLE_POINTER     8
    #define LFDS611QUEUE_ALIGN_DOUBLE_POINTER     16
    #define LFDS611QUEUE_BARRIER_COMPILER_LOAD    _ReadBarrier()
    #define LFDS611QUEUE_BARRIER_COMPILER_STORE   _WriteBarrier()
    #define LFDS611QUEUE_BARRIER_COMPILER_FULL    _ReadWriteBarrier()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_LOAD   _mm_lfence()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_STORE  _mm_sfence()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_FULL   _mm_mfence()
  #endif

  #if (!defined _WIN64 && defined _WIN32 && defined _MSC_VER && defined WIN_KERNEL_BUILD)
    // TRD : 32-bit Windows kernel with the Microsoft C compiler, any CPU
    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <wdm.h>
    typedef unsigned long int                lfds611QUEUE_atom_t;
    #define LFDS611QUEUE_INLINE                   __forceinline
    #define LFDS611QUEUE_ALIGN(alignment)         __declspec( align(alignment) )
    #define LFDS611QUEUE_ALIGN_SINGLE_POINTER     4
    #define LFDS611QUEUE_ALIGN_DOUBLE_POINTER     8
    #define LFDS611QUEUE_BARRIER_COMPILER_LOAD    _ReadBarrier()
    #define LFDS611QUEUE_BARRIER_COMPILER_STORE   _WriteBarrier()
    #define LFDS611QUEUE_BARRIER_COMPILER_FULL    _ReadWriteBarrier()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_LOAD   _mm_lfence()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_STORE  _mm_sfence()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_FULL   _mm_mfence()

    // TRD : this define is documented but missing in Microsoft Platform SDK v7.0
    #define _InterlockedCompareExchangePointer(destination, exchange, compare) _InterlockedCompareExchange((volatile long *) destination, (long) exchange, (long) compare)
  #endif

  #if (defined __unix__ && defined __x86_64__ && __GNUC__)
    // TRD : any UNIX with GCC on x64
    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    typedef unsigned long long int           lfds611QUEUE_atom_t;
    #define LFDS611QUEUE_INLINE                   inline
    #define LFDS611QUEUE_ALIGN(alignment)         __attribute__( (aligned(alignment)) )
    #define LFDS611QUEUE_ALIGN_SINGLE_POINTER     8
    #define LFDS611QUEUE_ALIGN_DOUBLE_POINTER     16
    #define LFDS611QUEUE_BARRIER_COMPILER_LOAD    __asm__ __volatile__ ( "" : : : "memory" )
    #define LFDS611QUEUE_BARRIER_COMPILER_STORE   __asm__ __volatile__ ( "" : : : "memory" )
    #define LFDS611QUEUE_BARRIER_COMPILER_FULL    __asm__ __volatile__ ( "" : : : "memory" )
    #define LFDS611QUEUE_BARRIER_PROCESSOR_LOAD   __sync_synchronize()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_STORE  __sync_synchronize()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_FULL   __sync_synchronize()
  #endif

  #if (defined __unix__ && defined __i686__ && __GNUC__)
    // TRD : any UNIX with GCC on x86
    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    typedef unsigned long int                lfds611QUEUE_atom_t;
    #define LFDS611QUEUE_INLINE                   inline
    #define LFDS611QUEUE_ALIGN(alignment)         __attribute__( (aligned(alignment)) )
    #define LFDS611QUEUE_ALIGN_SINGLE_POINTER     4
    #define LFDS611QUEUE_ALIGN_DOUBLE_POINTER     8
    #define LFDS611QUEUE_BARRIER_COMPILER_LOAD    __asm__ __volatile__ ( "" : : : "memory" )
    #define LFDS611QUEUE_BARRIER_COMPILER_STORE   __asm__ __volatile__ ( "" : : : "memory" )
    #define LFDS611QUEUE_BARRIER_COMPILER_FULL    __asm__ __volatile__ ( "" : : : "memory" )
    #define LFDS611QUEUE_BARRIER_PROCESSOR_LOAD   __sync_synchronize()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_STORE  __sync_synchronize()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_FULL   __sync_synchronize()
  #endif

  #if (defined __unix__ && defined __arm__ && __GNUC__)
    // TRD : any UNIX with GCC on ARM
    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    typedef unsigned long int                lfds611QUEUE_atom_t;
    #define LFDS611QUEUE_INLINE                   inline
    #define LFDS611QUEUE_ALIGN(alignment)         __attribute__( (aligned(alignment)) )
    #define LFDS611QUEUE_ALIGN_SINGLE_POINTER     4
    #define LFDS611QUEUE_ALIGN_DOUBLE_POINTER     8
    #define LFDS611QUEUE_BARRIER_COMPILER_LOAD    __asm__ __volatile__ ( "" : : : "memory" )
    #define LFDS611QUEUE_BARRIER_COMPILER_STORE   __asm__ __volatile__ ( "" : : : "memory" )
    #define LFDS611QUEUE_BARRIER_COMPILER_FULL    __asm__ __volatile__ ( "" : : : "memory" )
    #define LFDS611QUEUE_BARRIER_PROCESSOR_LOAD   __sync_synchronize()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_STORE  __sync_synchronize()
    #define LFDS611QUEUE_BARRIER_PROCESSOR_FULL   __sync_synchronize()
  #endif

  #define LFDS611QUEUE_BARRIER_LOAD   LFDS611QUEUE_BARRIER_COMPILER_LOAD; LFDS611QUEUE_BARRIER_PROCESSOR_LOAD; LFDS611QUEUE_BARRIER_COMPILER_LOAD
  #define LFDS611QUEUE_BARRIER_STORE  LFDS611QUEUE_BARRIER_COMPILER_STORE; LFDS611QUEUE_BARRIER_PROCESSOR_STORE; LFDS611QUEUE_BARRIER_COMPILER_STORE
  #define LFDS611QUEUE_BARRIER_FULL   LFDS611QUEUE_BARRIER_COMPILER_FULL; LFDS611QUEUE_BARRIER_PROCESSOR_FULL; LFDS611QUEUE_BARRIER_COMPILER_FULL

  /***** enums *****/
  enum lfds611QUEUE_data_structure_validity
  {
    LFDS611QUEUE_VALIDITY_VALID,
    LFDS611QUEUE_VALIDITY_INVALID_LOOP,
    LFDS611QUEUE_VALIDITY_INVALID_MISSING_ELEMENTS,
    LFDS611QUEUE_VALIDITY_INVALID_ADDITIONAL_ELEMENTS,
    LFDS611QUEUE_VALIDITY_INVALID_TEST_DATA
  };

  /***** structs *****/
  struct lfds611QUEUE_validation_info
  {
    lfds611QUEUE_atom_t
      min_elements,
      max_elements;
  };

  /***** public prototypes *****/
  void *lfds611QUEUE_abstraction_malloc( size_t size );
  void lfds611QUEUE_abstraction_free( void *memory );

  /***** lfds611QUEUE_liblfds *****/

  /***** public prototypes *****/
  void lfds611QUEUE_liblfds_abstraction_test_helper_increment_non_atomic( lfds611QUEUE_atom_t *shared_counter );
  void lfds611QUEUE_liblfds_abstraction_test_helper_increment_atomic( volatile lfds611QUEUE_atom_t *shared_counter );
  void lfds611QUEUE_liblfds_abstraction_test_helper_cas( volatile lfds611QUEUE_atom_t *shared_counter, lfds611QUEUE_atom_t *local_counter );
  void lfds611QUEUE_liblfds_abstraction_test_helper_dcas( volatile lfds611QUEUE_atom_t *shared_counter, lfds611QUEUE_atom_t *local_counter );





  /***** lfds611QUEUE_queue *****/

  /***** enums *****/
  enum lfds611QUEUE_queue_query_type
  {
    LFDS611QUEUE_QUEUE_QUERY_ELEMENT_COUNT,
    LFDS611QUEUE_QUEUE_QUERY_VALIDATE
  };

  /***** incomplete types *****/
  struct lfds611QUEUE_queue_state;

  /***** public prototypes *****/
  int lfds611QUEUE_queue_new( struct lfds611QUEUE_queue_state **sq, lfds611QUEUE_atom_t number_elements );
  void lfds611QUEUE_queue_use( struct lfds611QUEUE_queue_state *qs );
  void lfds611QUEUE_queue_delete( struct lfds611QUEUE_queue_state *qs, void (*user_data_delete_function)(void *user_data, void *user_state), void *user_state );

  int lfds611QUEUE_queue_enqueue( struct lfds611QUEUE_queue_state *qs, void *user_data );
  int lfds611QUEUE_queue_guaranteed_enqueue( struct lfds611QUEUE_queue_state *qs, void *user_data );
  int lfds611QUEUE_queue_dequeue( struct lfds611QUEUE_queue_state *qs, void **user_data );

  void lfds611QUEUE_queue_query( struct lfds611QUEUE_queue_state *qs, enum lfds611QUEUE_queue_query_type query_type, void *query_input, void *query_output );


  #define __LIBLFDS611QUEUE_H

#endif
