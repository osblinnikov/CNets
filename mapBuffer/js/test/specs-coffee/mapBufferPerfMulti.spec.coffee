isNode = typeof module isnt "undefined" and module.exports
if isNode
  s = {}
  s.mapBuffer = s.com_github_airutech_cnets_mapBuffer = require(__dirname + "/../../dist/com_github_airutech_cnets_mapBuffer/mapBuffer.js")
  s.types = s.com_github_airutech_cnets_types = require(__dirname + "/../../dist/com_github_airutech_cnets_types/types.js")
else
  s = self

describe "mapBuffer-send-receive-perf-multi", ->
  it "should send many messages during 3 seconds", ->
    expect(s.mapBuffer.create).toEqual jasmine.any(Function)
    expect(s.com_github_airutech_cnets_types.Worker).toEqual jasmine.any(Function)

    wrk0 = new s.com_github_airutech_cnets_types.Worker('/test/specs/mapBufferPerfMulti.sender.js')
    wrk1 = new s.com_github_airutech_cnets_types.Worker('/test/specs/mapBufferPerfMulti.sender.js')
    wrk2 = new s.com_github_airutech_cnets_types.Worker('/test/specs/mapBufferPerfMulti.sender.js')

    buffers = []
    buffers.length = 200
    mBufferToSender = new s.mapBuffer.create(buffers, 1000, 3)
    mBufferToSender.addConnection(undefined,undefined,undefined,wrk0,dstWrkPinId = 0,dstWrGridId = 0)
    mBufferToSender.addConnection(undefined,undefined,undefined,wrk1,dstWrkPinId = 0,dstWrGridId = 1)
    mBufferToSender.addConnection(undefined,undefined,undefined,wrk2,dstWrkPinId = 0,dstWrGridId = 2)
    mBufferToSender.syncConnections()

    buffers = []
    buffers.length = 200
    mBufferFromSender = new s.mapBuffer.create(buffers, 1000, 1)
    mBufferFromSender.addConnection(wrk0,srcWrkPinId = 1,srcWrkGridId = 0,undefined,undefined,undefined)
    mBufferFromSender.addConnection(wrk1,srcWrkPinId = 1,srcWrkGridId = 1,undefined,undefined,undefined)
    mBufferFromSender.addConnection(wrk2,srcWrkPinId = 1,srcWrkGridId = 2,undefined,undefined,undefined)
    mBufferFromSender.syncConnections()

    done = false
    
    runs ->
      
      startTime = new Date().getTime()
      nextTickTime = startTime + 1000
      fps = 0
      errorsCntr = 0

      rootR1 = mBufferFromSender.getReader(
        callback: (bufId, target)->
          # console.log "recv"
          obj = rootR1.readNextWithMeta()
          if obj.data != null
            # console.log obj.writer_grid_id
            fps++
            curTime = new Date().getTime()
            if curTime > nextTickTime
              console.log "fps: "+fps+", failed writes:"+errorsCntr
              nextTickTime += 1000
              errorsCntr = 0
              fps = 0
            rootR1.readFinished()
      )



      requestAnimFrame = (->
        requestAnimationFrame = undefined
        if typeof window!= 'undefined'
          requestAnimationFrame = window.requestAnimationFrame or window.webkitRequestAnimationFrame or window.mozRequestAnimationFrame
        return requestAnimationFrame or (callback) ->
          setTimeout callback, 0
          return
      )()

      
      senderFunc = ->
        curTime = new Date().getTime()
        if curTime > startTime + 3000
          done = true
          return
        obj = rootW0.writeNext()
        if obj != null
          # console.log "send"
          rootW0.writeFinished()
          # senderFunc()
        else
          errorsCntr++
        #   requestAnimFrame senderFunc
      rootW0 = mBufferToSender.getWriter( callback: senderFunc )
      for i in [0...buffers.length*2]
        senderFunc()

    waitsFor (->
      done
    ), "should finish", 5000