#!/bin/bash

OUTPUT="pdb"

gcc src/*.c -Iinclude -o $OUTPUT

echo "Compilation & Build completed → ./$OUTPUT"