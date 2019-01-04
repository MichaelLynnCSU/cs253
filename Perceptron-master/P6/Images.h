#include "Histogram.h"

enum ClusteringAlgorithm {
	NORM_HISTOGRAM,
	NORM_HISTOGRAM_QUADRANTS,
	INVERSE_DIFFERENCE
};

class Images
{
public:
	Images();
	ClusteringAlgorithm _clusteringAlgorithm;
	int LoadHistogram(string file, ClusteringAlgorithm _algorithm);
	void GenerateBin();
	double Compare(const Images & _image);
	void Copy(const Images & _image);
	void Add(const Images & _image);
	void Average(unsigned int denominator);
	void SetFileName(string Filename);
	string GetFileName();
	vector<Histogram> getHistogram();



private:
	int _width, _height;
	int _depth;	 
	string _fileName;
	int *_pixels; // dynamic array, Size is not known at compile time
	int *_quadrantPixels[4];  // partially dynamic array and static array
	double _size, _quadrantSize;
    std::vector<Histogram> _histogram;
	

	};

