#ifndef com_github_osblinnikov_cnets_readerWriter_statsCollectorStatic_H
#define com_github_osblinnikov_cnets_readerWriter_statsCollectorStatic_H

#include "./readerWriter.h"
#include "./writer.h"
#include <pthread.h>

com_github_osblinnikov_cnets_readerWriter_EXPORT_API
  void statsCollectorStatic_setWriter(writer wIn);

com_github_osblinnikov_cnets_readerWriter_EXPORT_API
  struct writer statsCollectorStatic_getWriter();

com_github_osblinnikov_cnets_readerWriter_EXPORT_API
  void statsCollectorStatic_setStatsInterval(uint64_t i);

com_github_osblinnikov_cnets_readerWriter_EXPORT_API
  uint64_t statsCollectorStatic_getStatsInterval();

com_github_osblinnikov_cnets_readerWriter_EXPORT_API
  int statsCollectorStatic_getNextLocalId();

#endif /* com_github_osblinnikov_cnets_readerWriter_statsCollectorStatic_H */