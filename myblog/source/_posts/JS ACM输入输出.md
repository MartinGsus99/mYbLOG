# ACM输入输出

> Javascript V8 + Javascript Node

## 1.单行输入

```js
let line=readline()
```

```js
//输入两个整数A\B
let line=readline()
let nums=line.split(" ")
let res=0
let data=nums[0]*nums[1]

```

可以将解题核心函数放入函数，函数内写法如同leetcode

```js
while(line=readlie()){
	var lines=line.splt(' ').map(Number)
    var a=lines[0]
    var b=lines[1]
    
    funcation add(a,b){
        return a+b
    }
    print(add(a,b))
}	
```

## 2.多行输入

```js
let n=parseInt(readline())

var inputs=[]

while(line=readline()){
    line=parseInt(line)
    inputs.push(line)
}

var res-new Set(inputs)

Array.from(res).sort((a,b)=>a-b).forEach(item=>print(item))
```

## 3.输入矩阵

```js
while(line=readline()){
    let nums=line.split(' ')
    var row=+nums[0]
    var col=+nums[1]
    var map=[]
    
    for(let i=0;i<row;i++){
        map.push([])
        let mapline=readline().split(' ')
        for(let j=0;j<col;j++){
            map[i][j]=+mapline[j]
        }
    }
}
```

> Javascript Node

## 1.单行输入

```js
var readline=require('readline')

const rl=readline.createInterface({
    input:process.stdin,
    output:process.stdout
})

rl.on('line',function(line){
    var arr=line.split(" ")
    console.log(parseInt(arr[0])+parseInt(arr[1]))
})
```

## 2.处理多行输入

```js
const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});
const inputArr = [];//存放输入的数据
rl.on('line', function(line){
  //line是输入的每一行，为字符串格式
    inputArr.push(line.split(' '));//将输入流保存到inputArr中（注意为字符串数组）
}).on('close', function(){
    console.log(fun(inputArr))//调用函数并输出
})

//解决函数
function fun() {
	xxxxxxxx
	return xx
}

```

















