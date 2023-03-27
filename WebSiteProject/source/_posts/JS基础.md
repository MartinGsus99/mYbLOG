# JS高级程序设计

## 一、基础基础基础

### 1.基础语法

- for-in

```js
//for-in语法是一种精准的迭代语句，可以用来枚举对象的属性；
for(property in expression){
    statement;
}

for(var propName in window){
    document.write(propName);
}
```

- with

```js
//将代码的作用域设置到一个特定的对象中
with(expression) statement;
```

### 2.变量、作用域、内存

- ##### 基本类型和引用类型的值

基本数据类型（可以直接操作保存在变量中的实际的值）：Undefined、NULL、Boolean、Number、String；

引用类型的值是保存在内存中的对象；

与其他语言不同，JS不允许直接访问内存中的位置；在操作对象时，实际操作的是对象的引用；

- ##### 复制变量值

从一个变量向另一个变量复制基本类型和引用类型时存在不同；

复制基本类型会创建基本类型的副本：

![](https://s3.bmp.ovh/imgs/2023/03/03/7a78a945b6267d99.jpg)

当一个变量赋值引用类型的值，同样也会将存储的值复制一份放到新变量分配的空间中国，不同的是，这个值的副本其实是一个指针，而这个指针指向存储在堆中的一个对象；

复制结束后，两个变量实际上引用同一个对象；因此改变其中一个变量会改变另一个；

![](https://s3.bmp.ovh/imgs/2023/03/03/18376e88b0eb8200.jpg)

- ##### 传递参数

ES中所有的参数都是按值传递的；

```js
function add(num){
    num+=10;
    return num;
}

var count=20;
var result=add(count);

//result=30,count=20不变
//这是因为addTen()中的参数num是count的值传递，而不是引用传递两者是相互无关的。
```

- 检测类型

要检测一个变量是不是基本类型？（typeof)

检测基本数据类型时，typeof很好用，但是检测引用类型用处不大，需要使用instanceof;

```js
tpyeof s;
variable instanceof constructor
```

- 作用域

Web浏览器中，全局执行环境被认为是window对象；

每个函数都有自己的执行环境，当执行流进入一个函数时，函数的环境会被推入一个环境栈中；

代码在一个环境中执行时，会创建变量对象的一个作用域链（scope chanin）：其作用是为了保证对执行环境有权访问的所有变量和函数有序的访问；

- 延长作用域链

有些语句可以在作用域链的前端临时增加一个变量对象，该变量对象在代码执行后被移除；

```
try-catch语句的catch
with语句
```

### 3.垃圾收集

JS具有自动垃圾收集机制，执行环境会负责管理代码执行过程中使用的内存。

原理：找出不再使用的变量，释放内存；垃圾收集器按照固定时间间隔周期性执行；

- 标记清除

当变量进入环境，标记为进入环境，方法可能是设置标志位；

- 引用计数

记录每个值被引用的次数，当声明了一个变量并且将一个引用类型赋给该变量，则这个值的引用次数就是1；

一个值赋给一个变量，引用次数+1；相反对这个值引用的变量右取得了另一个值，则引用次数-1；

问题：

```js
function problem(){
    var objA=new Object();
    var objB=new object();
    
    objectA.someOtherObject=objectB;
    objectA.anotherObject=objectA;
}
```

ObjectA和B通过各自的属性相互引用，两个对象的引用次数都是2；

这会导致函数执行后继续存在，引用次数永远不会为0；

```js
//解决方法
objA.someOther..=null;
objB.ano..=null;
```

- 性能问题
- 引用解除

```js
function createPerson(name){ 
 var localPerson = new Object(); 
 localPerson.name = name; 
 return localPerson; 
} 
var globalPerson = createPerson("Nicholas"); 
// 手工解除 globalPerson 的引用
globalPerson = null; 

```

### 4.引用类型

- 使用对象
- 创建、操作数组
- 理解基本的JS类型
- 使用基本类型和基本包装类型

> 引用类型的值（对象）是引用类型的一个实例；

- ##### Object类型

```js
//创建Object实例
//1.new操作符后跟Object构造函数
var person=new Object();
person.name="Martin";
person.age=29;

//2.对象字面量表示法
var person={
    name:"Martin",
    age:29,
    "address":"江苏省东南大学"			//属性名可以使用字符串，最后一个属性后不加逗号，会在早的版本导致错误
}


```

- ##### Array类型

```js
//ES的数组每一项可以保存不同类型的数据；大小动态调整；

//创建方式
//1.Array构造函数；
var colors=new Array(20);
var colors=new Array("red","blue","yellow");
//也可以省略new
var colors=Array(3);

//2.数组字面量表示法 
var colors=["red","blue","yellow"];

var nums=[1,2,]		//不要这样！！！
var options=[，，，] //不要这样；

//添加元素
color[color.length]="black";

//检测数组instanceof 问题在于如果存在两个不同的Array构造函数，会出错；
if(value instanceof Array){
    ...
}
    
//更好的方法
if(Array.isArray(value)){
    ...
}
```

```js
//转换方法
var colors = ["red", "blue", "green"]; // 创建一个包含 3 个字符串的数组
alert(colors.toString()); // red,blue,green 
alert(colors.valueOf()); // red,blue,green 
alert(colors); // red,blue,green。由于 alert()要接收字符串参数，所以它会在后台调用 toString()方法，由此会得到与直接调用 toString()方法相同的结果

//栈方法
array.push();		//尾部压入
array.pop();		//尾部弹出

//队列方法
array.push();		//尾部入队
array.shift();		//首部出队
array.unshift();	//首部入队

//重排序方法
array.sort();		//升序排列，方法会调用每个数组项的 toString()转型方法，然后比较得到的字符串
array.reverse();	//反转数组

//sort方法可以接受一个比较函数
function compare(value1, value2) { 
 if (value1 < value2) { 
 return 1; 
 } else if (value1 > value2) { 
 return -1; 
 } else { 
 return 0; 
 } 
} 
var values = [0, 1, 5, 10, 15]; 
values.sort(compare); 
alert(values); // 15,10,5,1,0

```

```js
//操作方法
//concat（）方法基于当前数组项创建一个新的数组；
var colors=["red","yellow"];
var colors2=colors.concat("green",["blue","grey"]);

//slice（）方法接受一或者两个参数，为岂止位置；
//slice方法不会影响原始数组；
var colors = ["red", "green", "blue", "yellow", "purple"]; 
var colors2 = colors.slice(1); 
var colors3 = colors.slice(1,4); 

//splice()方法
splice(0,2);  //删除前两项
splice(2,0,"red","green")  //从位置2开始插入red,green;
splice(2,1,"red")			//替换第二项为red；
```

```js
//位置方法
indexOf()			//从头开始查找
lastIndexOf()		//从尾部开始查找


```

### 5.迭代方法

- every():对数组中的每一项运行给定函数，如果该函数对每一项都返回 true，则返回 true。
- some()：对数组中的每一项运行给定函数，如果该函数对任一项返回 true，则返回 true。
- filter():对数组中的每一项运行给定函数，返回该函数会返回 true 的项组成的数组.
- foreach():：对数组中的每一项运行给定函数。这个方法没有返回值。
- map()：对数组中的每一项运行给定函数，返回每次函数调用的结果组成的数组。

### 6.归并方法

```js
//reduce():从第一项开始遍历；
//reduceRight():从最后一项开始遍历；
//接受的参数：prev,next，索引，数组对象
var values=[1,2,3,4,5];
//第一次调用，pre=1.cur=2;第二次：pre=3(1+2的结果)，cur=3
var sum=values.reduce(function(prev,cur,index,array)=>{
                      return prev+cur;
                      });
alert(sum);				//15

```

### 7.正则表达式



## 二、面向对象的程序设计

- 理解对象属性
- 理解并创建对象
- 理解继承

### 1.属性类型

> ES中有两种属性：数据属性和访问器属性

- 数据属性

> 数据属性包含一个数据值的位置，在这个位置可以读取和写入值。
>
> 1. Configurable：表示是否能通过delete删除属性从而重新定义属性，能否修改属性的特性，能否把属性修改为访问器属性；默认为true；
> 2. Enumerable：表示是否可以通过for-in循环返回属性；默认为true;
> 3. Writable:表示能否修改属性的值；默认为true；
> 4. Value:数据值，默认为undefined；

```js
var person={};
Objcect.defineProperty(person."name",{
                       configuable:false,		//一旦设置为false,就不能变回可配置的了；
                       writable:false,
                       value:"Martin"，
                       });
console.log(person.name);		//"Martin"
person.name="Jack";				//无法修改，非严格模式下赋值会被忽略；严格模式下，抛出错误；
```

- 访问器属性

> 不包含数据值，包含一对儿~~
>
> getter()和setter();
>
> 1. configurable:表示是否能通过delete删除属性从而重新定义属性，能否修改属性的特性，能否把属性修改为访问器属性；默认为true；
> 2. Enumerable：表示是否可以通过for-in循环返回属性；默认为true;
> 3. Get:读取属性时调用，默认undefined；
> 4. Set:写入属性时调用，默认undefined；

```js
var book={
    _year:2004,			//前置下划线表示只可以通过对象方法访问；
    edition:1
};

Objcect.defineProperty(book,"year",{
    get:function(){						//只写getter意味着不能写，写入会被忽略；严格模式报错；
        return this._year;
    },
    set:function(newValue){
        if(newValue>2004){
            this._year=newValue;
            this.edition+=newValue-2004;
        }
    }
});

//定义多个属性
Object.defineProperties(book,{
    _year:{
        value:2004,
    },
    edition:{
        value:1
    },
    year:{
       get:function(){						//只写getter意味着不能写，写入会被忽略；严格模式报错；
        return this._year;
        },
        set:function(newValue){
            if(newValue>2004){
                this._year=newValue;
                this.edition+=newValue-2004;
            }
        }
    }
})

```

```js
//读取属性的特性
var year=Object.getOwnPropertyDescriptor(book,"_year");
console.log(year.value);
```

### 2.创建对象

> 工厂模式抽象了具体创建对象的过程，考虑到ES中无法创建类，开发人员就发明了一i中函数

##### 工厂模式

```js
function createPerson(name,age,job){
    var o=new Objcet();
    o.name=name;
    o.age=age;
    o.job=job;
    o.sayName=function(){
        console.log(this.name);
    };
    return o;
}
```

> 工厂模式虽然解决了创建多个相似对象的问题，但是没有解决对象识别的问题，无法知道一个对象的类型；

##### 构造函数模式

> ES中的构造函数能船舰特定类型的对象；
>
> 像Object和Array这样的原生构造函数，运行时会自动出现再执行环境；

```js
function Person(name,age,job){
    this.name=name;
    this.age=age;
    this.job=job;
    
    this.sayName=function(){
        console.log(this.name);
    }
}
```

除了相同部分，有如下区别：

- 没有显式的创建对象；
- 直接将属性和方法赋给了this对象；
- 没有return；

Note：构造函数使用应该使用首字母大写的开头，非构造函数小写字母开头；

```js
//要创建Person实例，需要使用new
let newPerson=new Person("Martin",18,"Programmer");
console.log(newPerson.constructor==Person);   //true
console.log(newPerson instanceof Person);	//true
```

> 创建自定义的构造函数意味着将来可以将他的实例标识为一种特定的类型；
>
> 构造函数虽然好用，但是也不是没有缺点。
>
> 主要问题是：每个方法都要再实例上重新创建一遍；
>
> 不同实例创建相同函数名的函数，会导致不同的作用域链和标识符解析。
>
> 创建相同的Function实例完全没有必要，况且有this对象在根本不用在执行代码前九八函数绑定到特定的对象上面；

```js
//优化方法
function Person(name,age){
    this.name=name;
    this.age=age;
    
    this.sayName=sayName;
}

function sayName(){
    console.log(this.name);
}
```

> 构造函数内部将sayName属性设置成全局的sayName函数。
>
> 新的问题：虽然方法定义在全局作用域，但实际上只能被某个对象调用，让全局作用域名不副实；
>
> 更进一步，如果一个对象需要定义很多方法，则需要定义多个全局函数，失去封装性；

##### 原型模式

> 我们创建的每个函数都有一个prototype属性，这个属性是一个指针，指向一个对象。
>
> Prototype就是通过调用构造函数而创建的那个对象实例的原型对象；
>
> 使用原型对象的好处是可以让所有对象实例共享它所包含的属性和方法，即不用再构造函数中定义对象实例的信息，而是将这些信息直接添加到原型对象中；

```js
function Person(){
    
}

Person.prototype.name="Martin";
Person.prototype.age=23;
Person.prototype.sayName=function(){
    console.log(this.name);
};

var person1=new Person();
var person2=new Person();
person1.name="Martin"
person2.name="Jack"
person1.sayName();   //"Martin"
person2.sayName();	//"Jack"

console.log(person1.sayName()==person2.sayName())	//true
```

##### 理解原型对象

> 无论什么时候，只要创建了新韩淑，会为这个函数创建一个prototype属性，这个属性指向函数的原型对象。
>
> 默认情况下，所有原型对象都会自动获得一个constructor属性，这个属性包含一个指向prototype属性所在函数的指针。
>
> 举前面的例子：
>
> Person.prototype.constructor指向Person，通过这个构造函数可以伪原型对象添加其他属性；

![](https://s3.bmp.ovh/imgs/2023/03/08/953a324fdcd4fa42.png)

> 当为对象实例添加一个属性时，属性会屏蔽原型对象中保存的同名属性；
>
> 原型对象中的属性值不变；只会修改实例中的属性；
>
> 使用delete操作符可以完全删除实例属性，达到访问原型属性值的目的；
>
> 使用hasOwnProperty()来检查属性值是来自于原型还是实例；

![](https://s3.bmp.ovh/imgs/2023/03/08/b6a6f03230b36450.png)

##### 原型与in操作符

> 有两种方式使用in操作符：单独使用和for-in循环使用；
>
> 单独使用：通过对象能返回给定属性时返回true（不论原型和实例）；hasOwnProperty()只适用于实例；
>
> tips:如果in返回true而hasOwnProperty()返回false，可以确定属性是原型中的属性；
>
> for-in中使用：返回的是通过对象访问的，可以枚举的属性；

```js
//获得对象上所有的可枚举实例
object.keys();

var p=new Person();
var pKeys=Obcject.keys(p);
```

##### 更简单的原型语法

```js
//简写prototype
function Person(){}

Person.prototype={
    name:"Martin",
    age:29,
    job:"Software Engineer",
    sayName:function(){
        alert(this.name);
    }
};

//上面的代码里，将Person.prototype设置为一个字面量创建的新对象；但是此时constructor不再指向Person了；
//每创建一个函数，同时会创建他的prototype对象，这个对象自动获得constructor属性；
Person.prototype={
    constructor:Person,
    name:"Martin",
    age:29,
    job:"Software Engineer",
    sayName:function(){
        alert(this.name);
    }
};
```

##### 组合使用：构造函数模式和原型模式

> 构造函数用于定义实例属性；原型模式用于定义方法和共享属性；
>
> 共享方法，但是每个实例有自己的属性副本；

```js
function Person(name, age, job){ 
 this.name = name; 
 this.age = age; 
 this.job = job; 
 this.friends = ["Shelby", "Court"]; 
} 
Person.prototype = { 
 constructor : Person, 
 sayName : function(){ 
 alert(this.name); 
 } 
} 
```

##### 动态原型模式

> 通过将所有信息封装到构造函数，再构造函数中初始化原型；

```js
function Person(name, age, job){ 
 this.name = name; 
 this.age = age; 
 this.job = job; 
    if(typeof this.sayName!="function"){
        Person.prototype.sayName=function(){
            alert(this.name);
        }
    }
} 
```

##### 寄生构造函数

```js
function Person(name, age, job){ 
 var o = new Object(); 
 o.name = name; 
 o.age = age; 
 o.job = job; 
 o.sayName = function(){ 
 alert(this.name); 
 }; 
 return o; 
} 
var friend = new Person("Nicholas", 29, "Software Engineer"); 
friend.sayName(); //"Nicholas" 
```

### 3.继承

- 接口继承：只继承方法签名；
- 实现继承：继承实际方法；

ES只支持实现继承，主要依靠原型链实现；

#### （1）原型链

> 利用原型让一个引用类型继承另一个引用类型的属性和方法；

```js
//原型链基本模式

function SuperType(){
    this.property=true;
}

SuperType.prototype.getSuperValue=function(){
    return this.property;
};

function SubType(){
    this.subproperty=false;
}

SubType.prototype=new SuperType();		//子类的原型是父类的实例；子类获得父类的所有属性和方法；

SubType.prototype.getSubValue=function(){
    return this.subproperty;
};

var instacne=new SubType();
console.log(instacne.getSuperValue());		//true;
```

![](https://s3.bmp.ovh/imgs/2023/03/11/606aeed6b87048a8.png)

- 别忘记默认的原型

> 所有引用类型都默认继承Object；

![](https://s3.bmp.ovh/imgs/2023/03/11/ccdc684bf208d6d1.png)

- 确定原型和实例的关系

```js
instance instanceof Object;
Objcet.prototype.isPrototypeOf(instance);
```

- 谨慎的定义代码

> 子类优势需要重写超类中的某个方法，或者添加超累不存在的某个方法；
>
> 不管怎样，给原型添加的代码一定要放在替换原型语句之后；

```js
function SuperType(){ 
 this.property = true; 
} 
SuperType.prototype.getSuperValue = function(){ 
 return this.property; 
}; 
function SubType(){ 
 this.subproperty = false; 
} 

//继承了 SuperType 
SubType.prototype = new SuperType(); 
//!!!!添加新方法
SubType.prototype.getSubValue = function (){ 
 return this.subproperty; 
}; 
//重写超类型中的方法
SubType.prototype.getSuperValue = function (){ 
 return false; 
}; 
var instance = new SubType(); 
alert(instance.getSuperValue()); //false 

```

##### Notice!!!

使用原型链实现继承时，不能使用对象字面量创建原型方法；因为会重写原型链；

```js
function SuperType(){ 
 this.property = true; 
} 
SuperType.prototype.getSuperValue = function(){ 
 return this.property; 
}; 
function SubType(){ 
 this.subproperty = false; 
} 
//继承了 SuperType 
SubType.prototype = new SuperType(); 
//使用字面量添加新方法，会导致上一行代码无效
SubType.prototype = { 
 getSubValue : function (){ 
 return this.subproperty; 
 }, 
 someOtherMethod : function (){ 
 return false; 
 } 
}; 
var instance = new SubType(); 
alert(instance.getSuperValue()); //error! 
```

- 原型链的问题

> 问题来自于包含引用类型值的原型；
>
> 包含引用类型值的原型属性会被所有实例共享，这也是在构造函数而不是在原型对象中定义属性的原因；
>
> 在通过原型来实现继承时，原型实际上会变成另一个类型的实例；于是原先实例的属性也就变成了现在的原型属性了；

```js
//定义了一个colors属性
function SuperType(){
    this.colors=['red','grenn']l
}

function SubType(){
    
}

//子类原型设为父类
SubType.protptype=new SuperType();
var instance1=new SubType();
//所有的子都会共享colors；
instance1.colors.push('black');
alert(instance1.colors);			//red\gren\black

var instance2=new SubType();
alert(instance2.colors);			//red\green\black
```

#### （2）借用构造函数

> 伪造对象或者经典继承；
>
> 在子类构造函数的内部调用超类型构造函数；

```js
//定义了一个colors属性
function SuperType(){
    this.colors=['red','grenn']l
}

function SubType(){
    SuperType.call(this);	//继承了supertype；实际上在未来新创建的SubType实例时调用SuperType的构造函数；
}

var ins=new SubType();
ins.colors.push("black");
console.log(ins.colors);	//red.green.black;
var ins2=new SubType();
console.log(ins2.colors);	//red.green;	//不会共享colors了；

```

##### 传递参数

> 相比于原型链，借用构造函数有一个很大的优势，可以在子类型构造函数中向超累型构造函数传递参数；

```js
//定义了一个colors属性
function SuperType(){
    this.name=name;
}

function SubType(){
    SuperType.call(this,"Martin");		//调用父类构造函数实际上为子类的实例设置了name属性；
    this.age=29;		//为了确保父类构造函数不会重写子类的属性，可以在调用父类构造函数忠厚添加子类定义的属性；
}

var ins=new SubType();
console.log(ins.name);		//Martin
console.log(ins.age);		//29

```

##### 问题

> 仅仅借用构造函数，无法避免构造函数模式存在的问题：方法都在构造函数中定义，无法函数复用；
>
> 超类原型定义的方法对子类而言也是不可见得；

#### （3）组合继承

> 组合继承：有时叫伪经典继承，指将原型链和借用构造函数的技术组合到一块儿，发挥二者之长的继承模式；
>
> 背后的思路是使用原型链实现对原型属性和方法的继承，通过借用构造函数来实现对实例属性的继承；

























