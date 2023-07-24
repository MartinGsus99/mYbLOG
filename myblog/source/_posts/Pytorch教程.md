# Pytorch教程

## 一、入门

### 1.用处

- NumPy的替代品、可以利用GPU的性能进行计算。
- 深度学习研究平台拥有猪狗多灵活性和速度

### 2.Tensors（张量）

Tensors类似于NumPy的ndarrays,可以使用GPU进行计算

```py
from __future__ import print_function
import torch

#构造一个3*3的未初始化矩阵
x=torch.empty(3,3)
#构造一个3*3的随机初始化矩阵
y=torch.rand(3,3)
#构造一个全为0，类型为long的矩阵
z=torch.zeros(3,3,dtype=torch.long)
#构造一个含有数据的张量
a=torch.tensor([1,2,3])
#获取其维度信息
print(x.size())
#torch.size是一个元组
```

### 3.操作

```py
print('x',x)
print('y',y)
result=torch.empty(5,3)
print(x+y)
#指定输出
torch.add(x,y,out=result)
print(result)


#改变大小
x = torch.randn(4, 4)
y=x.view(16)
#-1表示自适应(拉直)，8表示列数
z=x.view(-1,8)
print(x.size(),y.size(),z.size())
print(z.item())
```

### 4.自动微分

`autograd`是PyTorch中所有网络神经的核心，为Tensors上苏哦有的操作提供自动微分

```
from __future__ import print_function
import torch

x=torch.ones(2,2,requires_grad=True)
y=x+2
z=y*y*3
out=z.mean()
out.backward()
print(x.grad)
```

### 5.神经网络

> 神经网络可以通过torch.nn包来创建
>
> 神经网络是基于自动梯度来定义一些模型。一个nn.Module包括层和一个方法forward(input)和输出

![img](http://pytorchchina.com/wp-content/uploads/2018/12/mnist.png)

​	图上是一个简单的前馈神经网络，接受输入，输入一个接一个通过层，最后给出输出。

#### 典型神经网络训练过程特点

- 定义一个可训练参数的神经网络

- 迭代整个输入

- 通过神经网络处理输入

- 计算loss

- 反向传播梯度到神经网络的参数

- 更新网络的参数，典型的一个更新方法为
  $$
  weight=weight-learningRate*gradient
  $$
  

  ```py
  import torch
  import torch.nn as nn
  import torch.nn.functional as F
  import torch.optim as optim
  
  class Net(nn.Module):
    def __init__(self) -> None:
      super(Net,self).__init__()
      #1 input image channel
      self.conv1=nn.Conv2d(1,6,5)
      #kernel
      self.conv2=nn.Conv2d(6,16,5)
      #an affine operation: y=Wx+b
      self.fc1=nn.Linear(16*5*5,120)
      self.fc2=nn.Linear(120,84)
      self.fc3=nn.Linear(84,10)
      
    def forward(self,x):
      #max pooling over a (2,2) window
      x=F.max_pool2d(F.relu(self.conv1(x)),(2,2))
      x=F.max_pool2d(F.relu(self.conv2(x)),2)
      x=x.view(-1,self.num_flat_features(x))
      x=F.relu(self.fc1(x))
      x=F.relu(self.fc2(x))
      x=self.fc3(x)
      return x
    
    def num_flat_features(self,x):
      size=x.size()[1:]   
      num_features=1
      for s in size:
        num_features*=s
      return num_features
    
  net=Net()
  print(net)  
  
  #创建一个32*32的输入
  input=torch.randn(1,1,32,32)
  output=net(input)
  print(output)
  #将所有参数梯度缓存区置0，用随机的梯度来反向传播
  net.zero_grad()
  output.backward(torch.randn(1,10))
  
  #损失函数:需要一对输入：模型输出和目标，计算一个值来评估输出距离目标有多远
  #有一些不同的损失函数在nn包中，一个简单的损失函数是nn.MSELoss，计算输出和目标的均方误差
  target=torch.randn(10)
  target=target.view(1,-1)
  criterion=nn.MSELoss()
  loss=criterion(output,target)
  print("LOSS:",loss)
  print(loss.grad_fn)  # MSELoss
  print(loss.grad_fn.next_functions[0][0])  # Linear
  print(loss.grad_fn.next_functions[0][0].next_functions[0][0])  # ReLU
  
  net.zero_grad() 
  
  #反向传播
  print('CONV1.bias.grad before backward',net.conv1.bias.grad)
  
  print('CONV1.bias.grad after backward',net.conv1.bias.grad)
    
  #更新神经网络参数
  #最简单的更新规则是随机梯度下降
  # create your optimizer
  optimizer = optim.SGD(net.parameters(), lr=0.01)
  optimizer.step()    # Does the update
  
  ```

  如果你是用神经网络，你想使用不同的更新规则，类似于 SGD, Nesterov-SGD, Adam, RMSProp, 等。为了让这可行，我们建立了一个小包：torch.optim 实现了所有的方法。使用它非常的简单。

  ```py
  import torch.optim as optim
  
  # create your optimizer
  optimizer = optim.SGD(net.parameters(), lr=0.01)
  
  # in your training loop:
  optimizer.zero_grad()   # zero the gradient buffers
  output = net(input)
  loss = criterion(output, target)
  loss.backward()
  optimizer.step()    # Does the update
  
  ```

  











