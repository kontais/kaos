#!/bin/bash
set -e
. ./headers.sh

mkdir -p "$SYSROOT/boot/"


for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE)
done
