# Install script for directory: /msu/data/t3work13/dcianciolo/gepOutput2/gep/source/athena/Trigger/TrigL0GepPerf

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/InstallArea/x86_64-slc7-gcc62-opt")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/src/athena/Trigger/TrigL0GepPerf" TYPE DIRECTORY FILES "/msu/data/t3work13/dcianciolo/gepOutput2/gep/source/athena/Trigger/TrigL0GepPerf/" USE_SOURCE_PERMISSIONS REGEX "/\\.svn$" EXCLUDE REGEX "/\\.git$" EXCLUDE REGEX "/[^/]*\\~$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDebugx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE OPTIONAL FILES "/msu/data/t3work13/dcianciolo/gepOutput2/gep/build/x86_64-slc7-gcc62-opt/lib/libTrigL0GepPerf.so.dbg")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE MODULE OPTIONAL FILES "/msu/data/t3work13/dcianciolo/gepOutput2/gep/build/x86_64-slc7-gcc62-opt/lib/libTrigL0GepPerf.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libTrigL0GepPerf.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libTrigL0GepPerf.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/cvmfs/sft.cern.ch/lcg/releases/binutils/2.28-a983d/x86_64-centos7/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libTrigL0GepPerf.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/python/TrigL0GepPerf" TYPE FILE OPTIONAL FILES "/msu/data/t3work13/dcianciolo/gepOutput2/gep/build/x86_64-slc7-gcc62-opt/python/TrigL0GepPerf/TrigL0GepPerfConf.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process( COMMAND ${CMAKE_COMMAND} -E touch
      $ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/python/TrigL0GepPerf/__init__.py )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/python/TrigL0GepPerf" TYPE FILE RENAME "CaloClusterTopoGetterGep.py" FILES "/msu/data/t3work13/dcianciolo/gepOutput2/gep/source/athena/Trigger/TrigL0GepPerf/python/CaloClusterTopoGetterGep.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/python/TrigL0GepPerf" TYPE FILE RENAME "JetBuilder.py" FILES "/msu/data/t3work13/dcianciolo/gepOutput2/gep/source/athena/Trigger/TrigL0GepPerf/python/JetBuilder.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/python/TrigL0GepPerf" TYPE FILE RENAME "L0GepSimulationSequence.py" FILES "/msu/data/t3work13/dcianciolo/gepOutput2/gep/source/athena/Trigger/TrigL0GepPerf/python/L0GepSimulationSequence.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/python/TrigL0GepPerf" TYPE FILE FILES "/msu/data/t3work13/dcianciolo/gepOutput2/gep/build/x86_64-slc7-gcc62-opt/python/TrigL0GepPerf/CaloClusterTopoGetterGep.pyc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/python/TrigL0GepPerf" TYPE FILE FILES "/msu/data/t3work13/dcianciolo/gepOutput2/gep/build/x86_64-slc7-gcc62-opt/python/TrigL0GepPerf/JetBuilder.pyc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/python/TrigL0GepPerf" TYPE FILE FILES "/msu/data/t3work13/dcianciolo/gepOutput2/gep/build/x86_64-slc7-gcc62-opt/python/TrigL0GepPerf/L0GepSimulationSequence.pyc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/jobOptions/TrigL0GepPerf" TYPE FILE RENAME "createL0GepSimulationSequence.py" FILES "/msu/data/t3work13/dcianciolo/gepOutput2/gep/source/athena/Trigger/TrigL0GepPerf/share/createL0GepSimulationSequence.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/data/TrigL0GepPerf" TYPE FILE RENAME "data.txt" FILES "/msu/data/t3work13/dcianciolo/gepOutput2/gep/source/athena/Trigger/TrigL0GepPerf/data/data.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process( COMMAND ${CMAKE_COMMAND}
      -E make_directory
      $ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/include )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process( COMMAND ${CMAKE_COMMAND}
         -E create_symlink ../src/athena/Trigger/TrigL0GepPerf/TrigL0GepPerf
         $ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/include/TrigL0GepPerf )
endif()

