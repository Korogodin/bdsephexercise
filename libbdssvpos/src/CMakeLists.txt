if (NOT DEFINED BUILD_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ON)
endif (NOT DEFINED BUILD_SHARED_LIBS)

file(GLOB libbdssvpos_HEADERS "${PROJECT_SOURCE_DIR}/include/libbdssvpos/*.h")

include_directories("${PROJECT_SOURCE_DIR}/include")

set(libbdssvpos_SRCS
    bdssvpos.cpp
    kepler.cpp
)

add_library(bdssvpos-static STATIC ${libbdssvpos_SRCS})
install(TARGETS bdssvpos-static DESTINATION lib${LIB_SUFFIX})

if(BUILD_SHARED_LIBS)
  add_library(bdssvpos SHARED ${libbdssvpos_SRCS})
  install(TARGETS bdssvpos DESTINATION lib${LIB_SUFFIX})
else(BUILD_SHARED_LIBS)
  message(STATUS "Not building shared libraries")
endif(BUILD_SHARED_LIBS)

install(FILES ${libbdssvpos_HEADERS} DESTINATION include)
