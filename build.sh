#!/bin/bash

set -e

mkdir -p out

$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ \
  -shared -fPIC \
  -o out/libpathfix.so \
  zygisk/pathfix.cpp

mkdir -p module/zygisk
cp out/libpathfix.so module/zygisk/

cp module.prop module/
cp customize.sh module/

cd module
zip -r ../zygisk-pathfix.zip *
