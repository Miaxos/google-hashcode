#include <iostream>
#include "Parser.h"
#include "Arbitre.h"
#include <Windows.h>
#include <string>

int main(int argc, char *argv[])
{
	std::cout << "Hello world" << std::endl;

	std::cout << argv[0] << endl;

	if (argc != 3)
	{
		std::cerr << "Erreur : nombre de parametres invalide" << std::endl;
		return EXIT_FAILURE;
	}

	

	Parser parser;
	parser.parseData_in(argv[1]);
	parser.parseData_out(argv[2]);
	Arbitre arb(parser.getList_satellite_in(), parser.getList_pictaken());
	if (arb.list_valid() == false)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}