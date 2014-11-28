
from helper import *
#           Environment
Import( 'env', 'args' )

def add_dependencies(env, args):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  AddDependency(args,'com_github_airutech_cnets_types',join(args['PROJECTS_ROOT_PATH'],'src/github.com/airutech/cnets/types/c'))
  '''[[[end]]] (checksum: fadfcc0286d5ede2436d06ea30ca4283)'''
  # AddPthreads(env, args)
  # AddNetwork(args) 

c = {}

c['PROG_NAME'] = 'com_github_airutech_cnets_queue'
c['sourceFiles'] = [
  'queue.c',
  "lfds611/lfds611_liblfds/lfds611_liblfds_abstraction_test_helpers.c",
  "lfds611/lfds611_liblfds/lfds611_liblfds_aligned_free.c",
  "lfds611/lfds611_liblfds/lfds611_liblfds_aligned_malloc.c",
  "lfds611/lfds611_freelist/lfds611_freelist_delete.c",  
  "lfds611/lfds611_freelist/lfds611_freelist_get_and_set.c",  
  "lfds611/lfds611_freelist/lfds611_freelist_new.c",  
  "lfds611/lfds611_freelist/lfds611_freelist_pop_push.c",  
  "lfds611/lfds611_freelist/lfds611_freelist_query.c",  
  "lfds611/lfds611_queue/lfds611_queue_delete.c",
  "lfds611/lfds611_queue/lfds611_queue_new.c",
  "lfds611/lfds611_queue/lfds611_queue_query.c",
  "lfds611/lfds611_queue/lfds611_queue_queue.c",
  "lfds611/lfds611_abstraction/lfds611_abstraction_malloc.c",
  "lfds611/lfds611_abstraction/lfds611_abstraction_free.c"
]
c['testFiles'] = ['queueTest.c']
c['runFiles'] = ['main.c']
c['defines'] = []
c['paths'] = [join(args['SNOCSCRIPT_PATH'],'src','lfds611')]
c['inclDepsDynamic'] = add_dependencies
c['inclDepsStatic'] = add_dependencies
DefaultLibraryConfig(c, env, args)