

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
  s.types = s.com_github_airutech_cnets_types = require(__dirname + "/../../dist/com_github_airutech_cnets_types/types.js")
  s.readerWriter = s.com_github_airutech_cnets_readerWriter = require(__dirname + "/../../dist/com_github_airutech_cnets_readerWriter/readerWriter.js")
#[[[end]]] (checksum: 2cbe5e7e53fc23b1d0ee20ae96ff0635)