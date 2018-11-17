#include "noisegenerator.h"
#include <iostream>

#include <stdlib.h>
#include <math.h>

using namespace std;

NoiseGenerator::NoiseGenerator(){
}

NoiseGenerator::~NoiseGenerator(){
}

float NoiseGenerator::noise(int x, int y, int octave){
    int n = x+y*57;
    n = (n<<13)^n;
    float num = (1.0-((n*(n*n*15731+789221)+1376312589) & 0x7fffffff)/1073741824.0);
    return (num/2)+.5;
}

//returns a weighted averaging of 9 surrounding noise values
float NoiseGenerator::smoothNoise(int x, int y, int octave){
    float corners = (noise(x-1,y-1,octave)+noise(x+1,y-1,octave)+noise(x-1,y+1,octave)+noise(x+1,y+1,octave))/16.;
    float sides = (noise(x-1,y,octave)+noise(x+1,y,octave)+noise(x,y-1,octave)+noise(x,y+1,octave))/8.;
    float center = noise(x,y,octave)/4.;
    return corners+sides+center;
}

float NoiseGenerator::cosineInterpolate(float a, float b, float x){
    float v1 = x*M_PI;
    float v2 = (1 - cos(v1)) * .5;
    return a*(1-v2) + b*v1;
}

float NoiseGenerator::interpolateNoise(float x, float y, int octave){
    //getting values as integers
    int integerX = (int)x;
    float fractionalX = x - integerX;

    int integerY = (int)y;
    float fractionalY = y - integerY;

    //getting the smoothings of 4 values in neighborhood of x,y
    float res1 = smoothNoise(integerX, integerY,octave);
    float res2 = smoothNoise(integerX+1, integerY,octave);
    float res3 = smoothNoise(integerX, integerY+1,octave);
    float res4 = smoothNoise(integerX+1, integerY+1,octave);

    //interpolate between the smoothed values
    float interp1 = cosineInterpolate(res1,res2,fractionalX);
    float interp2 = cosineInterpolate(res3,res4,fractionalX);

    return cosineInterpolate(interp1, interp2, fractionalY);
}


float NoiseGenerator::generateValueNoise2D(float x, float y){
//    float total = 0;
//    //p = persistence
//    float p = .2;

//    //n = number of octaves
//    int numOctaves = 1;

//    for(int i=0; i<numOctaves; i++){
////        float freq = .008;

//        float freq = pow(2,i);
////        float amp = pow(p,i);

//        float amp = .4;

//        total += interpolateNoise(x*freq, y*freq, i)*amp;
//    }
//    return total;

    return ((cos(x*.05)+sin(y*.05)))*.2;

//    return 0;
}


