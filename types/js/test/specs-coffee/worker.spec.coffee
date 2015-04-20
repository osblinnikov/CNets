isNode = typeof module isnt "undefined" and module.exports
if isNode
  s = {}
  s.com_github_osblinnikov_cnets_types = require(__dirname + "/../../dist/com_github_osblinnikov_cnets_types/types.js")
else
  s = self

describe "WebWorker-API", ->
  it "should define the used API", ->
    expect(s.com_github_osblinnikov_cnets_types.Worker).toEqual jasmine.any(Function)
    wrk = new s.com_github_osblinnikov_cnets_types.Worker("/test/specs/eval.js")
    expect(wrk.postMessage).toEqual jasmine.any(Function)
    expect(wrk.terminate).toEqual jasmine.any(Function)
    wrk.terminate()
    return
  return
