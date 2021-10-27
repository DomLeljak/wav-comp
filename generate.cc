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
	boost::random::uniform_real_distribution<> uni_dist_2(.80, 1.2);
	boost::variate_generator<base_generator_type&, boost::random::uniform_real_distribution<> > uni(generator, uni_dist);
	boost::variate_generator<base_generator_type&, boost::random::uniform_real_distribution<> > uni_2(generator, uni_dist_2);

	int Nx, Ns;
	int periods = 8; // number of periods
	std::cout << "Number of data points: ";
	std::cin >> Nx;
	std::cout << "Number of data sets: ";
	std::cin >> Ns;

	float* data = new float[Ns * Nx];

	if (data == nullptr)
		std::cout << "Error: memory could not be allocated";

	for (int i = 0; i < Ns; i++){
		for (int x = 0; x < Nx; x++){
			data[Nx*i + x] = uni_2() * sin (2 * x * periods * 2 * M_PI / Nx)
				* uni_2() * std::sqrt(x) * sin (x * periods * 2 * M_PI / Nx)
				+ 0.1 * std::sqrt(x) *  uni()
				+ std::sqrt(x);
			printf("%d, %d: %4f \n", i, Nx, data[x]);
		}
	}

	{

		std::ofstream myfile;
		myfile.open("data/data.csv");
		if (!myfile) {
			std::cerr << "can't open output file" << std::endl;
		}

		for (int x = 0; x < Nx; x++){
			myfile << std::fixed << std::setprecision(4) << x * periods * 2 * M_PI / Nx;
			for (int i = 0; i < Ns; i++){
				myfile << "	" << data[i*Nx + x];
			}
			myfile << std::endl;
		}
		myfile.close();
		
		return 0;
	
	}
	
	delete[] data;

	return 0;

}
