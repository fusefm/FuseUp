project(FuseUp)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(FuseUp_SRCS uploaddialog.cpp useredit.cpp FuseUp.cpp main.cpp)
set(FuseUp_UI_SRCS main.ui userEdit.ui uploadDialog.ui)
set(FuseUp_RCS res.qrc)

qt4_automoc(${FuseUp_SRCS})
qt4_wrap_ui(FuseUp_UI_SRCS_H ${FuseUp_UI_SRCS})
qt4_add_resources(FuseUp_compiled_RCS ${FuseUp_RCS})
add_executable(FuseUp ${FuseUp_SRCS} ${FuseUp_UI_SRCS_H} ${FuseUp_compiled_RCS})
target_link_libraries(FuseUp ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSQL_LIBRARY} ${QT_QTNETWORK_LIBRARY})
