# 1.1
不缺内存的情况下，一般的标准库中都会有排序的函数或者排序的容器，可以直接使用，比如在C++中我们可以直接使用一个std::set来对对象进行
排序，见[代码](./src/1_1.cpp)。

# 1.2
书中为了保存1000万个不重复的数是否存在的这样的信息，使用了一个bitset，我们可以利用数组 + 位运算实现一个自己的bitset。
见[代码](./src/1_2.cpp)，像这种数据不重复且互相特别紧邻的情况下，使用bitset比较合适，可以减少很多内存占用。

# 1.3
本题就是要使用一下我们自己写的bitset，并且和系统库中的std::set的插入来作比较，以下是在我机器上两者的性能对比。

| 方法 | 数据量| 总耗时 |
| --- | --- | --- |
| std::set | 100w | 615ms |
| BitSet | 100w | 14ms | 
可以看到自己实现的BitSet比系统库的std::set性能要高出不少，主要有这样几个原因：
1. std::set的底层实现一般是某种树状结构，属于一种动态增长的数据结构，所以在数据插入过程中会不断分配内存，这个分配内存的过程是耗时的（std::set没有reserve()类似的函数来预先分配内存）。
2. BitSet对特定位进行置位的复杂度是O(1), 但是std::set插入一个元素的复杂度是O(logN), 所以BitSet会更快一些。

但是BitSet只适用于已知数据范围且数据分布比较密集的场景，如果数据分布是稀疏的，那么内存利用率就会相应降低，如果数据范围太大，那么或许BitSet根本无法表示这些数据。

# 1.4
本题的意思是要让我们自己写一个随机数的生成器。之前的练习中，我一直是使用的C++的中random中的随机数函数。
这里我们先了解一下C++中的随机数相关的函数，然后自己设计一个均匀分布的随机数函数。
C++中的随机数看上去复杂，实际上比较简单，只有两个概念：
1. Uniform random bit generator：均匀分布的随机数生成器。
2. Random number distribution：各种随机数分布。

其中第1项是最基本的，使用随机数生成器生成的随机数全部都是满足均匀分布的，只不过生成的算法有所不同而已(比如说基于线性同余、梅森旋转算法等)。比较标志性的生成器有这样几种：
1. linear_congruential_engine
2. mersenne_twister_engine
3. subtract_with_carry_engine
4. random_device
其中random_device比较特殊，是一个纯粹的无规律的随机数生成器，应该是连均匀分布都不能保证，一般只拿来生成seed。

上面的这些随机数生成器比较原始，用起来要填的参数很多，C++就预先实例化了几个常用的生成器，比如说：
1. mt19937, 实际上就是mersenne_twister_engine的一个特殊实例。
2. minstd_rand, 实际上就是linear_congruential_engine的一个特殊实例。

随机数分布对象实际上是对随机数生成器生成的结果进行了后处理(post process)，把均匀分布变成了其他的分布，C++中提供的分布有这样几种：
1. 均匀分布： uniform_int_distribution、uniform_real_distribution
2. 伯努利分布：binomial_distribution
3. 泊松分布：poisson_distribution
4. 正态分布： normal_distribution
5. 采样分布：discrete_distribution

整体的random的使用方法是这样的：
```C++
// 使用random_device产生随机数种子
std::random_device r;
std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};

// 按照自己的需求选取一种随机数生成器
std::mt19937 generator(seed);
// 如果只是要均匀的随机数的话，对范围和分布没限制，那么就直接生成就行了
unsigned int random = generator();

// 大多数情况下，我们需要符合某种分布，在特定范围的随机数，这时候就需要定义一种分布。
 std::normal_distribution<> dist(0, 1);
 int i = 0;
 for (int i = 0; i < count; i++) {
     // 使用分布产出数据，参数中需要带上特定的generator。
     d(generator);
 }
```

接下来我们来实现一下自己的随机数生成器。