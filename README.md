# NavetasResearch
median current filter code

To quickly look at the outputs of the code, please take a look at these two files.  The input was created using gen_data.py and the output was created using a C++ implementation of a median filter for the current data.
input  : data/example_data.txt
output : results/example_out_median.txt

To build: 
1) Navigate to root (NavetasResearch)
2) mkdir build; cd build
3) ccmake ../src
4) make

To run tests:
1) navigate to build directory
2) run: ./bin/test_readData and ./bin/test_medianFilter

To run main executable:
1) navigate to build directory
2) run: ./bin/readDataMedianFilter ../data/example_data.txt ../results/example_out_median.txt 
Usage: readDataMedianFilter [inFile] [outFile] <options>
Where <options> are one or more of the following:
  <-windowSize n>    Size of the window (default = 100k)

Directory structure

data/:
    |- example_data.txt: generated from scripts/gen_data.py as providing by Navetas
    |- testData/
        |- records.txt : generated from scripts/gen_data_createDataForTests.py same output as in scripts/gen_data.py
        |- records_currentMedian.txt : generated from scripts/gen_data_createDataForTests.py , plain text list of currents
        |- records_justCurrentText.txt: generated from scripts/gen_data_createDataForTests.py , list of medians over window size 100k computed using naive implementation in python.

results/:
    |- example_out_median.txt

scripts
    |- gen_data.py : as providing by Navetas
    |- gen_data_createDataForTests.py : to compute data/testData which is then used in src/tests

src/
    |- readData.cpp : read current values from file created by scripts/gen_data.py
    |- currentMedianFilter.cpp : computes a sliding window median filter
    |- readDataMedianFilter.cpp : creates an executable using the other two classes

src/tests/
    |_ test_readData.cpp : tests file readData.cpp 
    |_ test_medianFilter.cpp : tests file currentMedianFilter.cpp
