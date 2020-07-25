project(Logger)

set(SOURCES Sources/Logger.cpp)
set(HEADERS Logger.hpp)

add_library(Logger ${SOURCES} ${HEADERS})
target_link_libraries(Logger boost_date_time)
target_include_directories(Logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})