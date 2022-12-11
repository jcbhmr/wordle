#!/bin/bash -e

tools/gen-repo-index.sh
xmake
mkdir -vp test/__snapshot__
asciinema rec --overwrite -c 'xmake r' -i 5 --cols 70 --rows 24 test/__snapshot__/e2e.json
agg test/__snapshot__/e2e.json test/__snapshot__/e2e.gif
