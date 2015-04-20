

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
  s.selector = s.com_github_osblinnikov_cnets_selector = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_selector/selector.js")
#[[[end]]] (checksum: b9adce2b9002b53d27aa9fddf6833b35) (2eaaa3e4c4115733b480c57493cb66ba)