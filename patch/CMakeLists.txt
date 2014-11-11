execute_process(COMMAND patch 
   ${PROJECT_SOURCE_DIR}/mpip-code/make-wrappers.py 
   ${CMAKE_CURRENT_SOURCE_DIR}/make-wrappers.py.patch
   )
execute_process(COMMAND patch
   ${PROJECT_SOURCE_DIR}/mpip-code/mpiPi.c 
   ${CMAKE_CURRENT_SOURCE_DIR}/mpiPi.c.patch
   )
execute_process(COMMAND patch
   ${PROJECT_SOURCE_DIR}/mpip-code/mpiPi.h.in 
   ${CMAKE_CURRENT_SOURCE_DIR}/mpiPi.h.in.patch
   )
execute_process(COMMAND patch
   ${PROJECT_SOURCE_DIR}/mpip-code/mpip_timers.h
   ${CMAKE_CURRENT_SOURCE_DIR}/mpip_timers.h.patch
   )
execute_process(COMMAND patch
   ${PROJECT_SOURCE_DIR}/mpip-code/mpi.protos.txt.in
   ${CMAKE_CURRENT_SOURCE_DIR}/mpi.protos.txt.in.patch
   )
execute_process(COMMAND patch
   ${PROJECT_SOURCE_DIR}/mpip-code/mpi.io.protos.txt
   ${CMAKE_CURRENT_SOURCE_DIR}/mpi.io.protos.txt.patch
   )

configure_file(make.def.in ${PROJECT_SOURCE_DIR}/npb/NPB3.3-MPI/config/make.def @ONLY)
