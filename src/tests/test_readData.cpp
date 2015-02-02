#include <readData.h>
#include <iostream>
#include <fstream>
#include <string>  
#include <cmath>
#include <cstdlib>


	//test if readData class is correct, compared with currents listed in a text file
int main(){


	readData reader;
	reader.initFileForProcessing("../data/testData/records.txt");
	std::string testFile="../data/testData/records_justCurrentText.txt";
	std::ifstream myfile (testFile.c_str());

	std::string line;
	float current_notBin;
	float current_bin;
	int numRecords=0;
	float epsilon=0.00001;
	bool success=true;


	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			current_notBin=std::atof(line.c_str());
			if (reader.getCurrent(current_bin)){

				if ( std::abs(current_bin - current_notBin) > epsilon){
					std::cerr<<"line number "<<numRecords<<" does not match in files"<<std::endl;
					std::cerr<<"bin: "<<current_bin<<std::endl;
					std::cerr<<"nbin: "<<current_notBin<<std::endl;
					success=false;
				}
			}
			else{	
				std::cerr<<"too few entries in the binary output"<<std::endl;
				success=false;
			}
			numRecords++;
		}
		if (reader.getCurrent(current_bin)){
			std::cerr<<"too many entries in the binary output"<<std::endl;
			success=false;
		}
		myfile.close();
	}
  	else {
		std::cout << "Unable to open file"; 
					success=false;
	}
	if(success) std::cout<<"tests passed"<<std::endl;
	else std::cout<<"tests failed"<<std::endl;
	



}
