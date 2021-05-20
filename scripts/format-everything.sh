#!/bin/bash

ROOT_DIR=$(dirname "$(dirname "$0")")

find "${ROOT_DIR}/src/" -iname "*.h" -o -iname "*.cpp" -o -iname "*.c" | xargs clang-format -i
find "${ROOT_DIR}/include/ciglagl/" -iname "*.h" -o -iname "*.cpp" -o -iname "*.c" | xargs clang-format -i