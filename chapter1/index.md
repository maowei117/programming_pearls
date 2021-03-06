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

接下来我们来实现一下自己的随机数生成器，一个严谨的随机数生成器是有很多trick的，但是我们为了简便，就用线性同余法做一个简单的就行，代码见[1_4](./src/1_4.cpp)。从随机结果上来看，我们这里实现的简易随机数生成器生成的随机数分布还不是很均匀，本书后面还有与随机数相关的讨论，等到12章的时候再来详细讨论一下。

# 1.5
要存储1kw的数字，使用BitSet的方式，我们需要1kw个bit（约1.192MB）。而本题中限制了我们只能使用1MB的内存。那么显然我不能一次把所有数据
全部都加载到内存中。

这里就可以使用多趟的算法：我们限制BitSet的大小为1MB，这样我们可以处理的数据从0 - 8388607（1 * 1024 * 1024 * 8 = 8388608）。
第一趟处理，我们只关注[0, 8388607]之间的值，第二趟处理我们处理[8388608, 10000000]之间的值，只不过第二趟处理的时候，我们要对
BitSet加上一个偏置8388608。代码见[1_5](./src/1_5.cpp)

最后借用一下书后答案里面的一句话：k趟算法可以使用k * n的时间，n / k的空间完成对n个小于n的无重复正整数的排序。

# 1.6
这个题目很有意思，之前我们说位图只适用于不重复数据的统计，原因是对于每个数字，我们只使用了1bit来存储这个数字的状态。对于1bit而言，
只有两种状态，0或者1，所以我们无法通过这1bit来得到具体数字出现的次数。

这里如果需求变成了，每个数字最多重复出现10次，那么按照位图的思路，我们可以用4个bit来存储一个数字的状态，这样允许数字最多重复出现
15次(2 ^ 4 - 1)。这里就有点信息论的味道了，要存储这些数字出现次数的信息，每个数字需要4个bit才够。
按照这种方式来计算，存储1kw的数字，我们一共需要 1kw * 4bit = 4.77MB。

但是考虑到一个问题，真实情况中，其实并不是所有数字都可能出现的，也就是说我们这个位图可能是稀疏的。当我们使用位图的时候，我们是为每个
数字都分配了4bit来存储。当位图是稀疏的时候，我们可以换种思路，不要用位图，而是把数字都存下来再进行排序，表示0 - 1kw的数字需要24bit。
N个数字需要24 * N bit。

随着数据量的改变和实际条件的改变，我们可以看到不同方案的优势，这就是数据结构和算法带来的魅力。

# 1.7
这个题目一下问了很多问题，我们逐一来解答一下：
1. 如果某个数出现超过一次的话，会发生什么？这种情况下如何报错，并调用错误处理函数？
因为bitset只用了一个bit来表示某个数字是否存在，并不能记录数字出现的次数，所以出现多次和出现一次是一样的效果，都表现为这个数字出现了。
这种情况下，我们输入每个数字的时候，需要进行一下check，确保这个数字对应的bit为0，否则这个数字就曾经出现过，就需要报错，伪代码如下:
```
if bit[i] == 1:
    throw NumRepeatedError;

// continue process.

```
2. 当输入的整数小于0或者大于n的时候会发生什么？应该如何处理这种异常？
这种边界检查如果不做的话，就会导致`bit[i]`访问到预定的内存外。如果内存是在栈中申请的，那么可能会抛出SegmentFault。如果内存是堆中
申请的，那么就是未定义的行为，会写入到错误的内存中。所以边界检查是很有意义的，可以像下面这样检查：
```
if i < 0 or i >= n:
    throw NumRangeError;
```
3. 程序还应该包含哪些检查？
要对一个函数做何种程度的参数检查，这个其实是一个工程上的追求的平衡。当输入参数的情况比较复杂的时候，为了排除异常情况，通常要加
的检查就多一些。但是如果对性能有一定要求，那么加太多的异常检查代码可能又没有必要。一般来说，异常参数检查是结合参数的实际情况，先
有一个参数的测试用例，然后来针对性的编写代码进行异常参数的检查。

