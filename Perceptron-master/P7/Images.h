#include "Histogram.h"

enum ClusteringAlgorithm {
	NORM_HISTOGRAM,
	NORM_HISTOGRAM_QUADRANTS,
	INVERSE_DIFFERENCE,
	NORM_HISTOGRAM_QUADRANTS_Tri
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
	int *_pixels; 
    int * _quadrantPixels[4];
	int * _triPixels[9];
    int _index[9] = { 0 };  // each array gets its own index initialed to 0
	double _size, _quadrantSize;
    std::vector<Histogram> _histogram;
	

	};

