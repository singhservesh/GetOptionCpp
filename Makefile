MK_DEFS_FILE := config
MK_DEFS_FILE_DEP := config.d
TMP := $(shell echo $(MK_DEFS_FILE).$$$$)
PWD := $(shell pwd)

WRK_AREA :=$(shell cd ..; pwd)
DEP_AREA :=$(WRK_AREA)/pf_ob

LIB_AREA :=$(strip $(DEP_AREA)/lib)
OBJ_AREA :=$(strip $(DEP_AREA)/obj)
SRC_DEP_AREA :=$(strip $(DEP_AREA)/dep)

MOVE := @mv
ECHO := @echo

SUBDIRS := src example 
all:$(MK_DEFS_FILE)
	@for n in $(SUBDIRS); do \
        make -s -C$${n} $(@);\
        done
	
$(MK_DEFS_FILE):$(MK_DEFS_FILE_DEP)

$(MK_DEFS_FILE_DEP): Makefile
	@set -e
	$(ECHO) "+ Started generating definition file: $(MK_DEFS_FILE)"
	$(ECHO) "" >> $(TMP)
	$(ECHO) "#----- THIS FILE IS GENERATED FROM [ $< ]. DO NOT SUBMIT ON REPOSITORY." > $(TMP)
	$(ECHO) "" >> $(TMP)
	$(ECHO) "WRK_AREA     :=$(WRK_AREA)" >> $(TMP)
	$(ECHO) "DEP_AREA     :=$(DEP_AREA)" >> $(TMP)
	$(ECHO) "LIB_AREA     :=$(LIB_AREA)" >> $(TMP)
	$(ECHO) "OBJ_AREA     :=$(OBJ_AREA)" >> $(TMP)
	$(ECHO) "SRC_DEP_AREA :=$(SRC_DEP_AREA)" >> $(TMP)
	@touch $(MK_DEFS_FILE_DEP)
	$(MOVE)  $(TMP) $(MK_DEFS_FILE)
	$(ECHO) "+ Finished generating definition file: $(MK_DEFS_FILE)"

clear:clean;
clean:
	@for n in $(SUBDIRS); do \
        make -s -C$${n} $(@);\
        done
	rm -rf  $(MK_DEFS_FILE_DEP);
	rm -fr $(DEP_AREA);
	@rm -rf $(MK_DEFS_FILE);

