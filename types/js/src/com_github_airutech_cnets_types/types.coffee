

#[[[cog
#import cogging as c
#c.tpl(cog,templateFile,c.a(prefix=configFile))
#]]]

isNode = typeof module isnt "undefined" and module.exports and process and process.title != 'browser'
if isNode
  s = {}
else
  s = self



s.com_github_airutech_cnets_types =
  create: ()->
    that = this
    
    #dummy
#[[[end]]] (checksum: 573bd6781a129adf050691d6429e4ccd)

s.com_github_airutech_cnets_types.bufferReadData = ->
  self = this
  self.nested_buffer_id = 0
  self.writer_grid_id = 0
  self.data = null
  true

s.com_github_airutech_cnets_types.bufferKernelParams = (target, grid_id, additionalData)->
  self = this
  self.target = target
  self.additionalData = additionalData
  self.grid_id = grid_id
  self.internalId = 0
  self.copy = ->
    return new bufferKernelParams(self.target, self.grid_id, self.additionalData)
  self.getObj = ->
    if typeof self.grid_id == 'undefined' or self.grid_id < 0
      self.grid_id = self.target.grid_id
    return {additionalData: self.additionalData, grid_id: self.grid_id, internalId: self.internalId}
  true

s.com_github_airutech_cnets_types.MessagePort = (anotherPort)->
  slf = this
  slf.anotherPort = anotherPort
  if slf.anotherPort
    slf.anotherPort.anotherPort = slf
  slf.isClosed = false
  listenersSize = 0
  listeners = {}
  listenersWithCapture = {}
  findListener = (type,listener, useCapture)->
    l = listeners[""+useCapture]
    if not l
      return false

    for i,v of l
      if v == type
        for t,tv of v
          if tv == listener
            return [i,t]
    return false

  slf.addEventListener = (type, listener, useCapture)->
    if slf.isClosed
      return
    if !findListener(type, listener, useCapture)
      l = listeners[""+useCapture]
      if not l
        l = listeners[""+useCapture] = {}
      if !l[type]
        l[type] = []
      l[type].push(listener)
      listenersSize++

  slf.removeEventListener = (type, listener, useCapture)->
    if slf.isClosed
      return
    r = findListener(type, listener, useCapture)
    if !r
      return
    listeners[""+useCapture][r[0]].splice(r[1], 1)
    listenersSize--
    if listeners[""+useCapture][r[0]].length == 0
      delete listeners[""+useCapture][r[0]]


  slf.dispatchEvent = (evt, pfResult)->
    # console.log "dispatchEvent slf.isClosed "+slf.isClosed
    if slf.isClosed
      return
    type = evt.type
    # console.log "dispatchEvent to host"
    if type == 'message' and "function" is typeof slf.onmessage
      # console.log "onMessage ok"
      slf.onmessage(evt)
    # else
      # console.log "no on message"
    if listenersSize <= 0
      return
    for useCapture,l of listeners
      if useCapture=="false" and not pfResult
        continue
      # console.log "dispatchEvent "+useCapture
      # l = listeners[useCapture]#for capturing
      for i,v of l
        if i == type
          for t,tv of v
            console.log tv
            tv(this,evt)

  slf.start = ->
    slf.isClosed = false

  slf.close = ->
    slf.isClosed = true

  slf.postMessage = (msg, ports)->
    slf.anotherPort.dispatchEvent({data:msg,ports:ports, type:'message'},true)
  true

if s.MessageChannel
  s.com_github_airutech_cnets_types.MessageChannel = s.MessageChannel
else if !s.com_github_airutech_cnets_types.MessageChannel
  s.com_github_airutech_cnets_types.MessageChannelArtificial = true
  MessageChannel = s.MessageChannel = s.com_github_airutech_cnets_types.MessageChannel = ->
    slf = this
    slf.port1 = new s.com_github_airutech_cnets_types.MessagePort(undefined)
    slf.port2 = new s.com_github_airutech_cnets_types.MessagePort(slf.port1)
    true


