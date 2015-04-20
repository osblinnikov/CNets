

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

s.com_github_osblinnikov_cnets_readerWriter =
  create: ()->
    that = this
    
    #dummy
#[[[end]]] (checksum: a170b28e951333fd8ed9dc0613862d10) (45d66d2c2fab0a8a235cc434febfbcac)


#IMPLEMENTATION GOES HERE

s.com_github_osblinnikov_cnets_readerWriter.reader = (bufKernParam)->
  self = this
  self.buffer = bufKernParam
  self.readNextWithMeta = ()->
    if not self.buffer
      return {}
    #todo: add here special code for debuging data flow
    return self.buffer.target.readNextWithMeta(self.buffer)

  self.readNext = ()->
    if not self.buffer
      return 0
    #todo: add here special code for debuging data flow
    return self.buffer.target.readNext(self.buffer)

  self.readFinished = ->
    if not self.buffer
      return 0
    #todo: add here special code for debuging data flow
    return self.buffer.target.readFinished(self.buffer)

  self.size = ->
    if not self.buffer
      return 0
    return self.buffer.target.size(self.buffer)

  self.getGridId = ->
    if not self.buffer
      return 0
    return self.buffer.target.grid_id

  self.timeout = ->
    if not self.buffer
      return 0
    return self.buffer.target.timeout(self.buffer)

  self.gridSize = ->
    if not self.buffer
      return 0
    return self.buffer.target.gridSize(self.buffer)

  self.uniqueId = ->
    if not self.buffer
      return 0
    return self.buffer.target.uniqueId(self.buffer)

  self.addSelector = (linkCont)->
    if not self.buffer
      return -1
    return self.buffer.target.addSelector(self.buffer, linkCont)
  true

s.com_github_osblinnikov_cnets_readerWriter.writer = (bufKernParam)->
  self = this
  self.buffer = bufKernParam
  self.writeNext = (make_timeout)->
    if not self.buffer
      return 0
    #todo: add here special code for debuging data flow
    return self.buffer.target.writeNext(self.buffer, make_timeout)

  self.writeFinished = ->
    if not self.buffer
      return 0
    #todo: add here special code for debuging data flow
    return self.buffer.target.writeFinished(self.buffer)

  self.size = ->
    if not self.buffer
      return 0
    return self.buffer.target.size(self.buffer)

  self.getGridId = ->
    if not self.buffer
      return 0
    return self.buffer.target.grid_id

  self.timeout = ->
    if not self.buffer
      return 0
    return self.buffer.target.timeout(self.buffer)

  self.gridSize = ->
    if not self.buffer
      return 0
    return self.buffer.target.gridSize(self.buffer)

  self.uniqueId = ->
    if not self.buffer
      return 0
    return self.buffer.target.uniqueId(self.buffer)

  self.copy = ->
    return new writer(self.buffer.copy())
  true

s.com_github_osblinnikov_cnets_readerWriter.statsCollectorStatic =
  w: null
  setWriter: (wIn)->
    if w == null
      w = wIn
    else
      console.error("WARN: statsCollectorStatic: setWriter: writer already set")

  getWriter:->
    if w != null
      return w.copy()
    else
      return null;

  localId: 0
  getNextLocalId: ->
    #console.log "nextLocalId"+this.localId
    return this.localId++

  statsInterval: 0
  setStatsInterval: (i)->
    this.statsInterval = i
  getStatsInterval: ->
    return this.statsInterval



if isNode
  module.exports = s.com_github_osblinnikov_cnets_readerWriter