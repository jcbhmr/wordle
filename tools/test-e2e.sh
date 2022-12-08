#!/bin/bash -e

tools/gen-repo-index.sh
xmake
mkdir -vp test/__snapshot__
asciinema rec --overwrite -c 'xmake r' -i 5 test/__snapshot__/e2e.json
agg test/__snapshot__/e2e.json test/__snapshot__/e2e.gif
