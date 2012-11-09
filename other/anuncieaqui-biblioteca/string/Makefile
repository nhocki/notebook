FILES = .karkkainen.cpp.hash .morris_pratt.cpp.hash .aho_corasick.cpp.hash .manacher.cpp.hash .aho_corasick_2.cpp.hash

all: $(FILES)

.PHONY: clean

$(FILES): .%.hash: %
	../gen_hash.sh $< $@

clean:
	rm -f $(FILES)
