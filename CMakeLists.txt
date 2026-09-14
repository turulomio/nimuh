cmake_minimum_required(VERSION 4.3)

project(nimuh
    VERSION 1.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MINGW)
    if(NOT WIN_ARCH)
        if(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set(WIN_ARCH "x86")
        else()
            set(WIN_ARCH "x64")
        endif()
    endif()

    if(WIN_ARCH STREQUAL "x86")
        if(EXISTS "${PROJECT_SOURCE_DIR}/.mingw32/mingw32/include")
            set(MINGW_PREFIX "${PROJECT_SOURCE_DIR}/.mingw32/mingw32")
            set(CMAKE_FIND_ROOT_PATH "${PROJECT_SOURCE_DIR}/.mingw32/mingw32")
        elseif(EXISTS "${PROJECT_SOURCE_DIR}/.mingw32/include")
            set(MINGW_PREFIX "${PROJECT_SOURCE_DIR}/.mingw32")
            set(CMAKE_FIND_ROOT_PATH "${PROJECT_SOURCE_DIR}/.mingw32")
        elseif(EXISTS "/mingw32/include")
            set(MINGW_PREFIX "/mingw32")
            set(CMAKE_FIND_ROOT_PATH "/mingw32")
        elseif(EXISTS "/usr/i686-w64-mingw32/usr")
            set(MINGW_PREFIX "/usr/i686-w64-mingw32/usr")
            set(CMAKE_FIND_ROOT_PATH "/usr/i686-w64-mingw32")
        elseif(EXISTS "/usr/i686-w64-mingw32")
            set(MINGW_PREFIX "/usr/i686-w64-mingw32")
            set(CMAKE_FIND_ROOT_PATH "/usr/i686-w64-mingw32")
        else()
            set(MINGW_PREFIX "${PROJECT_SOURCE_DIR}/.mingw32/mingw32")
            set(CMAKE_FIND_ROOT_PATH "${PROJECT_SOURCE_DIR}/.mingw32/mingw32")
        endif()
    else()
        if(EXISTS "${PROJECT_SOURCE_DIR}/.mingw64/mingw64/include")
            set(MINGW_PREFIX "${PROJECT_SOURCE_DIR}/.mingw64/mingw64")
            set(CMAKE_FIND_ROOT_PATH "${PROJECT_SOURCE_DIR}/.mingw64/mingw64")
        elseif(EXISTS "${PROJECT_SOURCE_DIR}/.mingw64/include")
            set(MINGW_PREFIX "${PROJECT_SOURCE_DIR}/.mingw64")
            set(CMAKE_FIND_ROOT_PATH "${PROJECT_SOURCE_DIR}/.mingw64")
        elseif(EXISTS "/mingw64/include")
            set(MINGW_PREFIX "/mingw64")
            set(CMAKE_FIND_ROOT_PATH "/mingw64")
        elseif(EXISTS "/usr/x86_64-w64-mingw32/usr")
            set(MINGW_PREFIX "/usr/x86_64-w64-mingw32/usr")
            set(CMAKE_FIND_ROOT_PATH "/usr/x86_64-w64-mingw32")
        elseif(EXISTS "/usr/x86_64-w64-mingw32")
            set(MINGW_PREFIX "/usr/x86_64-w64-mingw32")
            set(CMAKE_FIND_ROOT_PATH "/usr/x86_64-w64-mingw32")
        else()
            set(MINGW_PREFIX "${PROJECT_SOURCE_DIR}/.mingw64/mingw64")
            set(CMAKE_FIND_ROOT_PATH "${PROJECT_SOURCE_DIR}/.mingw64/mingw64")
        endif()
    endif()

    set(CMAKE_PREFIX_PATH "${MINGW_PREFIX}" ${CMAKE_PREFIX_PATH})
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif()

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
    message(STATUS "Compiling for MINGW (${WIN_ARCH})")

    set(DIST "${PROJECT_SOURCE_DIR}/dist/nimuh-${nimuh_VERSION}-${WIN_ARCH}/")
    set(DATA_DIR "./data/")

    target_sources(nimuh PRIVATE "data/nimuh.rc")
    target_link_libraries(nimuh PRIVATE -lopengl32 -static -static-libgcc -static-libstdc++)

    install(TARGETS nimuh DESTINATION ${DIST})
    install(DIRECTORY data DESTINATION ${DIST})

    file(GLOB RUNTIME_DLLS
        "${MINGW_PREFIX}/bin/*SDL*.dll"
        "${MINGW_PREFIX}/bin/libexpat*.dll"
        "${MINGW_PREFIX}/bin/libjpeg*.dll"
        "${MINGW_PREFIX}/bin/libturbojpeg*.dll"
        "${MINGW_PREFIX}/bin/libpng*.dll"
        "${MINGW_PREFIX}/bin/libtiff*.dll"
        "${MINGW_PREFIX}/bin/libwebp*.dll"
        "${MINGW_PREFIX}/bin/libsharpyuv*.dll"
        "${MINGW_PREFIX}/bin/libmad*.dll"
        "${MINGW_PREFIX}/bin/*zlib*.dll"
        "${MINGW_PREFIX}/bin/liblzma*.dll"
        "${MINGW_PREFIX}/bin/libogg*.dll"
        "${MINGW_PREFIX}/bin/libvorbis*.dll"
        "${MINGW_PREFIX}/bin/libFLAC*.dll"
        "${MINGW_PREFIX}/bin/libdeflate*.dll"
        "${MINGW_PREFIX}/bin/libjbig*.dll"
        "${MINGW_PREFIX}/bin/libLerc*.dll"
        "${MINGW_PREFIX}/bin/libzstd*.dll"
        "${MINGW_PREFIX}/bin/libwinpthread*.dll"
        "${MINGW_PREFIX}/bin/libgcc_s*.dll"
        "${MINGW_PREFIX}/bin/libstdc++*.dll"
    )
    if(RUNTIME_DLLS)
        install(FILES ${RUNTIME_DLLS} DESTINATION ${DIST})
    endif()

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -E rm -rf "${PROJECT_SOURCE_DIR}/dist/nimuh-${PROJECT_VERSION}-${WIN_ARCH}/"
        COMMENT "Uninstalling nimuh on Windows..."
    )
else()
    message(STATUS "Compiling for Linux")

    include(GNUInstallDirs)

    if(NOT DATA_DIR)
        set(DATA_DIR "${CMAKE_INSTALL_FULL_DATADIR}/nimuh/data")
    endif()

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
