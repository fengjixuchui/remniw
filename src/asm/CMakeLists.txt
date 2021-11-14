# Generate rwir.cpp using olive
add_custom_target(rwir ALL DEPENDS rwir.cpp)
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/rwir.cpp ${CMAKE_CURRENT_SOURCE_DIR}/rwir.h
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/olive
  ARGS ${CMAKE_CURRENT_SOURCE_DIR}/rwir.brg
  DEPENDS olive
)

add_executable(llc-olive ${CMAKE_CURRENT_SOURCE_DIR}/rwir.cpp)
add_dependencies(llc-olive rwir)
target_link_libraries(llc-olive PRIVATE ${llvm_libs})