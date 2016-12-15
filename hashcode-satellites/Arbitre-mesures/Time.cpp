#include "Time.h"
#include<windows.h>
#include<stdio.h>
#include <shellapi.h>
#include<time.h>
#include<iostream>
#include <vector>

using namespace std;

Time::Time()
{

}

Time::~Time()
{
}

double Time::getTime(const char * exec)
{
	clock_t endPoint;
	double time;

	//récupère le temps avant l'exécution du fichier
	const clock_t startPoint = clock();

	//exécution du fichier
	HINSTANCE hNewExe = ShellExecuteA(NULL, "open", exec, NULL, NULL, SW_SHOW);

	//si la valeur retournée est inférieure ou égale à 32, elle échoue
	if ((DWORD)hNewExe <= 32)
	{
		cout << "Echec, erreur n° :" << (DWORD)hNewExe << endl;
	}
	else
	{
		cout << "Succès.\n" << endl;
	}

	//récupère le temps après l'exécution du fichier
	endPoint = clock();

	//time représente le temps d'exécution de l'exécutable
	time = (double)(endPoint = startPoint);

	cout << "Le temps d'exécution de l'exécutable est " << time << "secondes.\n" << endl;

	return time;
}


std::vector<const char *> GetFileNamesInDirectory(std::string directory) {
	std::vector<const char *> files;
	WIN32_FIND_DATA fileData;
	HANDLE hFind;

	if (!((hFind = FindFirstFile(directory.c_str(), &fileData)) == INVALID_HANDLE_VALUE)) {
		while (FindNextFile(hFind, &fileData)) {
			files.push_back(fileData.cFileName);
		}
	}

	FindClose(hFind);
	return files;
}

int main() 
{
	Time time;
	std::vector<const char *> fileNames = GetFileNamesInDirectory("*");

	//on parcourt tous les exécutables et on lance la fonction qui ramène le temps d'exécution
	for (int i = 0; i < fileNames.size(); i++) {
		std::cout << time.getTime(fileNames[i]) << std::endl;
	}

	return 0;
}


