#include "Dataset.h"

int main(int argc, char * argv[]) {
	
	if (argv[1] == NULL) {
		cerr << "Not file argument" << endl;
	}
	ifstream file(argv[1]);
	Dataset _data;
	//Unlike in PA5, all depth images must be 128x128 pixels. Any other
	//size in an error.
	_data.LoadCluster(file, ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS);

	int target = 1;
	int size = _data.ClusterSize();
	if (target > size) {
		cerr << "Not enough images: ";
		return -1;
	}
	

    _data.AgglomerativeClustering(size, target);



	system("pause");
	return 0;
}

