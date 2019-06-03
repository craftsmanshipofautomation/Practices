PKG_CONFIG := pkg-config

define MKDIR?
	$(shell mkdir -p $1)
endef

OUTDIR := out
$(call MKDIR?, ${OUTDIR})
PROJECTDIR := $(shell pwd)
LIBOUTDIR := ${PROJECTDIR}/out/lib
$(call MKDIR?, ${LIBOUTDIR})
LIBSRCDIR := lib

# E denotes sources that use lib and mostly are executables
# S denotes the otherwise which are mostly sub project
EDIRS := leetcode test interview
SDIRS := take-away
EDIRS := $(addsuffix /,${EDIRS})
SDIRS := $(addsuffix /,${SDIRS})
EOUTDIRS := $(addprefix ${OUTDIR}/,${EDIRS})
SOUTDIRS := $(addprefix ${OUTDIR}/,${SDIRS})
$(foreach d,${EOUTDIRS},$(call MKDIR?,${d}))
$(foreach d,${SOUTDIRS},$(call MKDIR?,${d}))

CFLAGS := -std=c11
CXXFLAGS := -std=c++11
CPPFLAGS := -Wall -g -fsanitize=address -fpic
INCLUDEFLAGS := -I${LIBSRCDIR}
LOADFLAGS := -L${LIBOUTDIR}
RPATH := -Wl,-rpath=${LIBOUTDIR}
LIBFLAGS := -shared
LINKFLAGSC := -lpthread -lm
LINKFLAGSCXX := -lgtest -lpthread

# must defer assignment to prevent expansion of automatic variables
DEPFLAGS = -MT $$@ -MMD -MP -MF ${OUTDIR}/$$*.Td
POSTCOMPILE = @mv -f ${OUTDIR}/$$*.Td ${OUTDIR}/$$*.d && touch $$@ # touch to update

COMPILE.BASE.C = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS)
COMPILE.BASE.CXX = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) 
# only objects has to do with *.d
COMPILE.OBJ.C =       ${COMPILE.BASE.C}   -c $$<       -o $$@
COMPILE.OBJ.CXX =     ${COMPILE.BASE.CXX} -c $$<       -o $$@
COMPILE.SO.C =        ${COMPILE.BASE.C}   ${LIBFLAGS}  -o $$@  $$^
COMPILE.SO.CXX =      ${COMPILE.BASE.CXX} ${LIBFLAGS}  -o $$@  $$^
COMPILE.EXE.C =       ${COMPILE.BASE.C}   ${INCLUDEFLAGS} ${LOADFLAGS} -o $$@  $$< ${RPATH} ${LINKFLAGSC}   -l_c   
COMPILE.EXE.CXX =     ${COMPILE.BASE.CXX} ${INCLUDEFLAGS} ${LOADFLAGS} -o $$@  $$< ${RPATH} ${LINKFLAGSCXX} -l_cxx 

LIBSRCDIR := lib
LIBCXXSRC := $(wildcard ${LIBSRCDIR}/*.cpp)
LIBCSRC := $(wildcard ${LIBSRCDIR}/*.c)

LIBCXX := ${LIBOUTDIR}/lib_cxx.so
LIBC := ${LIBOUTDIR}/lib_c.so

ECXXSRC := $(wildcard $(addsuffix *.cpp, ${EDIRS})) $(wildcard *.cpp)
ECSRC := $(wildcard $(addsuffix *.c, ${EDIRS})) $(wildcard *.c)

CPPEXT :=.cpp
CEXT :=.c
OBJEXT :=.o
SOEXT :=.so
SPACE := 

# $(call DECLARE,group,source-ext,name)
define DECLARE
${3}OBJS=$${${1}:%${2}=${OUTDIR}/%.o}
${3}EXTLESS=$${${1}:%${2}=${OUTDIR}/%}
${3}DEP=$${${1}:%${2}=${OUTDIR}/%.d}
endef

$(eval $(call DECLARE,LIBCXXSRC,${CPPEXT},LIBCXX))
$(eval $(call DECLARE,LIBCSRC,${CEXT},LIBC))
$(eval $(call DECLARE,ECXXSRC,${CPPEXT},ECXX))
$(eval $(call DECLARE,ECSRC,${CEXT},EC))

ECXX := ${ECXXEXTLESS}
EC := ${ECEXTLESS}

define MAKETARGETS
${1}: ${OUTDIR}/%${2}: %${3} ${OUTDIR}/%.d
	${4}
	${POSTCOMPILE}	
endef

define  MAKELIBRARY
${1}: %${2}: ${3}
	${4}
endef

all: ${LIBCXX} ${LIBC} ${ECXX} ${EC}

# LIBRARIES
$(eval $(call MAKELIBRARY,${LIBCXX},${SOEXT},${LIBCXXOBJS},${COMPILE.SO.CXX}))
$(eval $(call MAKELIBRARY,${LIBC},${SOEXT},${LIBCOBJS},${COMPILE.SO.C}))

# LIBRARY OBJECTS
$(eval $(call MAKETARGETS,${LIBCXXOBJS},${OBJEXT},${CPPEXT},${COMPILE.OBJ.CXX}))
$(eval $(call MAKETARGETS,${LIBCOBJS},${OBJEXT},${CEXT},${COMPILE.OBJ.C}))

# EXECUTABLE
$(eval $(call MAKETARGETS,${ECXX},${SPACE},${CPPEXT},${COMPILE.EXE.CXX}))
$(eval $(call MAKETARGETS,${EC},${SPACE},${CEXT},${COMPILE.EXE.C}))

# DEPENDENCIES

ifneq "${MAKECMDGOALS}" "clean"
-include ${ECXXDEP} ${ECDEP} ${LIBCXXDEP} ${LIBCDEP}
endif

# SUB PROJECTS 

%.d: ;

.PRECIOUS: ${ECXXDEP} ${ECDEP} ${ECXXOBJS} ${ECOBJS} \
			${LIBCXXDEP} ${LIBCDEP} ${LIBCXXOBJS} ${LIBCOBJS}

.PHONY: config clean run
config:
	@cd leetcode && /usr/bin/python3.6 generate.py

clean:
	@rm out -rf

run: out/${x}
	@make --silent && out/${x}