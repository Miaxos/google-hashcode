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

	//r�cup�re le temps avant l'ex�cution du fichier
	const clock_t startPoint = clock();

	//ex�cution du fichier
	HINSTANCE hNewExe = ShellExecuteA(NULL, "open", exec, NULL, NULL, SW_SHOW);

	//si la valeur retourn�e est inf�rieure ou �gale � 32, elle �choue
	if ((DWORD)hNewExe <= 32)
	{
		cout << "Echec, erreur n� :" << (DWORD)hNewExe << endl;
	}
	else
	{
		cout << "Succ�s.\n" << endl;
	}

	//r�cup�re le temps apr�s l'ex�cution du fichier
	endPoint = clock();

	//time repr�sente le temps d'ex�cution de l'ex�cutable
	time = (double)(endPoint = startPoint);

	cout << "Le temps d'ex�cution de l'ex�cutable est " << time << "secondes.\n" << endl;

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

	//on parcourt tous les ex�cutables et on lance la fonction qui ram�ne le temps d'ex�cution
	for (int i = 0; i < fileNames.size(); i++) {
		std::cout << time.getTime(fileNames[i]) << std::endl;
	}

	return 0;
}