if s.Worker and !s.com_github_airutech_cnets_types.MessageChannelArtificial
  s.com_github_airutech_cnets_types.Worker = s.Worker
else
  Worker = s.Worker = s.com_github_airutech_cnets_types.Worker = (scriptFile) ->
    slf = this
    slf.scriptFile = scriptFile
    __timer = null
    __text = []
    __ports = []
    __fileContent = null
    started = false
    slf.internalWorker = {}
    slf.onerror = null
    slf.onmessage = null

    listenersSize = 0
    listeners = {}
    listenersWithCapture = {}
    findListener = (type,listener, useCapture)->
      l = listeners[""+useCapture]
      if not l
        return false

      for i,v of l
        if v == type
          for t,tv of v
            if tv == listener
              return [i,t]
      return false

    slf.addEventListener = (type, listener, useCapture)->
      if !findListener(type, listener, useCapture)
        l = listeners[""+useCapture]
        if not l
          l = listeners[""+useCapture] = {}
        if !l[type]
          l[type] = []
        l[type].push(listener)
        listenersSize++

    slf.removeEventListener = (type, listener, useCapture)->
      r = findListener(type, listener, useCapture)
      if !r
        return
      listeners[""+useCapture][r[0]].splice(r[1], 1)
      listenersSize--
      if listeners[""+useCapture][r[0]].length == 0
        delete listeners[""+useCapture][r[0]]


    slf.dispatchEvent = (evt, pfResult)->
      type = evt.type
      # console.log "dispatchEvent to host"
      if type == 'message' and "function" is typeof slf.onmessage
        slf.onmessage(evt)
      if listenersSize <= 0
        return
      for useCapture,l of listeners
        if useCapture=="false" and not pfResult
          continue
        # console.log "dispatchEvent"
        # l = listeners[useCapture]#for capturing
        for i,v of l
          if i == type
            for t,tv of v
              tv(evt)


    importScripts = ->
      isNode = typeof module isnt "undefined" and module.exports and __dirname

      #turn arguments from pseudo-array in to array in order to iterate it
      params = Array::slice.call(arguments)
      i = 0
      j = params.length

      while i < j
        if isNode
          arrName = params[i].split('/').pop().split('.')
          arrName.pop()
          this[arrName.join('.')] = require(process.cwd()+"/"+params[i])
        else
          script = document.createElement("SCRIPT")
          script.src = params[i]
          script.setAttribute "type", "text/javascript"
          document.getElementsByTagName("HEAD")[0].appendChild script
        i++
      return



    # child has run its and called for it's parent to be notified
    postMessage = (text) ->
      # console.log "outPost"
      # console.log text
      slf.dispatchEvent({data:text, type:'message'},true)
      # return slf.onmessage(data: text)  if "function" is typeof slf.onmessage
      false

    slf.internalWorker =
      postMessage: postMessage


    stop = ->
      slf.terminate()


    setImmediate = setImmediate or (cb) ->
      __timer = setTimeout cb, 0
      return

    clearImmediate = clearImmediate or (timer)->
      clearTimeout timer

    requestAnimFrame = (->
      requestAnimationFrame = undefined
      if typeof window!= 'undefined'
        requestAnimationFrame = window.requestAnimationFrame or window.webkitRequestAnimationFrame or window.mozRequestAnimationFrame
      return requestAnimationFrame or (callback) ->
        setTimeout callback, 1
        return
    )()

    # Method that starts the threading
    slf.postMessage = (text,ports) ->
      # console.log "inPost"
      __ports.push(ports)
      __text.push(text)
      __iterate()
      true

    __iterate = ->
      # Execute on a timer so we dont block (well as good as we can get in a single thread)
      # if __timer == null
      #   __timer = setImmediate(__onIterate)

      #request next available moment instead of looping
      requestAnimFrame(__onIterate)
      true

    __onIterate = ->
      if __text.length or __ports.length
        try
          # console.log "postMessage to worker"
          # console.log __text[0]
          slf.internalWorker.onmessage data: __text.shift(), ports:__ports.shift()   if "function" is typeof slf.internalWorker.onmessage
          return true
        catch ex
          return slf.onerror(ex)  if "function" is typeof slf.onerror
      false

    slf.terminate = ->
      if __timer != null
        clearImmediate(__timer)
        __timer = null
      true


    # HTTP Request
    getHTTPObject = ->
      xmlhttp = undefined
      try
        xmlhttp = new XMLHttpRequest()
      catch e
        try
          xmlhttp = new ActiveXObject("Microsoft.XMLHTTP")
        catch e
          xmlhttp = false
      xmlhttp

    evalStringContents = (__fileContent)->
      # slf.internalWorker = {}
      eval __fileContent
      if typeof this.onmessage is 'function'
        slf.internalWorker.onmessage = this.onmessage
      # slf.internalWorker.postMessage = postMessage

    http = getHTTPObject()
    if http
      http.open "GET", scriptFile, false
      http.send null
      if http.readyState is 4
        strResponse = http.responseText

        #var strResponse = http.responseXML;
        switch http.status
          when 404 # Page-not-found error
            alert "Error: Not Found. The requested function could not be found."
          when 500 # Display results in a full s for server-side errors
            alert strResponse
          else
            __fileContent = strResponse
            # IE functions will become delagates of the instance of Worker
    else
      fs = require('fs')
      __fileContent = fs.readFileSync( process.cwd()+scriptFile, "utf8")

    evalStringContents.bind(slf)(__fileContent)

    #
    #         at this point we now have:
    #         a delagate "onmessage(event)"
    #
    # slf.importScripts = (src) ->

    #   # hack time, this will import the script but not wait for it to load...
    #   script = document.createElement("SCRIPT")
    #   script.src = src
    #   script.setAttribute "type", "text/javascript"
    #   document.getElementsByTagName("HEAD")[0].appendChild script
    #   true

    true


