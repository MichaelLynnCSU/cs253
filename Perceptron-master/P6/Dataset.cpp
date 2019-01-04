#include "Dataset.h"



Dataset::Dataset()
{
}


int Dataset::LoadCluster(ifstream & file, ClusteringAlgorithm _algorithm)
{

	while (!file.eof()){
	string fileName = "";
	getline(file, fileName);
	fileName.erase(std::remove(fileName.begin(), fileName.end(), ' '), fileName.end());
		 Cluster _cluster;	
		_cluster.LoadImage(fileName, _algorithm);
		_clusters.push_back(_cluster);
	}
		
	return 1;
}

int Dataset::ClusterSize()
{
	return _clusters.size();
}

int Dataset::AgglomerativeClustering(int ClusterSize, int Target)
{	
	//Check to see if were done. If not call this function Recursivly.
	if (ClusterSize == Target) { // base case
		return 1; // done clustering
	}
	else {
		//The highest value of the compare.
		double value = 0;
		
		//When you find a new highest value save I and J as the clusters.
		unsigned int closest[2] = { 0,0 };
		for (unsigned int i = 0; i < _clusters.size(); ++i) {
			for (unsigned int j = 0; j < _clusters.size(); ++j) {
				if (i == j) {
					continue;
				}
			//	cout << _clusters[j].GetImageNames();
				double temp = _clusters[i].Compare(_clusters[j]);
		
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
		
		for (unsigned int i = 0; i < _clusters.size(); ++i) {
			_clusters[i].DisplayClusters();
		}
		cout << value << endl;
		printf("\n\n");
	   	
		AgglomerativeClustering(ClusterSize - 1, Target);
		return -1;
	}
}

