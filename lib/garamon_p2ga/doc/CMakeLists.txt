find_package (Doxygen)

message("p2ga_SOURCE_DIR     " ${p2ga_SOURCE_DIR})
message("p2ga_BINARY_DIR     " ${p2ga_BINARY_DIR})
message("DOXYGEN_EXECUTABLE  " ${DOXYGEN_EXECUTABLE})

if(DOXYGEN_FOUND)
  configure_file (${p2ga_SOURCE_DIR}/doc/Doxyfile-html.cmake ${p2ga_BINARY_DIR}/doc/Doxyfile-html)
  add_custom_target (html ${DOXYGEN_EXECUTABLE} ${p2ga_BINARY_DIR}/doc/Doxyfile-html)
endif (DOXYGEN_FOUND)
