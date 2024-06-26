# Copyright (C) 2021 Morten Jagd Christensen, LICENSE: BSD2
# 

include Makefile.macros



# User only needs to edit below
MODULES = alu
UNITS = 
# User only needs to edit above

TARGETS = $(addsuffix Test, $(addprefix bin/, $(UNITS))) $(addsuffix Test, $(addprefix bin/, $(MODULES)))

vpath %.sv src/modules src/units src/packages

all: directories $(TARGETS)

# Create dependencies using macros
# main targets
$(foreach module, $(MODULES), $(eval $(call make_bintargets,$(module))))
$(foreach unit, $(UNITS), $(eval $(call make_bintargets,$(unit))))
# dependencies
$(foreach module, $(MODULES), $(eval $(call make_mktargets,$(module),modules)))
$(foreach unit, $(UNITS), $(eval $(call make_mktargets,$(unit),units,$(UNITS.$(unit)))))


#
runtest: all $(TARGETS)
	@for test in $(TARGETS); do ./$$test || exit 1; done

coverage: runtest
	verilator_coverage --annotate logs/annotate --annotate-all --annotate-min 1 -write-info logs/merged.info logs/alu.dat

genhtml: coverage
	genhtml logs/merged.info --output-directory logs/html

gtest:
	@./scripts/makegtest

# make sure build directory is created
.PHONY: directories
#
directories: build

build:
	@mkdir -p build bin


format:
	@git diff -U0 HEAD^ ../computer/ | clang-format-16

# Misc clean targets
clean:
	@rm -fr build *.bak bin logs

realclean: clean
	@rm -fr googletest db output_files simulation
