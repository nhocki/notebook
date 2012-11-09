biblioteca.pdf:
	pdflatex biblioteca.tex
	pdflatex biblioteca.tex

docs.pt_BR.pdf:
	pdflatex docs.pt_BR.tex

.PHONY: clean biblioteca.pdf

clean:
	rm -f biblioteca.pdf biblioteca.log biblioteca.aux biblioteca.toc \
	   docs.pt_BR.pdf docs.pt_BR.log docs.pt_BR.aux docs.pt_BR.toc
