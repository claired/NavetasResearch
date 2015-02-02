#include <readData.h>


void readData::closeFile(){
	fin.close();
}

bool readData::initFileForProcessing(const char *filename){
	records = 0;
	fin.open(filename, std::ios::in|std::ios::binary);
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

bool readData::getCurrent(float &current){
	
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
			return false;
	}


	//convert to two IEEE 754 float32 numbers, the first for voltage and the second for current.
	//for the purpose of a median current filter, we can discard voltage.
	fin.read(buffer_currVolt, 4);
	fin.read(buffer_currVolt, 4);
	memcpy(&current,buffer_currVolt,4);	

	//decrement records for next call
	records--;

	return true;


}


