#ifndef COATING_AREA_H
#define COATING_AREA_H
#include <iostream>


using namespace std;

class Coating_Area
{

public:
//Obliczanie kosztu pow�oki - deklaracje

//Anodowanie
float CalculateAnodizingCost(float&,float&);

//Cynkowanie
float CalculateGalvanizingCost(float&,float&);

//Hartowanie
float CalculateHardeningCost(float&,float&);

//Czernienie
float CalculateBlackeningCost(float&,float&);

//Naw�glanie
float CalculateCarburizingCost(float&,float&);
	
	
};

#endif
