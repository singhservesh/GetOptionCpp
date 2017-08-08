ifneq ($(MAKECMDGOALS),clean)
include ../config
endif


EXTENSION := $(shell which gcc)

WRK_AREA     :=$(strip $(WRK_AREA))
DEP_AREA     :=$(strip $(DEP_AREA))
LIB_AREA     :=$(strip $(LIB_AREA))
OBJ_AREA     :=$(strip $(OBJ_AREA))
SRC_DEP_AREA :=$(strip $(SRC_DEP_AREA))

PWD  := $(strip $(shell pwd))
REL_DEP_PATH := $(subst $(WRK_AREA),,$(PWD))
KEY  := $(strip getopt)

BIN      :=
DEP_PATH :=$(SRC_DEP_AREA)/$(KEY)
LIB_PATH :=$(LIB_AREA)
LIBNAME  :=$(LIB_AREA)/lib$(KEY).a
OBJ_PATH :=$(OBJ_AREA)/$(KEY)

#utilities
#FLAG   :=-MD -g -W -Wall -Wno-parentheses  -DYYERROR_VERBOSE
FLAG    :=-MD -O3 -W -Wall -Wno-parentheses  -DYYERROR_VERBOSE
AR      := @ar
ARFLAGS := -rv
RANLIB  := ranlib
RM      := @rm -f
DATE     := date "+%m/%d/%y %H.%M.%S"

#GCC    :=g++
ECHO := @echo
ATOMIC := @set -e
LIBFLAG :=-L$(LIB_PATH)
LIBLIST :=

#STATIC_STDCPP_LIB :=$(shell $(CXX) -print-file-name=libstdc++.a)

STATIC_STDCPP_LIB := -lstdc++

CPPSOURCES := GetOptCpp.C
OBJECTS := $(CPPSOURCES:%.C=$(OBJ_PATH)/%.o)


all:$(LIBNAME)
$(LIBNAME): Makefile $(OBJECTS)
	$(ATOMIC)
	$(ECHO) "+ building librry $(LIBNAME) ."
	@mkdir -p $(LIB_PATH)
	$(RM) $(LIBNAME)
	@$(AR) $(ARFLAGS) $(LIBNAME) $(OBJECTS)
	$(RANLIB) $(LIBNAME)
	$(ECHO) "+   "
	$(ECHO) "+  (`$(DATE)`) lib $@ done."
	$(ECHO) "+   "

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPFILES)
endif

$(OBJ_PATH)/%.o:%.C
	$(ECHO) "+ building objects for  $(LIBNAME)"
	@mkdir -p $(DEP_PATH)
	@mkdir -p $(OBJ_PATH)
	$(CXX) $(FLAG) -MF $(DEP_PATH)/$*.d $(CFLAG) -c  $<  -o  $@
	$(ECHO) "+  "
	$(ECHO) "+  (`$(DATE)` Building $(*F) done."
	$(ECHO) "+  "


$(DEP_PATH)/%.d:Makefile
	$(ATOMIC)
	@mkdir -p $(DEP_PATH)
	@mkdir -p $(OBJ_PATH)
	$(CXX) $(FLAG) -MF $@ $(CFLAG) -c $(*F).C -o $(OBJ_PATH)/$(*F).o
	$(ECHO) ""
tags:
	ctags --extra=+f $(CPPSOURCES) $(CPPSOURCES:.C=.H)

clean clear:
	@for n in $(SUBDIRS); do \
	make -C$${n} $(@);\
	done


Makefile:  ;

