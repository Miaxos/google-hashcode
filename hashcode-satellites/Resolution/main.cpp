#include <iostream>
#include "Satellite.hpp"
#include "ArgumentInvalideException.hpp"
#include "Simulation.hpp"

int main(int argc, char *argv[])
{
	//s.parseData("/Users/anthonygriffon/Desktop/hashcodeXcode/hashcode/hashcode/final_round_2016.in/forever_alone.in");
//    s.parseData("/Users/anthonygriffon/Desktop/hashcodeXcode/hashcode/hashcode/final_round_2016.in/constellation.in");
    if(argc != 3)
    {
        std::cerr << "Erreur : nombre de parametres invalide" << std::endl;
        return EXIT_FAILURE;
    }

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
    Simulation s;
    
    s.parseData(argv[1]);
    //s.resolutionSimple();
    s.resolutionDeux();
    s.writeData(argv[2]);

    return EXIT_SUCCESS;
}
