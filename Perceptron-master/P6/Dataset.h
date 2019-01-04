#include "Cluster.h"

class Dataset
{
public:
	Dataset();

	int LoadCluster(ifstream& file, ClusteringAlgorithm _algorithm);
	int ClusterSize();
	int AgglomerativeClustering(int ClusterSize, int Target);

private:
	std::vector<Cluster> _clusters;
};

