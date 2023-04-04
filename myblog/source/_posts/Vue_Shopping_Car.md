---
title: Vue购物车
date: 2020-11-20 17:41:45
categories: 
    - 前端
tags: 
    - VUE
    - 笔记
    - Vue.js实战
mp3: 
cover: img/vue_js_shizhan.jpg
---


```html
//一个购物车实例
//重点在数据的绑定和computed属性，methods方法在后面的章节
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <script src="./js/vue.js"></script>
    <style type="text/css">
        table {
            border: 1px solid black;
        }
        th{
            border: 1px solid black;
        }
        td{
            border: 1px solid black;
        }

    </style>
</head>

<body>
    <div id="app" v-cloak>
        <template v-if="list.length">
            <table>
                <thead>
                    <tr>
                        <th></th>
                        <th>Name</th>
                        <th>Price</th>
                        <th>Count</th>
                        <th>Option</th>
                    </tr>
                </thead>
                <tbody>
                    <tr v-for="(item,index) in list">
                        <td>{{ index+1 }}</td>
                        <td>{{ item.name }}</td>
                        <td>{{ item.price }}</td>
                        <td>
                            <button @click="handleReduce(index)" :disabled="item.count === 1">-</button>
                            {{ item.count }}
                            <button @click="handleAdd(index)">+</button>
                        </td>
                        <td>
                            <button @click="handleRemove(index)">移除</button>
                        </td>
                    </tr>
                </tbody>
            </table>
            <div>总价：¥ {{ total }}</div>
        </template>

        <div v-else>购物车竟然是空的，快来添加心仪的商品！</div>
    </div>

    <script>
        var app = new Vue({
            el: '#app',
            data: {
                list: [
                    {
                        id: 1,
                        name: 'iPhone',
                        price: 9998,
                        count: 1,
                    },
                    {
                        id: 2,
                        name: 'iPad',
                        price: 3988,
                        count: 1,
                    },
                    {
                        id: 3,
                        name: 'iWatch',
                        price: 2599,
                        count: 1,
                    }
                ]
            },
            methods: {
                handleAdd: function (index) {
                    this.list[index].count++;
                },
                handleReduce: function (index) {
                    if (this.list[index].count === 1) {
                        return;
                    }
                    else {
                        this.list[index].count--;
                    }
                },
                handleRemove: function (index) {
                    this.list.splice(index, 1);
                }
            },
            computed: {
                total: function () {
                    var total = 0;
                    for (var i = 0; i < this.list.length; i++) {
                        var item = this.list[i];
                        total += item.price * item.count;
                    }
                    return total.toString().replace(/\B(?=(\d{3})+$)/g, ',');
                }
            },
        })
    </script>
    <script src="../Nowebpack/js/shopping_car.js"></script>
</body>

</html>
```

