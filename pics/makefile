.PHONY: pics clean

psfiles := $(patsubst %.mp,%.1,$(wildcard *.mp))

pics: $(psfiles)

%.1: %.mp
	mpost $<

clean:
	rm -f *.log *.mpx manual-figure*.dpth manual-figure*.pdf