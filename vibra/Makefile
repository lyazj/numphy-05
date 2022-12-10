#!/usr/bin/env -S make -f

include ../Makefile.conf

# CFLAGS := $(subst -O3,-Og,$(CFLAGS))
RUN += plot anim
OUT += vibra*.pdf vibra*.jpg

include ../Makefile.rule

plot.run: vibra.out
anim.run: jpg

jpg:
	$(RM) *.jpg; $(MAKE) $(patsubst %.pdf,%.jpg,$(shell ls vibra-0.17678-?.?????.pdf))

jpg-ref:
	$(RM) *.jpg; $(MAKE) $(patsubst %.pdf,%.jpg,$(shell ls vibra-0.17678-?.?????-ref.pdf))

%.jpg: %.pdf
	pdftoppm -r 300 -jpeg $< ${@:%.jpg=%}
