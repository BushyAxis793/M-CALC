#include "Density.h"



float Density::CalculateMaterialMass(double material_density,float material_volume)
{
	float final_material_mass = material_density * material_volume;
	
	return final_material_mass;
}

float Density::CalculateMaterialPrice(float material_mass,float mass_price)
{
	float final_material_price = material_mass * mass_price;
	
	return final_material_price;
}




