cmake_minimum_required(VERSION 2.8.9)
project(nimuh)

set(prefix "${CMAKE_INSTALL_PREFIX}")
set(exec_prefix "${CMAKE_INSTALL_PREFIX}/bin")

set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/nimuh")
configure_file( config.h.in src/config.h )
include_directories(src)

find_package(EXPAT)
find_package(OpenGL)
find_package(SDL_mixer)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

include_directories(${SDL_INCLUDE_DIR})# ${SDLIMAGE_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp")
add_executable(nimuh ${SOURCES})

target_link_libraries(nimuh ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${OPENGL_LIBRARIES} ${EXPAT_LIBRARIES} ${SDL_MIXER_LIBRARIES})
install(DIRECTORY data DESTINATION ${DATA_DIR})
