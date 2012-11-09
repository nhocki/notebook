FILES = .point.cpp.hash .isect_primitives.cpp.hash .polygon_primitives.cpp.hash .misc_primitives.cpp.hash .hull.cpp.hash .kd_tree.cpp.hash .range_tree.cpp.hash .enclosing_circle.cpp.hash .closest_points.cpp.hash

all: $(FILES)

.PHONY: clean

$(FILES): .%.hash: %
	../gen_hash.sh $< $@

clean:
	rm -f $(FILES)
