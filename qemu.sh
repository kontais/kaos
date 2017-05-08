#!/bin/bash
set -e
. ./iso.sh

#qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom myos.iso -curses
DISPLAY=:0 qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom myos.iso -monitor stdio
