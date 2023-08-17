---
title: Pytorch教程
date: 2023-07-26 10:00:00
categories:
  - PyTorch
tags:
  - AI
  - 笔记
mp3:
cover: img/bg3.jpg
---

# Pytorch 教程

## 一、入门

### 1.用处

- NumPy 的替代品、可以利用 GPU 的性能进行计算。
- 深度学习研究平台拥有猪狗多灵活性和速度

### 2.Tensors（张量）

Tensors 类似于 NumPy 的 ndarrays,可以使用 GPU 进行计算

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

`autograd`是 PyTorch 中所有网络神经的核心，为 Tensors 上苏哦有的操作提供自动微分

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

> 神经网络可以通过 torch.nn 包来创建
>
> 神经网络是基于自动梯度来定义一些模型。一个 nn.Module 包括层和一个方法 forward(input)和输出

![img](http://pytorchchina.com/wp-content/uploads/2018/12/mnist.png)

 图上是一个简单的前馈神经网络，接受输入，输入一个接一个通过层，最后给出输出。

#### 典型神经网络训练过程特点

- 定义一个可训练参数的神经网络

- 迭代整个输入

- 通过神经网络处理输入

- 计算 loss

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

### 6.PyTorch 图像分类器

 通常来说，处理图像、文本、或者视频数据的时候，可以使用 python 包将数据加载成 numpy 数组格式。数组转换为`torch.*Tensor`

- 图像：Pillow、OpenCV
- 语音：scipy、librosa
- 文本：NLTK 和 SpaCy

#### 训练一个图像分类器

- 使用`torchvision`加载并且归一下 CIFAR10 的训练和测试数据集
- 定义一个卷积神经网络
- 定义一个损失函数
- 在训练样本数据上训练网络
- 在测试样本数据集上测试网络

`⭐Note：`数据集：CIFAR10，包含是个类别，图像尺寸为 33232，RGB 3 32\*32

```py
import torch
import torchvision
import torchvision.transforms as transforms
import matplotlib.pyplot as plt
import numpy as np

import torch.nn as nn
import torch.nn.functional as F

import torch.optim as optim

#定义一个卷积神经网络，修改为3通道的图片
class Net(nn.Module):
  def __init__(self, *args, **kwargs) -> None:
     super(Net,self).__init__(*args, **kwargs)
     self.conv1=nn.Conv2d(3,6,5)
     self.pool=nn.MaxPool2d(2,2)
     self.conv2=nn.Conv2d(6,16,5)
     self.fc1=nn.Linear(16*5*5,120)
     self.fc2=nn.Linear(120,84)
     self.fc3=nn.Linear(84,10)

  def forward(self,x):
    x=self.pool(F.relu(self.conv1(x)))
    x=self.pool(F.relu(self.conv2(x)))
    x=x.view(-1,16*5*5)
    x=F.relu(self.fc1(x))
    x=F.relu(self.fc2(x))
    x=self.fc3(x)
    return x

net=Net()

#定义一个损失函数和优化器，分类交叉熵做损失函数、动量SGD做优化器
criteria=nn.CrossEntropyLoss()
optimizer=optim.SGD(net.parameters(),lr=0.001,momentum=0.9)

#torchvision数据集的输出是范围在[0,1]之间的PILImage图像，我们将他们转换为归一化范围为[-1,1]之间的张量Tensors
transforms=transforms.Compose(
  [transforms.ToTensor(),
   transforms.Normalize((0.5,0.5,0.5),(0.5,0.5,0.5))]
)

trainSet=torchvision.datasets.CIFAR10(root='./picData',train=True,download=False,transform=transforms)
trainloader=torch.utils.data.DataLoader(trainSet,batch_size=4,shuffle=True,num_workers=0)

testSet=torchvision.datasets.CIFAR10(root='./picData',train=False,download=False,transform=transforms)
testloader=torch.utils.data.DataLoader(testSet,batch_size=4,shuffle=False,num_workers=0)

classes=('plane','car','bird','cat','deer','dog','frog','horse','ship','truck')

# 展示一些训练中的图片
def showPic(img):
    img=img/2+0.5
    npimg=img.numpy()
    plt.imshow(np.transpose(npimg,(1,2,0)))
    plt.show()

dataIter=iter(trainloader)
images,labels=next(dataIter)

# showPic(torchvision.utils.make_grid(images))
print(' '.join('%5s' % classes[labels[j]] for j in range(4)))

#在数据迭代器上循环传给网络和优化器输入
for epoch in range(2):
  running_loss=0.0
  for i,data in enumerate(trainloader,0):
    inputs,labels=data
    optimizer.zero_grad()
    outputs=net(inputs)
    loss=criteria(outputs,labels)
    loss.backward()
    optimizer.step()

    running_loss+=loss.item()
    #输出loss
    if i%2000==1999:
      print('[%d,%5d] loss:%.3f' % (epoch+1,i+1,running_loss/2000))
      running_loss=0.0
print('Finished Training')

outputs=net(images)
_,predicted=torch.max(outputs,1)
print("Predicted:"," ".join("%5s" % classes[predicted[j]] for j in range(4)))

#查看在整个数据集上的表现
correct=0
total=0
with torch.no_grad():
  for data in testloader:
    images,labels=data
    outputs=net(images)
    _,predicted=torch.max(outputs.data,1)
    total+=labels.size(0)
    correct+=(predicted==labels).sum().item()

class_correct=list(0. for i in range(10))
class_total=list(0. for i in range(10))
with torch.no_grad():
  for data in testloader:
    images,labels=data
    outputs=net(images)
    _,predicted=torch.max(outputs,1)
    c=(predicted==labels).squeeze()
    for i in range(4):
      label=labels[i]
      class_correct[label]+=c[i].item()
      class_total[label]+=1

for i in range(10):
  print("Accuracy of %5s : %2d %%" % (classes[i],100*class_correct[i]/class_total[i]))
```

#### 转移到 GPU 上

- 检测 GPU

```py
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

# Assume that we are on a CUDA machine, then this should print a CUDA device:

print(device)
net.to(device)
#记住你也必须在每一个步骤向GPU发送输入和目标：
inputs, labels = inputs.to(device), labels.to(device)
```

### 7.数据并行处理

### 8.数据加载和处理

- #### scikit-image:用于图像的 IO 和变换

- #### pandas:用于更容易地进行 CSV 解析

```py
from __future__ import print_function,division
import os
import torch
import pandas as pd
from skimage import io,transform
import numpy as np
import matplotlib.pyplot as plt
from torch.utils.data import dataset,dataloader
from torchvision import transforms,utils

import warnings
#忽略警告
warnings.filterwarnings("ignore")

plt.ion()

def show_landmarks(image, landmarks):
    """显示带有地标的图片"""
    plt.imshow(image)
    plt.scatter(landmarks[:, 0], landmarks[:, 1], s=10, marker='.', c='g')
    plt.pause(10)  # pause a bit so that plots are updated


#读取数据集
def read_data_set(path):
  landmarks_frame=pd.read_csv(path)

  n=65
  img_name=landmarks_frame.iloc[n,0]
  landmarks=landmarks_frame.iloc[n,1:].to_numpy()
  landmarks=landmarks.astype('float').reshape(-1,2)

  print("Image name:{}".format(img_name))
  print("Landmarks shape:{}".format(landmarks.shape))
  print("First 4 landmarks:{}".format(landmarks[:4]))

  #展示图片
  face_data="./data/faces"
  plt.figure()
  show_landmarks(io.imread(os.path.join(face_data, img_name)),landmarks)
  plt.show()



if __name__=='__main__':
  read_data_set("./data/faces/face_landmarks.csv")

```

#### 数据集类

`torch.utils.data.dataset`是表示数据集的抽象类，因此自定义数据集应继承`dataset`并覆盖以下方法`__len__`实现返还数据集的尺寸。`__getitem__`用来获取一些索引数据。

#### 建立数据集类

在`__init__`中读取 CSV 文件内容，在`__getitem__`中读取图片，这样为了节省内存空间，只有在需要用到图片的时候才读取而不是一开始就把图片全部存进内存。

我们的数据样本按照字典`{'image':image,'landmarks':landmarks}`组织。

```py
class FaceLandmarksDataset(dataset):
  def __init__(self,csv_file,root_dir,transform=None):
    self.landmarks_frame=pd.read_csv(csv_file)
    self.root_dir=root_dir
    self.transform=transform

  def __len__(self):
    return len(self.landmarks_frame)

  def __getitem__(self,idx):
    img_name=os.paht.join(self.root_dir,self.landmarks_frame.iloc[idx,0])
    image=io.imread(img_name)
    landmarks=np.array([landmarks])
    landmarks=landmarks.astype('float').reshape(-1,2)
    sample={'image':image,'landmarks':landmarks}

    if self.transform:
      sample=self.transform(sample)

    return sample
```

#### 数据可视化

```py
def data_visualization(csv_file,path):
  face_dataset=FaceLandmarksDataset(csv_file=csv_file,root_dir=path)
  fig=plt.figure()

  for i in range(len(face_dataset)):
    sample=face_dataset[i]
    print(i,sample['image'].shape,sample['landmarks'].shape)
    ax=plt.subplot(1,4,i+1)
    plt.tight_layout()
    ax.set_title("Sample #{}".format(i))
    ax.axis('off')
    show_landmarks(**sample)

    if i==3:
      plt.show()
      break


```

#### 数据变换

> 通过上面的例子可以发现图片并不是相同的尺寸，绝大多数神经网络都假定图片的尺寸相同，因此我们需要进行一些预处理。

- `rescale`：缩放图片
- `randomCrop`：随机裁剪
- `ToTensor`：把 numpy`格式图片转换为torch`格式的图片

把它们写成可调用的类的形式而不是简单的函数，这样就不需要每次调用时传递一遍参数。我们只需要实现`__call__`方法，必要的时候实现 `__init__`方法。我们可以这样调用这些转换:

```py
tsfm = Transform(params)
transformed_sample = tsfm(sample)
```

##### 变换方法

```py
#图像处理类
#缩放
class Rescale(object):
  def __init__(self,output_size):
    assert isinstance(output_size,(int,tuple))
    self.output_size=output_size
  """将样本中的图像重新缩放到给定大小。.
  Args:
      output_size（tuple或int）：所需的输出大小。 如果是元组，则输出为
        与output_size匹配。 如果是int，则匹配较小的图像边缘到output_size保持纵横比相同。
  """
  def __call__(self,sample):
    image,landmarks=sample['image'],sample['landmarks']

    h,w=image.shape[:2]
    if isinstance(self.output_size,int):
      if h>w:
        new_h,new_w=self.output_size*h/w,self.output_size*w/h
      else:
        new_h,new_w=self.output_size,self.output_size*w/h
    else:
        new_h,new_w=self.output_size,self.output_size
    new_h,new_w=int(new_h),int(new_w)

    img=transform.resize(image,(new_h,new_w))
    landmarks=landmarks*[new_w/w,new_h/h]
    return {'image':img,'landmarks':landmarks}

#随机裁切
class RandomCrop(object):
  """随机裁剪样本中的图像.

  Args:
      output_size（tuple或int）：所需的输出大小。 如果是int，方形裁剪是。
  """
  def __init__(self, output_size):
      assert isinstance(output_size, (int, tuple))
      if isinstance(output_size, int):
          self.output_size = (output_size, output_size)
      else:
          assert len(output_size) == 2
          self.output_size = output_size

  def __call__(self, sample):
      image, landmarks = sample['image'], sample['landmarks']

      h, w = image.shape[:2]
      new_h, new_w = self.output_size
      top = np.random.randint(0, h - new_h)
      left = np.random.randint(0, w - new_w)
      image = image[top: top + new_h,
                    left: left + new_w]

      landmarks = landmarks - [left, top]
      return {'image': image, 'landmarks': landmarks}

#转换为Tensors
class ToTensor(object):
    """将样本中的ndarrays转换为Tensors."""
    def __call__(self, sample):
        image, landmarks = sample['image'], sample['landmarks']

        # 交换颜色轴因为
        # numpy包的图片是: H * W * C
        # torch包的图片是: C * H * W
        image = image.transpose((2, 0, 1))
        return {'image': torch.from_numpy(image),
                'landmarks': torch.from_numpy(landmarks)}

```

##### 组合转换

```py
scale = Rescale(256)
crop = RandomCrop(128)
composed = transforms.Compose([Rescale(256),
                               RandomCrop(224)])

# 在样本上应用上述的每个变换。
fig = plt.figure()
sample = face_dataset[65]
for i, tsfrm in enumerate([scale, crop, composed]):
    transformed_sample = tsfrm(sample)

    ax = plt.subplot(1, 3, i + 1)
    plt.tight_layout()
    ax.set_title(type(tsfrm).__name__)
    show_landmarks(**transformed_sample)

plt.show()
```

## 二、PyTorch小试牛刀

### 1.ReLU网络

该网络有单一的隐藏层，并将使用梯度下降训练。通过最小化网络输出和真正结果的欧几里得距离，来拟合随机生成的数据。

#### Numpy实现

numpy是用于科学计算的通用框架，它对计算图、深度学习和梯度一无所知。

```py
import numpy as np

# N是批量大小；D_in是输入维度；
# H是隐藏层维度；D_out是输出维度。
N,D_in,H,D_out=64,1000,100,10

#创建随机输入和输出数据
x=np.random.randn(N,D_in)
y=np.random.randn(N,D_out)

#随机初始化权重
w1=np.random.randn(D_in,H)
w2=np.random.randn(H,D_out)

learning_rate=1e-6
for t in range(500):
  #前向传递：计算预测值y
  h=x.dot(w1)
  h_relu=np.maximum(h,0)
  y_pred=h_relu.dot(w2)
  
  #计算和打印损失loss
  loss=np.square(y_pred-y).sum()
  print("Round:",t,loss)
  
  #反向传播，计算w1和w2相对于损失的梯度
  grad_y_pred=2.0*(y_pred-y)
  grad_w2=h_relu.T.dot(grad_y_pred)
  grad_h_relu=grad_y_pred.dot(w2.T)
  grad_h=grad_h_relu.copy()
  grad_h[h<0]=0
  grad_w1=x.T.dot(grad_h)
  
  #更新权重
  w1-=learning_rate*grad_w1
  w2-=learning_rate*grad_w2
```

#### PyTorch实现

上述numpy的例子中，需要手动实现神经网络的前向和后向传递。手动实现反向传递对于小型双层网络来说并不是dawn提，但是对于大型复杂网络来说很快就会变得非常繁琐。

## 三、聊天机器人

### 1.下载数据文件



















