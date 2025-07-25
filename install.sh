#!/usr/bin/env bash

requirement_missing=0

check_tool() {
	if [[ -z "$1" ]]; then
		echo >&2 "$2"
		requirement_missing=1
	fi
}

cmake_exists=$(command -v cmake)
ninja_exists=$(command -v ninja)
make_exists=$(command -v make)
clang_exists=$(command -v clang)

check_tool "$cmake_exists" "❌ Error: 'cmake' not found. Please install it first."
check_tool "$ninja_exists$make_exists" "❌ Error: Neither 'ninja' nor 'make' is found. Please install one (ninja recommended)."
check_tool "$clang_exists" "❌ Error: 'clang' not found. Please install it first."

if [[ $requirement_missing -eq 1 ]]; then
	exit 1
fi

if [[ -n "$ninja_exists" ]]; then
	echo "🔧 Building with Ninja..."
	cmake --workflow ninja-full-build
elif [[ -n "$make_exists" ]]; then
	echo "🔧 Building with Make..."
	cmake --workflow make-full-build
fi

install_path=${1:-/usr/local/bin}
sudo cp ./build/app/app "$install_path/dorg"

if ! command -v dorg &> /dev/null; then
	echo >&2 "⚠️ Installation failed. Try copying $(pwd)/build/app/app to system's installation path manually."
	exit 2
fi

cat <<EOF

✅ Installation successful!

👉 To generate the default config file, run:
   dorg get-config > /path/to/config/dorg/default.yml

You can also place a user config at:
   ~/.config/dorg/user.yml

EOF
