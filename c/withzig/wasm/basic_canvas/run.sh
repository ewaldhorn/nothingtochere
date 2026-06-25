#!/bin/bash
# run.sh — Serve the demo with Python's built-in HTTP server.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

echo "==> Serving on http://localhost:9000"
python3 -m http.server 9000
