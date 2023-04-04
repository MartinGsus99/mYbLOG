---
title: Javascript高级程序设计（6）
date: 2021-1-12 21:18:45
categories: 
    - 前端
tags: 
    - Javascript
    - 笔记
    - Javascript高级程序设计
mp3: 
cover: img/bg1.jpg
---

# CH6

### 6.1 对象

```javascript
//eailer
var person=new Object();
person.name="Martin";
person.age=18;
person.job="Student";

person.sayName=function(){
    alert(person.name);
    console.log(person.name);
};

person.sayAge=function(){
    alert(person.age);
    console.log(person.age);
};

person.sayJob=function(){
    alert(person.job);
    console.log(person.job);
};


//Face to object
var person1={
    name:"Jack",
    age:21,
    job:"Software Engineer.",

    sayName:function(){
        console.log(this.name);
    },
    sayAge:function(){
        console.log(this.age);
    },
    sayJob:function(){
        console.log(this.job);
    }
}

```

#### 6.1.1 属性类型：数据属性和访问器属性

##### （1）数据属性：

​		Configurable:表示能否通过delete删除属性从而重新定义属性；修改特性；修改为访问器属性；注：直接在对象上定义的属性，默认值为true；

​		Enumerable：表示能否通过for-in循环返回属性；注：直接在对象上定义的属性，默认值为true；

​		Writable：表示能否修改属性得值；注：直接在对象上定义的属性，默认值为true；

​		Value：属性的数据值；默认为undefined；

使用Object.defineProperty()方法修稿属性默认得特性；三个参数：属性所在的对象，属性名，描述符对象（以上四个数据属性）；

```javascript

var person2={};
Object.defineProperty(person2,"name",{
    Writable:false,
    value:"Jack"
});

alert(person2.name);
person1.name="Nancy";
alert(person2.name);

//输出结果为Jack；非严格模式下，赋值被忽略；严格模式下，抛出错误；
```

##### （2）访问器属性：

​		Configurable:表示能否通过delete删除属性从而重新定义属性；修改特性；修改为访问器属性；注：直接在对象上定义的属性，默认值为true；

​		Enumerable：表示能否通过for-in循环返回属性；注：直接在对象上定义的属性，默认值为true；		

​		Get：读取属性时调用的函数，默认为undefined；

​		Set：写入属性时使用，默认为undefined；

```javascript
//访问器属性实例
var book={
    _year:2021,
    edition:1
};
Object.defineProperty(book,"year",{
    get:function(){
        return this._year;
    },
    set:function(newValue){
        this._year=newValue;
        this.edition+=newValue-2021;
    }
});

book.year=2023;
alert(book.edition);
```

6.1.2 定义多个属性：Object.defineproperties()方法

```javascript
var book = {};
Object.defineProperties(book, {
    _year: {
        writable: true,
        value: 2020
    },
    edition: {
        writable: true,
        value: 1
    },
    year: {
        get: function () {
            return this._year;
        },
        set: function (newValue) {
            if (newValue > this._year) {
                this._year = newValue;
                this.edition += newValue - 2020;
            }
        }
    }
})

```

### 6.2创建对象

#### 6.2.1工厂模式

​	解决了创建对象的问题但是没有解决对象识别的问题；

#### 6.2.2构造函数模式

​	（1）创建一个新对象；

​	（2）将函数得作用域赋值给对象；

​	（3）执行构造函数得代码，为对象添加属性；

​	（4）返回新对象；

```javascript

//工厂模式方法
function createPerson(name,age,job){
    var o=Object();
    o.name=name;
    o.age=age;
    o.job=job;
    o.sayHi=function(){
        alert(o.name);
    }
    return o;
}

//构造函数方法模式
function Person(name,age,job){
    this.name=name;
    this.age=age;
    this.job=job;

    //函数模式的缺点，sayName函数会在每个实例中重复一遍，解决方法：讲该函数移到Person外，this.sayName=sayName调用;
    this.sayName=function(){
        alert(this.name);
    };

}

var person1=createPerson("Martin",18,"Software enigneer");
var person2=new Person("Matin",20,"Cyber Security Engineer");


```

6.2.3 原型模式

好处：可以让所有对象实例共享它包含的属性和方法；（不必在构造函数中定义对象实例的信息，而是将这些信息直接添加到原型对象中）

