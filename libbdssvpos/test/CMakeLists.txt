if (CMAKE_CROSSCOMPILING)
  message(STATUS "Skipping unit tests, cross compiling")
else (CMAKE_CROSSCOMPILING)

  find_package(Check)
  if (NOT CHECK_FOUND)
    message(STATUS "Skipping unit tests, Check library not found!")
  else (NOT CHECK_FOUND)

    include_directories(${CHECK_INCLUDE_DIRS})
    set(TEST_LIBS ${TEST_LIBS} ${CHECK_LIBRARIES} pthread bdssvpos m)

    # Check needs to be linked against Librt on Linux
    if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
      set(TEST_LIBS ${TEST_LIBS} rt)
    endif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

    include_directories("${PROJECT_SOURCE_DIR}/include")

    FILE(GLOB generated_c_sources auto*.c)
    FILE(GLOB check_cpp_sources check_*.cpp)
    add_executable(test_bdssvpos ${check_cpp_sources})

    target_link_libraries(test_bdssvpos ${TEST_LIBS})
    add_custom_command(
      TARGET test_bdssvpos POST_BUILD
      COMMENT "Running unit tests"
      COMMAND test_bdssvpos
    )
  endif (NOT CHECK_FOUND)
endif (CMAKE_CROSSCOMPILING)
