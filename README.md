DwarfCode

DwarfCode is a performance prediction tool for MPI applications on diverse computing platforms. The goal is to accurately predict the running time of applications for task scheduling and job migration. First, DwarfCode collects the execution traces to record the computing and communication events. Then, it merges the traces from different processes into a single trace. After that, DwarfCode identifies and compresses the repeating patterns in the final trace to shrink the size of the events. Finally, a dwarf code is generated to mimic the original program behavior. This smaller running benchmark is replayed in the target platform to predict the performance of the original application.

=========

Build
-------

1.  run git submodule init; git submodule update # it would download source from web,
2.  mkdir build; cd build
3.  cmake ..  # it would patch them
4.  open mpip-code and run ./configure;make
5.  open npb/NPB3.3-MPI and compile according its' readme

description
-------------

trace2symbol.cpp 对日志作初步处理。这一步取出需要记录的内容。
order.cpp 对日志进行归整化。
combine.cpp 合并日志。
circle.cpp 收缩日志中的循环。
reconstruct.cpp 构建判例程序。

对于部分应用，从combine开始的步骤目前还不能直接完成，需要手工处理。
