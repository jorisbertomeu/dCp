#!/bin/bash

NBR_TEST=5

function checkDiff() {
    echo -e "\033[34mTesting difference between both files $1 and $2\033[0m"
    diff $1 $2 | wc -l > diffRes
    result=$(cat diffRes)
    if [ "$result" -eq "0" ]; then
       echo -e "\033[32m>> No difference\033[0m"
    else
       echo -e "\033[31m>> Files are differents\033[0m"
    fi
    rm -fr diffRes
}

rm -fr tests
mkdir tests
#Compilation
echo -e "\033[33m----- [COMPILATION] -----\033[0m"
make all
echo -e "\033[33m-------------------------\033[0m"
#TEST 1
echo -e "\033[33m----- [TEST 1/$NBR_TEST] -----\033[0m"
echo -e "\033[34mDescription : Test Usage\033[0m"
./dcp
echo -e "\033[33m----------------------\033[0m"
#TEST 2
echo -e "\033[33m----- [TEST 2/$NBR_TEST] -----\033[0m"
echo -e "\033[34mDescription : Basic copy (little text file)\033[0m"
mkdir ./tests/test2
touch ./tests/test2/testFile
echo "test" > ./tests/test2/testFile
./dcp ./tests/test2/testFile ./tests/test2/testFileCopied
#echo "titi" > ./tests/test2/testFileCopied #Test checkDiff function (Expecting 
checkDiff ./tests/test2/testFile ./tests/test2/testFileCopied
echo -e "\033[33m----------------------\033[0m"
#TEST 3
echo -e "\033[33m----- [TEST 3/$NBR_TEST] -----\033[0m"
echo -e "\033[34mDescription : Basic copy (png file)\033[0m"
echo "Downloading file ... Please, wait"
mkdir ./tests/test3
wget https://upload.wikimedia.org/wikipedia/commons/thumb/3/35/Tux.svg/200px-Tux.svg.png -o /dev/null
mv 200px-Tux.svg.png ./tests/test3/testImage.png
./dcp ./tests/test3/testImage.png ./tests/test3/testImageCopied.png
checkDiff ./tests/test3/testImage.png ./tests/test3/testImageCopied.png
echo -e "\033[33m----------------------\033[0m"
#TEST 4
echo -e "\033[33m----- [TEST 4/$NBR_TEST] -----\033[0m"
echo -e "\033[34mDescription : Basic copy (big file - 100MB)\033[0m"
if [ "$1" == "--fast" ]; then
    echo -e "\033[33mTest ignored (--fast indeed)\033[0m"
else
    echo "Downloading file ... Please, wait"
    mkdir ./tests/test4
    wget http://download.thinkbroadband.com/100MB.zip -o ./tests/test4/download.log
    mv 100MB.zip ./tests/test4/testBigFile.zip
    ./dcp ./tests/test4/testBigFile.zip ./tests/test4/testBigFileCopied.zip
    checkDiff ./tests/test4/testBigFile.zip ./tests/test4/testBigFileCopied.zip
fi
echo -e "\033[33m----------------------\033[0m"
#TEST 5
echo -e "\033[33m----- [TEST 5/$NBR_TEST] -----\033[0m"
echo -e "\033[34mDescription : Basic copy (Multiple files)\033[0m"
echo "Downloading file ... Please, wait"
mkdir ./tests/test5
wget https://github.com/jorisbertomeu/dCp/archive/master.zip -o ./tests/test5/download.log
mv master.zip ./tests/test5/testMultipleFile.zip
unzip ./tests/test5/testMultipleFile.zip -d ./tests/test5/
mkdir ./tests/test5/result
./dcp ./tests/test5/dCp-master/* ./tests/test5/result/
ls -l ./tests/test5/dCp-master/ | awk '{print $5, $9}' > ./tests/test5/.r1
ls -l ./tests/test5/result/ | awk '{print $5, $9}' > ./tests/test5/.r2
checkDiff ./tests/test5/.r1 ./tests/test5/.r2
echo -e "\033[33m----------------------\033[0m"
#LS SUMMARY
ls -Rrtl ./tests
