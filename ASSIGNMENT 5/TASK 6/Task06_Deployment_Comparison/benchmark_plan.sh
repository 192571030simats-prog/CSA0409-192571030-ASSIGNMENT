#!/usr/bin/env bash
set -euo pipefail
echo "Deployment benchmark plan"
echo "1. Record cold start time with /usr/bin/time."
echo "2. Record memory with ps -o rss= -p PID and docker stats."
echo "3. Measure HTTP throughput with: hey -n 10000 -c 50 http://127.0.0.1:8000/"
echo "4. Repeat at least 3 times and report median and p95 latency."
echo "5. Use the same application version and equivalent CPU/memory limits."
