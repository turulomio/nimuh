cmake_minimum_required(VERSION 3.0.0)
project(nimuh VERSION 1.0.6)


configure_file( config.h.in ${PROJECT_SOURCE_DIR}/src/config.h )


find_package(EXPAT REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

include_directories(src)
include_directories(${SDL_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp")


IF (MINGW)
    message(STATUS "Compiling for MINGW")

    set(DIST "${PROJECT_SOURCE_DIR}/dist/nimuh-${nimuh_VERSION}/")

    set(DATA_DIR "./data/")

    add_executable(nimuh ${SOURCES} "data/nimuh.rc")
    target_link_libraries(nimuh ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${EXPAT_LIBRARIES} ${SDL_MIXER_LIBRARIES} -lopengl32 -static -static-libgcc -static-libstdc++)

    install(TARGETS nimuh DESTINATION ${DIST})
    install(DIRECTORY data DESTINATION ${DIST})

    install(FILES /mingw64/bin/SDL.dll  DESTINATION ${DIST})    
    install(FILES /mingw64/bin/libSDL_mixer-1-2-0.dll DESTINATION ${DIST})
    install(FILES /mingw64/bin/libjpeg-8.dll DESTINATION ${DIST})
    install(FILES /mingw64/bin/libpng16-16.dll DESTINATION ${DIST})
    install(FILES /mingw64/bin/libtiff-5.dll  DESTINATION ${DIST})
    install(FILES /mingw64/bin/SDL_image.dll  DESTINATION ${DIST})
    install(FILES /mingw64/bin/libexpat-1.dll  DESTINATION ${DIST})
    install(FILES /mingw64/bin/libwebp-7.dll  DESTINATION ${DIST})
    install(FILES /mingw64/bin/libmad-0.dll  DESTINATION ${DIST})
    install(FILES /mingw64/bin/zlib1.dll  DESTINATION ${DIST})
    install(FILES /mingw64/bin/liblzma-5.dll  DESTINATION ${DIST})
    install(FILES /mingw64/bin/libogg-0.dll  DESTINATION ${DIST})
    install(FILES /mingw64/bin/libvorbis-0.dll  DESTINATION ${DIST})
    install(FILES /mingw64/bin/libvorbisenc-2.dll  DESTINATION ${DIST})
    install(FILES /mingw64/bin/libvorbisfile-3.dll  DESTINATION ${DIST})

ELSE()
    message(STATUS "Compiling for Linux")
    set(prefix "${CMAKE_INSTALL_PREFIX}")
    set(exec_prefix "${CMAKE_INSTALL_PREFIX}/bin")

    set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/nimuh/data")
    set(APPLICATIONS_DIR "${CMAKE_INSTALL_PREFIX}/share/applications")

    find_package(OpenGL)

    add_executable(nimuh ${SOURCES})
    target_link_libraries(nimuh ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${OPENGL_LIBRARIES} ${EXPAT_LIBRARIES} ${SDL_MIXER_LIBRARIES})

    install(TARGETS nimuh DESTINATION ${exec_prefix})
    install(DIRECTORY data DESTINATION ${DATA_DIR}/../)
    install(FILES "nimuh.desktop" DESTINATION "${APPLICATIONS_DIR}")
    
ENDIF (MINGW)
configure_file( config.h.in ${PROJECT_SOURCE_DIR}/src/config.h )
