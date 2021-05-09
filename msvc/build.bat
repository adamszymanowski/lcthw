@echo off

mkdir builds
pushd builds
cl ../%1 -Zi -TC -Wall -wd4710

popd ..