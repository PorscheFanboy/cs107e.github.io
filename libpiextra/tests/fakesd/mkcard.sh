#!/bin/bash
hdiutil create -format UDTO -size 5g card -fs FAT32 -layout MBRSPUD -srcfolder "$(git rev-parse --show-toplevel)/../cs107e.github.io"
mv card.cdr card.img
