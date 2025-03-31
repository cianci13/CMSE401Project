# Set the minimum required CMake version:
cmake_minimum_required( VERSION 3.7 FATAL_ERROR )

project(UserAnalysis)

# Pick up a local version of the AtlasCMake code if it exists:
find_package( AtlasCMake QUIET )

# Find the project that we depend on:
#find_package( AnalysisBase )

# Set up CTest:
atlas_ctest_setup()

# Set up a work directory project:
atlas_project( WorkDir 21.2.189
   USE AnalysisBase 21.2.189
    )

# Set up the runtime environment setup script(s):
lcg_generate_env( SH_FILE ${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh )
install( FILES ${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh
   DESTINATION . )

# Set up CPack:
atlas_cpack_setup()
