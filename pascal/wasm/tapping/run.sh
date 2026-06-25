#!/bin/sh
# Serve the current directory on port 9000 for browser testing.
set -e

echo "→ http://localhost:9000"
python3 -m http.server 9000
