{{ self.title() }}

{{ s('background') }}


{{ s('description') }}

有 $T$ 个时刻, 有 $n$ 个人, 有 $m$ 条预言. 

每个预言有两个种类:

* $0$ $t$ $x$ $y$: 在 $t$ 时刻, 若 $x$ 是死亡状态, 那么在 $t+1$ 时刻, $y$ 也是死亡状态.
* $1$ $t$ $x$ $y$: 在 $t$ 时刻, 若 $x$ 是生存状态, 那么在 $t$ 时刻, $y$ 是死亡状态. 

每个人都想知道, 有多少个人有可能和他一起, 活到 $T+1$ 时刻.  

注意人是不能复活的, 可以在时刻 $1$ 就是死亡状态. 

{{ s('input format') }}

{{ self.input_file() }}

输入第一行包含三个整数 $T, n, m$. 

接下来有 $m$ 行, 每行表示一条预言, 每条预言第一个整数 $c$ 表示预言的类型. 

* $c=0$: 接下来读入 $t, x, y$
* $c=1$: 接下来读入 $t, x, y$

保证 $t \le T, 1 \le x, y \le n$

{{ s('output format') }}

{{ self.output_file() }}

输出 $n$ 个数表示答案, 用空格分割. 

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('sample', 2) }}

{{ self.sample_file() }}

{{ self.title_sample_description() }}

{{ s('subtasks') }}

{{ tbl('data') }}

