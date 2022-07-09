#ifndef SURFACE_AREA_H
#define SURFACE_AREA_H

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

using namespace std;

class Surface_Area
{

public:
//Obliczanie pola powierchni materia³u  - deklaracje

//prêt okr¹g³y
float CalculateRoundRod(float,float);
	
//rura okr¹g³a
float CalculateRoundPipe(float,float,float);

//prêt szeœciok¹tny
float CalculateHexagonalRod(float, float);

//rura szeœciok¹tna
float CalculateHexagonalPipe(float,float,float);

//prêt kwadratowy
float CalculateSquareRod(float,float);

//blacha/plaskowniki
float CalculatePlate(float,float,float);

//profil kwadratowy
float CalculateSquareProfile(float,float,float,float);

//k¹townik
float CalculateAngleProfile(float,float,float,float);

//ceownik
float CalculateCProfile(float,float,float,float);

//teownik
float CalculateTProfile(float,float,float,float);

//dwuteownik
float Calculate2TProfile(float,float,float,float);

	
};

#endif
