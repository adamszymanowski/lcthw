set -e
make ex17ec
./builds/ex17ec ./builds/ecdb.dat c
./builds/ex17ec ./builds/ecdb.dat s 1 adam adam@adam.com
./builds/ex17ec ./builds/ecdb.dat s 2 max max@adam.com
./builds/ex17ec ./builds/ecdb.dat s 3 bart bart@adam.com
./builds/ex17ec ./builds/ecdb.dat l
./builds/ex17ec ./builds/ecdb.dat d 2
echo "----"
./builds/ex17ec ./builds/ecdb.dat l
xxd ./builds/ecdb.dat