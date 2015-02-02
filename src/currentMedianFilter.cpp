#include <readData.h>
#include <currentMedianFilter.h>


//initialises datastructures used within class; including queue and multiset populated with windowSize of 0s
void currentMedianFilter::initialise (const char *inputFilename_in,const char *outputFilename_in,unsigned int windowSize_in){
	//initialise datastructures
	windowSize=windowSize_in;
	inputFilename=inputFilename_in;
	outputFilename=outputFilename_in;
	if (windowSize % 2 == 0 ) isWindowSizeEven=true;
	else isWindowSizeEven=false;
	median = window.begin();
	medianPoint =windowSize/2;

	for (int i=0; i<windowSize; i++){
		windowQueue.push(0.0);
		window.insert(0.0);
		if (i<=medianPoint) median++;		
	}
}

//moves window one record forward.  
//current : is the new record which is to be added to the window
//numRecordsAnalysed : counts how many records has been seen in total thus far, whilst this is less than the window size, we know we need to remove 0s, which will be the first element of a multiset.  This feature increases performance slightly.
//the front element of queue, is the record to be removed.
void currentMedianFilter::slideWindow(float current, unsigned int numRecordsAnalysed){
	float directionOfMedian=0;
	float nextInQueue;
	if (numRecordsAnalysed>=(windowSize/2)){
		//1) erase record at the back of the window
		nextInQueue=windowQueue.front();
		std::multiset<float>::iterator firstMatchNextInQueue=window.equal_range(nextInQueue).first;		
		if (firstMatchNextInQueue==median){
			directionOfMedian=directionOfMedian-0.5; 
			//logic explanation :
			// => +0.5 (-1) =-0.5, -1 because median incremented here
			median++; 
			window.erase(window.equal_range(nextInQueue).first);
		}else{
			window.erase(window.equal_range(nextInQueue).first);
			if (nextInQueue>*median) directionOfMedian=directionOfMedian-0.5;
			else directionOfMedian=directionOfMedian+0.5; 
			// Logic explanation :
			//if (nextInQueue<=*median) ; equality tested here, the firstMatchNextInQueue is the 
			//first entry that matches the nextInQueue. If there is an equality here and we know 
			//it is not the median value, it must be below the median.
		}
		//2) insert new record at the front of the window
		window.insert(current);
		if (current<*median)directionOfMedian=directionOfMedian-0.5;
		else directionOfMedian=directionOfMedian+0.5;
		//Logic explanation :
		//if current==median, window will insert current after previous instances of the value, 
		// thus we can consider current==median to be equivallent to current>median

		//3) consoladate the direction the median point (iterator) should go
		if(directionOfMedian==1)median++; 
		else if(directionOfMedian==-1)median--;
		else if(directionOfMedian!=0)std::cerr<<"unexpected property"<<std::endl;
	}
	else{	
		//to improve performance
		//assuming window is populated with 0s initially and multiset is ordered
		window.erase(window.begin());
		window.insert(current);
		median++;
	}

			

}

//find the windows median, using the iterator
float currentMedianFilter::getMedianValue(){
	float medianVal=*median;
	if(isWindowSizeEven){
		median--;
		medianVal=(medianVal+*median)/2;
		median++;
	}
	return medianVal;
}

//read records from file, process data and print output to another file.
void currentMedianFilter::evaluation(){
	if(window.size()==0){
		std::cerr<<"ensure you have initialised the currentMedianFilter"<<std::endl;
		return;
	}
  	std::ofstream outputFile (outputFilename);
	readData inputFile;
	if (inputFile.initFileForProcessing(inputFilename) && outputFile.is_open() )  {		
		int numRecordsAnalysed=0;	
		float current=-1.0;
		
		// get data until file is empty.
		while (inputFile.getCurrent(current)){
			slideWindow(current, numRecordsAnalysed);
	      		float medianVal = getMedianValue();
			outputFile<<medianVal<<"\n";
			windowQueue.push(current);
			windowQueue.pop();	
			numRecordsAnalysed++;

		}
		inputFile.closeFile();	
		outputFile.close();
	}
	

}
