#!/bin/sh
set -eu
gcc -std=c11 -Wall -Wextra -O2 ../Task06/copy_file.c -o copy_file
gcc -std=c11 -Wall -Wextra ../Task07/process_control.c -o process_control
echo '=== copy output ==='; ./copy_file
if command -v strace >/dev/null 2>&1; then echo '=== strace summary ==='; strace -c ./copy_file; else echo 'strace not installed'; fi
echo '=== process timing ==='; /usr/bin/time -v ./process_control
