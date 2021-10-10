add_executable(llc-olive)

target_sources(
    llc-olive PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/rwir.cpp)

target_link_libraries(llc-olive PRIVATE ${llvm_libs})