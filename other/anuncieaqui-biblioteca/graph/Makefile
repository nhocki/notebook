FILES = .busacker_gowen.cpp.hash .dinic.cpp.hash .gabow.cpp.hash .scc.cpp.hash .link_cut.cpp.hash .gomory_hu.cpp.hash .heavy_light.cpp.hash .kuhn_munkres.cpp.hash

all: $(FILES)

.PHONY: clean

$(FILES): .%.hash: %
	../gen_hash.sh $< $@

clean:
	rm -f $(FILES)
