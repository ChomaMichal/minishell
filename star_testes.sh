#!/run/current-system/sw/bin/bash

./sta "*.c" > tmp1
ls *.c > tmp2
diff tmp1 tmp2
rm tmp1 tmp2

