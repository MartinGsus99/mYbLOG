---
title: 机器学习-CH2-模型评估与选择
date: 2020-11-07 22:15:45
categories: 
    - 计算机科学
tags: 
    - 机器学习
mp3: 
cover: img/machinelearning.jpg
---

## 一、经验误差与过拟合
	

 1. 错误率：E=a/m
 2. 误差：样本真实输出与预测输出之间的差异
 		a.训练误差 b.测试误差 c.泛化误差
 3. 注：努力使经验误差最小化；
 4. 过拟合： 将训练样本的特点当作所有样本的一般性质。
 5. 欠拟合：队训练样本的一般性质尚未学好。

 

## 二、评估方法
	

 1. 评估方向：泛化性能、时间开销、存储开销、可解释性等。
 2. 留出法：直接将数据集划分为两个互斥集合；两个集合尽可能保持数分布的一致性；随即划分、重复实验取均值；训练/测试=2：1 ~ 4：1
 3. 交叉验证法：将数据划分为K个大小相似的互斥子集，每次使用k-1个子集作为训练集，余下的作为测试集，最终得到k个结果的均值，k常取：10；
 4. 自助法：假设给定的数据集包含d个样本。该数据集有放回地抽样m次，产生m个样本的训练集。这样原数据样本中的某些样本很可能在该样本集中出现多次。没有进入该训练集的样本最终形成检验集（测试集）；
 5. 注：数据较小使用自助法，数据量足够使用留出法和交叉验证法；

## 三、性能度量
	

 1. 性能度量是衡量模型泛化能力的评价标准；
 2. 回归：均方误差
 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106122704230.png#pic_center)
 3. 分类：错误率、精度
 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106122838653.png#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106122856105.png#pic_center)
 4. 查准率、查全率、F1
例：
判断得是否正确，在二分类任务中有四种表现形式，还拿西瓜🍉举例：
好西瓜判断成好西瓜，判断正确①；
好西瓜判断成坏西瓜，判断错误②；
坏西瓜判断成好西瓜，判断错误③；
坏西瓜判断成坏西瓜，判断正确④；
其中，①和④都是判断正确，②和③都是判断错误。错误率和精度是①和④、②和③的综合判断，只有判断正确与否的概念，没有正例反例的区别。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106202201469.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNTQ5NDI2,size_16,color_FFFFFF,t_70#pic_center)
查准率P：【真正例样本数】与【预测结果是正例的样本数】的比值。

查全率T：【真正例样本数】与【真实情况是正例的样本数】的比值。
注：P-R图（即以查全率做横轴，查准率做纵轴的平面示意图）
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020110620242432.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNTQ5NDI2,size_16,color_FFFFFF,t_70#pic_center)
当曲线没有交叉的时候：外侧曲线的学习器性能优于内侧；
当曲线有交叉的时候：
第一种方法是比较曲线下面积，但值不太容易估算；
第二种方法是比较两条曲线的平衡点，平衡点是“查准率=查全率”时的取值，在图中表示为曲线和对角线的交点。平衡点在外侧的曲线的学习器性能优于内侧。

 5. ROC与AUC
 真正例率（TPR）：【真正例样本数】与【真实情况是正例的样本数】的比值。（查全率）
假正例率（FPR）：【假正例样本数】与【真实情况是反例的样本数】的比值。
ROC图全名“受试者工作特征”，以真正例率为纵轴，以假正例率为横轴。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106202702423.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNTQ5NDI2,size_16,color_FFFFFF,t_70#pic_center)
性能度量的方法：绘制ROC曲线
当曲线没有交叉的时候：外侧曲线的学习器性能优于内侧；
当曲线有交叉的时候：比较ROC面积，即AUC。
 6. 代价敏感错误率与代价曲线
 性能度量的方法：绘制代价曲线
 代价曲线的横轴是正例概率代价P(+)cost，纵轴是归一化代价 cost_{norm} 。
 
## 四、比较检验（见《概率论》）

 1. 二项检验
 2. t检验
 3. 交叉验证t检验
 4. 5*2交叉检验


## 五、偏差与方差
偏差：期望输出与真实标记的差别。
偏差度量学习算法期望预测与真实结果的偏离程度，刻画拟合能力；
方差度量同样大小训练集的变动所导致的学习性能的变化，刻画数据扰动的影响；
噪声表达学习算法的期望泛化误差的下线，刻画了学习问题本身的难度；
偏差-方差窘境：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020110722102568.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNTQ5NDI2,size_16,color_FFFFFF,t_70#pic_center)




