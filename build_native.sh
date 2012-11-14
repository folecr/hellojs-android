# set params
# NDK_ROOT_LOCAL=/path/to/android/ndk
# MOZILLA_ROOT_LOCAL=/path/to/spidermonkey
# GAME_ROOT_LOCAL=/path/to/the/game/directory

APPNAME="jsplayer-android"

# options

debug=
verbose=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ code for $APPNAME using Android NDK

OPTIONS:
-d	Build in debug mode
-v  Turn on verbose output
-h	this help

Dependencies :
CLANG_ROOT
NDK_ROOT

Paths to sources (defaults are in ./submodules) :
COCOS2DX_ROOT
MOZILLA_ROOT

Define this to run the build script from an external directory :
APP_ROOT

EOF
}

while getopts "dvh" OPTION; do
case "$OPTION" in
d)
debug=1
;;
v)
verbose=1
;;
h)
usage
exit 0
;;
esac
done

# exit this script if any commmand fails
set -e

# paths

if [ -z "${NDK_ROOT+aaa}" ]; then
# ... if NDK_ROOT is not set, use "$HOME/bin/android-ndk"
    NDK_ROOT="$HOME/bin/android-ndk"
fi

# paths with defaults hardcoded to relative paths

if [ -z "${APP_ROOT+aaa}" ]; then
    APP_ROOT="$PWD"
fi

if [ -z "${MOZILLA_ROOT+aaa}" ]; then
    MOZILLA_ROOT="$PWD/submodules/mozilla-prebuilt"
fi

echo "NDK_ROOT: $NDK_ROOT"
echo "APP_ROOT: $APP_ROOT"
echo "MOZILLA_ROOT: $MOZILLA_ROOT"

# Currently we only have the android app
APP_ANDROID_ROOT="$APP_ROOT"

DEBUG_OPTIONS=
if [[ $debug ]]; then
    DEBUG_OPTIONS="NDK_DEBUG=1"
fi

VERBOSE_OPTIONS=
if [[ $verbose ]]; then
    VERBOSE_OPTIONS="NDK_LOG=1 V=1"
fi

# Exit on error
set -e

# build
echo "Building native code..."
set -x
$NDK_ROOT/ndk-build -C $APP_ANDROID_ROOT $DEBUG_OPTIONS $VERBOSE_OPTIONS\
    NDK_MODULE_PATH=${APP_ANDROID_ROOT}/jni:${MOZILLA_ROOT}
set +x

echo "... Building native code : Done."
