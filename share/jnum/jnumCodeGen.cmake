set(JNUM_CODEGEN_DIR ${CMAKE_CURRENT_LIST_DIR})
function(target_jnum TARGETNAME INDIR INFILE OUTDIR)

  file(RELATIVE_PATH REL_INFILE ${INDIR} ${INFILE})
  string(REPLACE ".jnum" ".hpp" REL_OUTFILE ${REL_INFILE})
  set(OUTFILE "${OUTDIR}/${REL_OUTFILE}")

  add_custom_command(
    OUTPUT ${OUTFILE}
    COMMAND ${PYTHON3_EXECUTABLE} ${JNUM_CODEGEN_DIR}/../../share/jnum/scripts/jnum.py
    --input ${INFILE} --output ${OUTFILE} --relative ${REL_OUTFILE}
    DEPENDS ${INFILE}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Generating enum header ${REL_OUTFILE}"
    )

  string(REPLACE "/" "_" OUTTARGET ${REL_OUTFILE})
  string(REPLACE "." "_" OUTTARGET ${OUTTARGET})
  add_custom_target(
    ${OUTTARGET}
    DEPENDS ${OUTFILE}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
  add_dependencies(${TARGETNAME} ${OUTTARGET})
endfunction()

function(target_jnum_directory TARGETNAME LINK_TYPE INDIR INSTALL_FLAG )
  file(RELATIVE_PATH REL_INDIR ${PROJECT_SOURCE_DIR} ${INDIR})
  set(OUTDIR "${PROJECT_BINARY_DIR}/jnum/${REL_INDIR}/include")
  file(GLOB_RECURSE JNUM_SOURCE_LIST "*.jnum")
  string(REPLACE "/" "_" INDIR_TARGET ${REL_INDIR})

  file(MAKE_DIRECTORY ${OUTDIR})

  target_include_directories(
    ${TARGETNAME}
    ${LINK_TYPE}
    $<BUILD_INTERFACE:${OUTDIR}>
    $<INSTALL_INTERFACE:include>
    )

  foreach(JNUM_FILE ${JNUM_SOURCE_LIST})
    target_jnum(${TARGETNAME} ${INDIR} ${JNUM_FILE} ${OUTDIR})
  endforeach()

  # Install Generated Headers
  if(INSTALL_FLAG STREQUAL "INSTALL_YES")
    install(
      DIRECTORY ${OUTDIR}
      DESTINATION  ${CMAKE_INSTALL_PREFIX}
      )
  elseif(INSTALL_FLAG STREQUAL "INSTALL_NO")
  else()
    message(FATAL_ERROR "Incorrect Arguments Passed")
  endif()
endfunction()

