isNode = typeof module isnt "undefined" and module.exports
if isNode
  s = {}
  s.com_github_osblinnikov_cnets_types = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_types/types.js")
else
  s = self

describe "eval.js", ->
  it "should eval the given code", ->
    wrk = new s.com_github_osblinnikov_cnets_types.Worker("/test/specs/eval.js")
    result = null
    done = false
    runs ->
      wrk.onmessage = (msg) ->
        result = msg.data
        done = true
        wrk.terminate()
        return

      wrk.postMessage ("postMessage(\"abc\")")
      return

    waitsFor (->
      done
    ), "should finish", 500
    runs ->
      expect(result).toEqual "abc"
      return

    return

  return
