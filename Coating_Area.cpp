#include "Coating_Area.h"


//Obliczanie kosztu pow³oki

//Anodowanie
float Coating_Area::CalculateAnodizingCost(float &surfaceArea, float &anodizingCost)
{
    
     float anodizingFinalCost = surfaceArea*anodizingCost;
     
     return anodizingFinalCost;
}

//Cynkowanie
float Coating_Area::CalculateGalvanizingCost(float &materialMass,float &galvanizingCost)
{
    float galvanizingFinalCost = materialMass * galvanizingCost;
	
    return galvanizingFinalCost;
}

//Hartowanie
float Coating_Area::CalculateHardeningCost(float &materialMass,float &harderingCost)
{
    float harderingFinalCost = materialMass * harderingCost;
	
    return harderingFinalCost;
}

//Czernienie
float Coating_Area::CalculateBlackeningCost(float &materialMass,float &blackeningCost)
{
    float blackeningFinalCost = materialMass * blackeningCost;
	
    return blackeningFinalCost;
}

//Nawêglanie
float Coating_Area::CalculateCarburizingCost(float &material_mass,float &carburizing_cost)
{
	return 0;///Brak danych wymaganych do napisania algorytmu
}
