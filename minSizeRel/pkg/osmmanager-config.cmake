# Compute installation prefix relative to this file.
get_filename_component(_dir "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_prefix "${_dir}/../.." ABSOLUTE)

# Import the targets.
include("${_prefix}/lib/OSMManager-1.0/OSMManager-targets.cmake")

# Report other information.
set(OSMManager_INCLUDE_DIRS "${_prefix}/include/OSMManager-1.0/")

file(GLOB OSMManager_LIBRARIES "${_prefix}/lib/OSMManager-1.0/lib*")
