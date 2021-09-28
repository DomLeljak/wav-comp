#include <iostream>
#include <fstream>
#include <iomanip>
#include <boost/random.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <time.h>

int main()
{
	
	typedef boost::mt19937 base_generator_type;
	base_generator_type generator(time(0));
	boost::random::uniform_real_distribution<> uni_dist(-1.,1.);
	boost::variate_generator<base_generator_type&, boost::random::uniform_real_distribution<> > uni(generator, uni_dist);

	int N;
	std::cout << "Number of data points: ";
	std::cin >> N;
	float* data = new float[N];
	if (data == nullptr)
		std::cout << "Error: memory could not be allocated";

	for (int x = 0; x < N; x++){
		data[x] = sin (x * 2 * M_PI / N) + 0.1 * uni();
		printf("%4f \n", data[x]);
	}

	{

		std::ofstream myfile;
		myfile.open("data/data.csv");
		if (!myfile) {
			std::cerr << "can't open output file" << std::endl;
		}

		for (int x = 0; x < N; x++){
			myfile << std::fixed << std::setprecision(4) << x * 2 * M_PI / N << "	" << data[x] << std::endl;
		}

		myfile.close();
		
		return 0;
	
	}
	
	delete[] data;
	data = NULL;

	return 0;

}
