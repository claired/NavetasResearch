#include <currentMedianFilter.h>
#include <iostream>
#include <stdlib.h> 

const int hashSize = 16;

//tasks
//1 Reads data files generated using gen_data.py --Done--
//2 Start with an initial window of 100,000 zeros --Done--
//3 Runs an online median filter over the current values with a window size of 100,000. --Done--
//4 write --Done--

void usage()
{
  std::cerr << "Usage: readDataMedianFilter [inFile] [outFile] <options>\n";
  std::cerr << "Where <options> are one or more of the following:\n";
  std::cerr << "\t<-windowSize n>    Size of the window (default = 100k)\n";
  exit(1);
}



int main(int argc, char* argv[]){
	//default parameters
//	std::string inputFilename="../data/output.txt";
//	std::string outputFilename="../data/median_out.txt";
	unsigned int windowSize=100000;
	char *outputFilename;
	char *inputFilename;
	if (argc < 3) {
		usage();
	}

  // Read input and output names
	inputFilename  = argv[1];
	argc--;
	argv++;
	outputFilename = argv[1];
	argc--;
	argv++;

	while (argc > 1) {
		bool ok = false;
		if ((ok == false) && (strcmp(argv[1], "-windowSize") == 0)) {
			argc--;
			argv++;
			windowSize = atoi(argv[1]);
			argc--;
			argv++;
			ok = true;
		}
		if (ok == false) {
			std::cerr << "Unknown option: " << argv[1] << std::endl;
			usage();
		}
	}

	currentMedianFilter currentMedianFilter;	
	currentMedianFilter.initialise(inputFilename, outputFilename, windowSize);
	currentMedianFilter.evaluation();

	return 0;       
}    


