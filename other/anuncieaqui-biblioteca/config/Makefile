FILES = .dotemacs.hash .hashgen.hash .template.cpp.hash .dotvimrc.hash .flymake.mk.hash

all: $(FILES)

.PHONY: clean

$(FILES): .%.hash: %
	../gen_hash.sh $< $@

clean:
	rm -f $(FILES)
