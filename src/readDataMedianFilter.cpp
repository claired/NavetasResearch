#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>   

const int hashSize = 16;
const int BLOCK_COUNT_RANGE_MIN = 50000;
const int BLOCK_COUNT_RANGE_MAX = 250000;
const int BLOCK_SIZE_RANGE_MIN = 0;
const int BLOCK_SIZE_RANGE_MAX = 20;
//tasks
//1 Reads data files generated using gen_data.py --Done--


int main(){
	std::string filename="../data/output.txt";
	int windowSize=100000;
	int medianPoint = windowSize/2;
  
	std::ifstream fin(filename.c_str(), std::ios::in|std::ios::binary);
	if (fin.is_open()){
	//skip hash for now, assume the has has been checked on reciept of data
		for (int i =0 ; i< hashSize; i++){
			fin.ignore();
	        }
		std::cout<<filename<<std::endl;

		unsigned int records = 0;
		char buffer_records[4];
		char buffer_currVolt[4];

	
		int count=0;

		// loop through a series of blocks of data
		while (fin.read(buffer_records, 4)!=0){

			//convert to unsigned 32bit integer containing the number of records in the block
			records = buffer_records[0] | (buffer_records[1]<<8) | (buffer_records[2]<<16) | (buffer_records[3]<<24);
	    
			//i is index in block of data
			for (int i=0; i<records; i++){
				float current;
				float voltage;

				//convert to two IEEE 754 float32 numbers, the first for voltage and the second for current.
				fin.read(buffer_currVolt, 4);
				memcpy(&voltage,buffer_currVolt,4);

				fin.read(buffer_currVolt, 4);
				memcpy(&current,buffer_currVolt,4);
				

				//just print for now, do something smarter later
				std::cout<<records<<"\nv "<<voltage<<"\nc "<<current<<std::endl;
			}

		}

	}
	fin.close();
	return 0;       
}    


