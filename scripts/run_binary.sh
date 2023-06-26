#!/bin/bash

# Set the path to the binary and library
binary_path="./BackToTheFuture"
library_path="libzip.so"

# Check if the binary and library files exist
if [ ! -f "$binary_path" ]; then
  echo "Binary file not found: $binary_path"
  exit 1
fi

if [ ! -f "$library_path" ]; then
  echo "Library file not found: $library_path"
  exit 1
fi

# Set the library search path
export LD_LIBRARY_PATH="$(pwd)"


# Run the binary with the library
"$binary_path"

# Unset the library search path
unset LD_LIBRARY_PATH
