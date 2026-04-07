#!/bin/bash

NDK=/usr/local/lib/android/sdk/ndk/25.2.9519653
TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/linux-x86_64/bin

TARGET=aarch64-linux-android
API=24

$TOOLCHAIN/${TARGET}${API}-clang++ \
  -shared -fPIC \
  zygisk/pathfix.cpp \
  -o libpathfix.so \
  -ldl
