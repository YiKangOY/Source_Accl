2022/03/03

- [x] Blockmatmul.cpp 数据流并非标准形式（是否影响性能并不确定）

- [x] Matmul.cpp 数据流问题，同上

- [x] Matmul.cpp 作为顶层模块时，不应使用数据流形式建模（后续不会作为顶层，不重要）

- [x] Matmul.cpp :10,11 用作输入子矩阵的stream在并行后由于深度不够可能会死锁（改为在循环loc内部声明变量）

- [x] Matmul.cpp :35 无法展平具有多个子循环的循环。

- [x] Matmul.cpp 18,27 Load AB操作pipeline导致综合很慢？

- [x] 以上问题，不用dataflow即可避免

2022/03/04 Cosim fail 可能的原因

- [ ] 数据量过大导致错误

- [ ] 数据采用了float，位宽问题。

- [ ] 顶层模块的stream
