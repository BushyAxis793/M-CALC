#include "Volume.h"


//Obliczanie objêtoœci materia³u - definicje

//Prêt okr¹g³y
float Volume::CalculateRoundRod(float diameterOut ,float length)
{
    float r = diameterOut/2;
    float l = length;
    float circleSurfaceArea,  finalVolume = 0;
    
    circleSurfaceArea = M_PI*pow(r,2);
    
    finalVolume = circleSurfaceArea*l;
  
    return finalVolume/1000000;
}

//rura okr¹g³a
float Volume::CalculateRoundPipe(float diametrOut,float wallThickness,float length)
{
    float r_out = diametrOut/2;
    float b = wallThickness;
    float l = length;
    float diameter_in = diametrOut-2*b;
    float r_in = diameter_in/2;
    
    float circleSurfaceAreaOut,circleSurfaceAreaIn, volumeOut,volumeIn,finalVolume = 0;
    
    circleSurfaceAreaOut = M_PI*pow(r_out,2);
    
    circleSurfaceAreaIn =  M_PI*pow(r_in,2);
    
    volumeOut = circleSurfaceAreaOut*l;
    
    volumeIn = circleSurfaceAreaIn*l;
    
    finalVolume = volumeOut - volumeIn;
    
    return finalVolume/1000000;
}

//prêt szeœciok¹tny
float Volume::CalculateHexagonalRod(float height, float length)
{
    float h = height;
    float l = length;
    float side = 0;
    float finalVolume;
    
    side = h/sqrt(3);
    
    finalVolume = ((3*pow(side,2)*sqrt(3))/2)*l;
    
    return finalVolume/1000000;
}

//rura szeœciok¹tna
float Volume::CalculateHexagonalPipe(float height,float diameterIn,float length)
{
    float h = height;
    float r_in = diameterIn/2;
    float l = length;
    float circleSurfaceAreaIn, side, volumeIn,volumeOut,finalVolume = 0;
    
   	side = h/sqrt(3);
    
    volumeOut = ((3*pow(side,2)*sqrt(3))/2)*l;
    
    circleSurfaceAreaIn = M_PI*pow(r_in,2);
    
    volumeIn = circleSurfaceAreaIn * l;
    
    finalVolume = volumeOut - volumeIn;
    
    return finalVolume/1000000;
    
}

//prêt kwadratowy
float Volume::CalculateSquareRod(float side,float length)
{
    float a = side;
    float l = length;
    float finalVolume = 0;
    
    finalVolume = pow(a,2)*l;
    
    return finalVolume/1000000;
}

//blacha/plaskownik
float Volume::CalculatePlate(float thickness,float width,float length)
{
    float a = width;
    float b = thickness;
    float c = length;
    float finalVolume = 0;
    
    finalVolume = a*b*c;
    
    return finalVolume/1000000;
}

//profil kwadratowy
float Volume::CalculateSquareProfile(float height,float width,float wallThickness,float length)
{
    float a = height;
    float b = width;
    float c = wallThickness;
    float l = length;
    float a_in = a-c*2;
    float b_in = b-c*2;
    float volumeIn,volumeOut,finalVolume = 0;
    
    volumeOut = a*b*l;
    
    volumeIn = a_in*b_in*l;
    
    finalVolume = volumeOut - volumeIn;
    
    return finalVolume/1000000;
}

//k¹townik
float Volume::CalculateAngleProfile(float height,float width,float wallThickness,float length)
{
	float a = height;
    float b = width;
    float c = wallThickness;
    float l = length;
    float volume_1,volume_2,finalVolume = 0;
    
    volume_1 = a*c*l;
    
    volume_2 = (b-c)*c*l;
    
    finalVolume = volume_1 + volume_2;
    
    return finalVolume/1000000;

}

//ceownik
float Volume::CalculateCProfile(float height,float width,float wallThickness,float length)
{
    float a = height;
    float b = width;
    float c = wallThickness;
    float l = length;
    float volume_1,volume_2,finalVolume = 0;
    
    volume_1 = (b-c)*c*l;
    
    volume_2 = a*c*l;
    
    finalVolume = volume_1*2 + volume_2;
    
    return finalVolume/1000000;
}

//teownik
float Volume::CalculateTProfile(float height,float width,float wallThickness,float length)
{
	float a = height;
    float b = width;
    float c = wallThickness;
    float l = length;
    float volume_1,volume_2,finalVolume = 0;
    
    volume_1 = a*c*l;
    
    volume_2 = (b-c)*c*l;
    
    finalVolume = volume_1 + volume_2;
    
    return finalVolume/1000000;
}

//dwuteownik
float Volume::Calculate2TProfile(float height,float width,float wallThickness,float length)
{
	float a = height;
    float b = width;
    float c = wallThickness;
    float l = length;
    float volume_1,volume_2,finalVolume = 0;
    
    volume_1 = (b-c)*c*l;
    
    volume_2 = a*c*l;
    
    finalVolume = volume_1*2 + volume_2;
    
    return finalVolume/1000000;

}

