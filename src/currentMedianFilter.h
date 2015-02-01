
#include <iostream>
#include <fstream>
#include <string.h>   
#include <stdio.h>
#include <queue>
#include <set>

//implementation decissions:
//queue selected since it is a simple way to keep track of first in first out (FIFO) data, apt for sliding windows.
//multiset chosen, because ordered data with (O)log(n) search and allows multiple entrants

class currentMedianFilter{
private:
	unsigned int windowSize;
	bool isWindowSizeEven;
	char *inputFilename;
	char *outputFilename;
	std::queue<float> windowQueue;
	std::multiset<float> window;
	unsigned int medianPoint;
	//median is an iterator that will keep track of the median point.
	std::multiset<float>::iterator median;

public:
	void initialise (char *, char *, unsigned int );
	void evaluation();
	void slideWindow(float , unsigned int );
	float getMedianValue();
};


