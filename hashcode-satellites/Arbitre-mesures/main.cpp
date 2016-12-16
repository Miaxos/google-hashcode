#include <iostream>
#include "Parser.h"
#include "Arbitre.h"
#include <Windows.h>
#include <string>

int main(int argc, char *argv[])
{
	


	if (argc != 3)
	{
		std::cerr << "Erreur : nombre de parametres invalide" << std::endl;
		return EXIT_FAILURE;
	}

	

	
	Arbitre arb(argv[1],argv[2]);
	int &score = arb.getScore();

	
	std::cout << "Score = " <<score << std::endl;
	return EXIT_SUCCESS;
}