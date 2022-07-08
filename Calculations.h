#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#pragma once

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

#include "Currencies.h"


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
    void CalculateFinalEuroPrice(Currency::Euro&);

};


#endif // !CALCULATIONS_H




