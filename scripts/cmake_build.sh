#!/usr/bin/env bash
set -euo pipefail

# Usage help
usage() {
  echo "Usage: $0 <CMAKE_BUILD_TYPE> <MBED_TARGET>"
  echo "  CMAKE_BUILD_TYPE: Debug | Develop | Release"
  exit 2
}

# Read args
CMAKE_BUILD_TYPE="${1:-}"
MBED_TARGET="${2:-}"

# Basic presence checks
[[ -z "${CMAKE_BUILD_TYPE}" ]] && usage

# Validate CMAKE_BUILD_TYPE
case "${CMAKE_BUILD_TYPE}" in
  Debug|Develop|Release)
    ;;
  *)
    echo "Error: Invalid CMAKE_BUILD_TYPE='${CMAKE_BUILD_TYPE}'. Must be one of: Debug, Develop, Release." >&2
    exit 1
    ;;
esac

# Prepare build directory
mkdir -p build
rm -rf build/*
cd build

# Configure and build
cmake .. -GNinja \
  -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}" \
  -DMBED_TARGET=LPC1768

ninja full_binary
