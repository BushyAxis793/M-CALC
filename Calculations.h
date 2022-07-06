#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#pragma once

#include <iostream>
#include <string>
#include <list>



using namespace std;

class Calculations
{
public:
	struct MaterialGenre
	{

        string materialName;
        string materialGenreName;
        double materialDensity;
	};
    list<MaterialGenre> materialGenreList;



public:
	MaterialGenre GetGenre();
	void SetGenre(string, string, double);

};


#endif // !CALCULATIONS_H




