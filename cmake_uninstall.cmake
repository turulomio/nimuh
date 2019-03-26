# Example of install/uninstall rule (header only here)
set(MANIFEST "${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt")

if(NOT EXISTS ${MANIFEST})
  message(FATAL_ERROR "Cannot find install manifest: '${MANIFEST}'")
endif()

file(STRINGS ${MANIFEST} files)
foreach(file ${files})
  if(EXISTS ${file})
    message(STATUS "Removing file: '${file}'")

    exec_program(
       ${CMAKE_COMMAND} ARGS "-E remove ${file}"
       OUTPUT_VARIABLE stdout
       RETURN_VALUE result
    )

    if(NOT "${result}" STREQUAL 0)
      message(FATAL_ERROR "Failed to remove file: '${file}'.")
    endif()
    else()
      MESSAGE(STATUS "File '${file}' does not exist.")
    endif()
endforeach(file)


IF (MINGW)
    message(STATUS "Uninstalling in MINGW")
    set(DATA_DIR "${PROJECT_SOURCE_DIR}/dist/nimuh-${nimuh_VERSION}/")
ELSE()
    message(STATUS "Uninstalling in Linux")
    set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/nimuh/")
ENDIF (MINGW)

exec_program(${CMAKE_COMMAND} ARGS "-E remove_directory ${DATA_DIR}")
message(STATUS "Removing ${DATA_DIR}")