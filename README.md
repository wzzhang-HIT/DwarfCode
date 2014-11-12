DwarfCode
-------
DwarfCode is a performance prediction tool for MPI applications on diverse computing platforms. The goal is to accurately predict the running time of applications for task scheduling and job migration. First, DwarfCode collects the execution traces to record the computing and communication events. Then, it merges the traces from different processes into a single trace. After that, DwarfCode identifies and compresses the repeating patterns in the final trace to shrink the size of the events. Finally, a dwarf code is generated to mimic the original program behavior. This smaller running benchmark is replayed in the target platform to predict the performance of the original application.

=========
Authors:	
-------
1. wzzhang-HIT: <wzzhang@hit.edu.cn>
2. yuanjing zhang: <zhangyuanjing@nis.hit.edu.cn>
3. xiehuc: <xiehuc@gmail.com>

License:	GPLv3

Build
-------

1.  run git submodule init; git submodule update # it would download source from web,
2.  mkdir build; cd build
3.  cmake ..  # it would patch them
4.  open mpip-code and run ./configure;make
5.  open npb/NPB3.3-MPI and compile according its' readme

Description
-------------

1. trace2symbol.cpp and order.cpp:  record and symbolize the communication and computation events
2. combine.cpp:                     merge the traces from these processes into a single trace 
3. circle.cpp:                      identify and compress the repeating patterns in the trace to shrink the events size
4. reconstruct.cpp:                 convert the merged and compressed trace into an executable program


