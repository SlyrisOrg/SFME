#!/bin/bash

PROGNAME=$0

CCOMPILER="gcc"
CXXCOMPILER="g++"
TYPE="Debug"

function parse_args()
{
    while getopts ":c:x:t:h" opt; do
	case $opt in
	    c)
		CXXCOMPILER=$OPTARG
		;;
	    x)
		CCOMPILER=$OPTARG
		;;
	    t)
		TYPE=$OPTARG
		;;
	    h)
		echo "Usage: $PROGNAME [-c <compiler>] [-t <Debug | Release>]"
		exit 0
		;;
	    \?)
		echo "Invalid argument -$OPTARG, see $PROGNAME -h"
		;;
	esac
    done

    shift $(expr $OPTIND - 1)
    for t in "$@"; do
	TARGETS+="$t "
    done
}

function print_settings()
{
    echo "C compiler: $CCOMPILER"
    echo "C++ compiler: $CXXCOMPILER"
    echo "Build type: $TYPE"
}

function build_targets
{
    mkdir -p $BUILD_DIR
    cd $BUILD_DIR
    cmake -DCMAKE_BUILD_TYPE=$TYPE -DCMAKE_C_COMPILER=$CCOMPILER_EXE -DCMAKE_CXX_COMPILER=$CXXCOMPILER_EXE -DSFME_BUILD_TESTS=ON -DSFME_BUILD_EXAMPLES=ON ..
    make -j2
    cd ..
}

function run_ctest
{
    cd $BUILD_DIR
    ctest --no-compress-output -T Test -D ExperimentalMemCheck || exit 1
    cd ..
}

function run_xunit
{
    cd bin
    for i in *-test; do
	./$i --gtest_output="xml:${i}-${TYPE}-result.xml" || exit 1
    done
    cd ..
    mkdir -p test-result/ctest
    cp bin/*.xml test-result/
    cp $BUILD_DIR/Testing/*/*.xml test-result/ctest/
}

parse_args "$@"
CCOMPILER_EXE=$(which $CCOMPILER)
CXXCOMPILER_EXE=$(which $CXXCOMPILER)
BUILD_DIR=${CXXCOMPILER}-${TYPE}-build
print_settings
build_targets
run_ctest
run_xunit
