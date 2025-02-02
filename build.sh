#!/bin/sh

script_dir="$(dirname -- "$(readlink -f -- "$0")")"
build_dir="$script_dir"/cmake-build

mkdir -p _dependency-cache
mkdir -p "$build_dir"

cmake -B "$build_dir" -S "$script_dir" #-G "MinGW Makefiles"

#cd "$build_dir"

#cmake --build "$build_dir" --target freetype

#cmake --build "$build_dir" --target util

cmake --build "$build_dir" --target server
cmake --build "$build_dir" --target client
