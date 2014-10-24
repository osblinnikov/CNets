

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
  s.queue = s.com_github_airutech_cnets_queue = require(__dirname + "/../../dist/com_github_airutech_cnets_queue/queue.js")
  s.types = s.com_github_airutech_cnets_types = require(__dirname + "/../../dist/com_github_airutech_cnets_types/types.js")
  s.readerWriter = s.com_github_airutech_cnets_readerWriter = require(__dirname + "/../../dist/com_github_airutech_cnets_readerWriter/readerWriter.js")
  s.mapBuffer = s.com_github_airutech_cnets_mapBuffer = require(__dirname + "/../../dist/com_github_airutech_cnets_mapBuffer/mapBuffer.js")
  s.runnablesContainer = s.com_github_airutech_cnets_runnablesContainer = require(__dirname + "/../../dist/com_github_airutech_cnets_runnablesContainer/runnablesContainer.js")
  s.selector = s.com_github_airutech_cnets_selector = require(__dirname + "/../../dist/com_github_airutech_cnets_selector/selector.js")
#[[[end]]] (checksum: 2eaaa3e4c4115733b480c57493cb66ba)