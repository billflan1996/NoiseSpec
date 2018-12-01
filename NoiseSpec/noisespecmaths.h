#ifndef NOISESPECMATHS_H
#define NOISESPECMATHS_H

/* NoiseSpecMaths:
 * Reusable functions for maths operations.
 */

#include <QObject>
#include <QList>
#include <QVector>
#include <cmath>

int round2(int number); // round up to nearest power of 2

void four1(float * data, unsigned int nn, int isign); // FFT from numerical recipes

QVector<float> PowerFFT(float * data, unsigned int N); // do power FFT, output a vector

void Sort(QList<int> & Data); // Sorting routine (bubble sort)

// Window functions: fracTime is time/maxTime
enum FFTWindow {noWindow, oldWindow, Hanning, Hamming, Blackman};

float NoWindow(float fracTime);
float HannWindow(float fracTime);
float HammingWindow(float fracTime);
float BlackmanWindow(float fracTime);


#endif // NOISESPECMATHS_H
