#include "Histogram.h"

Histogram::Histogram() {
	// TODO Auto-generated constructor stub;
	for (unsigned int init = 0; init < 64; init++) {
		_buckets[init] = 0;
		_normalizedBuckets[init] = 0;
	}

}


int Histogram::GenerateBuckets(int *_pixels, int size) {

	_numPixels = size;
	for (int pixel = 0; pixel < _numPixels; pixel++)
		if (_pixels[pixel] >= 0 && _pixels[pixel] <= 255) { // range check
			int min = 0;  // algorithm
			int max = 0;
			for (unsigned int range = 0; range < 64; range++) { // loop through all ranges
				min = 4 * ((range + 1) - 1);
				max = (4 * (range + 1)) - 1;

				//		cout << endl << min << " to " << max << endl;

				if (_pixels[pixel] >= min && _pixels[pixel] <= max) {
					_buckets[range]++;
				}
			}
		}
		else {
			cerr << "outside of range" << endl;
			return -1;
		}
		return 1;
}




void Histogram::Normalize()
{
	//Go through each bucket and divide by the total number of pixels.
	double total = 0;
	for (unsigned int i = 0; i < 64; ++i) {
		_normalizedBuckets[i] = _buckets[i] / _numPixels;
		total += _normalizedBuckets[i];
	}
}


double Histogram::Compare(const Histogram & _histogram)
{
	double sum = 0;

	for (unsigned int i = 0; i < 64; ++i) {
		sum += min(_normalizedBuckets[i], _histogram._normalizedBuckets[i]);
	}

	return sum;

}

void Histogram::Display() {
	for (unsigned int i = 1; i < 64; i++) { // print
		cout << _normalizedBuckets[i] << " ";
	}
	cout << endl << endl;
}


void Histogram::Add(Histogram _histogram) {
	for (unsigned int i = 0; i < 64; ++i) {
		_normalizedBuckets[i] += _histogram._normalizedBuckets[i];
	}
}

void Histogram::Copy(Histogram _histogram) {
	for (unsigned int i = 0; i < 64; ++i) {
		// Initialize _clusterAverage
		_normalizedBuckets[i] = _histogram._normalizedBuckets[i];
	}
}

void Histogram::Average(unsigned int denominator) {
	for (unsigned int i = 0; i < 64; ++i) {
		// Average each bin by dividing by number of histograms merged into each bin
		_normalizedBuckets[i] /= denominator;
	}
}
