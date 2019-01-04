#include "Dataset.h"

int main(int argc, char * argv[]) {
	
	if (argv[1] == NULL) {
		cerr << "Not file argument" << endl;
	}
	string filename = argv[1];
	ifstream file(PATH + filename);	
	
	if (argv[2] == NULL) {
		cerr << "Not file argument" << endl;
	}
	string filename2 = argv[2];
	ifstream file2(PATH2 + filename2);

	//Unlike in PA5, all depth images must be 128x128 pixels. Any other
	//size in an error.
	//	NORM_HISTOGRAM,
	//	NORM_HISTOGRAM_QUADRANTS,
	//	INVERSE_DIFFERENCE,
	//	NORM_HISTOGRAM_QUADRANTS_Tri
	
	Dataset _data;
	_data.LoadCluster(file, ClusteringAlgorithm::NORM_HISTOGRAM, PATH);
	_data.GeneratePerceptrons();
	
	int target = 7; // Recursive cluster target	
	Dataset _data2;
	_data2.LoadCluster(file2, ClusteringAlgorithm::NORM_HISTOGRAM, PATH2);
	_data2.TrainClusters(_data.getPrecptrons());  // perceptrons cluster evaluations
	_data2.AgglomerativeClustering(_data2.ClusterSize(), target, _data.getPrecptrons());


	system("pause");
	return 0;
}

