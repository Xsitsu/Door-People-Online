#!/bin/sh

script_dir="$(dirname -- "$(readlink -f -- "$0")")"
build_dir="$script_dir"/cmake-build

mkdir -p _dependency-cache

cmake -B "$build_dir" -S "$script_dir"

cmake --build "$build_dir" --target freetype

#cmake --build "$build_dir" --target server
#cmake --build "$build_dir" --target client


read var1
