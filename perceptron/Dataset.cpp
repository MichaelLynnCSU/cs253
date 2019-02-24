#include "Dataset.h"



Dataset::Dataset()
{
}


int Dataset::LoadCluster(ifstream & file, ClusteringAlgorithm _algorithm, string path)
{


	while (!file.eof()) {
		string fileName = "";
		getline(file, fileName);

		fileName.erase(std::remove(fileName.begin(), fileName.end(), ' '), fileName.end());
		Cluster _cluster;	// outside loop to prevent constructor/deconstructor getting called everytime	
		_cluster.LoadImage(fileName, _algorithm, path);
		_clusters.push_back(_cluster);
	}

	return 1;
}

int Dataset::ClusterSize()
{
	return _clusters.size();
}



void Dataset::GeneratePerceptrons()
{
	std::set<string> UniqueID;                           // empty set of strings
	int numFiles = _clusters.size(); // Or something else that gets the size
	for (int j = 0; j < numFiles; ++j)
	{
		UniqueID.insert(_clusters[j].getImages()[0].GetFileName().substr(0, 6));
	}


	for (const string &ID : UniqueID) {
		Perceptron _perceptron;  // 4 class perceptron cases
		string target = ID; // Target class 1
		string source = " ";  // Source
		for (int i = 0; i < 100; i++) {  // N = 100	
			for (int j = 0; j < _clusters.size(); j++) {
				source = _clusters[j].getImages()[0].GetFileName().substr(0, 6);
				_perceptron.train(target, _clusters[j].GetClusterAverage(), source);
			}
		}
		_perceptrons.push_back(_perceptron);
		_perceptron.DisplayWeights();
		cout << endl << endl;
	}
}


int Dataset::AgglomerativeClustering(int ClusterSize, int Target, vector<Perceptron> _perceptrons)
{

	//Check to see if were done. If not call this function Recursivly.
	if (ClusterSize == Target) { // base case
		return 1; // done clustering
	}
	else {
		//The highest value of the compare.
		double value = 0;
		double epsilon = numeric_limits<double>::min();
		double difference = 0.0;
		double squared = 0.0;
		double eps = 0.0;
		//When you find a new highest value save I and J as the clusters.
		unsigned int closest[2] = { 0,0 };
		for (unsigned int i = 0; i < _clusters.size(); ++i) {
			for (unsigned int j = 0; j < _clusters.size(); ++j) {
				if (i == j) {
					continue;
				}
				double temp = 0.0;
				//	cout << _clusters[j].GetImageNames();
				for (unsigned int p = 0; p < _perceptrons.size(); ++p) {
					difference = (_clusters[i]._perceptronIndex[p] - _clusters[j]._perceptronIndex[p]);
					squared = pow(difference, 2);
					eps = squared + epsilon;
					temp += (1 / eps);

				}
				// temp = _clusters[i].Compare(_clusters[j]);

				/*printf("Cluster(%i, %i):", i, j);
				std::cout << temp << std::endl;*/
				if (temp > value) {
					// _clusters[i].DisplayClusters();
					// _clusters[j].DisplayClusters();
					//cout << temp << endl;
					value = temp;
					closest[0] = i;
					closest[1] = j;
				}
			}
		}

		//Merge the closest clusters.
		_clusters[closest[0]].Merge(_clusters[closest[1]]);

		//Delete the second cluster.
		_clusters.erase(_clusters.begin() + closest[1]);

		// recompute cluster perceptrons evaluations
		RetrainCluster(_perceptrons, _clusters[closest[0]]);
		double sum = 0;
		for (unsigned int i = 0; i < _clusters.size(); ++i) {
			_clusters[i].DisplayClusters();
			//	sum += _clusters[i].GenerateClusterQuality();
				// cluster returns the count of the most occurring class for a cluster
		}
		cout << "simialarity: " << value << endl;
		//	cout << "quality: " << (sum/7) << endl;
		printf("\n\n");

		AgglomerativeClustering(ClusterSize - 1, Target, _perceptrons);
		return -1;
	}
}



vector<Perceptron> Dataset::getPrecptrons()
{
	return _perceptrons;
}

void Dataset::TrainClusters(vector<Perceptron> _perceptrons)
{
	for (int i = 0; i < _clusters.size(); i++) {
		for (int j = 0; j < _perceptrons.size(); j++) {
			_clusters[i]._perceptronIndex[j] = _perceptrons[j].evaluate(_clusters[i].GetClusterAverage());
		}
	}

}

void Dataset::RetrainCluster(vector<Perceptron> _perceptrons, Cluster & _cluster)
{
	for (int j = 0; j < _perceptrons.size(); j++) {
		_cluster._perceptronIndex[j] = _perceptrons[j].evaluate(_cluster.GetClusterAverage());
	}


}

