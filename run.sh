#!/bin/sh

echo "Making generator and main program."
#make main program
make

#make generator
cd generator
make
echo
#run generator and create euler path
echo "Creating graph path with 5 nodes 8 edges and running algorithm."
./generator 5 8 -e

#copy created graph to main folder
cd ..
cp $(pwd)/generator/matrix.txt $(pwd)

#run algortihm
./euler matrix.txt
mv paths.txt paths1_txt
echo

#run generator and create euler path
echo "Creating graph cycle with 42 nodes 42 edges and running algorithm."
cd generator
./generator 42 42 -E

#copy created graph to main folder
cd ..
cp $(pwd)/generator/matrix.txt $(pwd)

#run algortihm
./euler matrix.txt


echo
#clearing generator folder
echo "Cleaning after testing."
cd generator
make clean
rm matrix.txt

#clearing main folder
cd ..
make clean
