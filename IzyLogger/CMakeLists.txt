add_executable (IzyLogger  "IzyLogger.hpp" "IzyLogger.ixx" "Main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET IzyLogger PROPERTY CXX_STANDARD 20)
endif()