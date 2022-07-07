#ifndef DENSITY_H
#define DENSITY_H
#include <iostream>


class Density
{
//Gêstoœci materia³ów [kg/dm^3] - deklaracje
 	
public:	
//Stall
double steel_density[7] = 
{	
	 7.85,
	 7.5,
	 7.7,
	 7.8,
	 7.9,
	 8.0,
	 8.1
};

//Aluminium
double aluminium_density[8] = 
{
	 2.71, 			//PA4 AW-6082
	 2.79,			//PA6 AW-2017A
	 2.81,			//PA9 AW-7075
	 2.68,			//PA11 AW-5754
	 2.66,			//PA13 AW-5083
	 2.7,			//PA38 AW-6060
	 2.85,			//AW-2007
	 2.78			//PA47 AW-7020
};

//Br¹z
double bronze_density[9] = 
{
	 8.5, 			
	 7.695,			//BA83
	 7.8,			//BA8
	 8.197,			//BA5
	 8.295,			//BB2
	 8.4,			//BB1.7
	 8.497,			//BK1, BK31
	 8.895,			//B2, B4, B8, B443
	 8.895			//BB21, BC2
};

//Mosi¹dz
double brass_density[1] = 
{
	 8.5			
	
};

//Cooper
double copper_density[1] = 
{
	 8.9			
	
};

//O³ów
double lead_density[1] = 
{
	 11.68		
	
};

public:
float CalculateMaterialMass(float& ,float);

float CalculateMaterialPrice(float&,float&);
	
};

#endif
