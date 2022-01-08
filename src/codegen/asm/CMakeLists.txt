# Generate rwir.cpp using olive
add_custom_target(brg ALL DEPENDS AsmBuilderHelper.cpp AsmBuilderHelper.h)
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/AsmBuilderHelper.cpp ${CMAKE_CURRENT_SOURCE_DIR}/AsmBuilderHelper.h
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/olive
  ARGS ${CMAKE_CURRENT_SOURCE_DIR}/AsmBuilderHelper.brg
  DEPENDS olive
)

add_executable(remniw-llc ${CMAKE_CURRENT_SOURCE_DIR}/remniw-llc.cpp
                          ${CMAKE_CURRENT_SOURCE_DIR}/AsmBuilderHelper.cpp
                          ${CMAKE_CURRENT_SOURCE_DIR}/AsmInstruction.cpp
                          ${CMAKE_CURRENT_SOURCE_DIR}/AsmFunction.cpp
                          ${CMAKE_CURRENT_SOURCE_DIR}/AsmContext.cpp)
add_dependencies(remniw-llc brg)
target_link_libraries(remniw-llc PRIVATE ${llvm_libs})