{{ self.title() }}

{{ s('background') }}

JYY和探险队顺利完成了火星上的任务。在离开前，探险队正好赶上了火星人一年一度最盛大的节日“气球节”。然而，火星人遇到了每年一度的麻烦：怎样最美观地摆放气球。JYY决定请你设计算法帮助火星人解决这个问题。

{{ s('description') }}

在庆典开始前，火星人会把气球准备好并串在一根绳子上。气球按顺序排列可以看成是一个由小写字母组成的长度为$n$的字符串$S$。然后，火星人会按照字符串的顺序逐个把气球加入到一个庆典的圆环上，并且表演一个节目庆祝。

下图展示了一串气球`cbbadbcd`在进行到第5个节目时的情形，此时在庆典环上的气球是`cbbad`。

{{ img('/home/jyy/shared/JSTSC19/celebrate/statement/balloons.png', size = 0.4, align = 'middle', inline = False, env = ['tex', 'md']) }}

为了让每个节目都更好看，火星人希望在每个节目开始前调整气球在环上的顺序，使得每个节目的气球排布都最美观。对于一组气球(一个字符串)，火星人认为最美观的字符串是庆典圆环上按绳子方向读出**字典序最小的字符串**，例如对于`cbbad`，共有5个读出字符串的位置：

* `cbbad` ($i=1$)
* `bbadc` ($i=2$)
* `badcb` ($i=3$)
* `adcbb` ($i=4$)
* `dcbba` ($i=5$)

如果有多个字典序最小的字符串，火星人希望找出**离绳头最近**的那个(即$i$最小的那个)。更严谨地说，对于字符串$T$，定义
$$T_i = T[i\ldots |T|] :: T[1\ldots i-1]\ (1\le i \le |T|)\textrm{，}$$
其中$::$是字符串的拼接操作。定义$f(T)$为最小的$i$ ($1\le i \le |T|$)满足$T_i = \min\{T_1,T_2,\ldots,T_{|T|}\}$。

JYY希望你帮助他设计一个算法，让火星人每个节目的气球排列都最美观，即对于给定字符串$S$的每一个前缀$S[1\ldots i]$ ($1\le i \le |S|$)，求出$f(S[1\ldots i])$。

{{ s('input format') }}

{{ self.input_file() }}

输入文件只有一行，该行包括一个字符串$S$。

{{ s('output format') }}

{{ self.output_file() }}

在一行中对于每个 $i$ ($1\le i\le |S|$)，输出一个整数$f(S[1\ldots i])$。输出的数字之间以空格分隔。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('sample', 2) }}

{{ self.sample_file() }}


{{ s('subtasks') }}

{{ tbl('data') }}

