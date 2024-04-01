# Data-Structure-with-CandCpp
自己用C和C++实现了一些数据结构，写得一坨，仅用于数据结构知识的学习强化。

# 有关Hashset的
HashClass和RBTree头文件是Hashset有关的，用C++简单实现了一下JAVA容器Hashset的底层逻辑，代码可读性非常一般，我自己第二天看的第一天代码都一脸懵逼很久，顺便熟悉熟悉C++。
该Hashset容器有以下特点：底层为数组，占有元素的坑超过负载因子自动扩容，发生哈希碰撞的元素会用链表的方式解决，如果链表挂载元素的长度超过阈值，转化为红黑树，红黑树的实现可参考红黑树的C语言实现，基本就是这个代码转化为类和对象版本。
#### 插入元素的一些说明：
链表插入是头插法，但是是插在第一个元素的后面。对于自定义类型的插入，需要重载各种比较符。  
showTable：如果哈希表的元素是链表，则会按顺序打印链表的数据，如果元素是红黑树，我用了中序遍历，因此会从小到大展示元素，以此来debug是否成功转化为了红黑树。

# 有关Vector的实现
我写了一个很长的基础Vector，并实现了迭代器iterator，与其相关的insert操作上做了一些优化，使得insert操作的速度比标准模块快了好几个量级，优化策略是将for循环一个个元素的移动调用move和copy的标准库函数来优化

# 有关两个栈的实现
我写了两个栈，一个栈是数组实现，自动扩容，一个栈是链表栈  
通过压力测试来测试二者的性能，链表栈的执行时间比数组栈慢了很多，因为要经常开辟内存存放元素，而数组栈速度快，空间上要求高。  
这是一个空间与时间取舍的一个例子，效果直观（doge）

# 有关一堆数据结构的 -。-
突然一天的心血来潮，暴花一上午写了堆巨基础的数据结构，最终就是为了用自己写的队列实现树的层次遍历。

