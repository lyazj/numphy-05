#!/usr/bin/env -S make -f

include ../Makefile.conf

# CFLAGS := $(subst -O3,-Og,$(CFLAGS))
RUN += plot
OUT += rand.pdf chi2.pdf

include ../Makefile.rule

plot.run: rand.out

rand.run:
	./rand 1670725183 > rand.out 2> rand.log & tail -f rand.log --pid=$$!
