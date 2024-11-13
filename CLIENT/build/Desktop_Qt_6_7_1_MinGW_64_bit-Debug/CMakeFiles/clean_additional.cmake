# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CLIENT_autogen"
  "CMakeFiles\\CLIENT_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CLIENT_autogen.dir\\ParseCache.txt"
  )
endif()
