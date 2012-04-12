# set params
NDK_ROOT_LOCAL=/path/to/android/ndk
MOZILLA_ROOT_LOCAL=/path/to/spidermonkey
GAME_ROOT_LOCAL=/path/to/the/game/directory

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ native code using Android NDK

OPTIONS:
   -h	this help
EOF
}

while getopts "s" OPTION; do
	case "$OPTION" in
		h)
			usage
			exit 0
			;;
	esac
done

# try to get global variable
if [ $NDK_ROOT"aaa" != "aaa" ]; then
    NDK_ROOT_LOCAL=$NDK_ROOT
    echo "use global definition of NDK_ROOT: $NDK_ROOT"
fi

if [ $MOZILLA_ROOT"aaa" != "aaa" ]; then
    MOZILLA_ROOT_LOCAL=$MOZILLA_ROOT
    echo "use global definition of MOZILLA_ROOT: $MOZILLA_ROOT"
fi

if [ $GAME_ROOT"aaa" != "aaa" ]; then
    GAME_ROOT_LOCAL=$GAME_ROOT
    echo "use global definition of GAME_ROOT: $GAME_ROOT_LOCAL"
else
# if GAME_ROOT is not set
# use current directory
    GAME_ROOT_LOCAL=$PWD
    echo "using current directory for GAME_ROOT: $GAME_ROOT_LOCAL"
fi

# Currently we only have the android game
GAME_ANDROID_ROOT=$GAME_ROOT_LOCAL

# build
echo "Building native code..."
$NDK_ROOT_LOCAL/ndk-build -C $GAME_ANDROID_ROOT \
    NDK_MODULE_PATH=${GAME_ANDROID_ROOT}/jni:${MOZILLA_ROOT_LOCAL}
echo "... Building native code : Done."
