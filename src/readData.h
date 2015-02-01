#include <iostream>
#include <fstream>
#include <string.h>   
#include <stdio.h>
 

class readData{
	private:
		static const int hashSize = 16;
		unsigned int records ;
		std::ifstream fin;
	
	public:
		void closeFile();
		bool initFileForProcessing(char *);
		float getCurrent();

};
