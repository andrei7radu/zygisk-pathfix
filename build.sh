#!/bin/bash

NDK=$ANDROID_NDK_HOME
TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/linux-x86_64/bin

TARGET=aarch64-linux-android
API=24

$TOOLCHAIN/${TARGET}${API}-clang++ \
  -shared -fPIC \
  zygisk/pathfix.cpp \
  -o libpathfix.so \
  -ldl
