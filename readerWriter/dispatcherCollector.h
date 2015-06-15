#ifndef readerWriter_cnets_osblinnikov_github_com_dispatcherCollector_H
#define readerWriter_cnets_osblinnikov_github_com_dispatcherCollector_H

#include "./Exports.h"
#include "./readerWriter.h"
#include "./writer.h"
#include <pthread.h>

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  void dispatcherCollector_setWriter(writer wIn);

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  struct writer dispatcherCollector_getWriter();

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  int dispatcherCollector_getNextLocalId();

#endif /* readerWriter_cnets_osblinnikov_github_com_dispatcherCollector_H */
