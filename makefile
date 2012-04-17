.PHONY: all pdf ps pics clean

all: pdf

pdf: manual.pdf 

manualpics := $(patsubst %.mp,%.1,$(wildcard pics/[a-z]*.mp))

manual.pdf: manual.tex $(manualpics)
	pdflatex -shell-escape manual.tex
	pdflatex -shell-escape manual.tex

pics/%.1: pics/%.mp
	make -C pics $(@F)

clean:
	rm -f *.aux
	rm -f *.log
	rm -f *.dvi
	rm -f *.ps
	rm -f *.pdf
	make -C pics clean
