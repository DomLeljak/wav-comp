#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include </usr/include/matplotlib-cpp/matplotlibcpp.h>
#include <boost/multi_array.hpp>

namespace plt = matplotlibcpp;
	
typedef boost::multi_array<float, 2> b_array_2d;
typedef b_array_2d::index b_index;

struct vecdata {

	std::vector<float> x;
	std::vector<float> y;

};

int numline(std::ifstream&);
void loaddata(std::ifstream&, b_array_2d *, int);
vecdata plotinput(b_array_2d, int);

int main() {

	std::ifstream myfile;
	myfile.open("data/data.csv");
	if (!myfile) {
		std::cout << "Unable to open file";
		exit(1); // terminate with error
	}
	int N = numline(myfile);
	myfile.clear(); // read to EOF, reset error bits
	myfile.seekg(std::ios::beg); // seek back to beginning of file

	b_array_2d data(boost::extents[2][N]);
	
	loaddata(myfile, &data, N);

	myfile.close();

	plt::plot(plotinput(data, N).x, plotinput(data, N).y, "og");
	plt::show();

	return 0;                    

}                                    
                                      
                                     
int numline(std::ifstream& fin) {     
	
	std::string temp; 
	int numberOfLines = 0;       
	
	while(getline(fin, temp))    
	{
		numberOfLines++;
	}
	
	return numberOfLines;

}

void loaddata(std::ifstream& fin, b_array_2d *dat, int n) {
	
	int cols = 0;

	for(b_index j = 0; j < n; j++) {
		for(b_index i = 0; i < 2; i++) {
			fin >> (*dat)[i][j];
			// compile with run below for diagnostics
			// printf(" for (i,j) = (%d %d): %f \n", i, j, (*dat)[i][j]);
		}
		cols++;
	}
}

// This part is redundant:
// I'm filling the boost::multi_array
// and then populating vectors using that.
// The boost::multi_array might come
// in handy later.

vecdata plotinput(b_array_2d dat, int n) {
	
	std::vector<float> aps(n), ord(n);
	vecdata output;

	for(int i=0; i<n; i++) {
		aps.at(i) = dat[0][i];
		ord.at(i) = dat[1][i];
	}

	output.x = aps;
	output.y = ord;

	return output;

}
