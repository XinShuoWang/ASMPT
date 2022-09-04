# 问题描述
- 构建Windows平台应用程序（首选MFC框架）
- 一开始窗口中只有4个图形元素，每个元素都有一个值（1到 4），升序排成一行
- 图形还应该具有其他属性，例如形状、颜色和大小等
- 用户可以进行插入操作：
  - 插入到队头：新元素的值 = 原始第一个元素的值 - 1
  - 插入到队尾：新元素的值 = 原来的最后一个元素的值 + 1
  - 插入到队中：新元素的值 = 相邻元素的平均值
- 用户还可以删除该行的元素，所有其他元素保持不变
- 行应该自动对齐，彼此之间的空间相等

# 分析
具体可能会涉及到以下几项技术：
- MFC框架：
  - 使用MFC框架绘制并填充图形、打印数字、清除窗口已经绘制的图形
  - 使用MFC框架与用户交互，获得用户输入
- C++类的多态特性：图形可以被抽象出来一个基类，每个类都可以实现自己的Draw()方法
- 智能指针：在管理图形的时候可以使用智能指针代替new/delete手动管理内存
- STL：还会涉及到STL的使用
- 数学计算：因为要求图形自动对齐，所以每次都要计算出每个图形的坐标
- 异常处理：
  - 当用户新插入的图形高度大于窗口的高度，此时不能继续添加图形
  - 当用户插入的图形宽度之和大于窗口的宽度，此时不能继续添加图形
  - 当输入模块是空值的时候，操作无效

# 实现
## 输入模块
用户需要与输入模块进行交互，交代待插入元素的形状、相对参照物的位置、参照物、颜色、大小等信息，这些信息需要以ListBox的形式让用户输入，
当然也可以使用文本框来进行输入，但是这样的话异常处理逻辑就会变得复杂，这里为了专注于MFC的展示就没有引入文本框输入功能。

## 渲染模块
用户完成输入之后渲染就需要及时的更新窗口的图形，这里主要使用MFC提供的接口来绘制图形，下方给出了几个绘制图形的代码片段。
```
// 绘制矩形
cdc->Rectangle(x - w / 2, y - h / 2, x + w / 2, y + h / 2);

// 绘制圆
cdc->Ellipse(x - r, y - r, x + r, y + r);

// 打印数值
cdc->TextOutW(x, y, content);
```

## 中间数据结构
为了降低用户输入模块与渲染模块之间的耦合，我使用了`graphic_elements_`，`insert_option_`, `delete_option_`等数据结构。
这些数据结构使得用户输入模块与渲染模块之间有连接，但是又不至于太乱，每个模块都只对这些中间数据结构负责。
关于这些具体数据结构的选型与用途参考下面的代码片段。

```
/* 
 * This data structure is used as the interaction hub between the rendering module and the user module.
 * The rendering module renders according to this data structure, and the user module will operate this
 * data structure to achieve the purpose of adding or deleting.
 * 
 * Although using std::list may be more in line with the requirements,
 * in order to facilitate the subsequent use of the index to insert nodes directly,
 * I still use std::vector, and in the case of a small amount of data, there is almost 
 * no performance gap between std::vector and std::list.
 * 
 * The use of pointers is to facilitate the use of C++'s polymorphic features.
 * 
 * Using smart pointers can reduce the mental burden of memory management.
 */
std::vector<std::shared_ptr<ASMPT::Shape>> graphic_elements_;

// All operations of adding nodes will be recorded in this structure
ASMPT::AddEventOption insert_option_;

// All operations of deleting nodes will be recorded in this structure
ASMPT::DelEventOption delete_option_;
```


# 演示
## 用户界面
![interface display](https://user-images.githubusercontent.com/56379080/188304781-3384ea4a-643e-454a-ae30-24a014453bcc.png)

## 插入操作
### 队头插入
![insert_begin](https://user-images.githubusercontent.com/56379080/188308301-f51a7ab9-0156-44a2-9986-ce4a4caacb1b.gif)

### 队尾插入
![insert_end](https://user-images.githubusercontent.com/56379080/188308323-887c0ef7-f61b-45a7-bcff-0f57e397419e.gif)

### 队中插入
![insert_middle](https://user-images.githubusercontent.com/56379080/188308349-09c1d36c-50aa-42ef-a1d6-152e0d7505f6.gif)

### 插入（）
![insert_all](https://user-images.githubusercontent.com/56379080/188308394-e356cc3b-90cf-4536-85bb-01af56aaddf5.gif)

## 删除操作
![delete](https://user-images.githubusercontent.com/56379080/188308363-1e9bea9d-7ae0-4d0e-8935-eb26a21e58d1.gif)


# 自我介绍
我在研究生期间一直从事数据库内核、体系结构、存储相关的研究工作，因此对于C/C++使用较为熟练。
在此之前我并没有接触过MFC编程，但是在本次小任务中我凭借良好的C++基础与较强的学习理解能力快速的完成了任务。


