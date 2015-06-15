#ifndef types_cnets_osblinnikov_github_com_bufferKernelParams_H
#define types_cnets_osblinnikov_github_com_bufferKernelParams_H

#include "./bufferReadData.h"
#include "./arrayObject.h"

#define bufferKernelParams_create(_NAME_,_target, _grid_id, fullName_)\
    bufferKernelParams _NAME_;\
    _NAME_.bufferId = -1;\
    _NAME_.grid_id = _grid_id;\
    _NAME_.internalId = 0;\
    _NAME_.target = (void*)_target;\
    _NAME_.readNextWithMeta = fullName_##readNextWithMeta;\
    _NAME_.readNext = fullName_##readNext;\
    _NAME_.readFinished = fullName_##readFinished;\
    _NAME_.writeNext = fullName_##writeNext;\
    _NAME_.writeFinished = fullName_##writeFinished;\
    _NAME_.size = fullName_##size;\
    _NAME_.timeout = fullName_##timeout;\
    _NAME_.gridSize = fullName_##gridSize;\
    _NAME_.uniqueId = fullName_##uniqueId;\
    _NAME_.addSelector = fullName_##addSelector; \
    _NAME_.setKernelIds = fullName_##setKernelIds; \
    _NAME_.getKernelIds = fullName_##getKernelIds;

typedef struct bufferKernelParams{
  unsigned bufferId;
  unsigned grid_id;
  unsigned internalId;
  void* target;
  bufferReadData (*readNextWithMeta)(struct bufferKernelParams *params, int waitThreshold);
  void* (*readNext)(struct bufferKernelParams *params, int waitThreshold);
  int (*readFinished)(struct bufferKernelParams *params);
  void* (*writeNext)(struct bufferKernelParams *params, int waitThreshold);
  int (*writeFinished)(struct bufferKernelParams *params);
  int (*size)(struct bufferKernelParams *params);
  int64_t (*timeout)(struct bufferKernelParams *params);
  int (*gridSize)(struct bufferKernelParams *params);
  int (*uniqueId)(struct bufferKernelParams *params);
  int (*addSelector)(struct bufferKernelParams *params, void* selectorContainer);
  void (*setKernelIds)(struct bufferKernelParams *params, void* ids, void (*idsDestructor)(void*));
  void* (*getKernelIds)(struct bufferKernelParams *params);
}bufferKernelParams;

#endif /* types_cnets_osblinnikov_github_com_bufferKernelParams_H */
