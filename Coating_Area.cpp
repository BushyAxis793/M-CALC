#include "Coating_Area.h"


//Obliczanie kosztu pow³oki

//Anodowanie
float Coating_Area::CalculateAnodizingCost(float surface_area, float anodizing_cost)
{
    
     float anodizig_final_Cost = surface_area*anodizing_cost;
     
     return anodizig_final_Cost;
}

//Cynkowanie
float Coating_Area::CalculateGalvanizingCost(float material_mass,float galvanizing_cost)
{
	float galvanizing_final_cost = material_mass * galvanizing_cost;
	
	return galvanizing_final_cost;
}

//Hartowanie
float Coating_Area::CalculateHardeningCost(float material_mass,float hardening_cost)
{
	float hardening_final_cost = material_mass * hardening_cost;
	
	return hardening_final_cost;
}

//Czernienie
float Coating_Area::CalculateBlackeningCost(float material_mass,float blackening_cost)
{
	float blackening_final_cost = material_mass * blackening_cost;
	
	return blackening_final_cost;
}

//Nawêglanie
float Coating_Area::CalculateCarburizingCost(float material_mass,float carburizing_cost)
{
	return 0;///Brak danych wymaganych do napisania algorytmu
}
