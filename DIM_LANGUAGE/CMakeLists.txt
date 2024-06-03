# CMakeList.txt : CMake project for DIM_LANGUAGE, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (DIM_LANGUAGE "Interpreter/interpreter.cpp" "Interpreter/interpreter.h" "Lexer/lexer.cpp" "Lexer/lexer.h" "Parser/parser.cpp" "Parser/parser.h"  "LIBS/standart/standart.h" "Tokens/tokens.h" "Configuration/config.h" "Configuration/config.h"  "Error/error.cpp" "Error/error.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DIM_LANGUAGE PROPERTY CXX_STANDARD 17)
endif()