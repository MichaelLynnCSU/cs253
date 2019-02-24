#ifndef Histogram_H_
#define Histogram_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
//#include "vld.h"
using namespace std;


class Histogram {
public:
	Histogram();

	int GenerateBuckets(int *_pixels, int size);
	void Normalize();
	double Compare(const Histogram & _histogram);
	void Display();

	void Add(Histogram _histogram);  // Used for AverageCluster
	void Copy(Histogram _histogram);	 // Used for AverageCluster
	void Average(unsigned int denominator);	 // Used for AverageCluster
	double GetNormilizedElement(int index);	 // Used for Perceptron


private:
	int _buckets[64];
	double _normalizedBuckets[64];
	double _numPixels;
};

#endif /* OK_H_ */
