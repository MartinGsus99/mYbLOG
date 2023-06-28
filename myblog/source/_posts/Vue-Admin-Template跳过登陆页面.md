---
title: Vue登录页面跳过
date: 2023-06-25 21:33:45
categories:
  - 前端
tags:
  - VUE
  - 笔记
  - 项目问题
mp3:
cover: img/bg3.jpg
---

# Vue 登录页面跳过

### 1.业务需求

- 后端暂时无法提供接口
- 需要查看前端页面效果

### 2.方法

```js
/*
 * @Author: Aruver
 * @Date: 2022-10-08 09:45:03
 * @LastEditors: Aruver
 * @qq: 37919926
 */
import router from './router'
import store from './store'
import { Message } from 'element-ui'
import NProgress from 'nprogress' // progress bar
import 'nprogress/nprogress.css' // progress bar style
import { getToken } from '@/utils/auth' // get token from cookie
import getPageTitle from '@/utils/get-page-title'

NProgress.configure({ showSpinner: false }) // NProgress Configuration

const whiteList = ['/login'] // no redirect whitelist

router.beforeEach(async (to, from, next) => {
  // start progress bar
  NProgress.start()

  // set page title
  document.title = getPageTitle(to.meta.title)

  // determine whether the user has logged in
  // const hasToken = getToken()

  // if (hasToken) {
  //   if (to.path === '/login') {
  //     // if is logged in, redirect to the home page
  //     next({ path: '/' })
  //     NProgress.done()
  //   } else {
  //     const hasGetUserInfo = store.getters.name
  //     if (hasGetUserInfo) {
  //       next()
  //     } else {
  //       try {
  //         // get user info
  //         // await store.dispatch('user/getInfo')

  //         next()
  //       } catch (error) {
  //         // remove token and go to login page to re-login
  //         await store.dispatch('user/resetToken')
  //         Message.error(error || 'Has Error')
  //         next(`/login?redirect=${to.path}`)
  //         NProgress.done()
  //       }
  //     }
  //   }
  // } else {
  //   /* has no token*/

  //   if (whiteList.indexOf(to.path) !== -1) {
  //     // in the free login whitelist, go directly
  //     next()
  //   } else {
  //     // other pages that do not have permission to access are redirected to the login page.
  //     next(`/login?redirect=${to.path}`)
  //     NProgress.done()
  //   }
  // }

  //跳过登录，设置默认的token，然后输入其中一个路由进入页面
  const hasToken = 'admin-token'
  const role = 'admin'
  if (hasToken) {
    next()
    const accessRoutes = await store.dispatch('permission/generateRoutes', role)
    // dynamically add accessible routes
    router.addRoutes(accessRoutes)
  }
})

router.afterEach(() => {
  // finish progress bar
  NProgress.done()
})
```
