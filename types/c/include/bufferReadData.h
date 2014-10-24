#ifndef com_github_airutech_cnets_types_bufferReadData_H
#define com_github_airutech_cnets_types_bufferReadData_H

typedef struct bufferReadData{
  void* data;
  unsigned nested_buffer_id;
  unsigned writer_grid_id;
}bufferReadData;

#endif /* com_github_airutech_cnets_types_bufferReadData_H */