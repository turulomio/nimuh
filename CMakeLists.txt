cmake_minimum_required(VERSION 2.8.9)
project(nimuh)

IF (MINGW)
    message(STATUS "Compiling for MINGW")

set(prefix "${PROJECT_SOURCE_DIR}")
set(exec_prefix "${PROJECT_SOURCE_DIR}")

set(DATA_DIR "./data")
configure_file( config.h.in ${PROJECT_SOURCE_DIR}/src/config.h )

include_directories(src)

find_package(EXPAT REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

include_directories(${SDL_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp")
add_executable(nimuh ${SOURCES})
target_link_libraries(nimuh  ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${EXPAT_LIBRARIES} ${SDL_MIXER_LIBRARIES} -lopengl32 -static -static-libgcc -static-libstdc++)

install(TARGETS nimuh DESTINATION ${exec_prefix})
install(DIRECTORY data DESTINATION ${DATA_DIR}/../)

#^vfind_library(<some_var> NAMES <name_of_lib> PATHS "<path/to/lib>")
#With a defined EXECUTABLE_PATH, for instance:
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#you could move the .dll files that your executable need, with
#file(COPY ${<some_var>}    DESTINATION ${EXECUTABLE_OUTPUT_PATH})







ELSE()
message(STATUS "LINUX")
set(prefix "${CMAKE_INSTALL_PREFIX}")
set(exec_prefix "${CMAKE_INSTALL_PREFIX}/bin")

set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/nimuh/data")
set(APPLICATIONS_DIR "${CMAKE_INSTALL_PREFIX}/share/applications")
configure_file( config.h.in ${PROJECT_SOURCE_DIR}/src/config.h )

include_directories(src)

find_package(EXPAT)
find_package(OpenGL)
find_package(SDL_mixer)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

include_directories(${SDL_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp")
add_executable(nimuh ${SOURCES})
target_link_libraries(nimuh ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${OPENGL_LIBRARIES} ${EXPAT_LIBRARIES} ${SDL_MIXER_LIBRARIES})

install(TARGETS nimuh DESTINATION ${exec_prefix})
install(DIRECTORY data DESTINATION ${DATA_DIR}/../)
    install(FILES "nimuh.desktop" DESTINATION "${APPLICATIONS_DIR}")
endif (MINGW)

