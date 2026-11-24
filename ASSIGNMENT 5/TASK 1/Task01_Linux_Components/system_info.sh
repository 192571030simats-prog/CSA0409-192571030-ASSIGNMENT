#!/usr/bin/env bash
set -euo pipefail
echo "Linux system overview"
uname -a
echo
echo "Distribution:"
if [ -r /etc/os-release ]; then . /etc/os-release; echo "${PRETTY_NAME:-unknown}"; fi
echo
echo "CPU and memory:"
grep -m1 'model name' /proc/cpuinfo || true
free -h
echo
echo "Root filesystem:"
df -h /
