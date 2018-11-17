#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

#include "math.h"

class NoiseGenerator
{
public:
    NoiseGenerator();
    ~NoiseGenerator();
    float generateValueNoise2D(float x, float y);
    float noise(int x, int y, int octave);
    float smoothNoise(int x, int y, int octave);
    float interpolateNoise(float x, float y, int octave);
    float cosineInterpolate(float a, float b, float x);

private:

};

#endif // NOISEGENERATOR_H
