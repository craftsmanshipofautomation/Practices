## 不可维护的编译系统

PKG_CONFIG := pkg-config

define MKDIR?
	$(shell mkdir -p $1)
endef

## 所有二进制都在 out 目录
OUT_DIR := out
## 创建目录
$(call MKDIR?, ${OUT_DIR})
## 项目目录
PROJECT_DIR := $(shell pwd)
## 动态库输出目录
LIB_OUT_DIR := ${PROJECT_DIR}/out/lib
## 创建目录
$(call MKDIR?, ${LIB_OUT_DIR})
## 动态库源码
LIB_SRC_DIR := lib

## E 表示使用动态库的代码目录
## S 表示独立的 sub project
E_DIRS := test
S_DIRS := trade
## 加上后缀
E_DIRS := $(addsuffix /,${E_DIRS})
S_DIRS := $(addsuffix /,${S_DIRS})
## 输出目录
E_OUT_DIRS := $(addprefix ${OUT_DIR}/,${E_DIRS})
S_OUT_DIRS := $(addprefix ${OUT_DIR}/,${S_DIRS})
## 创建这些目录
$(foreach d,${E_OUT_DIRS},$(call MKDIR?,${d}))
$(foreach d,${S_OUT_DIRS},$(call MKDIR?,${d}))

# -std=c11 is harmful
CFLAGS := -m64
CXXFLAGS := -std=c++17
CPPFLAGS := -Wall -g -fsanitize=address -fpic -O0
# -fsanitize=address will generate extra checking code
INCLUDEFLAGS := -I${LIB_SRC_DIR}
LOADFLAGS := -L${LIB_OUT_DIR}
RPATH := -Wl,-rpath=${LIB_OUT_DIR}
LIBFLAGS := -shared
LINKFLAGSC := -lpthread -lm
LINKFLAGSCXX := -lgtest -lpthread

## automation 变量需要转义
## 构建依赖
DEP_FLAGS = -MT $$@ -MMD -MP -MF ${OUT_DIR}/$$*.Td
## 编译之后，将 .Td 文件重命名为 .d, 并更新目标的时间戳
POSTCOMPILE = @mv -f ${OUT_DIR}/$$*.Td ${OUT_DIR}/$$*.d && touch $$@ # touch to update

## 指定编译器
COMPILE.BASE.C = $(CC) $(DEP_FLAGS) $(CFLAGS) $(CPPFLAGS)
COMPILE.BASE.CXX = $(CXX) $(DEP_FLAGS) $(CXXFLAGS) $(CPPFLAGS) 
COMPILE.OBJ.C =       ${COMPILE.BASE.C}   -c $$<       -o $$@
COMPILE.OBJ.CXX =     ${COMPILE.BASE.CXX} -c $$<       -o $$@
COMPILE.SO.C =        ${COMPILE.BASE.C}   ${LIBFLAGS}  -o $$@  $$^
COMPILE.SO.CXX =      ${COMPILE.BASE.CXX} ${LIBFLAGS}  -o $$@  $$^
COMPILE.EXE.C =       ${COMPILE.BASE.C}   ${INCLUDEFLAGS} ${LOADFLAGS} -o $$@  $$< ${RPATH} -l_c   ${LINKFLAGSC}      
COMPILE.EXE.CXX =     ${COMPILE.BASE.CXX} ${INCLUDEFLAGS} ${LOADFLAGS} -o $$@  $$< ${RPATH} -l_cxx ${LINKFLAGSCXX}  

## .cpp 编译 libcxx.so
LIBCXX_SRC := $(wildcard ${LIB_SRC_DIR}/*.cpp)
## .c 编译 libc.so
LIBC_SRC := $(wildcard ${LIB_SRC_DIR}/*.c)

LIBCXX := ${LIB_OUT_DIR}/lib_cxx.so
LIBC := ${LIB_OUT_DIR}/lib_c.so

## 所有源码文件都带有目录前缀, 包括不同目录
ECXX_SRC := $(wildcard $(addsuffix *.cpp, ${E_DIRS}))
EC_SRC := $(wildcard $(addsuffix *.c, ${E_DIRS}))


SPACE := 

## $(call DECLARE,group,source-ext,name)
## 声明：${3} 用来命名： 
define DECLARE
${3}_OBJS=$${${1}:%${2}=${OUT_DIR}/%.o}
${3}_EXTLESS=$${${1}:%${2}=${OUT_DIR}/%}
${3}_DEP=$${${1}:%${2}=${OUT_DIR}/%.d}
endef

$(eval $(call DECLARE,LIBCXX_SRC,.cpp,LIBCXX))
$(eval $(call DECLARE,LIBC_SRC,.c,LIBC))
$(eval $(call DECLARE,ECXX_SRC,.cpp,ECXX))
$(eval $(call DECLARE,EC_SRC,.c,EC))

## 表示不同 E 目录下的执行文件，一个源码文件对应一个执行文件
ECXX := ${ECXX_EXTLESS}
EC := ${EC_EXTLESS}

## 创建文本
### 带目录前缀的可执行文件: 输出目录/%: %.文件类型 依赖
###		编译
###		生成依赖
define MAKE_TARGETS
${1}: ${OUT_DIR}/%${2}: %${3} ${OUT_DIR}/%.d
	${4}
	${POSTCOMPILE}	
endef

## 中间文件: 输出目录/%.中间文件扩展名 : cpp 文件 依赖
##	


## 动态库: %.SO : 中间文件
define  MAKE_LIBRARY
${1}: %${2}: ${3}
	${4}
endef

TEST_DIR := test system
TEST_DATA := $(foreach d,${TEST_DIR},$(wildcard ${d}/*.txt))
TEST_DATA_DEST := $(addprefix ${OUT_DIR}/,${TEST_DATA})

all: ${LIBCXX} ${LIBC} ${ECXX} ${EC} ${TEST_DATA_DEST}

# LIBRARIES
$(eval $(call MAKE_LIBRARY,${LIBCXX},.so,${LIBCXX_OBJS},${COMPILE.SO.CXX}))
$(eval $(call MAKE_LIBRARY,${LIBC},.so,${LIBC_OBJS},${COMPILE.SO.C}))

# LIBRARY OBJECTS
$(eval $(call MAKE_TARGETS,${LIBCXX_OBJS},.o,.cpp,${COMPILE.OBJ.CXX}))
$(eval $(call MAKE_TARGETS,${LIBC_OBJS},.o,.c,${COMPILE.OBJ.C}))

# EXECUTABLE
$(eval $(call MAKE_TARGETS,${ECXX},${SPACE},.cpp,${COMPILE.EXE.CXX}))
$(eval $(call MAKE_TARGETS,${EC},${SPACE},.c,${COMPILE.EXE.C}))

# DEPENDENCIES

ifneq "${MAKECMDGOALS}" "clean"
-include ${ECXX_DEP} ${EC_DEP} ${LIBCXX_DEP} ${LIBC_DEP}
endif

# SUB PROJECTS 

%.d: ;

# TEST DATA
${TEST_DATA_DEST}: ${OUT_DIR}/%.txt: %.txt 
	@cp $^ $@ 

.PRECIOUS: ${ECXX_DEP} ${EC_DEP} ${ECXXOBJS} ${ECOBJS} \
			${LIBCXX_DEP} ${LIBC_DEP} ${LIBCXX_OBJS} ${LIBC_OBJS}

.PHONY: config clean run
config:
	@cd leetcode && /usr/bin/python3.6 generate.py

clean:
	@rm out -rf

run: out/$(basename ${x})
	@make --silent  && cd $(dir $<) && ./$(notdir $<)
