
#include <iostream>
#include <fstream>
#include <string.h>   
#include <stdio.h>
const int hashSize = 16;

//tasks
//1 Reads data files generated using gen_data.py --Done--


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
				

	//just print for now, do something smarter later
	std::cout<<records<<"c "<<current<<std::endl;		

	//decrement records for next call
	records--;
	return current;


}

int main(){
	std::string filename="../data/output.txt";
	int windowSize=100000;
	int medianPoint = windowSize/2;

	if (initFileForProcessing(filename))  {
		float current=-1.0;
		// loop through a series of blocks of data
		while ((current=getCurrent())!=-1.0){

		
		}

	}
	closeFile();
	return 0;       
}    


