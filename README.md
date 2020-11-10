# C++基于STL的ini读写类

## 更新日志

### v0.0.1

经过测试，只要是文本，后缀ini或者是txt，对程序是不影响的。不过比较尴尬的一点，代码只考虑了对注释屏蔽，但没考虑保存注释，所以在写入时会自动删除注释。

### v0.0.2

改变函数接收参数的方式，使用模板接收参数，优化函数在传递参数过程中的体验。删除了测试部分代码

### v0.0.3

1. 增加异常机制，提高可用性
2. 扩充部分函数，部分功能提供多种方法
