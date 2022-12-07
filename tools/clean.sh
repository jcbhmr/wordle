#!/bin/bash -e
rm -rf .xmake build
for PKGDIR in pkgs/*/; do
  pushd "$PKGDIR"
  rm -rf .xmake build
  popd
done
