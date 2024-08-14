clear
# block
echo "======================================================"
echo Compiling Block
zig cc block.c -o block.out
./block.out 1
./block.out 2
./block.out 4 3
rm block.out
# box
echo "======================================================"
echo Compiling Box
zig cc box.c -g -o box.out
./box.out 1
./box.out 2
./box.out 3
./box.out 4
./box.out 5
./box.out 5 8
./box.out 20 4
rm box.out
