#ifndef types_cnets_osblinnikov_github_com_serializator_H
#define types_cnets_osblinnikov_github_com_serializator_H

#include "./types.h"

typedef struct serializator_types_cnets_osblinnikov_github_com{
  void* context;
  arrayObject (*serialize)(struct serializator_types_cnets_osblinnikov_github_com* , void* target );
  void (*deserialize)(struct serializator_types_cnets_osblinnikov_github_com* , arrayObject binary );
}serializator_types_cnets_osblinnikov_github_com;

types_cnets_osblinnikov_github_com_EXPORT_API
  void serializator_types_cnets_osblinnikov_github_com_init(
    struct serializator_types_cnets_osblinnikov_github_com* that
  );

#endif /* types_cnets_osblinnikov_github_com_serializator_H */
