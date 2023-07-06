# TS问题

### 1.如何在typescript中解决 error TS2451: Cannot redeclare block-scoped variable 'name'

- 原因：在默认状态下，`typescript` 将 `DOM typings` 作为全局的运行环境，所以当我们声明 `name`时， 与 `DOM` 中的全局 `window` 对象下的 `name` 属性出现了重名。因此，报了 `error TS2451: Cannot redeclare block-scoped variable 'name'.` 错误。
- 解决方法：

1. 将运行环境由DOM typings更改为其他运行环境

```json
{
    "compilerOptions":{
        "lib":[
            "es2015"
        ]
    }
}
```

2. 为了避免与全局得变量出现重名，将脚本封装到模块内。Module有自己的作用域，自然不会与全局作用域得变量产生冲突。

```ts
const name = 'youthcity';

function greeter(name:string) {
  return `Hello ${name}`;
}
console.log(greeter(name));

export {};
```





