#ifndef readerWriter_cnets_osblinnikov_github_com_dispatcherCollector_H
#define readerWriter_cnets_osblinnikov_github_com_dispatcherCollector_H

#include "./Exports.h"
#include "./readerWriter.h"
#include "./writer.h"
#include <pthread.h>

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  void dispatcherCollector_deinit();

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  void dispatcherCollector_addWriter(writer wIn);

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  struct writer* dispatcherCollector_getWriter();

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  void dispatcherCollector_getStartLocalId();

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  void dispatcherCollector_tagAsStartLocalId();

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  unsigned dispatcherCollector_getLocalId();

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
  unsigned dispatcherCollector_getNextLocalId();

#endif /* readerWriter_cnets_osblinnikov_github_com_dispatcherCollector_H */
