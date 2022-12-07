#!/bin/bash -e
for PKGDIR in pkgs/*/; do
  pushd "$PKGDIR"
  xmake -P .
  popd
done
