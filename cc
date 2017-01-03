#!/bin/sh

rm -rf build

./configure

pushd build &>/dev/null

make

popd &>/dev/null
