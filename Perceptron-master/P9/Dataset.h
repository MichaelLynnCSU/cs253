#include "Cluster.h"
#include "Perceptron.h"
#include <set>
class Dataset
{
public:
	Dataset();

	int LoadCluster(ifstream& file, ClusteringAlgorithm _algorithm, string path);
	int ClusterSize();
	int AgglomerativeClustering(int ClusterSize, int Target, vector<Perceptron> _perceptrons);
	void GeneratePerceptrons();
	vector<Perceptron> getPrecptrons();
	void TrainClusters(vector<Perceptron> _perceptrons);
	void RetrainCluster(vector<Perceptron> _perceptrons, Cluster  &_cluster);
private:
	std::vector<Cluster> _clusters;
	std::vector<Perceptron> _perceptrons;
};

