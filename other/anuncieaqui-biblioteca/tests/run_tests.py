#!/usr/bin/env python

import sys, subprocess, os;

testlist = file('test_list', 'r');

for test in testlist:
  test = test.rstrip('\n');
  sys.stdout.write('Executando teste {0}... '.format(test));
  sys.stdout.flush();

  if subprocess.call(['g++', '-o' + test, test + '.cpp']):
    print 'Erro de compilacao do programa {0}!'.format(test);
    break;

  p = subprocess.Popen('./' + test + ' < ' + test + '.in > ' + test + '.out', shell=True);
  os.waitpid(p.pid, 0);

  if subprocess.call(['diff', '-u', test + '.out', test + '.sol']):
    print 'Erro no teste do programa {0}!'.format(test);
    break;
  print 'OK!'
