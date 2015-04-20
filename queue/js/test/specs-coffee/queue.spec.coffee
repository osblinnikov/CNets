

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
#[[[end]]] (checksum: eaaae8941e3ab5ed07eb3eda0d6938a1) (64ba36e4082e3bfc0587d9222c943056)