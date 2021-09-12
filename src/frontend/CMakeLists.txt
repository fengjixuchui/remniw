# include generated files in project environment
include_directories(${ANTLR_RemniwGrammar_OUTPUT_DIR})

# Define a library for the front end
add_library(frontend)
target_sources(frontend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Type.h
                                ${CMAKE_CURRENT_SOURCE_DIR}/Type.cpp
                                ${CMAKE_CURRENT_SOURCE_DIR}/AST.h
#                                ${CMAKE_CURRENT_SOURCE_DIR}/AST.cpp
                                ${CMAKE_CURRENT_SOURCE_DIR}/ASTBuilder.h
                                ${CMAKE_CURRENT_SOURCE_DIR}/ASTBuilder.cpp
                                ${CMAKE_CURRENT_SOURCE_DIR}/ASTVisitor.h
                                ${CMAKE_CURRENT_SOURCE_DIR}/RecursiveASTVisitor.h
                                ${CMAKE_CURRENT_SOURCE_DIR}/RecursiveASTVisitor.cpp
                                ${CMAKE_CURRENT_SOURCE_DIR}/ASTPrinter.h
)
target_include_directories(frontend PRIVATE ${ANTLR_RemniwGrammar_OUTPUT_DIR})
target_link_libraries(frontend PRIVATE antlr4_static)