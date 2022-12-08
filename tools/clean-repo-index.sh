#!/bin/bash -e

for PACKAGEDIR in packages/*/; do
  pushd "$PACKAGEDIR"
  rm -vrf build/packages
  popd
done
rm -vrf build/packages
