#include <currentMedianFilter.h>
#include <cstdlib>
#include <cmath>

	//test if median filter matches median computed naive python implementation (with numpy)
int main(){

;
	std::string median="../data/testData/records_currentMedian.txt";
	std::string inputFilename="../data/testData/records.txt";
	float epsilon=0.00001;
	std::string output="/tmp/output.txt";
	unsigned int windowSize=100000;
	int lineNum=0;
	bool success=true;

	currentMedianFilter currentMedianFilter;	
	currentMedianFilter.initialise(inputFilename.c_str(), output.c_str(), windowSize);
	currentMedianFilter.evaluation();

	std::string line, line2;
	std::ifstream myfile (median.c_str());
	std::ifstream myfile2 (output.c_str());

	if (myfile.is_open())
	{
		std::cout<<output<<std::endl;
		while ( getline (myfile,line) ){
			if(!getline(myfile2,line2)) {
				std::cerr<<" too few lines in the C++ implementation"<<std::endl;
				success=false;
			}
			else if (std::abs(std::atof(line2.c_str()) - std::atof(line.c_str())) > epsilon){
				std::cout<<" medians don't match on line "<<lineNum<<std::endl;
				std::cout<<line2<<", "<<line<<std::endl;
				success=false;
			}	
			lineNum++;
		}
		if(getline (myfile2,line2) ) {
			std::cerr<<" too many lines in the C++ implementation"<<std::endl;
			success=false;
		}
	}
	else {
		std::cout << "Unable to open file"; 
					success=false;
	}
	if(success) std::cout<<"tests passed"<<std::endl;
	else std::cout<<"tests failed"<<std::endl;


}
