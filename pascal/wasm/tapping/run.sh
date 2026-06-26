#!/bin/sh
# Build and serve the current directory on port 9000 for browser testing.
set -e

# Build first — if this fails, run.sh aborts too (set -e)
./build.sh

echo "→ http://localhost:9000"
python3 -m http.server 9000
