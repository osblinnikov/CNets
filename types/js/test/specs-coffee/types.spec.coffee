

#[[[cog
#import cogging as c
#c.tpl(cog,templateFile,c.a(prefix=configFile))
#]]]

isNode = typeof module isnt "undefined" and module.exports and process and process.title != 'browser'
if isNode
  s = {}
else
  s = self

  s.types = s.com_github_airutech_cnets_types = require(__dirname + "/../../dist/com_github_airutech_cnets_types/types.js")
#[[[end]]] (checksum: 9f1fa37f9756122d07b4284c0e26f9b7)