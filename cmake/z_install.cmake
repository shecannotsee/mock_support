
########################################################################################################################
# Install module                                                                                                       #
########################################################################################################################

# local debug
set(CMAKE_INSTALL_PREFIX "./")
# Release Code
# set(CMAKE_INSTALL_PREFIX "/")

message(STATUS "The default installation path is ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Please use \"make install DESTDIR=./PATH\" to set install path")

# test install
install(TARGETS
    ${test_name} DESTINATION ${PROJECT_NAME}/bin
    )

if (generate_lib STREQUAL "ON")
    # include install
    install(FILES
            ${CMAKE_SOURCE_DIR}/src/cpp-stub/stub.h
            ${CMAKE_SOURCE_DIR}/src/cpp-stub/addr_any.h
            ${CMAKE_SOURCE_DIR}/src/cpp-stub/addr_pri.h
            DESTINATION ${PROJECT_NAME}/include/cpp-stub
        )
    install(FILES
            ${CMAKE_SOURCE_DIR}/src/class_support.h
            ${CMAKE_SOURCE_DIR}/src/mock_thread.h
            ${CMAKE_SOURCE_DIR}/src/std_mutex_support.h
            ${CMAKE_SOURCE_DIR}/src/std_thread_support.h
            DESTINATION ${PROJECT_NAME}/include/
    )
    # lib install
    install(TARGETS
        ${library_static_name} ${library_dynamic_name}
        DESTINATION ${PROJECT_NAME}/lib
        )
    # cmake install
    install(FILES
            ${CMAKE_SOURCE_DIR}/cmake/${project_name}-config.cmake
            DESTINATION ${PROJECT_NAME}/cmake
            )
endif ()


