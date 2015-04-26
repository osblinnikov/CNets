from helper import *
#           Environment
Import( 'env' )

def add_dependencies(env):
  AddDependency(env,'types_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/types')
  AddDependency(env,'selector_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/selector')
  AddDependency(env,'mapBuffer_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/mapBuffer')
  AddDependency(env,'runnablesContainer_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/runnablesContainer')
  AddDependency(env,'readerWriter_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/readerWriter')
  AddDependency(env,'queue_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/queue')

c = {}
c['PROG_NAME'] = 'parent'
c['inclDeps'] = add_dependencies
DefaultParentConfig(env, c)

 