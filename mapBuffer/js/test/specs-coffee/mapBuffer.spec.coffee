isNode = typeof module isnt "undefined" and module.exports
if isNode
  s = {}
  s.mapBuffer = s.com_github_osblinnikov_cnets_mapBuffer = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_mapBuffer/mapBuffer.js")
  s.types = s.com_github_osblinnikov_cnets_types = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_types/types.js")
else
  s = self

describe "mapBuffer-API", ->
  it "should define the used API", ->
    expect(s.mapBuffer.create).toEqual jasmine.any(Function)
    m = new s.mapBuffer.create()
    expect(m.setDispatcher).toEqual jasmine.any(Function)
    expect(m.dispatchMessage).toEqual jasmine.any(Function)
    expect(m.getReader).toEqual jasmine.any(Function)
    expect(m.getWriter).toEqual jasmine.any(Function)
    expect(m.readNext).toEqual jasmine.any(Function)
    expect(m.readNextWithMeta).toEqual jasmine.any(Function)
    expect(m.readFinished).toEqual jasmine.any(Function)
    expect(m.writeNext).toEqual jasmine.any(Function)
    expect(m.writeFinished).toEqual jasmine.any(Function)
    expect(m.size).toEqual jasmine.any(Function)
    expect(m.gridSize).toEqual jasmine.any(Function)
    expect(m.uniqueId).toEqual jasmine.any(Function)
    expect(m.init).toEqual jasmine.any(Function)
    expect(m.addConnection).toEqual jasmine.any(Function)
    expect(m.syncConnections).toEqual jasmine.any(Function)
    return

describe "mapBuffer-send-receive", ->
  it "should send the given message", ->
    expect(s.mapBuffer.create).toEqual jasmine.any(Function)
    expect(s.com_github_osblinnikov_cnets_types.Worker).toEqual jasmine.any(Function)

    wrk0 = new s.com_github_osblinnikov_cnets_types.Worker('/test/specs/mapBuffer.sender.js')
    wrk1 = new s.com_github_osblinnikov_cnets_types.Worker('/test/specs/mapBuffer.receiver.js')

    buffers = []
    buffers.length = 2
    mBufferToSender = new s.mapBuffer.create(buffers, 1000, 1)
    rootW0 = mBufferToSender.getWriter()

    mBufferToSender.registerSrc(undefined, undefined)
    mBufferToSender.registerDst(wrk0, 0)
    mBufferToSender.syncRegister()

    buffers = []
    buffers.length = 2
    mBufferExchange = new s.mapBuffer.create(buffers, 1000, 1)
    mBufferExchange.registerSrc(wrk0, 1)
    mBufferExchange.registerDst(wrk1, 0)
    mBufferExchange.syncRegister()

    buffers = []
    buffers.length = 2
    mBufferFromReceiver = new s.mapBuffer.create(buffers, 1000, 1)

    result = undefined
    done = false
    rootR1 = mBufferFromReceiver.getReader(
      callback: (bufId, target)->
        # console.log "recevied!!!!!!!! eeee"
        done = true
        obj = rootR1.readNext()
        if obj != null
          result = obj.obj
          console.log "successfuly read message:"+result
          rootR1.readFinished()
    )


    mBufferFromReceiver.registerSrc(wrk1, 1)
    mBufferFromReceiver.registerDst(undefined, undefined)
    mBufferFromReceiver.syncRegister()

    runs ->
      obj = rootW0.writeNext()
      if obj != null
        console.log "write Next OK"
        obj.obj = "Test Should Be Passed"
        rootW0.writeFinished()

    waitsFor (->
      done
    ), "should finish", 2000
    
    #wrk0.postMessage({type:'stop'})
    #wrk1.postMessage({type:'stop'})

    runs ->
      expect(result).toEqual "Test Should Be Passed"
      return

