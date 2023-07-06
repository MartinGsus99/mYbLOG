---
title: TS 基础
date: 2023-06-26 21:33:45
categories:
  - 前端
tags:
  - VUE
  - 笔记
  - TS
mp3:
cover: img/bg3.jpg
---

# TS 基础

# TypeScript

## 一、什么是TypeScript?

### 1.Why we choose TypeScript?

- JavaScript构建大型复杂Web应用系统不容易；
- TypeScript为JS的超集，具有可选的类型且可以编译为纯JS。从技术上讲，TS是具有静态类型的JS。
- 

![](https://pic4.zhimg.com/80/v2-9be3e79b82f92d9476b42040d6af894f_720w.webp)

### 2.为什么需要向JS添加静态类型？

- 避免经典的错误“undefined is not a function.”
- 在不严重破坏代码的情况下，重构代码更容易。
- 使大型复杂的应用源码更加容易阅读。动态类型的自由特性经常会导致错误，错误不仅会降低程序员的呢工作效率，还会由于增加新代码的成本而使开发陷入停顿。JavaScript无法合并类型以及编译时缺乏错误检查，使它不适合作为企业和大型代码库中服务器端代码。

## 二、基础

### 1.基础类型

TS拥有和JS几乎一样的数据类型，此外还添加了枚举类型；

```tsx

1.布尔型
let isDone:boolean=false;

2.数字:TS里面的所有数字都是浮点数；
let decLiteral:number=6;
let hexLiteral:number=0xf00d;
let binaryLiteral:number=0b1010;
let oct:number=0o744;

3.字符串 “” ''
let name:string="Bob";

模板为字符串``
let name:string=`Gene`;
let age:number=37;
let sentence:string=`Hello,my name is ${name},and I will be ${age+1} years old next month;`;
let sentence: string = "Hello, my name is " + name + ".\n\n" +
    "I'll be " + (age + 1) + " years old next month.";

4.数组 []
let list:number[]=[1,2,3];
数组泛型
let list:Array<number>=[1,2,3];

5.元组 {}
let x:[string,number];
x=['hello','10'];
console.log(x[0].substr(1));

6.枚举 enum
enum Color {r,g,b};
let c:Color=Color.g;

enum Color{r=1,g,b};
let c:Color=Color.g;

enum Color={r=1,g=2,b=4};
let c:Color=Color.g;

枚举提供的遍历是可以通过枚举的值得到他的名字；
enum Color{red=1,g,b};
let colorName:string=Color[2];
console.log(colorName);   //g

7.任意值 any：有时候我们想要在编程阶段还哦不清楚的类型指定一个类型，这些值可能是动态的；
let notSure:any=4;
notSure="May be a string ";
notSure=false;
Object类型的变量只是允许你给它赋任意值 - 但是却不能够在它上面调用任意的方法，即便它真的有这些方法：
let notSure:any=4;
notSure.ifExists();
notSure.toFixed();

let prettySure:Object=4;
prettySure.toFixed();  //error;
只知道一部分数据的类型时，any类型也是有用的。比如，你有一个数组，它包含了不同的类型的数据：
let list:any[]=[1,true,"String"];

8.空值
function wanuser():void{
    alert("This is a warning message");
}
声明一个void类型的变量没有什么大用，因为你只能为它赋予undefined和null
默认情况下null和undefined是所有类型的子类型。 就是说你可以把null和undefined赋值给number类型的变量。
当你指定了--strictNullChecks标记，null和undefined只能赋值给void和它们各自。

9.Never
// 返回never的函数必须存在无法达到的终点
function error(message: string): never {
    throw new Error(message);
}

// 推断的返回值类型为never
function fail() {
    return error("Something failed");
}

// 返回never的函数必须存在无法达到的终点
function infiniteLoop(): never {
    while (true) {
    }
}

10.断言类型
有时我会比编译器更清楚某个值的详细信息；
通过断言可以告诉编译器，不进行特殊的数据检查和结构。运行时无影响只在编译时起作用；

“尖括号“语法
let someValue:any="this is a strong";

let strLenght:number=(<string>someValue).length;
as 语法
let someValue:any="this is a string";
let strl:number=(someValue as string).length;
两种形式是等价的。 至于使用哪个大多数情况下是凭个人喜好；
 然而，当你在TypeScript里使用JSX时，只有as语法断言是被允许的。
尽可能地使用let来代替var


```

#### 类型守卫

> 类型保护是可执行运行时检查得一种表达式，用于确保该类型在一定得范围内。换句话说，类型保护可以保证一个字符串是一个字符串。尽管他的值可以为一个数值。类型保护与特性检测并不是完全不同，其主要思想是尝试检测属性、方法或原型，以确定如何处理值；

- in关键字

```ts
//in

interface Admin {
  name: string
  privileges: string[]
}

interface Employee {
  name: string
  startDate: Date
}

type unknownEmployee = Admin | Employee

function printEmployeeInformation(emp: unknownEmployee) {
  console.log('Name: ' + emp.name)
  if ('privileges' in emp) {
    console.log('Privileges: ' + emp.privileges)
  }
  if ('startDate' in emp) {
    console.log('Start Date: ' + emp.startDate)
  }
}

const e1 = {
  name: 'Max',
  privileges: ['create-server'],
}

printEmployeeInformation(e1)

```

- typeof

typeof 类型保护只支持两种形式：typeof v === "typename" 和 typeof v !== typename，"typename" 必须是 "number"， "string"，"boolean" 或 "symbol"。 但是 TypeScript 并不会阻止你与其它字符串比较，语言不会把那些表达式识别为类型保护。

- instanceof

- #### 自定义类型保护的类型谓词

#### 联合类型





### 2.变量声明

`let`和`const`是JavaScript里相对较新的变量声明方式。

`let`在很多方面与`var`是相似的，但是可以帮助大家避免在JavaScript里常见一些问题。 `const`是对`let`的一个增强，它能阻止对一个变量再次赋值。

```ts
for (var i = 0; i < 10; i++) {
    setTimeout(function() { console.log(i); }, 100 * i);
}

for (var i = 0; i < 10; i++) {
    // capture the current state of 'i'
    // by invoking a function with its current value
    (function(i) {
        setTimeout(function() { console.log(i); }, 100 * i);
    })(i);
}
//需要复习


```

##### let vs. const

 基本原则就是如果一个变量不需要对它写入，那么其它使用这些代码的人也不能够写入它们，并且要思考为什么会需要对这些变量重新赋值。 使用`const`也可以让我们更容易的推测数据的流动。

##### 属性重命名

```tsx
let { a: newName1, b: newName2 } = o;

let newName1 = o.a;
let newName2 = o.b;
//指示类型
let {a, b}: {a: string, b: number} = o;
```

##### 解构 VS展开

```tsx
    let first=[1,2];
    let second=[3,4];
    let both=[0,...first,...second,5];

let defaults = { food: "spicy", price: "$$", ambiance: "noisy" };
let search = { ...defaults, food: "rich" };
//search的值为{ food: "rich", price: "$$", ambiance: "noisy" }。展开对象后面的属性会覆盖前面的属性。
//对象展开还有其它一些意想不到的限制。 首先，它仅包含对象 自身的可枚举属性。 大体上是说当你展开一个对象实例时，你会丢失其方法：
class C {
  p = 12;
  m() {
  }
}
let c = new C();
let clone = { ...c };
clone.p; // ok
clone.m(); // error!
```



### 3.接口

TS的核心原则之一就是对值所具有的结构进行类型检查。

在TS里接口的作用就是为这些类型命名和为你的代码或者第三方代码定义契约。

```tsx
function prinLabel(labelObj:{label:string}){
    console.log(labelObj.label);
}
//类型检查器会查看printLabel的调用。 printLabel有一个参数，并要求这个对象参数有一个名为label类型为string的属性。
//下面是接口描述
interface LabelValue{
    label:string;
}

function printLabel(labelObj:LabelValue){
    console.log(labelObj.label);
}
let myObj = {size: 10, label: "Size 10 Object"};
printLabel(myObj);
//只要传入的对象满足上面提到的必要条件，那么它就是被允许的。类型检查器不会去检查属性的顺序，只要相应的属性存在并且类型也是对的就可以。






```

接口里的属性不全都是必需的。有些是只在某些条件下存在，或者根本不存在。 可选属性在应用“option bags”模式时很常用，即给函数传入的参数对象中只有部分属性赋值了。

```tsx
interface SquareConfig{
    //带有可选属性的接口与普通的接口定义差不多，只是在可选属性名字定义的后面加一个?符号。
    color?:string;
    width?:number;
}


function createSquare(config:SquareConfig):{color:string; area:number}{
    let newSquare={color:"white",area:100};
    if(config.color){
        newSquare.color=config.color;
    }
    if(config.width){
        newSquare.area=config.width*config.width;
    }
    return newSquare;
}

let mySquare=createSquare({color:"black"});
```

可选属性的好处之一是可以对可能存在的属性进行预定义，好处之二是可以捕获引用了不存在的属性时的错误。

##### 可选属性

```tsx
interface SquareConfig{
    reaoly color?:string;
    width?:number;
}
    
let a: number[] = [1, 2, 3, 4];
let ro: ReadonlyArray<number> = a;  //只读数组

function CreateSquare(config:SquareConfig):{color:string;area:number}{
    let newSquare={color:"white",area:100};
    if(config.color){
        newSquare.color=config.color;
    }
    if(config.width){
        newSquare.area=config.width*config.width;
    }
    return newSquare;
}

let mySquare=createSquare({color:"blcak"});
//TypeScript会认为这段代码可能存在bug。 对象字面量会被特殊对待而且会经过额外属性检查，当将它们赋值给变量或作为参数传递的时候。 如果一个对象字面量存在任何“目标类型”不包含的属性时，你会得到一个错误。
// error: 'colour' not expected in type 'SquareConfig'
let mySquare = createSquare({ colour: "red", width: 100 });
```

最简单判断该用`readonly`还是`const`的方法是看要把它做为变量使用还是做为一个属性。 做为变量使用的话用`const`，若做为属性则使用`readonly`。

##### 额外的属性检查

绕开检查非常简单，常用的使用断言：

```tsx
let mySquare=createSquare({width:100,opacity:0.5} as SquareConfig);
```

最佳方式是添加一个字符串索引签名，前提是能够确定这个对象可能具有某些作为特殊用途使用的额外属性。

```tsx
interface SquareCOnfig{
    color?:string;
    width?:number;
    [propName:string] :any;
}
```

后一种跳过这些检查的方式，这可能会让你感到惊讶，它就是将这个对象赋值给一个另一个变量： 因为`squareOptions`不会经过额外属性检查，所以编译器不会报错。

```tsx
let squareOptions = { colour: "red", width: 100 };
let mySquare = createSquare(squareOptions);
```

##### 函数类型

除了描述带有属性的普通对象外，接口也可以描述函数类型。

```tsx
interface SearchFunc{
    (source:string,subStrimg:string):boolean;
}

//下例展示了如何创建一个函数类型的变量，并将一个同类型的函数赋值给这个变量。
let mySearch:SearchFunc;
mySearch=function(source:string,subString:string){
    let result=source.search(subString);
    return result >-1;
}
//函数的参数名不需要与接口里定义的名字相匹配。
mySearch = function(src: string, sub: string): boolean {
  let result = src.search(sub);
  return result > -1;
}
//函数的参数会逐个进行检查，要求对应位置上的参数类型是兼容的。 
```

### 4.类

##### 类的实例

```tsx
class Greeter{
    greeting:string;
    constructor(message:string){
        this.,greeting=message;
    }
    greet(){
        return "Hello"+this.greeting;
    }
}

let greeter=new Greeter("World");
```

##### 继承

```tsx
class Animal{
    move(distanceInMeters:number=0){
        console.log(`Animal moved ${distanceInMeters} m.`);
    }
}

class Dog extends Adnimal{
    bark(){
        console.log('Woof!Woof!');
    }
}

const dog=new Dog();
dog.bark();
dog.move(10);

```

一个更加复杂的例子

```jsx
class Animal{
    name:string;
    constructor(theName:string){
        this.name=theName;
    }
    
    move(distance:number=0){
        consloe.log(`${name} moved ${distance} m.`);
    }
}

class Snake extends Adnimal{    
    constructor(name:string){ 
        super(name);               //派生类包含了一个构造函数，它必须调用super()，它会执行基类的构造函数。 
    }             //在构造函数里访问this的属性之前，一定要调用super()。 TypeScript强制执行的一条重要规则。
    
    move(distance:number=5){
        consloe.log("Slithering...");
        super.move(distance);               //调用父类方法
    }
}

class Horse extends Adnimal{
    constructor(name:string){
        super(name);
    }
    
    move(distance=45){
        console.log("Galloping...");
        super.move(distance);
    }
}

let sam=new Snake("Sammy the Python");
ley tom:Animal=new Horse("Tommy the palomino.");

sam.move();
tom.move(34);

//Slithering...
//Sammy the Python moved 5m.
//Galloping...
//Tommy the Palomino moved 34m.

```

##### 公有、私有、受保护的修饰符

TS中，所有的成员都默认为Public；

```tsx
class Animal{
    public name:string;
    public constructor(theName:string){
        this.name=theName;
    }
    public move(distance:number){
        console.log('move~');
    }
}


```

private 不能在声明它的类的外部访问。

TS使用的是结构类型系统。如果所有成员的类型都是兼容的，就认为是类相兼容的。

protected 和private 相似，但是它的成员可以在派生类访问。

```tsx
class Person{
    protected name:string;
    constructor(name:string){
        this.name=name;
    }
}

class Employee extends Person{
    private department:string;
    
    constructor(name:string,department:string){
        super(name);
        this.department=department;
    }
    
    //派生类访问
    public getPitch(){
        return `Hello, my name is ${this.name} and i work in ${this.defartment}.`;
    }
}

let howard=new Employee("Howard","Sales");
console.log(howard.getPitch());
console.log(howard.name);   //error;
```

##### readonly

你可以使用`readonly`关键字将属性设置为只读的。 只读属性必须在  声明时或  构造函数里被初始化。

##### 存取器

TS支持通过getters/setters来截取对对象成员的访问。

```tsx
let password="password";

class Employee{
    private _fullname:string;
    
    get fullName():string{
        return this._fullname;
    }
    
    set fullName(name:string){
        if(password && password=='password'){
            this._fullName=name;
        }else
            {
                consloe.log("You have not permissiond.");
            }
    }
}
```

##### static静态属性

静态成员的属性只存在于类本身上而不是类的实例上。

```tsx
class Grid{
    static origin={x:0,y:0};
    calDisFromOriginPoint(point:{x:number; y:number;}){
        let xDist=(point.x-Grid.origin.x);
        let yDist=(point.y-Grid.origin.y);
        return Math.sqrt(xDist*xDist+yDist*yDist)/this.scale;
    }
    
    construtor(public scale:number){}
}

let grid1=new Grid(1.0);
let grid2=new Grid(5.0);
```

##### 抽象类

```tsx
abstract class Animal{
    abstract makeSound():void;
    move():void{
        console.log(`roaming the earch...`);
    }
}
```

https://typescript.bootcss.com/classes.html

抽象类作为其他派生类的基类使用。一般不会直接实例化。

不同于接口。抽象类可以包含成员的实现细节；

抽象类中的抽象方法不包含具体实现并且必须在派生类中实现。抽象方法的语法与接口方法类似。

两者都是定义方法签名但是不包含方法体；

抽象方法必须包含`abstract`关键字并且可以包含访问修饰符。

```tsx
abstract class Department{
    constructor(public name:string){
        
    }
    
    printName():void{
        console.log('Deartment name:' +this.name);
    }
    
    abstract printMeeting();void;
}

class AccountingDepartment extends Department{
    
    constructor(){
        super("Accounting and auditing");
        //派生类构造函数必须吊桶super（）；
    }
    
    //父类的抽象类在子类必须实现；
    printMeeting():void{
        console.log("The account ing meets each monday.");
    }
    
    generateReports():void{
        
    }
}



```

##### 把类当接口使用

```ts
class Poing{
    x:number;
    y:number;
}

interface Point3D extends Point{
    z:number;
}

let point3d:Point3D={
    x:1,
    y:2,
    z:3,
}
```

### 5.函数

##### 完整函数类型

```tsx
let myAdd:(x:number,y:number)=>number=function(
x:number,y:number
):number{
return x+y;
}
```

只要参数类型是匹配的，那么就认为它是有效的函数类型，而不在乎参数名是否正确。

可选参数必须跟在必须参数后面。 

与普通可选参数不同的是，带默认值的参数不需要放在必须参数的后面。 如果带默认值的参数出现在必须参数前面，用户必须明确的传入`undefined`值来获得默认值。 例如，我们重写最后一个例子，让`firstName`是带默认值的参数：

##### 剩余参数

在JavaScript里，你可以使用`arguments`来访问所有传入的参数。

在TypeScript里，你可以把所有参数收集到一个变量里：

```ts
function buildName(firstName: string, ...restOfName: string[]) {
  return firstName + " " + restOfName.join(" ");
}

let employeeName = buildName("Joseph", "Samuel", "Lucas", "MacKinzie");
```

##### this
