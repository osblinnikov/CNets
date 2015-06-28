#ifndef readerWriter_cnets_osblinnikov_github_com_bufferReadData_H
#define readerWriter_cnets_osblinnikov_github_com_bufferReadData_H

typedef struct bufferReadData{
  void* data;
  unsigned nested_buffer_id;
  unsigned writer_grid_id;
}bufferReadData;

#endif /* readerWriter_cnets_osblinnikov_github_com_bufferReadData_H */
