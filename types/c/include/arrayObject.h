#ifndef com_github_osblinnikov_cnets_types_arrayObject_H
#define com_github_osblinnikov_cnets_types_arrayObject_H

#include "./types.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct arrayObject{
  void* array;
  unsigned length;
  unsigned itemSize;
}arrayObject;

#define arrayObject_create(_NAME_, _type, _capacity)\
    arrayObject _NAME_;\
    _type* _NAME_##_data_ = (_type*)salloca(sizeof(_type)*_capacity);\
    _NAME_.array = (void*)_NAME_##_data_;\
    _NAME_.length = _capacity;\
    _NAME_.itemSize = sizeof(_type);

#define arrayObject_create_dynamic(_NAME_, _type, _capacity)\
    arrayObject _NAME_;\
    _type* _NAME_##_data_ = (_type*)malloc(sizeof(_type)*_capacity);\
    if(_NAME_##_data_ == NULL){printf("MALLOC FAILED FOR "_NAME_" "_type" "_capacity);}\
    _NAME_.array = (void*)_NAME_##_data_;\
    _NAME_.length = _capacity;\
    _NAME_.itemSize = sizeof(_type);

com_github_osblinnikov_cnets_types_EXPORT_API
struct arrayObject arrayObject_init_dynamic(unsigned itemSize, unsigned capacity);

com_github_osblinnikov_cnets_types_EXPORT_API
void arrayObject_free_dynamic(struct arrayObject arr);

com_github_osblinnikov_cnets_types_EXPORT_API
struct arrayObject arrayObjectNULL();

#endif /* com_github_osblinnikov_cnets_types_arrayObject_H */