#!/bin/bash -e

mkdir -vp build
builddir="$(realpath -s build)"
for packagedir in packages/*/; do (
  cd "$packagedir"
  xmake package -P . -o "$builddir"
); done
