#!/bin/sh

PluginName='NativeTextureLoader'

cd `dirname $0`

# Mac
echo "\n==============================\n Mac\n==============================\n"
rm -rf ../../Assets/$PluginName/Plugins/x86_64/$PluginName.bundle*
xcodebuild -project mac/$PluginName.xcodeproj -configuration Release build

# Android
echo "\n==============================\n Android\n==============================\n"
rm -rf ../../Assets/$PluginName/Plugins/Android/lib$PluginName.so
ndk-build
