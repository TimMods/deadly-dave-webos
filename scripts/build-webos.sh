#!/usr/bin/env bash
set -euo pipefail

cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.."
root=$PWD
build="$root/build/webos"
dist="$root/dist/webos"
sdk=${WEBOS_SDK:-"$HOME/arm-webos-linux-gnueabi_sdk-buildroot"}
toolchain="$sdk/share/buildroot/toolchainfile.cmake"
sdl="$build/sdl"
archive="$build/sdl.tar.gz"
release=release-2.30.12-webos.5
checksum=750ea26b41425ed54a58aba40d70970d4c0bae239142781f03dfcd153da475d1

if [[ ! -f "$toolchain" ]]; then
    printf 'Set WEBOS_SDK to the extracted webOS ARM SDK directory.\n' >&2
    exit 1
fi
command -v ares-package >/dev/null
mkdir -p "$sdl" "$dist"
if [[ ! -f "$archive" ]]; then
    curl --fail --location --retry 2 --output "$archive.part" \
        "https://github.com/webosbrew/SDL-webOS/releases/download/$release/SDL2-2.30.12-webos-abi.tar.gz"
    mv -- "$archive.part" "$archive"
fi
printf '%s  %s\n' "$checksum" "$archive" | sha256sum --check
tar -xzf "$archive" -C "$sdl"

cmake -S "$root" -B "$build/cmake" -DCMAKE_TOOLCHAIN_FILE="$toolchain" \
    -DDEADLY_DAVE_WEBOS_SDL="$sdl" -DCMAKE_BUILD_TYPE=Release
cmake --build "$build/cmake" --parallel

stage=$(mktemp -d "$build/package.XXXXXX")
trap 'rm -r -- "$stage"' EXIT
mkdir "$stage/lib"
install -m 755 "$build/cmake/deadly-dave" "$stage/deadly-dave"
"$sdk/bin/arm-webos-linux-gnueabi-strip" "$stage/deadly-dave"
install -m 644 "$sdl/lib/libSDL2-2.0.so.0" "$stage/lib/libSDL2-2.0.so.0"
install -m 644 "$sdl/share/licenses/SDL2/LICENSE.txt" "$stage/lib/SDL2-LICENSE.txt"
cp -- webos/appinfo.json assets/icon.png assets/splash.png LICENSE "$stage/"
cp -R -- res "$stage/"
ares-package -o "$dist" "$stage"
