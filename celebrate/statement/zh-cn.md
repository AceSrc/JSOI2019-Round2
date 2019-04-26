{{ self.title() }}

{{ s('background') }}

{{ s('description') }}

对于一个串 $T$, $f(T)$ 是指最小的 $i$, 使得 $T[i..|T|]T[1..i-1]$ 在 $T$ 的所有循环表示中字典序最小. 

给定一个字符串 $S$, 对其每个前缀 $S[1..i]$, 求 $f(S[1..i])$

{{ s('input format') }}

{{ self.input_file() }}

输入文件只有一行, 该行包括一个字符串, $S$. 

{{ s('output format') }}

{{ self.output_file() }}

在一行中对于每个 $i$, 输出 $f(S[1..i])$, 以空格分割. 

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

{{ s('sample', 2) }}

{{ self.sample_file() }}


{{ s('subtasks') }}

{{ tbl('data') }}

{{ s('scoring') }}

{{ s('hint') }}

