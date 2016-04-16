# - Try to find LIBTCOD
# Once done this will define
#  LIBTCOD_FOUND - System has LIBTCOD
#  LIBTCOD_INCLUDE_DIRS - The LIBTCOD include directories
#  LIBTCOD_LIBRARIES - The libraries needed to use LIBTCOD
#  LIBTCOD_DEFINITIONS - Compiler switches required for using LIBTCOD

find_path(LIBTCOD_INCLUDE_DIR libtcod.hpp PATH_SUFFIXES libtcod)

find_library(LIBTCOD_CXX_LIBRARY NAMES libtcodxx tcodxx)
find_library(LIBTCOD_C_LIBRARY NAMES libtcod tcod)

set(LIBTCOD_LIBRARIES ${LIBTCOD_CXX_LIBRARY} ${LIBTCOD_C_LIBRARY})
set(LIBTCOD_INCLUDE_DIRS ${LIBTCOD_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBTCOD_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LIBTCOD DEFAULT_MSG
                                  LIBTCOD_LIBRARY LIBTCOD_INCLUDE_DIR)

mark_as_advanced(LIBTCOD_INCLUDE_DIR LIBTCOD_LIBRARY)
