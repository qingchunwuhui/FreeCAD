
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${OCC_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${XercesC_INCLUDE_DIRS}
)

set(Arigin3D_LIBS
	Part
    FreeCADApp
)

SET(Arigin3D_SRCS
    AppArigin3D.cpp
    PreCompiled.cpp
    PreCompiled.h
	CXJPoint.h
	CXJPoint.cpp
)

add_library(Arigin3D SHARED ${Arigin3D_SRCS})
target_link_libraries(Arigin3D ${Arigin3D_LIBS})


fc_target_copy_resource(Arigin3D 
    ${CMAKE_SOURCE_DIR}/src/Mod/Arigin3D
    ${CMAKE_BINARY_DIR}/Mod/Arigin3D
    Init.py)

SET_BIN_DIR(Arigin3D Arigin3D /Mod/Arigin3D)
SET_PYTHON_PREFIX_SUFFIX(Arigin3D)

install(TARGETS Arigin3D DESTINATION ${CMAKE_INSTALL_LIBDIR})
