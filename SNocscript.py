from helper import *
#           Environment
Import( 'env' )

def add_dependencies(env):
  AddDependency(env,'com_github_osblinnikov_cnets_types','github.com/osblinnikov/cnets/types')
  AddDependency(env,'com_github_osblinnikov_cnets_selector','github.com/osblinnikov/cnets/selector')
  AddDependency(env,'com_github_osblinnikov_cnets_mapBuffer','github.com/osblinnikov/cnets/mapBuffer')
  AddDependency(env,'com_github_osblinnikov_cnets_runnablesContainer','github.com/osblinnikov/cnets/runnablesContainer')
  AddDependency(env,'com_github_osblinnikov_cnets_readerWriter','github.com/osblinnikov/cnets/readerWriter')
  AddDependency(env,'com_github_osblinnikov_cnets_queue','github.com/osblinnikov/cnets/queue')

c = {}
c['PROG_NAME'] = 'parent'
c['inclDeps'] = add_dependencies
DefaultParentConfig(env, c)

