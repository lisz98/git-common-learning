
**jthread**

> c++ 20 新增类

-----------------------------------------

类 jthread 表示单个执行线程。它拥有通常同 std::thread 的行为，除了 jthread 在析构时自动再结合，而且能在具体情况下取消/停止。

线程在构造关联的线程对象时（在任何操作系统调度延迟后）立即开始执行，始于作为构造函数参数提供的顶层函数。忽略顶层函数的返回值，而若它因抛异常退出，则调用 std::terminate 。顶层函数可经由 std::promise 向调用方交流其返回值或异常，或通过修改共享变量（要求同步，见 std::mutex 与 std::atomic ）。

不同于 std::thread ， jthread 逻辑上保有一个内部的 std::stop_source 类型私有成员，它维持共享停止状态。 jthread 的构造函数接受一个 std::stop_token 作为其首参数， jthread 将从其内部的 stop_source 传递它。这允许函数在其执行中检查是否已请求停止，而若已请求则返回。

std::jthread 对象亦可在不表示任何线程的状态（在默认构造、被移动、 detach 或 join 后），而执行线程可以与任何 jthread 对象关联（ detach 后）。

没有二个 std::jthread 对象可表示同一执行线程； std::jthread 非可复制构造 (CopyConstructible) 或可复制赋值 (CopyAssignable) ，尽管它为可移动构造 (MoveConstructible) 及可移动赋值 (MoveAssignable) 。

与`thread`相比，`jthread`新增了以下几个函数：

1、get_stop_source：返回与线程的停止状态关联的 stop_source 对象
2、get_stop_token：返回与线程的共享停止状态关联的 stop_token
3、request_stop：请求执行经由线程的共享停止状态停止