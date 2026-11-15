#!/bin/sh
set -eu
gcc -std=c11 -Wall -Wextra -fPIC -shared crypto_demo.c -o libcrypto_demo.so
gcc -std=c11 -Wall -Wextra linking_demo.c crypto_demo.c -o static_demo
gcc -std=c11 -Wall -Wextra linking_demo.c -L. -lcrypto_demo -Wl,-rpath,'$ORIGIN' -o dynamic_demo
gcc -std=c11 -Wall -Wextra linking_demo.c -ldl -o runtime_demo
echo "Built static_demo, dynamic_demo and runtime_demo"
