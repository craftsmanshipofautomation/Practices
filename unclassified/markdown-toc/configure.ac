# perform essential initialization for the generated configure script
AC_INIT([toc], [0.1.0])
AC_CONFIG_SRCDIR([src/toc.cpp])
AM_INIT_AUTOMAKE

AC_SUBST(INTI_CFLAGS)
AC_SUBST(INTI_LIBS)

# checks for the C++ compiler and sets the variables CXX, GXX and CXXFLAGS.
AC_PROG_CXX

#must be called at the end of configure.in to create the Makefiles.
AC_OUTPUT(Makefile src/Makefile)