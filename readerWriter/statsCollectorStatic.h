#ifndef readerWriter_cnets_osblinnikov_github_com_statsCollectorStatic_H
#define readerWriter_cnets_osblinnikov_github_com_statsCollectorStatic_H

#include "./Exports.h"
#include "./readerWriter.h"
#include "./writer.h"
#include <pthread.h>

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  void statsCollectorStatic_setWriter(writer wIn);

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  struct writer statsCollectorStatic_getWriter();

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  void statsCollectorStatic_setStatsInterval(uint64_t i);

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  uint64_t statsCollectorStatic_getStatsInterval();

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  int statsCollectorStatic_getNextLocalId();

#endif /* readerWriter_cnets_osblinnikov_github_com_statsCollectorStatic_H */
