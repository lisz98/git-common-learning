**线程**

--------------------------

# 介绍

类 thread 表示单个执行线程。线程允许多个函数同时执行。

线程在构造关联的线程对象时立即开始执行（等待任何OS调度延迟），从提供给作为构造函数参数的顶层函数开始。顶层函数的返回值将被忽略，而且若它以抛异常终止，则调用 std::terminate 。顶层函数可以通过 std::promise 或通过修改共享变量（可能需要同步，见 std::mutex 与 std::atomic ）将其返回值或异常传递给调用方。

std::thread 对象也可能处于不表示任何线程的状态（默认构造、被移动、 detach 或 join 后），并且执行线程可能与任何 thread 对象无关（ detach 后）。

没有两个 std::thread 对象会表示同一执行线程； std::thread 不是可复制构造 (CopyConstructible) 或可复制赋值 (CopyAssignable) 的，尽管它可移动构造 (MoveConstructible) 且可移动赋值 (MoveAssignable) 。
