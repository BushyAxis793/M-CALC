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

		string material_name;
		string material_genre_name;
		double material_density;
	};
	list<MaterialGenre> MG;



public:
	MaterialGenre GetGenre();
	void SetGenre(string, string, double);

};


#endif // !CALCULATIONS_H




