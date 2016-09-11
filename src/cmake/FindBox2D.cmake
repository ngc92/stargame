
# - Try to find Box2D
# Once done this will define
#  BOX2D_FOUND - System has BOX2D
#  Box2D_INCLUDE_DIRS - The BOX2D include directories
#  Box2D_LIBRARIES - The libraries needed to use BOX2D

# find libs
find_library (BOX2D_LIBRARY NAMES Box2D )

#find includes
find_path(BOX2D_INCLUDE_DIR Box2D/Box2D.hD)

# set variables
set(Box2D_LIBRARIES ${IRRLICHT_LIBRARY})
set(Box2D_INCLUDE_DIRS ${IRRLICHT_INCLUDE_DIR} )

# handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Box2D DEFAULT_MSG BOX2D_LIBRARY BOX2D_INCLUDE_DIR)

# mark vars as advanced
mark_as_advanced(BOX2D_LIBRARY BOX2D_INCLUDE_DIR)