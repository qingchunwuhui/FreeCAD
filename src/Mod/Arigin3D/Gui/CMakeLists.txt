
# 工程附加包含目录
include_directories(
	${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
	${CMAKE_BINARY_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${COIN3D_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${XercesC_INCLUDE_DIRS}
	${OCC_INCLUDE_DIR}
)

# 工程附加依赖项
link_directories(${OCC_LIBRARY_DIR})

set(Arigin3DGui_LIBS
	${OCC_LIBRARIES}
    # ${OCC_DEBUG_LIBRARIES}
	Arigin3D
    FreeCADGui
)

MESSAGE(STATUS ${OCC_LIBRARIES})

# 在工程中添加.ui文件
SET(Arigin3DGui_UIC_SRCS
	DlgCreatePoint.ui
)

# 添加QT资源文件
if (BUILD_QT5)
    qt5_add_resources(Arigin3D_QRC_SRCS Resources/Arigin3D.qrc)
	qt5_wrap_ui(Arigin3DGui_UIC_HDRS ${Arigin3DGui_UIC_SRCS})
else()
    qt4_add_resources(Arigin3D_QRC_SRCS Resources/Arigin3D.qrc)
	qt4_wrap_ui(Arigin3DGui_UIC_HDRS ${Arigin3DGui_UIC_SRCS})
endif()

#将QT编译的ui.h文件添加到工程文件UIC中
SOURCE_GROUP("Uic" FILES ${Arigin3DGui_UIC_HDRS})

SET(Dialog_CPP_SRCS
	DlgCreatePoint.cpp
)
	
SET(Dialog_HPP_SRCS
	DlgCreatePoint.h
)

fc_wrap_cpp(Arigin3DGui_MOC_SRCS ${Dialog_HPP_SRCS})
SOURCE_GROUP("Moc" FILES ${Arigin3DGui_MOC_SRCS})
	
SET(Dialog_SRCS
	${Dialog_CPP_SRCS}
	${Dialog_HPP_SRCS}
	DlgCreatePoint.ui
)
	
SOURCE_GROUP("Dialog" FILES ${Dialog_SRCS})

SET(Arigin3DGui_SRCS
    ${Arigin3D_QRC_SRCS}
	${Dialog_SRCS}
	${Arigin3DGui_UIC_HDRS}
	# ${Arigin3DGui_MOC_SRCS}  不能加入工程项目中，否则会报编译错误
    AppArigin3DGui.cpp
    Command.cpp
    PreCompiled.cpp
    PreCompiled.h
    Workbench.cpp
    Workbench.h
)


add_library(Arigin3DGui SHARED ${Arigin3DGui_SRCS})

target_link_libraries(Arigin3DGui ${Arigin3DGui_LIBS})

fc_target_copy_resource(Arigin3DGui 
    ${CMAKE_SOURCE_DIR}/src/Mod/Arigin3D
    ${CMAKE_BINARY_DIR}/Mod/Arigin3D
    InitGui.py)

SET_BIN_DIR(Arigin3DGui Arigin3DGui /Mod/Arigin3D)
SET_PYTHON_PREFIX_SUFFIX(Arigin3DGui)
    
install(TARGETS Arigin3DGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
