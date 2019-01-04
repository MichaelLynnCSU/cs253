#include "Histogram.h"


#define PATH "./perceptron_train/"
#define PATH2 "./perceptron_test/"

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
	int LoadHistogram(string file, ClusteringAlgorithm _algorithm, string path);
	void GenerateBin();
	double Compare(const Images & _image);	// Used for INVERSE_DIFFERENCE
	void Copy(const Images & _image);	// Used for INVERSE_DIFFERENCE
	void Add(const Images & _image);	// Used for INVERSE_DIFFERENCE
	void Average(unsigned int denominator);	// Used for INVERSE_DIFFERENCE

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
	int _index[9];  // each array gets its own index initialed to 0
	double _size, _quadrantSize;
    std::vector<Histogram> _histogram;
	

	};

