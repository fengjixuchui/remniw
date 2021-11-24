# Generate rwir.cpp using olive
add_custom_target(brg ALL DEPENDS ASMCodeGenerator.cpp ASMCodeGenerator.h)
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ASMCodeGenerator.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ASMCodeGenerator.h
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/olive
  ARGS ${CMAKE_CURRENT_SOURCE_DIR}/ASMCodeGenerator.brg
  DEPENDS olive
)

add_executable(remniw-llc ${CMAKE_CURRENT_SOURCE_DIR}/remniw-llc.cpp
                          ${CMAKE_CURRENT_SOURCE_DIR}/ASMCodeGenerator.cpp
                          ${CMAKE_CURRENT_SOURCE_DIR}/AsmInstruction.cpp)
add_dependencies(remniw-llc brg)
target_link_libraries(remniw-llc PRIVATE ${llvm_libs})