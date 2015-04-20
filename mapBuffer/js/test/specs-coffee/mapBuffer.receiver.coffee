importScripts(
  '/dist/com_github_osblinnikov_cnets_readerWriter/readerWriter.js',
  '/dist/com_github_osblinnikov_cnets_types/types.js',
  '/dist/com_github_osblinnikov_cnets_mapBuffer/mapBuffer.js'
)

onRun =
  callback: ->
    #dummy

_this = new Dispatcher(this)

_this.onStart = ->
  console.log "onStart receiver"

_this.onStop = ->
  console.log "onStop receiver"

bId = 0
readersWriters = {}

_bufferToReadTest = new mapBuffer.create()
_bufferToReadTest.setDispatcher(bId, _this)
readersWriters[bId] = _bufferToReadTest.getReader(onRun)
bId++

_bufferToWriteTest = new mapBuffer.create()
_bufferToWriteTest.setDispatcher(bId, _this)
readersWriters[bId] = _bufferToWriteTest.getWriter()
bId++


receivedData = null



onRun.callback = (mapBufferId, mapBufferObj)->
  switch mapBufferId
    when 0
      # console.log "onRun receiver _bufferToReadTest"
      r = readersWriters[mapBufferId].readNext()
      if r != null
        receivedData = r.obj
        readersWriters[mapBufferId].readFinished()
        onSend()
    when 1
      console.log "onRun receiver _bufferToWriteTest"
    else
      console.log "onRun receiver, unknown buffer"

onSend = ->
  if receivedData == null
    return
  r = readersWriters[1].writeNext()

  if r!=null
    r.obj = receivedData
    # console.log "send OK!"
    readersWriters[1].writeFinished()

    receivedData = null
  else
    setTimeout(onSend,100)