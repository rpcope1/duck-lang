cmake_minimum_required(VERSION 2.8)

include(FindSDL)
include(FindOpenGL)

# duck
add_executable(duck
  ../duck/main.c
  ../duck/interpreter.c
  ../duck/lexer.c
  ../duck/parser.c
  ../duck/grammar.c
  ../duck/duck.c
  ../duck/tables.c
  ../duck/memory.c
  ../duck/lib/library.c
  ../duck/lib/stdduck.c
  ../duck/lib/dmath.c
  ../duck/lib/drand.c
)

# gduck
add_executable(gduck
  ../duck/main.c
  ../duck/interpreter.c
  ../duck/lexer.c
  ../duck/parser.c
  ../duck/grammar.c
  ../duck/duck.c
  ../duck/tables.c
  ../duck/memory.c
  ../duck/lib/library.c
  ../duck/lib/stdduck.c
  ../duck/lib/SDLlib.c
  ../duck/lib/dmath.c
  ../duck/lib/drand.c
)

include_directories(../duck)

SET_TARGET_PROPERTIES(duck PROPERTIES COMPILE_FLAGS "-O2")
TARGET_LINK_LIBRARIES(duck -lm)
SET_TARGET_PROPERTIES(gduck PROPERTIES COMPILE_FLAGS "-D_GDUCK -D_LIB_SDL")
TARGET_LINK_LIBRARIES(gduck ${SDL_LIBRARY} ${OPENGL_LIBRARY} -lm)
