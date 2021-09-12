# Call macro to add lexer and grammar to your build dependencies.
antlr_target(RemniwGrammar ${CMAKE_SOURCE_DIR}/grammar/Remniw.g4 LEXER PARSER VISITOR)

# include generated files in project environment
include_directories(${ANTLR_RemniwGrammar_OUTPUT_DIR})

# compiler binary target
add_executable(remniw ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${ANTLR_RemniwGrammar_CXX_OUTPUTS})

# Build the phase specific libraries
add_subdirectory(frontend)
add_subdirectory(semantic)
add_subdirectory(codegen)
add_subdirectory(optimizer)

target_link_libraries(
  remniw
  PRIVATE frontend
          semantic
          codegen
#          optimizer
          antlr4_static
          ${llvm_libs})
target_include_directories(
  remniw
  PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/frontend
           ${CMAKE_CURRENT_SOURCE_DIR}/semantic
           ${CMAKE_CURRENT_SOURCE_DIR}/codegen
           ${CMAKE_CURRENT_SOURCE_DIR}/optimizer
${ANTLR_RemniwGrammar_OUTPUT_DIR}
)