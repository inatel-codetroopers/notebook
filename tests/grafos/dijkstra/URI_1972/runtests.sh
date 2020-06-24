
g++ -std=c++11 *.cpp -o a.out

for i in `find *.in`
do
    echo "Running test case $i"
    tc="${i%.*}"
    ./a.out < $tc.in > $tc.out
    diff $tc.sol $tc.out
done

rm *.out