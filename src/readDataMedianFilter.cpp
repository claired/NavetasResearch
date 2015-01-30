
#include <iostream>
#include <fstream>
#include <string.h>   
#include <stdio.h>
#include <queue>
#include <set>    
const int hashSize = 16;

//tasks
//1 Reads data files generated using gen_data.py --Done--
//2 Start with an initial window of 100,000 zeros --Done--
//3 Runs an online median filter over the current values with a window size of 100,000. --Doing--
//4 write


/////////////////READ DATA CLASS (to refactor later)//////////////
//private vars for data reading - move in to separate class when initial dev done
unsigned int records = 0;
std::ifstream fin;

void closeFile(){
	fin.close();
}

bool initFileForProcessing(std::string filename){
	fin.open(filename.c_str(), std::ios::in|std::ios::binary);
	if (fin.is_open()){
	//skip hash for now, assume the has has been checked on reciept of data
		for (int i =0 ; i< hashSize; i++){
			fin.ignore();
	        }
		std::cout<<filename<<std::endl;
		return true;
	}
	else {
		std::cerr<<"Error openning file"<<std::endl;
		return false;
	}
}

float getCurrent(){
	float current;
	char buffer_records[4];
	char buffer_currVolt[4];
	//see if there any records in this block left
	//note: it is possible for blocks to have no records.
	while (records==0){
		
		if (fin.read(buffer_records, 4))
			//convert to unsigned 32bit integer containing the number of records in the block
			records=buffer_records[0] | (buffer_records[1]<<8) | (buffer_records[2]<<16) | (buffer_records[3]<<24);
		else
			//if fin.read is 0, means EoF
			return -1.0;
	}


	//convert to two IEEE 754 float32 numbers, the first for voltage and the second for current.
	//for the purpose of a median current filter, we can discard voltage.
	fin.read(buffer_currVolt, 4);
	fin.read(buffer_currVolt, 4);
	memcpy(&current,buffer_currVolt,4);	

	//decrement records for next call
	records--;

	return current;


}

/////////////////READ DATA CLASS end (to refactor later)//////////////

//queue selected since it is a simple way to keep track of first in first out (FIFO) data, apt for sliding windows.
//multiset chosen, because ordered data with (O)logn search and allows multiple entrants

int main(){
	std::string filename="../data/output.txt";
	int windowSize=100000;
	int medianPoint = windowSize/2;

//initialise datastructures
  	std::queue<float> windowQueue;
	std::multiset<float> window;
	//median is an iterator that will keep track of the median point.
	std::multiset<float>::iterator median = window.begin();
	for (int i=0; i<windowSize; i++){
		windowQueue.push(0.0);
		window.insert(0.0);
		if (i<=medianPoint) median++;		
	}


	float current=-1.0;
	float nextInQueue;
	if (initFileForProcessing(filename))  {		
		int count=0;
		// get data until file is empty.
		while ((current=getCurrent())!=-1.0){
			float directionOfMedian=0;
			if (count>=windowSize){

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

			}
			else{
				window.erase(window.begin());
				directionOfMedian=directionOfMedian+0.5;
			}

			window.insert(current);
			if (current<*median)directionOfMedian=directionOfMedian-0.5;
			else directionOfMedian=directionOfMedian+0.5;
			//Logic explanation :
			//if current==median, window will insert current after previous instances of the value, 
			// thus we can consider current==median to be equivallent to current>median
			
			if(directionOfMedian==1)median++; 
			else if(directionOfMedian==-1)median--;
			else if(directionOfMedian!=0)std::cout<<"unexpected property"<<std::endl;

	      		float out_median=*median;//(a+b)/2;
		//print for now - this needs work, in the case window.size() is even

		//std::cout<<out_median<<count<<std::endl;
			windowQueue.push(current);
			windowQueue.pop();	
			count++;
		}
	
	}


	
	closeFile();
	return 0;       
}    


