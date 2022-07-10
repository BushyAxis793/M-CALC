#include "Surface_Area.h"

//Obliczanie pola powierchni materia³u  - definicje

//prêt okr¹g³y
float Surface_Area::CalculateRoundRod(float diameterOut,float length)
{

    float r = diameterOut/2;
    float l = length;
    float circleSurfaceArea, sideSurface, finalSurfaceArea = 0;
    
    circleSurfaceArea = M_PI*pow(r,2);
    
    sideSurface = 2*M_PI*r*l;
    
    finalSurfaceArea = 2*circleSurfaceArea + sideSurface;

//    std::cout<<finalSurfaceArea<<std::endl;

    return finalSurfaceArea/10000;

}

//rura okr¹g³a
float Surface_Area::CalculateRoundPipe(float diameterOut,float Wallthickness,float length)
{
    float r_out = diameterOut/2;
    float b = Wallthickness;
    float l = length;
    float diameter_in = diameterOut-2*b;
    float r_in = diameter_in/2;
    
    float circleSurfaceAreaOut, sideSurfaceOut,finalSurfaceAreaOut,
    circleSurfaceAreaIn,sideSurfaceIn,finalSurfaceAreaIn,
    finalSurfaceArea = 0;
    
    circleSurfaceAreaOut = M_PI*pow(r_out,2);
    
    sideSurfaceOut = 2*M_PI*r_out*l;
    
    circleSurfaceAreaIn = M_PI*pow(r_in,2);
    
    sideSurfaceIn = 2*M_PI*r_in*l;
    
    finalSurfaceAreaOut = 2*circleSurfaceAreaOut + sideSurfaceOut;
    
    finalSurfaceAreaIn = 2*circleSurfaceAreaIn + sideSurfaceIn;
    
    finalSurfaceArea = finalSurfaceAreaOut - finalSurfaceAreaIn;
    
    return finalSurfaceArea/10000;
    
}

//prêt szeœciok¹tny
float Surface_Area::CalculateHexagonalRod(float height, float length)
{
    float h = height;
    //float l = length;
    float side;
    float finalSurfaceArea;
    
    side = h/sqrt(3);
    
    finalSurfaceArea = (3*pow(side,2)*sqrt(3))/2;
    
    return finalSurfaceArea/10000;
}

//rura szeœciok¹tna
float Surface_Area::CalculateHexagonalPipe(float height,float diameterIn,float length)
{
    float h = height;
    float r_in = diameterIn/2;
    float l = length;
    float circleSurfaceArea, sodeSurface, finalSurfaceAreaIn,finalSurfaceAreaOut,finalSurfaceArea;
    
    
    circleSurfaceArea = M_PI*pow(r_in,2);
    
    sodeSurface = 2*M_PI*r_in*l;
    
    finalSurfaceAreaIn = 2*circleSurfaceArea + sodeSurface;
    
    finalSurfaceAreaOut =  CalculateHexagonalRod(h,l);
    
    finalSurfaceArea = finalSurfaceAreaOut - finalSurfaceAreaIn;
    
    return finalSurfaceArea/10000;
    
}

//prêt kwadratowy
float Surface_Area::CalculateSquareRod(float side,float length)
{
    float a = side;
    float l = length;
    float sideSurface,squareSurface,finalSurfaceArea = 0;
    
    squareSurface = 2*pow(a,2);
    
    sideSurface = (a*l)*4;
    
    finalSurfaceArea = squareSurface + sideSurface;
    
    return finalSurfaceArea/10000;
}

//blacha/plaskownik
float Surface_Area::CalculatePlate(float thickness,float width,float length)
{
    float a = width;
    float b = thickness;
    float c = length;
    float finalSurfaceArea;
    
    finalSurfaceArea = 2*a*b+2*a*c+2*b*c;
    
    return finalSurfaceArea/10000;
}

//profil kwadratowy
float Surface_Area::CalculateSquareProfile(float height,float width,float wallThickness,float length)
{
    float a = height;
    float b = width;
    float c = wallThickness;
    float l = length;
    float a_in = a-c*2;
    float b_in = b-c*2;
    float finalSurfaceAreaOut,finalSurfaceAreaIn,finalSurfaceArea = 0;
    
    finalSurfaceAreaOut = 2*a*b+2*a*l+2*b*l;
    
    finalSurfaceAreaIn = 2*a_in*b_in+2*a_in*l+2*b_in*l;
    
    finalSurfaceArea = finalSurfaceAreaOut- finalSurfaceAreaIn;
    
    return finalSurfaceArea/10000;
}

//k¹townik
float Surface_Area::CalculateAngleProfile(float height,float width,float wallThickness,float length)
{
	float a = height;
    float b = width;
    float c = wallThickness;
    float l = length;
    float finalSurfaceArea_1,finalSurfaceArea_2,finalSurfaceArea = 0;
    
    finalSurfaceArea_1 = 2*a*c+2*a*l+2*c*l;
    
    finalSurfaceArea_2 = 2*(b-c)*c+2*(b-c)*l+2*c*l;
    
    finalSurfaceArea = finalSurfaceArea_1 + finalSurfaceArea_2;
    
    return finalSurfaceArea/10000;

}

//ceownik
float Surface_Area::CalculateCProfile(float height,float width,float wallThickness,float length)
{
    float a = height;
    float b = width;
    float c = wallThickness;
    float l = length;
    float finalSurfaceArea_1,finalSurfaceArea_2,finalSurfaceArea = 0;
    
    finalSurfaceArea_1 = 2*a*c+2*a*l+2*c*l;
    
    finalSurfaceArea_2 = 2*(b-c)*c+2*(b-c)*l+2*c*l;
    
    finalSurfaceArea = finalSurfaceArea_1 + 2*finalSurfaceArea_2;
    
    return finalSurfaceArea/10000;
}

//teownik
float Surface_Area::CalculateTProfile(float height,float width,float wallThickness,float length)
{
	float a = height;
    float b = width;
    float c = wallThickness;
    float l = length;
    float finalSurfaceArea_1,finalSurfaceArea_2,finalSurfaceArea = 0;
    
    finalSurfaceArea_1 = 2*a*c+2*a*l+2*c*l;
    
    finalSurfaceArea_2 = 2*(b-c)*c+2*(b-c)*l+2*c*l;
    
    finalSurfaceArea = finalSurfaceArea_1 + finalSurfaceArea_2;
    
    return finalSurfaceArea/10000;
}

//dwuteownik
float Surface_Area::Calculate2TProfile(float height,float width,float wallThickness,float length)
{
    float a = height;
    float b = width;
    float c = wallThickness;
    float l = length;
    float finalSurfaceArea_1,finalSurfaceArea_2,finalSurfaceArea = 0;
    
    finalSurfaceArea_1 = 2*a*c+2*a*l+2*c*l;
    
    finalSurfaceArea_2 = 2*(b-c)*c+2*(b-c)*l+2*c*l;
    
    finalSurfaceArea = finalSurfaceArea_1 + 2*finalSurfaceArea_2;
    
    return finalSurfaceArea/10000;
}

void Surface_Area::SetMaterialSurfaceArea(float surfaceArea)
{
    materialSurfaceArea = surfaceArea;
}

float Surface_Area::GetMaterialSurfaceArea() const
{
    return materialSurfaceArea;
}
