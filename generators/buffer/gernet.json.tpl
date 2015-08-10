{
"name":"${_JAVA_PATH_}.${_NAME_}",
"gen":["github.com/osblinnikov/cnets/generators/buffer","github.com/osblinnikov/cnets/generators/build"],
"args": [{
  "name": "buffers",
  "type": "Object[]"
},{
  "name": "timeout_milisec",
  "type": "long"
},{
  "name": "readers_grid_size",
  "type": "int"
}],
"depends":[{
  "name":"github.com/osblinnikov/cnets/readerWriter"
},{
  "name":"github.com/osblinnikov/cnets/queue"
},{
  "name":"github.com/osblinnikov/cnets/types"
}]
}