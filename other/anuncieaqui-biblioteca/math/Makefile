FILES = .crt.cpp.hash .frac.cpp.hash .lis.cpp.hash .simplex.cpp.hash .romberg.cpp.hash .polynomials.cpp.hash .floyd.cpp.hash .pollard.cpp.hash .miller_rabin.cpp.hash .karatsuba.cpp.hash .sieve.cpp.hash .fft.cpp.hash

all: $(FILES)

.PHONY: clean

$(FILES): .%.hash: %
	../gen_hash.sh $< $@

clean:
	rm -f $(FILES)
