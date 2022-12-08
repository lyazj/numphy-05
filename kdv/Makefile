#!/usr/bin/env -S make -f

include ../Makefile.conf

# CFLAGS := $(subst -O3,-Og,$(CFLAGS))
BIN := $(filter-out kdv,$(BIN))
RUN += kz-plot merge
OUT += kz-plot-*.pdf kz-plot.pdf

include ../Makefile.rule

$(OBJ): defs.h
kz: kdv.o
kz-plot.run: kz.c kz.out
merge.run: kz-plot-0.pdf

kz-plot-0.pdf: kz-plot
	$(MAKE) kz-plot.run
