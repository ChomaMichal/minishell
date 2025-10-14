#!/bin/bash
set -e

expected=$(mktemp)
my=$(mktemp)

cd ..
make test > /dev/null

echo "pwd" | bash > $expected
echo "pwd" | ./test  > $my
diff -u expected my

echo "pwd PASSED"
