#include <iostream>
#include "Satellite.hpp"
#include "ArgumentInvalideException.hpp"
#include "Simulation.hpp"

int main()
{
	Simulation s;

	s.parseData("final_round_2016.in/forever_alone.in");

    /*
    try
    {
        Satellite s(176400, 7200, 120, 50, 500);

        s.tourSuivant(60, 20);
        std::cout << "Tour 1 : " << s << std::endl;

        for(unsigned int i = 0; i < 3599; i++)
        {
            s.tourSuivant(1, 1);
        }

        std::cout << "Tour 3600 : " << s << std::endl;
    }
    catch(ArgumentInvalideException e)
    {
        std::cerr << "Argument invalide pour le satellite : " << e.what() << std::endl;
    }
    */

    s.resolutionSimple();
	s.writeData("final_round_2016.out/forever_alone.out");

    return EXIT_SUCCESS;
}