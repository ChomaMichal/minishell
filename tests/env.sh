#!/bin/bash
set -e

expected=$(mktemp)
my=$(mktemp)

cd ..
make test > /dev/null

echo "env" | bash > $expected
echo "env" | ./test  > $my
diff -u $expected $my

echo "env PASSED"
