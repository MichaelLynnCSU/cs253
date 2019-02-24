#include "Cluster.h"




Cluster::Cluster()
{
	for (int i = 0; i < 3; ++i) {
		_perceptronIndex[i] = 0;
	}
}



void Cluster::LoadImage(string file, ClusteringAlgorithm _algorithm, string path)
{
	_clusteringAlgorithm = _algorithm;

	Images _image;

	_image.SetFileName(file);
	//	cout << input << endl;	

		// Load Histsograms with pixels
	_image.LoadHistogram(file, _algorithm, path);

	// Normialize histograms
	_image.GenerateBin();

	_images.push_back(_image);


	Histogram histogram;

	switch (_algorithm) {
	case ClusteringAlgorithm::NORM_HISTOGRAM:
		_clusterAverage.push_back(histogram);
		// Initialize _clusterAverage
		_clusterAverage[0].Copy(_image.getHistogram()[0]);

		break;
	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS:
		for (unsigned int i = 0; i < 4; ++i) {
			_clusterAverage.push_back(histogram);
			// Initialize _clusterAverage
			_clusterAverage[i].Copy(_image.getHistogram()[i]);
		}
		break;
	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS_Tri:
		for (unsigned int i = 0; i < 9; ++i) {
			_clusterAverage.push_back(histogram);
			// Initialize _clusterAverage normilized buckets
			_clusterAverage[i].Copy(_image.getHistogram()[i]);
		}
		break;
	case ClusteringAlgorithm::INVERSE_DIFFERENCE:
		GenerateImage();
		break;
	}
}

double Cluster::Compare(Cluster &_cluster)
{

	switch (_clusteringAlgorithm) {
	case ClusteringAlgorithm::NORM_HISTOGRAM:
	{
		double result = 0;
		result = _clusterAverage[0].Compare(_cluster._clusterAverage[0]);
		return result;
	}
	break;

	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS:
	{
		//Loop thru the array of _histograms. And compare all quadrants get results.
		//Return the average of the results.
		double result = 0;
		/*	cout << "compared clusterd: " << endl;
			DisplayClusters();
			_cluster.DisplayClusters();*/

		for (int i = 0; i < 4; ++i) {
			result += _clusterAverage[i].Compare(_cluster._clusterAverage[i]);
		}

		//cout << "result: " << result << endl;
		//cout << "End: " << endl;
		return result / 4;
	}
	break;
	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS_Tri:
	{
		//Loop thru the array of _histograms. And compare all quadrants get results.
		//Return the average of the results.
		double result = 0;


		/*	cout << "compared clusterd: " << endl;
		DisplayClusters();
		_cluster.DisplayClusters();*/

		for (int i = 0; i < 9; ++i) {
			result += _clusterAverage[i].Compare(_cluster._clusterAverage[i]);
		}

		//cout << "result: " << result << endl;
		//cout << "End: " << endl;
		return result / 9;
	}
	break;
	case ClusteringAlgorithm::INVERSE_DIFFERENCE:
		unsigned int _imgCount = _images.size();
		double _imgResult = 0;
		double _tempResult;
		for (unsigned int i = 0; i < _imgCount; ++i) {
			_tempResult = 0;
			for (unsigned int j = 0; j < _cluster._images.size(); ++j) {
				_tempResult += _images[i].Compare(_cluster._images[j]);
			}
			_tempResult /= _cluster._images.size();
			_imgResult += _tempResult;
		}
		_imgResult /= _imgCount;
		return _imgResult;
		break;
	}

}

void Cluster::Merge(const Cluster &_cluster)
{
	// merge clusters
	for (int i = 0; i < _cluster._images.size(); ++i) {
		_images.push_back(_cluster._images[i]);
	}

	switch (_clusteringAlgorithm) {
	case ClusteringAlgorithm::NORM_HISTOGRAM:
	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS:
		// recalculate _clusterAverage.
		GenerateHistogram();
		break;
	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS_Tri:
		// recalculate _clusterAverage.
		GenerateHistogram();
		break;
	case ClusteringAlgorithm::INVERSE_DIFFERENCE:
		GenerateImage();
		break;
	}


}

void Cluster::GenerateHistogram() {
	//Creates the average histogram of the (this) Cluster of all the images.
	for (int i = 0; i < _clusterAverage.size(); ++i) {
		for (int j = 1; j < _images.size(); ++j) {
			// skip initialized image and add corrasponding normilized buckets together
			_clusterAverage[i].Add(_images[j].getHistogram()[i]);
		}
		_clusterAverage[i].Average(_images.size());
	}


}

void Cluster::DisplayClusters()
{
	printf("Cluster: ");
	for (unsigned int i = 0; i < _images.size(); i++) {
		cout << _images[i].GetFileName();
		printf("  ");
	}
	printf("\n");
}

int Cluster::GenerateClusterQuality()
{
	//To measure the quality of the complete clustering, sum the number of images that match the dominant categories of their clusters across all the clusters, 
	// divide this number by the total number of images.A perfect clustering will get a score of 1.0.
	int index[100];
	vector<string> _names;
	for (unsigned int i = 0; i < _images.size(); i++) {
		_names.push_back(_images[i].GetFileName().substr(0, 6));
		index[i] = 1;
	}

	for (unsigned int i = 0; i < _images.size(); i++) {
		for (unsigned int j = 0; j < _images.size(); j++) {
			if (_names[i] == _names[j] && i != j) {
				index[i]++;
			}
		}
	}
	int largest = 0;
	for (int i = 0; i < sizeof(index) / sizeof(index[0]); i++) {
		if (index[i] > largest) {
			largest = index[i];
		}
	}

	return largest;
}

vector<Images> Cluster::getImages()
{
	return _images;
}


void Cluster::GenerateImage() { // case this back and reuse the pre existing add.copy, average using enum, this is redundent, Merge call
	_clusterImage.Copy(_images[0]);
	for (unsigned int i = 1; i < _images.size(); ++i) {
		_clusterImage.Add(_images[i]);
	}
	_clusterImage.Average(_images.size());
}

vector<Histogram> Cluster::GetClusterAverage()
{
	return _clusterAverage;
}




