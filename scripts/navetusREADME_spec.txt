Median Current Filter
---------------------
The attached gen_data.py file generates example data files containing voltage
and current readings - please see the top of gen_data.py for the file format.

Please write a C++ application that:
* Reads data files generated using gen_data.py
* Runs an online median filter over the current values with a window size of
100,000.
* Start with an initial window of 100,000 zeros
* Write the output of the filter to a text file, one value per line

Please send the final source files and any support (build etc) files required
to compile the application. If possible, please also send any version control
history generated while writing the application or point us towards an online
repository.

We will be looking for (most to least important):
1. A structured approach to the code - there's an opportunity to identify
submodules and suitable interfaces for the different tasks
2. Neat, well laid out code where it's clear what's going on
3. Use of the basic STL and libstdc++ libraries
4. Performance

Please do not use any libraries other than libstdc++ & the STL. A scrappy
and slow implementation can be put together in 20 minutes, but it will probably
take longer to put together a more complete implementation. As a guide, imagine
you are working in the development team at Navetas and submit the first
version that you would be happy to ask your colleagues to code review.

Please consider this test confidential (so we can use it with candidates in
future).
