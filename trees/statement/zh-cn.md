{{ self.title() }}

{{ s('background') }}


{{ s('description') }}

给定 $m$ 棵树, 根据这些树建立一个图 $G$. 

* 若点 $x, y$ 在同一棵树中, 且有一条树边连接 $x, y$, 那么在 $G$ 中 $x, y$ 之间有一条无向边. 
* 若点 $x, y$ 不在同一棵树中, 那么在 $G$ 中 $x, y$ 之间有一条无向边. 

求 $G$ 的哈密顿回路个数. 

{{ s('input format') }}

第一行读入 $m$, 表示有 $m$ 棵树. 

接下来有 $m$ 部分, 每部分是对一棵树的描述. 

对于第 $i$ 棵树, 首先读入树的大小 $k_i$. 

接下来 $k_i - 1$ 行, 每行两个整数 $x, y$, 表示该树 $x, y$ 之间有一条树边. 

{{ self.input_file() }}

{{ s('output format') }}

{{ self.output_file() }}

输出一个非负整数, 表示答案对 `998244353` 取模后的值. 

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

{{ s('sample', 2) }}

{{ self.sample_file() }}

{{ s('subtasks') }}

{{ tbl('data') }}

{{ s('scoring') }}

{{ s('hint') }}

