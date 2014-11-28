/***** public prototypes *****/
#include "liblfds611.h"

/***** defines *****/
#define and &&
#define or  ||

#define RAISED   1
#define LOWERED  0

#define NO_FLAGS 0x0

/***** private prototypes *****/
void *lfds611QUEUE_liblfds_aligned_malloc( size_t size, size_t align_in_bytes );
void lfds611QUEUE_liblfds_aligned_free( void *memory );

static LFDS611QUEUE_INLINE lfds611QUEUE_atom_t lfds611QUEUE_abstraction_cas( volatile lfds611QUEUE_atom_t *destination, lfds611QUEUE_atom_t exchange, lfds611QUEUE_atom_t compare );
static LFDS611QUEUE_INLINE unsigned char lfds611QUEUE_abstraction_dcas( volatile lfds611QUEUE_atom_t *destination, lfds611QUEUE_atom_t *exchange, lfds611QUEUE_atom_t *compare );
static LFDS611QUEUE_INLINE lfds611QUEUE_atom_t lfds611QUEUE_abstraction_increment( volatile lfds611QUEUE_atom_t *value );

/***** inlined code *****/
#include "lfds611_abstraction/lfds611_abstraction_cas.c"
#include "lfds611_abstraction/lfds611_abstraction_dcas.c"
#include "lfds611_abstraction/lfds611_abstraction_increment.c"

