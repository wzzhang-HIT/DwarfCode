if(NOT EXISTS ${PROJECT_SOURCE_DIR}/mpip-code/ChangeLog)
   execute_process(COMMAND svn 
      checkout -r430 # version 3.1.2
      svn://svn.code.sf.net/p/mpip/code/trunk
      ${PROJECT_SOURCE_DIR}/mpip-code
      RESULT_VARIABLE SVN_RESULT
      )
   if(NOT ${SVN_RESULT} EQUAL 0)
      message(FATAL "a error occur when checkout mpiP")
   endif()
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
      ${PROJECT_SOURCE_DIR}/mpip-code/mpi.protos.txt
      ${CMAKE_CURRENT_SOURCE_DIR}/mpi.protos.txt.patch
      )
endif()

configure_file(make.def.in ${PROJECT_SOURCE_DIR}/npb/NPB3.3-MPI/config/make.def @ONLY)