Dispatcher = s.Dispatcher = s.com_github_airutech_cnets_types.Dispatcher = (binds)->
  if typeof binds != 'array'
    binds = [binds]
  slf = this
  slf.bindObjects = binds

  slf.mapBuffers = []
  slf.isStarted = false
  slf.directPortId = undefined

  slf.addBuffer = (buf)->
    slf.mapBuffers.push(buf)

  slf.onCreate = undefined
  slf.onStart = undefined
  slf.onStop = undefined

  slf.postMessage = (msg)->
    # slf.bindObjectsPostMessage[0].bind(slf.bindObjects[0])(msg)
    if slf.bindObjects[0].internalWorker
      slf.bindObjects[0].internalWorker.postMessage(msg)
    else
      slf.bindObjects[0].postMessage(msg)

  slf.onmessage = (e)->
    for i in [0...slf.bindObjects.length]
      if slf.bindObjects[i].internalWorker
        slf.bindObjects[i].internalWorker.onmessage(e)
      else
        slf.bindObjects[i].onmessage(e)

  onMessageCallback = (e)->
    if !slf.isStarted and e.data.type == 'props'
      if slf.onCreate
        slf.onCreate(e.data)
      return 
        
    if !slf.isStarted and e.data.type != 'create'
      slf.isStarted = true
      if slf.onStart
        slf.onStart()


    #console.log "onMessageCallback "+e.data.bufId+" "+e.data.type
    if typeof e.data.bufId != 'undefined'
      if typeof slf.directPortId != 'undefined'
        e.data.portId = slf.directPortId
      slf.mapBuffers[e.data.bufId].dispatchMessage(e)

    if e.data.type == 'stop'
      if slf.isStarted
        slf.isStarted = false
        if slf.onStop
          slf.onStop()
        if self.close
          self.close()
        else
          console.error  "Kernel: onStop: I can't stop myself, no close() method found!"

  for i in [0...slf.bindObjects.length]
    if slf.bindObjects[i].internalWorker
      slf.bindObjects[i].internalWorker.onmessage = onMessageCallback
    else
      slf.bindObjects[i].onmessage = onMessageCallback

  true

if isNode
  module.exports = s.com_github_airutech_cnets_types
