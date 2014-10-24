importScripts(
  '/dist/com_github_airutech_cnets_readerWriter/readerWriter.js',
  '/dist/com_github_airutech_cnets_types/types.js',
  '/dist/com_github_airutech_cnets_mapBuffer/mapBuffer.js'
)

onRun =
  callback: ->
    #dummy

_this = new Dispatcher(this)

_this.onStart = ->
  console.log "onStart"

_this.onStop = ->
  console.log "onStop"

bId = 0
readersWriters = {}

_bufferToReadTest = new mapBuffer.create()
readersWriters[bId] = _bufferToReadTest.getReader(onRun)
_bufferToReadTest.setDispatcher(bId++, _this)

_bufferToWriteTest = new mapBuffer.create()
readersWriters[bId] = _bufferToWriteTest.getWriter()
_bufferToWriteTest.setDispatcher(bId++, _this)

receivedData = null

onRun.callback = (mapBufferId, mapBufferObj)->
  switch mapBufferId
    when 0
      console.log "onRun sender in 0"
      r = readersWriters[mapBufferId].readNext()
      if r != null
        receivedData = r.obj
        readersWriters[mapBufferId].readFinished()
        onSend()
    when 1
      console.log "onRun sender in 1"
    else
      console.log "onRun, unknown buffer"

onSend = ->
  if receivedData == null
    return
  r = readersWriters[1].writeNext()
  if r!=null
    r.obj = receivedData
    readersWriters[1].writeFinished()
    receivedData = null
  else
    setTimeout(onSend,100)