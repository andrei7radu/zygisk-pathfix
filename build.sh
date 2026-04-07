#!/bin/bash

NDK=$ANDROID_NDK_HOME

$NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ \
  -shared -fPIC \
  zygisk/pathfix.cpp \
  -o libpathfix.so \
  -ldl
