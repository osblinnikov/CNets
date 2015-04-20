

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
#[[[end]]] (checksum: 9ae5d93d42902c3ad600059a3efb0f1d) (adb56d060ef20f99ba95be34bbdef54d)