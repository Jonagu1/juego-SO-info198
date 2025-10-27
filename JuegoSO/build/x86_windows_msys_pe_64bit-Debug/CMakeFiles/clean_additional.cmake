# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\JuegoSO_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\JuegoSO_autogen.dir\\ParseCache.txt"
  "JuegoSO_autogen"
  )
endif()
