

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
  s.runnablesContainer = s.com_github_osblinnikov_cnets_runnablesContainer = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_runnablesContainer/runnablesContainer.js")
  s.queue = s.com_github_osblinnikov_cnets_queue = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_queue/queue.js")
  s.readerWriter = s.com_github_osblinnikov_cnets_readerWriter = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_readerWriter/readerWriter.js")
  s.mapBuffer = s.com_github_osblinnikov_cnets_mapBuffer = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_mapBuffer/mapBuffer.js")

s.com_github_osblinnikov_cnets_selector =
  create: (reducableReaders)->
    that = this
    that.reducableReaders = reducableReaders
    #dummy
#[[[end]]] (checksum: 3081c3ec59e5b5eabf5404e846fa2fd1) (e554beff1837cedf290fa5bfadec674b)

#########
# This is actually dummy implementation, and it will be never used, because JavaScript already fully asynchronous, and
# we don't need to wait explicitly for several events simultaneously
# this class exists only for compatibility with other languages
#########

if isNode
  module.exports = s.com_github_osblinnikov_cnets_selector