add_contract(oracle oracle ${CMAKE_CURRENT_SOURCE_DIR}/src/oracle.cpp

        )
target_include_directories(oracle
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/external
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

set_target_properties(oracle PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
target_compile_options(oracle PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian)