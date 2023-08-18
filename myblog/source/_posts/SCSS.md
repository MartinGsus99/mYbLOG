# SCSS

```scss
body {
  background: black;
}

span {
  color: #edecec;
  font-size: 50px;
  animation: spread 1s ease-in-out infinite alternate;
}

@keyframes spread {
  to {
    color: #72d885;
    text-shadow: 20px 0 70px #16a9e7;
  }
}

@for $i from 1 through 8 {
  span:nth-child(#{$i}) {
    animation-delay: ($i) * 0.2s;
  }
}

```

编译

```shell
sass ./style.scss ./style.css
```

```css
body {
  background: black;
}

span {
  color: #edecec;
  font-size: 50px;
  animation: spread 1s ease-in-out infinite alternate;
}

@keyframes spread {
  to {
    color: #72d885;
    text-shadow: 20px 0 70px #16a9e7;
  }
}
span:nth-child(1) {
  animation-delay: 0.2s;
}

span:nth-child(2) {
  animation-delay: 0.4s;
}

span:nth-child(3) {
  animation-delay: 0.6s;
}

span:nth-child(4) {
  animation-delay: 0.8s;
}

span:nth-child(5) {
  animation-delay: 1s;
}

span:nth-child(6) {
  animation-delay: 1.2s;
}

span:nth-child(7) {
  animation-delay: 1.4s;
}

span:nth-child(8) {
  animation-delay: 1.6s;
}

/*# sourceMappingURL=style.css.map */

```

