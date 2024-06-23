add_executable (RUN "release.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DIM_LANGUAGE PROPERTY CXX_STANDARD 17)
endif()