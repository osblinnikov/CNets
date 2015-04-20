

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
  s.queue = s.com_github_osblinnikov_cnets_queue = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_queue/queue.js")
  s.types = s.com_github_osblinnikov_cnets_types = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_types/types.js")
  s.readerWriter = s.com_github_osblinnikov_cnets_readerWriter = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_readerWriter/readerWriter.js")

s.com_github_osblinnikov_cnets_mapBuffer =
  create: (buffers,timeout_milisec,readers_grid_size)->
    that = this
    that.buffers = buffers
    that.timeout_milisec = timeout_milisec
    that.readers_grid_size = readers_grid_size
    #dummy
#[[[end]]] (cf74bbd4cfd26296ed286165ec2898ba)

#IMPLEMENTATION GOES HERE
mapBuffer = {}
s.mapBuffer = {}
mapBuffer.create = s.mapBuffer.create = s.com_github_osblinnikov_cnets_mapBuffer.create = (buffers, timeout_milisec, readers_grid_size)->
  self = this
  self.setDispatcher = (curBufId, dispatcherForAddingBuffer)->
    self.curBufId = curBufId
    self.dispatcherForAddingBuffer = dispatcherForAddingBuffer
    if self.dispatcherForAddingBuffer
      self.dispatcherForAddingBuffer.addBuffer(self)

  self.ports = []
  self.timeout_milisec = timeout_milisec
  self.buffers = buffers
  self.buffers_to_read = []
  self.buffers_addData = []
  self.buffers_grid_ids = []

  self.unique_id = -1
  self.readers_grid_size = readers_grid_size

  self.free_buffers = []
  self.gridQ = []

  self.faultyWriteQueue = []

  self.callbacksOnWrite = []
  self.callbacksOnRead = []

  self.channels = [] #channels for data transfer
  self.srcWorkers = {}
  self.dstWorkers = {}
  self.srcPorts = []
  self.srcPortsPins = []
  self.dstPorts = []
  self.dstPortsPins = []
  self.amIsource = false
  self.amIdestination = false
  self.initialized = false
  self.grid_id = -1

  self.init = (buffersLength,unique_id,readers_grid_size) ->
    if self.initialized
      return
    self.initialized = true
    self.buffers = []
    for i in [0...buffersLength]
      self.buffers.push({})
      self.buffers_to_read.push(0)
      self.buffers_addData.push({})
      self.free_buffers.push(i)
      self.buffers_grid_ids.push(-1)
    if unique_id < 0
      unique_id = s.com_github_osblinnikov_cnets_readerWriter.statsCollectorStatic.getNextLocalId()
    self.unique_id = unique_id
    self.readers_grid_size = readers_grid_size

  if buffers && buffers.length > 0
    self.init(buffers.length, self.unique_id, readers_grid_size)



  self.dispatchMessage = (ev)->
    if  typeof self.curBufId != 'undefined' and ev.data.bufId!=self.curBufId
      console.error "wrong buffer id ev.bufId("+ev.data.bufId+")!=self.curBufId("+self.curBufId+")"
      return
    # if typeof portId == 'undefined'
    #   portId = -1 #indicates that event received via local onmessage, or direct call
    msg = ev.data
    if msg.type!='create' and !self.ports.length
      console.error "ERROR: mapBuffer "+self.unique_id+" dispatchEvent: (!ev.ports)"
      return
    #console.log "dispatchMessage:"+msg.type
    switch msg.type
      when 'create'
        if ev.ports
          _s = self
          for i in [0...ev.ports.length]
            lastIndex = self.ports.length
            ev.ports[i].onmessage = ((lastIndex) ->
                return (e)->
                  #console.log "onMessage from port "+lastIndex
                  # e.data.bufId = _s.curBufId
                  e.data.portId = lastIndex
                  if _s.dispatcherForAddingBuffer
                    _s.dispatcherForAddingBuffer.onmessage(e)
                  else
                    _s.dispatchMessage(e)
              )(lastIndex)
            self.ports.push {wrk:ev.ports[i], bufId: msg.data.portsBufIds[i]}

        if msg.data.connectLocal and self.dispatcherForAddingBuffer and typeof self.curBufId != 'undefined'
          self.ports.push {wrk:self.dispatcherForAddingBuffer, bufId:-10}
          self.dispatcherForAddingBuffer.directPortId = self.ports.length - 1

        if (self.buffers && self.buffers.length > 0) || self.initialized
          console.error "ERROR: mapBuffer "+self.unique_id+" dispatchEvent create: multiple initialization msg: type="+msg.type
          return null

        #console.log "buffersLength: "+msg.data.buffersLength+" "+msg.data.unique_id+" "+msg.data.readers_grid_size
        self.init(msg.data.buffersLength,msg.data.unique_id,msg.data.readers_grid_size)

      when 'write'
        #console.log "write"
        if !msg.data.additionalData
          msg.data.additionalData = {}
        if self.amIsource
          #console.error self.amIsource+" "+self.amIdestination+" "+self.unique_id+" write msg.portId "+msg.portId
          return null
        msg.data.additionalData.bufId = msg.data.ownBufId
        msg.data.additionalData.portId = msg.portId
        msg.data.additionalData.internalId = msg.data.internalId #need to store, for sending it back
        self.faultyWriteQueue.push(msg.data)
        #write messages from faulty queue
        writeLocally()

      when 'read'
        if !msg.data.additionalData
          msg.data.additionalData = {}
        if self.amIdestination
          #console.error self.amIdestination+" "+self.amIsource+" "+self.unique_id+" read msg.portId "+msg.portId
          return null
        msg.data.additionalData.portId = msg.portId
        params = new s.com_github_osblinnikov_cnets_types.bufferKernelParams(self, -1, msg.data.additionalData)
        params.internalId = msg.data.internalId
        # console.log "mapBuffer "+self.unique_id+" read!"
        self.readFinished(params)
        #write messages from faulty queue
        writeLocally()

      else
        console.error "ERROR: mapBuffer "+self.unique_id+" dispatchEvent: unknown msg: type="+msg.type
        return

  writeLocally = ->
    while self.faultyWriteQueue.length > 0
      params = new s.com_github_osblinnikov_cnets_types.bufferKernelParams(self, self.faultyWriteQueue[0].grid_id, self.faultyWriteQueue[0].additionalData)
      # console.log "mapBuffer "+self.unique_id+" writeNext: params.additionalData.portId "+params.additionalData.portId
      r = self.writeNext(params)
      if r != null
        # console.log "writeLocally"
        r.obj = (self.faultyWriteQueue.shift()).obj
        self.writeFinished(params)
      else
        break

  self.getReader = (callbackObj)->
    if self.amIsource
      console.error "ERROR: mapBuffer "+self.unique_id+" getReader: you are setting me destination, but i'm already source, i can't be destination and source at the same time"
      return null
    self.amIdestination = true
    container = {}
    if typeof callbackObj == 'object' and typeof callbackObj.callback == 'function'
      self.callbacksOnWrite.push(callbackObj)
    return new s.com_github_osblinnikov_cnets_readerWriter.reader(new s.com_github_osblinnikov_cnets_types.bufferKernelParams(self,undefined,container))

  self.getWriter = (callbackObj)->
    if self.amIdestination
      console.error "ERROR: mapBuffer "+self.unique_id+" getWriter: you are setting me source, but i'm already destination, i can't be destination and source at the same time"
      return null
    self.amIsource = true
    container = {}
    if typeof callbackObj == 'object' and typeof callbackObj.callback == 'function'
      self.callbacksOnRead.push(callbackObj)
    return new s.com_github_osblinnikov_cnets_readerWriter.writer(new s.com_github_osblinnikov_cnets_types.bufferKernelParams(self,-1,container))

  self.readNext = (params)->
    return self.readNextWithMeta(params).data

  self.readNextWithMeta = (params)->
    res = new s.com_github_osblinnikov_cnets_types.bufferReadData()
    if self != params.target
      return res
    m = params.target
    if m==null or self.readers_grid_size == 0
      console.error "ERROR: mapBuffer "+self.unique_id+" readNextWithMeta: Some Input parameters are wrong"
      return res

    if self.gridQ.length > 0
      params.internalId = self.gridQ.shift()
      if params.internalId >= 0 && params.internalId < self.buffers.length
        res.data = self.buffers[params.internalId]
        res.writer_grid_id = self.buffers_grid_ids[params.internalId]

    return res

  self.readFinished = (params)->
    # console.log "mapBuffer "+self.unique_id+" readFinished:"
    if self != params.target
      return -1
    m = params.target
    if m==null or self.readers_grid_size == 0
      console.error "ERROR: mapBuffer "+self.unique_id+" readFinished: Some Input parameters are wrong"
      return -1

    if --self.buffers_to_read[params.internalId] > 0
      return 0
    # console.log "mapBuffer "+self.unique_id+" readFinished: buffers_to_read["+params.internalId+"]  = "+self.buffers_to_read[params.internalId]
    self.free_buffers.push(params.internalId)

    #check if it was written by another worker
    if typeof self.buffers_addData[params.internalId].portId != 'undefined' and self.buffers_addData[params.internalId].portId >= 0
      # console.log "send read"
      objPort = self.ports[self.buffers_addData[params.internalId].portId]
      # console.log objPort.wrk
      msgToSend =
        unique_id: self.unique_id
        bufId: self.buffers_addData[params.internalId].bufId
        type: 'read'
        data:
          internalId: self.buffers_addData[params.internalId].internalId
      objPort.wrk.postMessage(msgToSend)
      # console.log self.buffers_addData[params.internalId].portId
      self.buffers_addData[params.internalId].portId = undefined #clean up the info
    # else
    #   console.log ("mapBuffer "+self.unique_id+" readFinished: locally written - locally read")
    for i in [0...self.callbacksOnRead.length]
      self.callbacksOnRead[i].callback(self.curBufId,self)#to notify local readers

    return 0

  self.writeNext = (params)->
    res = null
    if self != params.target
      return res
    m = params.target
    if m==null or self.readers_grid_size == 0
      console.error "ERROR: mapBuffer "+self.unique_id+" writeNext: Some Input parameters are wrong"
      return res
    if self.free_buffers.length > 0
      params.internalId = self.free_buffers.shift()
      if self.buffers_to_read[params.internalId] > 0
        console.error "ERROR: mapBuffer "+self.unique_id+" writeNext: ERROR not all readers read buffer "+params.internalId+", there are "+self.buffers_to_read[params.internalId]+" remain!\n"
        return res
      res = self.buffers[params.internalId]
      # if typeof params.additionalData.portId !=
      self.buffers_addData[params.internalId] = params.additionalData
      # else
      #   self.buffers_addData[params.internalId].portId = undefined#to make sure portId is undefined

    return res

  self.writeFinished = (params)->
    res = -1
    if self != params.target
      return res
    m = params.target
    if m==null or self.readers_grid_size == 0
      console.error "ERROR: mapBuffer "+self.unique_id+" writeFinished: Some Input parameters are wrong"
      return res
    if self.buffers_to_read[params.internalId] > 0
      console.error "ERROR: mapBuffer "+self.unique_id+" writeFinished: ERROR not all readers read buffer "+params.internalId+", there are "+self.buffers_to_read[params.internalId]+" remain!\n"
      return res

    if self.amIsource
      self.buffers_to_read[params.internalId] = self.readers_grid_size
    else
      self.buffers_to_read[params.internalId] = 1

    if self.amIsource and typeof self.buffers_addData[params.internalId].portId == 'undefined'

      for i in [0...self.ports.length]
        # console.log "self.ports[i].bufId "+self.ports[i].bufId
        msgToSend =
          unique_id: self.unique_id
          bufId: self.ports[i].bufId
          type: 'write'
          data:
            grid_id: self.grid_id
            obj: self.buffers[params.internalId].obj
            internalId: params.internalId
            ownBufId: self.curBufId
        self.ports[i].wrk.postMessage(msgToSend)
    # if self.ports.length + 1 < self.readers_grid_size
      # console.warn "WARN: mapBuffer "+self.unique_id+" writeFinished: self.ports.length + 1 < self.readers_grid_size self.amIdestination="+self.amIdestination

    if self.amIdestination
      self.gridQ.push(params.internalId)
      # console.log "params.grid_id "+params.grid_id
      self.buffers_grid_ids[params.internalId] = params.grid_id

    # if self.callbacksOnWrite.length == 0
    #   console.warn "WARN: mapBuffer "+self.unique_id+" writeFinished: self.callbacksOnWrite.length == 0 "+self.amIsource+" "+self.buffers_addData[params.internalId].portId
    # else
    for i in [0...self.callbacksOnWrite.length]
      self.callbacksOnWrite[i].callback(self.curBufId,self)#to notify local readers

    return res

  self.size = (params)->
    return self.buffers.length

  self.gridSize = (params)->
    return self.readers_grid_size

  self.uniqueId = (params)->
    return self.unique_id

  self.syncConnections = ->
    # console.log "sync src"
    for grid_id, worker of self.srcWorkers
      if worker!=self
        sendCreateMesg(worker,self.dstPorts, self.dstPortsPins,grid_id)

    # console.log "sync dst"
    for grid_id, worker of self.dstWorkers
      if worker!=self
        sendCreateMesg(worker,self.srcPorts, self.srcPortsPins,grid_id)
    true

  sendCreateMesg = (worker,ports, portsPins,grid_id)->
    # console.log worker.wrk.scriptFile
    # console.log "sendCreateMesg uid:"+self.unique_id+" ports:"+ports.length
    # console.log portsPins
    # console.log "sendCreateMesg:"+worker.connectLocal
    msgToSend =
      unique_id: self.unique_id
      bufId: worker.pinId
      type: 'create'
      data:
        grid_id: grid_id
        connectLocal: worker.connectLocal
        portsBufIds: portsPins
        buffersLength: self.size()
        unique_id: self.unique_id
        readers_grid_size: self.gridSize()
    worker.wrk.postMessage(msgToSend, ports)

  addWorker = (isSrc, grid_id, wrk, thisBufferPinIdInWorker, port)->
    # console.log "addWorker:"+isSrc+" "+grid_id+" "+wrk.scriptFile+" "+thisBufferPinIdInWorker
    if isSrc
      wrks = self.srcWorkers
      portCont = self.srcPorts
      portContIds = self.srcPortsPins
    else
      wrks = self.dstWorkers
      portCont = self.dstPorts
      portContIds = self.dstPortsPins
    if wrks[grid_id] && !port
      console.log "addWorker: debug: several connections on the same worker"
      return

    if !wrk
      wrks[grid_id] =
        wrk: self #OURSELVES AS WORKER
      #   port: port
      return

    if port
      portCont.push port
      portContIds.push thisBufferPinIdInWorker

    wrks[grid_id] =
      connectLocal: !port
      pinId: thisBufferPinIdInWorker
      wrk: wrk

    true

  self.addConnection = (srcWrk,srcWrkPin,srcWrkIdInRWGrid,dstWrk,dstWrkPin,dstWrkIdInRWGrid)->
    #console.log "addConnection:"+srcWrk+" "+srcWrkPin+" "+srcWrkIdInRWGrid+" "+dstWrk+" "+dstWrkPin+" "+dstWrkIdInRWGrid
    if srcWrk and dstWrk
      #we have source and destination workers
      ch = new s.com_github_osblinnikov_cnets_types.MessageChannel()
      self.channels.push ch
      #console.log "addConnection interconnection"
      addWorker(true,srcWrkIdInRWGrid,srcWrk,srcWrkPin,ch.port1)
      addWorker(false,dstWrkIdInRWGrid,dstWrk,dstWrkPin,ch.port2)

    else if srcWrk
      #we have only source specified, so we are actual destination
      if self.amIsource
        console.error "ERROR: mapBuffer "+self.unique_id+" addConnection: you are setting me destination, but i'm already source, i can't be destination and source at the same time"
        return -1
      #console.log "addConnection root is destination"
      self.amIdestination = true
      _s = self
      self.ports.push {wrk: srcWrk,bufId:dstWrkPin}
      lastIndex = self.ports.length - 1
      srcWrk.addEventListener("message",(e)->
        # console.log "!!!!!!!!!!!!!!!!!!!!!!!!!!! message to root as destination "+_s.curBufId
        if e.data.unique_id != self.unique_id
          # console.error "unique_id is not match"
          return
        # e.data.bufId = _s.curBufId
        e.data.portId = lastIndex
        if _s.dispatcherForAddingBuffer
          _s.dispatcherForAddingBuffer.onmessage(e)
        else
          _s.dispatchMessage(e)
      ,false)

      addWorker(true,srcWrkIdInRWGrid,srcWrk,srcWrkPin,false)

    else if dstWrk
      #we have only destination specified, so we are actual source
      if self.amIdestination
        console.error "ERROR: mapBuffer "+self.unique_id+" addConnection: you are setting me source, but i'm already destination, i can't be destination and source at the same time"
        return -1
      #console.log "addConnection root is source"
      self.amIsource = true
      _s = self
      self.ports.push {wrk: dstWrk,bufId:dstWrkPin}
      lastIndex = self.ports.length - 1
      dstWrk.addEventListener("message",(e)->
        # console.log "!!!!!!!!!!!!!!!!!!!!!!!!!!! message to root as source "+_s.curBufId
        if e.data.unique_id != self.unique_id
          # console.error "unique_id is not match"
          return
        # e.data.bufId = _s.curBufId
        e.data.portId = lastIndex
        if _s.dispatcherForAddingBuffer
          _s.dispatcherForAddingBuffer.onmessage(e)
        else
          _s.dispatchMessage(e)
      ,false)

      addWorker(false,dstWrkIdInRWGrid,dstWrk,dstWrkPin,false)

    else
      console.error "ERROR: mapBuffer "+self.unique_id+" addConnection: neither source nor destination was specified"
      return -1
    return 0


  self.registeredSources = []
  self.registerSrc = (wrk, pinId)->
    #if wrk
    #  console.log "registerSrc: "+wrk.scriptFile+" "+pinId
    #else
    #  console.log "registerSrc: undefined "+pinId
    for v of self.registeredSources
      if v.wrk == wrk
        console.error "ERROR: mapBuffer registerSrc: src worker already registered"
        console.error wrk
        return
    if typeof wrk == 'undefined'
      self.grid_id = self.registeredSources.length
    self.registeredSources.push
      wrk: wrk
      pinId: pinId

  self.registeredDestinations = []
  self.registerDst = (wrk, pinId)->
    #if wrk
    #  console.log "registerDst: "+wrk.scriptFile+" "+pinId
    #else
    #  console.log "registerDst: undefined "+pinId
    for v of self.registeredDestinations
      if v.wrk == wrk
        console.error "ERROR: mapBuffer registerDst: dst worker already registered"
        console.error wrk
        return
    if typeof wrk == 'undefined'
      self.grid_id = self.registeredDestinations.length
    self.registeredDestinations.push
      wrk: wrk
      pinId: pinId

  self.syncRegister = () ->
    for srcId, src of self.registeredSources
      for dstId, dst of self.registeredDestinations
        self.addConnection(src.wrk, src.pinId, parseInt(srcId), dst.wrk, dst.pinId, parseInt(dstId))
    self.syncConnections()

  true

if isNode
  module.exports = s.com_github_osblinnikov_cnets_mapBuffer