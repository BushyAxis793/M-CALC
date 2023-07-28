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
    } mg;
    list<MaterialGenre> materialGenreList;
private:
    float dimension1 = 0;
    float dimension2 = 0;
    float dimension3 = 0;
    float dimension4 = 0;



public:
	MaterialGenre GetGenre();
	void SetGenre(string, string, double);
    void CalculateFinalEuroPrice(Currency::Euro&);

    void SetDimension1(float);
    float GetDimension1()const;

    void SetDimension2(float);
    float GetDimension2()const;

    void SetDimension3(float);
    float GetDimension3()const;

    void SetDimension4(float);
    float GetDimension4()const;

};


#endif // !CALCULATIONS_H




