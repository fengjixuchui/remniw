add_library(codegen)

target_sources(
    codegen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/CodeGeneratorImpl.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/CodeGeneratorImpl.cpp)

target_include_directories(
    codegen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_SOURCE_DIR}/src/frontend)

target_link_libraries(codegen PRIVATE frontend)