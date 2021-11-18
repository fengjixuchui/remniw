# REMNIW

项目名来源于：

> 寒暑易节，始一反焉。—— 愚公移山

**win**ter, sum**mer** ➡ ret**niw**, **rem**mus ➡ **rem**mus,ret**niw** ➡ **remniw**

## 初衷

本项目最初是本人为了学习 [Static Program Analysis](https://cs.au.dk/~amoeller/spa/)  而开的一个项目，想要动手实现书中的各种静态分析技术。

随着项目逐渐发展，不再限于 SPA 这本书中内容，演变成了一个将 remniw 源代码编译为 x64 汇编的编译器。

希望本项目对想自己实现编译器的爱好者有所帮助。因本人水平有限，代码中很多不足之处，欢迎各位以 Issue 和 Pull Request 的方式批评指正，感激不尽。

## 设计

remniw 编译器包含 5 个 phase：

- [frontend]() 输入为 remniw 的源代码，输出为 AST。remniw 使用 [ANTLR4](https://www.antlr.org/) 来定义 remniw 的语法、生成 Lexer 和 Parser
- [semantic analysis]() 语义分析阶段只在 AST 上做了非常简单的 type checking
- [ir code generation]() 输入为 AST，输出为 IR。remnniw 编译器的中间表示使用的是 [LLVM](https://www.llvm.org/) IR 的一个子集，只使用 LLVM IR 的子集有一个好处，在实现程序的静态分析、优化时只需要考虑有限的 llvm instruction，这样方便我们实现算法，更专注于分析、优化算法本身，而不会陷于繁多的 llvm instruction
- [optimization]() 输入为 LLVM IR，输出为优化后的 LLVM IR
- asm code generation 输入为优化后的 LLVM IR，输出为 x64 汇编。remniw 编译器基于 [Olive Code Generator Generator](https://suif.stanford.edu/pub/tjiang/olive.tar.gz) 实现 x64 汇编的自动生成

### 语法 Syntax

remniw 语言的语法设计脱胎于 SPA 中的 TIP 语言的语法，下面给出一个使用 remniw 语言编写的计算阶乘的程序源代码：

```
func rec(n int) int {
    var f int;
    if (n==0) { f=1; }
    else { f=n*rec(n-1); }
    return f;
}

func main() int {
    var n int;
    n = input;
    output rec(n);
    return 0;
}
```

### 中间表示 IR

remnniw 编译器的中间表示使用的是 LLVM IR 的一个子集，目前只使用了如下 instruction：

- ‘ret’ Instruction
- ‘br’ Instruction
- ‘add’ Instruction
- ‘sub’ Instruction
- ‘mul’ Instruction
- ‘sdiv’ Instruction
- 'alloca' instruction
- ‘load’ Instruction
- ‘store’ Instruction
- ‘icmp’ Instruction
- ‘call’ Instruction

只使用 LLVM IR 的子集有一个好处，在 middle-end 实现程序的静态分析、优化时只需要考虑有限的 llvm instruction，这样方便我们实现算法，更专注于分析、优化算法本身，而不会陷于繁多的 llvm instruction。

## 文档

remniw 编译器 5 个 phase 的详细文档位于 docs 目录下：

- [frontend]()
- [semantic analysis]()
- [ir code generation]()
- [optimization]()
- [asm code generation]()