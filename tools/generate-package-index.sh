#!/bin/bash -e

for PACKAGEDIR in packages/*/; do
  pushd "$PACKAGEDIR"
  rm -vrf build/packages
  xmake package -P .
  mkdir -vp ../../build/packages
  cp -vr build/packages/*/ ../../build/packages/
  popd
done
