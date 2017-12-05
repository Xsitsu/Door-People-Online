#!/bin/sh
set -e

cd ./Util/
make -f Makefile $1

cd ../Network/
make -f Makefile $1

cd ../GameCore/
make -f Makefile $1

cd ../Server/
make -f Makefile $1

:
