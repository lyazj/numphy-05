#!/usr/bin/env -S make -f

include ../Makefile.conf

# CFLAGS := $(subst -O3,-Og,$(CFLAGS))
RUN += plot
OUT += diff*.pdf

include ../Makefile.rule

plot.run: diff.out
