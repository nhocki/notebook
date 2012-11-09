#!/bin/sh

test_cpp() {
  echo "Testando "$1"..."
  if (g++ -o $1.bin $1.cpp -Wall -pedantic -lm -g) then
    if (./$1.bin < $1.in > $1.out) then
      diff -u $1.out $1.sol
      rm -f $1.out
      rm -f $1.bin
      echo $1": OK!"
    else
      echo $1": Programa não roda corretamente!"
    fi
  else
    echo $1": Erro de compilação!"
  fi
}

for i in *.cpp; do
  test_cpp `basename $i .cpp`
  echo
done

