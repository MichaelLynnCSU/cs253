#include "Images.h"


class Cluster
{
public:

	Cluster();

	ClusteringAlgorithm _clusteringAlgorithm;
	void LoadImage(string file, ClusteringAlgorithm _algorithm, string path);
	double Compare(Cluster &_cluster);
	void Merge(const Cluster  &_cluster);
	void GenerateHistogram();
	void DisplayClusters();
	int GenerateClusterQuality();
	vector<Images> getImages();
	void GenerateImage();
	vector<Histogram> GetClusterAverage();
	double _perceptronIndex[3];
private:
	std::vector<Images> _images;
	vector<Histogram> _clusterAverage;
	Images _clusterImage;


};

