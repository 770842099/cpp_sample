cmake_minimum_required(VERSION 3.16)

project(cppsample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cppsample main.cpp)
add_executable(bind_test bind.cpp)

include(GNUInstallDirs)
install(TARGETS cppsample
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
