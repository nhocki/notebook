#!/bin/sh

cat *.cpp | egrep '#include *\"\.\.' | sed "s/^ *#include \"\.\.\/\(.*\)\"/\1/"
