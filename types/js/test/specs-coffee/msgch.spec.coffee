isNode = typeof module isnt "undefined" and module.exports
if isNode
  s = {}
  s.com_github_airutech_cnets_types = require(__dirname + "/../../dist/com_github_airutech_cnets_types/types.js")
else
  s = self

describe "MessageChannel-API", ->
  it "should define the used API", ->
    expect(s.com_github_airutech_cnets_types.MessageChannel).toEqual jasmine.any(Function)
    ch = new s.com_github_airutech_cnets_types.MessageChannel()
    expect(ch.port1).toEqual jasmine.any(Object)
    expect(ch.port2).toEqual jasmine.any(Object)
    return

describe "MessageChannel-send", ->
  it "should send the given message", ->
    expect(s.com_github_airutech_cnets_types.MessageChannel).toEqual jasmine.any(Function)
    expect(s.com_github_airutech_cnets_types.Worker).toEqual jasmine.any(Function)
    ch = new s.com_github_airutech_cnets_types.MessageChannel()
    wrk1 = new s.com_github_airutech_cnets_types.Worker("/test/specs/msgch.sender.js")

    wrk1.postMessage("",[ch.port1])
    wrk2 = new s.com_github_airutech_cnets_types.Worker("/test/specs/msgch.receiver.js")
    wrk2.postMessage("",[ch.port2])
    result = null
    done = false
    runs ->
      wrk2.onmessage = (msg) ->
        result = msg.data
        done = true
        wrk2.terminate()
        return
        
      wrk1.postMessage ("abc")
      return

    waitsFor (->
      done
    ), "should finish", 2000
    runs ->
      expect(result).toEqual "abc"
      return