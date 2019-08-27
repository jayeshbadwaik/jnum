cmake_minimum_required(VERSION 3.12)

project(
  jnum
  VERSION 0.1.0
  DESCRIPTION "jnum : reflection enabled enum generation library"
  LANGUAGES CXX
  HOMEPAGE_URL "https://github.com/jayeshbadwaik/jnum"
  )


find_package(Python3 REQUIRED)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
  )

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/jnumConfig.cmake.in
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
  )

set(LIBNAME "${PROJECT_NAME}")
add_library(${LIBNAME} INTERFACE)

target_include_directories(
  ${LIBNAME}
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )


include(GNUInstallDirs)

install(
  TARGETS ${LIBNAME}
  EXPORT ${PROJECT_NAME}Target
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

install(
  EXPORT ${PROJECT_NAME}Target
  FILE  ${PROJECT_NAME}Target.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
  )

# Install Binaries
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/bin
  USE_SOURCE_PERMISSIONS
  DESTINATION  ${CMAKE_INSTALL_PREFIX}
  )

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include
  DESTINATION  ${CMAKE_INSTALL_PREFIX}
  )

install(
  FILES ${PROJECT_SOURCE_DIR}/mit.license
  DESTINATION  ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/copyright
  )

add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

install(
  FILES
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
  )


