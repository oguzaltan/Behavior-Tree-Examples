#!/usr/bin/env bash
set -euo pipefail

# build_all.sh - Build all example folders (t*/) using CMake
# Usage: ./build_all.sh [-j JOBS] [-p CMAKE_PREFIX_PATH]

JOBS=$(nproc || echo 1)
PREFIX=""

usage(){
  cat <<EOF
Usage: $0 [-j jobs] [-p cmake_prefix_path]

Options:
  -j jobs                 Number of parallel build jobs (default: detected CPU count)
  -p cmake_prefix_path    Pass this as -DCMAKE_PREFIX_PATH to cmake (useful to locate BehaviorTree.CPP)
  -h                      Show this help
EOF
}

while getopts ":j:p:h" opt; do
  case ${opt} in
    j) JOBS=${OPTARG} ;;
    p) PREFIX=${OPTARG} ;;
    h) usage; exit 0 ;;
    \?) echo "Invalid option: -${OPTARG}" >&2; usage; exit 1 ;;
  esac
done

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
echo "Root: $ROOT_DIR"

# Discover immediate subdirectories that contain a CMakeLists.txt (ignore hidden dirs)
EXAMPLES=()
for dir in "$ROOT_DIR"/*/; do
  [ -d "$dir" ] || continue
  base="$(basename "$dir")"
  # skip hidden/system folders
  [[ "$base" == .* ]] && continue
  if [ -f "$dir/CMakeLists.txt" ]; then
    EXAMPLES+=("$base")
  fi
done

IFS=$'\n' EXAMPLES=( $(printf '%s\n' "${EXAMPLES[@]}" | sort) )

if [ ${#EXAMPLES[@]} -eq 0 ]; then
  echo "No example folders with CMakeLists.txt found in $ROOT_DIR" >&2
  exit 1
fi

for d in "${EXAMPLES[@]}"; do
  SRC_DIR="$ROOT_DIR/$d"
  BUILD_DIR="$SRC_DIR/build"

  echo "\n=== Building $d ==="
  echo "Configuring..."
  if [ -n "$PREFIX" ]; then
    cmake -S "$SRC_DIR" -B "$BUILD_DIR" -DCMAKE_PREFIX_PATH="$PREFIX"
  else
    cmake -S "$SRC_DIR" -B "$BUILD_DIR"
  fi

  echo "Building (jobs=$JOBS)..."
  cmake --build "$BUILD_DIR" --parallel "$JOBS"
  echo "Built $d -> $BUILD_DIR"
done

echo "\nAll done. Executables are in each example's build directory (e.g. <example>/build/bt_simple_pick)."
