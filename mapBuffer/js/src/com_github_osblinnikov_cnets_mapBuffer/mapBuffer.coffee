

#[[[cog
#import cogging as c
#c.tpl(cog,templateFile,c.a(prefix=configFile))
#]]]

isNode = typeof module isnt "undefined" and module.exports and process and process.title != 'browser'
if isNode
  s = {}
else
  s = self

if isNode
  s.types = s.com_github_osblinnikov_cnets_types = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_types/types.js")
  s.queue = s.com_github_osblinnikov_cnets_queue = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_queue/queue.js")
  s.readerWriter = s.com_github_osblinnikov_cnets_readerWriter = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_readerWriter/readerWriter.js")

s.com_github_osblinnikov_cnets_mapBuffer =
  create: (buffers,timeout_milisec,readers_grid_size)->
    that = this
    that.buffers = buffers
    that.timeout_milisec = timeout_milisec
    that.readers_grid_size = readers_grid_size
    #dummy
#[[[end]]] (checksum: a2ad146945089ca837166c1104267b15) (a2ad146945089ca837166c1104267b15)
    true

#IMPLEMENTATION GOES HERE


if isNode
  module.exports = s.com_github_osblinnikov_cnets_mapBuffer