
# ${mock_support_FOUND}       : right get
# ${mock_support_INCLUDE_DIR} : include
# ${mock_support_LIBRARIES}   : lib
# ${mock_support_LINK_TARGET} : link target

set(mock_support "mock_support")
set(${mock_support}_FOUND "1")
set(${mock_support}_INCLUDE_DIR   "${CMAKE_PREFIX_PATH}/include")
set(${mock_support}_LIBRARIES     "${CMAKE_PREFIX_PATH}/lib")
set(${mock_support}_LINK_TARGET   "mock_support")