# 1.8
当区号也开始增加的时候，如果还是要限制在1MB的空间内对这些电话号码进行排序，那么我们可以用多趟算法：即每次只处理一个区号下的电话号码。
对于800、877、888这三个区号，我们只需要3趟排序即可完成。

那么如何来保存这些电话号码呢？因为大量电话号码的区号都是一样的，所以我们没必要把区号和电话号码一起存储，我们可以利用区号进行分桶，
每个桶内的电话号码区号都是相同的，他们共用一个区号。可以用10bit保存区号（这样支持0 - 1023之间的区号，其实还可以用更少的bit，因为这里
实际上只有3个区号，理论上来说2bit就够了。），然后每个区号对应一个bitset，存储方式如下：
```

| area_code(10bit) | bitset(1000w bit) | area_code(10bit) | bitset(1000w bit) | ... | 

```
这种方式，我们每次查找的时候先找到area_code，然后直接用电话号码作为偏移去找`bit[i]`，查看值是否为1即可。查询的复杂度是O(1)的。

# 1.9
bitset存在一个问题，那就是bitset中的bit本身就存储了状态，所以在使用之前必须要将bitset中所有的bit进行初始化。但是实际情况中，如果
这个bitset是稀疏的，那么我们如果还是将这个bitset全部初始化，就需要轮询这个bitset所有的bit一次，并设置为0。题目的要求是，有没有什么
办法使得我们有多少数字就初始化多少个bit呢？

举个例子，比如说我们用1000w个bit来构建了一个bitset，但是输入文件只有100个数字。这时候有什么办法使得我们能记录下是哪100个数字被置位
了么？（bitset在未初始化的情况下，所有的bit都可能是0或者1）。

对于这个问题，课后答案给了一个非常漂亮的解法，不过我们不直接讲这个解法，先自己尝试一下。要能记录哪个数字出现过，其实很简单，我们只
需要一个紧密的数组即可。
```C
record_array = []
pos = 0
while has_input():
    num = input();
    record_array[pos++] = num;
```
通过这个数组，我们就可以把数字保存到一个数组中，这样我们每次检查数字是否出现，就遍历一下record_array，就能知道对应的数字是否出现过了。
这种做法简单，但是查询数字是否存在这个操作是O(n)的，显然不可接受。

为了能快速查到，某个数字是否在向量集合中，我们需要能够根据数字本身，快速定位到它在record_array中的位置，这就有了题目后面的答案。
```C
index = 0
// from是和bitset同样大小的数组，用于保存数字在to中的索引。
from = [] 
// to是一个紧密的数组，用于保存出现过的数字。
to = []
while has_input():
    num = input();
    from[num] = index;
    to[index] = num;
    data[num] = 0; 
    index++;
```
通过这种设计，所有出现过的数字都会保存在to这个数组中，一共有index个。当我们要校验一个数n是否在集合中的时候，我们首先查from数组，看
from[n] < index是否成立，如果不成立，那么说明这个n都未被初始化。如果成立，我们还要查看to[from[n]] == n，只有保存在to数组中的，才
是出现过的数。

这就是一种典型的用空间换时间的做法，本来我如果只用to数组，也能保存出现的所有数，但是，因为to数组是无序的，所以我查找一个数是否在to中，
复杂度是O(N)的。就算我们把to数组排个序，查找起来复杂度也是O(logN)的。而这时候from数组的出现，其实就是给to数组中的内容加了个索引（hash）。
有了这个from数组之后，先通过输入本身 + 一定的计算（这里没有复杂的hash计算，直接就是数字本身映射到索引），就可以直接定位到数字被保存的位置。
这种思路应该是很值得借鉴的。

# 1.10
这里其实就是哈希表，然后用链表来解决哈希冲突。

# 1.11
这个题目的答案属实有点搞笑=。=，居然是用信鸽送底片，然后到另一边之后再来打印放大。

# 1.12
经典脑筋急转弯，用铅笔，我感觉NASA不会这么蠢（当然这也不好说）。
