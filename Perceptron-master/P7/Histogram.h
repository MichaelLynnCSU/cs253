#ifndef Histogram_H_
#define Histogram_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;


class Histogram {
public:
	Histogram();

	int GenerateBuckets(int *_pixels, int size);
	void Normalize();
	double Compare(const Histogram & _histogram);
	void Display();

	void Add(Histogram _histogram);
	void Copy(Histogram _histogram);

	void Average(unsigned int denominator);


private:
	
	int _buckets[64];
	double _normalizedBuckets[64];
	double _numPixels;
};

#endif /* OK_H_ */
