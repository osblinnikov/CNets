

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

s.com_github_airutech_cnets_queue =
  create: (capacity)->
    that = this
    that.data = []
    that.data.length = capacity
    that.maxIndex
    that.head
    that.tail
    that.capacity = capacity
    #dummy
#[[[end]]] (checksum: 57230aaac3982c2ac2918b269302d3b3)

#This implememtation actually will be never used, but made for consistency with other languages
s.com_github_airutech_cnets_queue.data = []

if isNode
  module.exports = s.com_github_airutech_cnets_queue