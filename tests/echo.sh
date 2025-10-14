#!/bin/bash
set -e

expected=$(mktemp)
my=$(mktemp)

echo "echo PASSED"
cd ..
make test > /dev/null

txt="helloworld"
echo "echo $txt" | bash > $expected
echo "echo $txt" | ./test  | grep  -v "<>minishell<>" > $my
diff -u $expected $my
echo "echo PASSED"

echo "echo -n $txt" | bash > $expected
echo "echo -n $txt" | ./test  | grep  -v "<>minishell<>" > $my
diff -u $expected $my
echo "echo PASSED"

txt="hello world"
echo "echo $txt" | bash > $expected
echo "echo $txt" | ./test  | grep  -v "<>minishell<>" > $my
diff -u $expected $my
echo "echo PASSED"

echo "echo -n $txt" | bash > $expected
echo "echo -n $txt" | ./test  | grep  -v "<>minishell<>" > $my
diff -u $expected $my
echo "echo PASSED"

