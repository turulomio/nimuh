cmake_minimum_required(VERSION 4.3)

project(nimuh
    VERSION 1.0.6
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies
find_package(EXPAT REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_mixer REQUIRED)

# Source files
file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(nimuh ${SOURCES})

# Target include directories
target_include_directories(nimuh PRIVATE
    src
    ${SDL_INCLUDE_DIR}
    ${SDL_IMAGE_INCLUDE_DIRS}
    ${SDL_MIXER_INCLUDE_DIRS}
    ${EXPAT_INCLUDE_DIRS}
)

# Common link libraries
if(TARGET SDL::SDL)
    target_link_libraries(nimuh PRIVATE SDL::SDL)
else()
    target_link_libraries(nimuh PRIVATE ${SDL_LIBRARY})
endif()

if(TARGET EXPAT::EXPAT)
    target_link_libraries(nimuh PRIVATE EXPAT::EXPAT)
else()
    target_link_libraries(nimuh PRIVATE ${EXPAT_LIBRARIES})
endif()

target_link_libraries(nimuh PRIVATE
    ${SDL_IMAGE_LIBRARIES}
    ${SDL_MIXER_LIBRARIES}
)

if(MINGW)
    message(STATUS "Compiling for MINGW")

    set(DIST "${PROJECT_SOURCE_DIR}/dist/nimuh-${nimuh_VERSION}/")
    set(DATA_DIR "./data/")

    target_sources(nimuh PRIVATE "data/nimuh.rc")
    target_link_libraries(nimuh PRIVATE -lopengl32 -static -static-libgcc -static-libstdc++)

    install(TARGETS nimuh DESTINATION ${DIST})
    install(DIRECTORY data DESTINATION ${DIST})

    install(FILES
        /mingw64/bin/SDL.dll
        /mingw64/bin/libSDL_mixer-1-2-0.dll
        /mingw64/bin/libjpeg-8.dll
        /mingw64/bin/libpng16-16.dll
        /mingw64/bin/libtiff-5.dll
        /mingw64/bin/SDL_image.dll
        /mingw64/bin/libexpat-1.dll
        /mingw64/bin/libwebp-7.dll
        /mingw64/bin/libmad-0.dll
        /mingw64/bin/zlib1.dll
        /mingw64/bin/liblzma-5.dll
        /mingw64/bin/libogg-0.dll
        /mingw64/bin/libvorbis-0.dll
        /mingw64/bin/libvorbisenc-2.dll
        /mingw64/bin/libvorbisfile-3.dll
        DESTINATION ${DIST}
    )

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -E rm -rf "${PROJECT_SOURCE_DIR}/dist/nimuh-${PROJECT_VERSION}/"
        COMMENT "Uninstalling nimuh on Windows..."
    )
else()
    message(STATUS "Compiling for Linux")

    include(GNUInstallDirs)

    set(DATA_DIR "${CMAKE_INSTALL_FULL_DATADIR}/nimuh/data")

    find_package(OpenGL REQUIRED)

    if(TARGET OpenGL::GL)
        target_link_libraries(nimuh PRIVATE OpenGL::GL)
    else()
        target_link_libraries(nimuh PRIVATE ${OPENGL_LIBRARIES})
    endif()

    install(TARGETS nimuh DESTINATION ${CMAKE_INSTALL_BINDIR})
    install(DIRECTORY data DESTINATION "${CMAKE_INSTALL_DATADIR}/nimuh")
    install(FILES "nimuh.desktop" DESTINATION "${CMAKE_INSTALL_DATADIR}/applications")

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_INSTALL_FULL_BINDIR}/nimuh"
        COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_INSTALL_FULL_DATADIR}/applications/nimuh.desktop"
        COMMAND ${CMAKE_COMMAND} -E rm -rf "${CMAKE_INSTALL_FULL_DATADIR}/nimuh"
        COMMENT "Uninstalling nimuh..."
    )
endif()

configure_file(config.h.in "${PROJECT_SOURCE_DIR}/src/config.h" @ONLY)
