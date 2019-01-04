#include "Images.h"

class Cluster
{
public:

	Cluster();
	~Cluster();
	ClusteringAlgorithm _clusteringAlgorithm;
	void LoadImage(string file, ClusteringAlgorithm _algorithm);
	double Compare(Cluster &_cluster);
	void Merge(const Cluster  &_cluster);
	void GenerateHistogram();
	void DisplayClusters();

	void GenerateImage();

private:
std::vector<Images> _images;
vector<Histogram> _clusterAverage;
Images _clusterImage;
};

