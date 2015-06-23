#ifndef types_cnets_osblinnikov_github_com_serializator_H
#define types_cnets_osblinnikov_github_com_serializator_H

#include "./types.h"
#include "./pt.h"

typedef struct serializator_types_cnets_osblinnikov_github_com{
  struct pt pt;
  int code;
  void *dst;
  int (*next)(struct serializator_types_cnets_osblinnikov_github_com *that, arrayObject to);
}serializator_types_cnets_osblinnikov_github_com;

typedef int (*serializator_types_cnets_osblinnikov_github_com_next)(struct serializator_types_cnets_osblinnikov_github_com *that, arrayObject to);

types_cnets_osblinnikov_github_com_EXPORT_API
  void serializator_types_cnets_osblinnikov_github_com_init(
    struct serializator_types_cnets_osblinnikov_github_com* that,
    serializator_types_cnets_osblinnikov_github_com_next next,
    void* dst
  );

#endif /* types_cnets_osblinnikov_github_com_serializator_H */
