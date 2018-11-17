AC_PREREQ([2.50])
AC_INIT(nimuh, 1.0)
AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE()
AC_PROG_CXX

dnl Check for SDL

SDL_VERSION=1.2.0
AM_PATH_SDL($SDL_VERSION,
    :,
    AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)

AC_CHECK_LIB(SDL_image, IMG_Load,,
             AC_MSG_ERROR([*** SDL_image not found!])
             )
AC_CHECK_LIB(SDL_mixer, Mix_OpenAudio,,
             AC_MSG_ERROR([*** SDL_mixer not found!])
             )

AC_CHECK_HEADERS([GL/gl.h GL/glu.h], [], [])
AC_CHECK_HEADER(expat.h,, [AC_MSG_ERROR([C compiler can't find <expat.h>])])






AM_CXXFLAGS="$AM_CFLAGS $SDL_CFLAGS"
AM_LDFLAGS="$AM_LDFLAGS $SDL_LIBS -lSDL_mixer -lSDL_image -lexpat -lGL -lGLU"

dnl LIBS="$LIBS $SDL_LIBS -lSDL_image -lSDL_mixer"
dnl CXXFLAGS="$CXXFLAGS $SDL_CXXFLAGS"

AC_SUBST(AM_CXXFLAGS)
AC_SUBST(AM_LDFLAGS)

AC_OUTPUT([
Makefile
src/Makefile
])
