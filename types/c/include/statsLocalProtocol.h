#ifndef com_github_airutech_cnets_types_statsLocalProtocol_H
#define com_github_airutech_cnets_types_statsLocalProtocol_H

typedef struct com_github_airutech_cnets_types_statsLocalProtocol {
  long gridId;
  int uniqueId;
  int packets;
  int bytes;
  BOOL writer;
}com_github_airutech_cnets_types_statsLocalProtocol;

#endif /* com_github_airutech_cnets_types_statsLocalProtocol_H */