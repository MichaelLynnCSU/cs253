#include "Cluster.h"



Cluster::Cluster()
{
}


Cluster::~Cluster()
{
}

void Cluster::LoadImage(string file, ClusteringAlgorithm _algorithm)
{
     	_clusteringAlgorithm = _algorithm;

		Images _image;
	
		_image.SetFileName(file);
	//	cout << input << endl;
		_image.LoadHistogram(file, _algorithm);
		_image.GenerateBin();
		_images.push_back(_image);
	
		Histogram histogram;

		switch (_algorithm) {
		case ClusteringAlgorithm::NORM_HISTOGRAM:	
			_clusterAverage.push_back(histogram);
			_clusterAverage[0].Copy(_image.getHistogram()[0]);
			break;
		case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS:
			//Set this histogram to the images histogram.
			for (unsigned int i = 0; i < 4; ++i) {
				_clusterAverage.push_back(histogram);
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
	//DisplayClusters();
	//_cluster.DisplayClusters();

	switch (_clusteringAlgorithm) {
	case ClusteringAlgorithm::NORM_HISTOGRAM:
		return _clusterAverage[0].Compare(_cluster._clusterAverage[0]);
		break;

	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS:
	{
		//Loop thru the array of _histograms. And compare all quadrants get results.
		//Return the average of the results.
		float result = 0;
	//	cout << "compared clusterd: " << endl;
	//	DisplayClusters();
	//	_cluster.DisplayClusters();

		for (unsigned int i = 0; i < 4; ++i) {
			result += _clusterAverage[i].Compare(_cluster._clusterAverage[i]);
		}
		result = result / 4;
		//cout << "result: " << result << endl;
		//cout << "End: " << endl;
		return result;
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
	for (unsigned int i = 0; i < _cluster._images.size(); ++i) {
		_images.push_back(_cluster._images[i]);
	}
	switch (_clusteringAlgorithm) {
	case ClusteringAlgorithm::NORM_HISTOGRAM:
	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS:
		//Making a function after this to recalculate _histogram.
		GenerateHistogram();
		break;
	case ClusteringAlgorithm::INVERSE_DIFFERENCE:
		GenerateImage();
		break;
	}
	

}

void Cluster::GenerateHistogram() {
	//Creates the average histogram of the (this) Cluster of all the images.
	//Populate the initialial
	for (unsigned int i = 0; i < _clusterAverage.size(); ++i) {
		_clusterAverage[i].Copy(_images[0].getHistogram()[i]);
		for (unsigned int j = 1; j < _images.size(); ++j) {
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

void Cluster::GenerateImage() {
	_clusterImage.Copy(_images[0]);
	for (unsigned int i = 1; i < _images.size(); ++i) {
		_clusterImage.Add(_images[i]);
	}
	_clusterImage.Average(_images.size());
}




