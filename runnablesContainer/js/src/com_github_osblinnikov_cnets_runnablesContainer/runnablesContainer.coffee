

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

s.com_github_osblinnikov_cnets_runnablesContainer =
  create: ()->
    that = this
    
    #dummy
#[[[end]]] (checksum: fe2214a36327e0221a46d2fea0cc634d) (3d34eb181308d8577151f1f4802484d6)

#Just dummy implementation of container. Kernel was moved to the types, to make mapBuffer more sustainable to changes
#and keep dependencies manageable

if isNode
  module.exports = s.com_github_osblinnikov_cnets_runnablesContainer