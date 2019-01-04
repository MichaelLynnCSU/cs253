#include "Images.h"

Images::Images()
{
	_width = 0;
	_height = 0;
	_depth = 0;
	_pixels = nullptr;
	for (int i = 0; i < 4; ++i) {
		_quadrantPixels[i] = nullptr;
	}


}


int Images::LoadHistogram(string file, ClusteringAlgorithm _algorithm)
{
	_clusteringAlgorithm = _algorithm;
//	cout << GetFileName() << endl;
	ifstream filopen(file);

	if (filopen.fail()) {
		cerr << "cannot find file" << endl;
		return -1;
	}
	else if (filopen.peek() == std::ifstream::traits_type::eof()) {
		std::cout << "Need at least one value" << endl;
		return -1;
	}

	char header = filopen.get();
	if (!(header == 'P')) {
		cerr << "invalid header";
		return -1;
	}

	char header2 = filopen.get();
	if (!(header2 == '2')) {
		cerr << "invalid header";
		return -1;
	}

	if (!(filopen >> _width)) {
		cerr << "invalid value";
		return -1;
	}
	if (!(filopen >> _height)) {
		cerr << "invalid value";
		return -1;
	}
	if (!(filopen >> _depth)) {
		cerr << "invalid value";
		return -1;
	}


	Histogram histogram;

	switch (_clusteringAlgorithm) {
	case ClusteringAlgorithm::NORM_HISTOGRAM:
	case ClusteringAlgorithm::INVERSE_DIFFERENCE:
		
		_histogram.push_back(histogram);
		//Read and store the pixels.
		_size = _width * _height;
		 _pixels = new int[_size];

	for (int i = 0; i < _size; ++i) {
		filopen >> _pixels[i];
		//	printf("Pixel:%i\n", _pixels[i]);
	}

	break;
	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS:
	{
		
		//Initalize the vector
		for (unsigned int i = 0; i < 4; ++i) {
			_histogram.push_back(histogram);
		}

		//Calculate Quarant Size
		 int _quadrantWidth = _width / 2;
		 int _quadrantHeight = _height / 2;
		_quadrantSize = _quadrantWidth * _quadrantHeight;

		//Initialize quadrants
		for ( int i = 0; i < 4; ++i) {
			_quadrantPixels[i] = new int[_quadrantSize];
		}
	
		

		//Go thru all the pixels and asign them to the corresponding quadrants.
		int i = 0, j = 0, k = 0, r = 0;
		for ( int x = 0; x < _width; ++x) {
			for ( int y = 0; y < _height; ++y) {
				if (x < _quadrantWidth) {
					if (y < _quadrantHeight) {
						//Array 1
						filopen >> _quadrantPixels[0][i++];
					}
					else {
						//Array 3
						filopen >> _quadrantPixels[2][j++];
					}
				}
				else {
					if (y < _quadrantHeight) {
						//Array2
						filopen >> _quadrantPixels[1][k++];
					}
					else {
						//Array4
						filopen >> _quadrantPixels[3][r++];
					}
				}
			}
		}
	}
	break;
	}



	filopen.close();
	return 1;
}

void Images::GenerateBin() {

	switch (_clusteringAlgorithm) {
	case ClusteringAlgorithm::NORM_HISTOGRAM:
		//Generate the buckets
		_histogram[0].GenerateBuckets(_pixels, _size);

		//Normalize them
		_histogram[0].Normalize();
		break;

	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS:
		for (unsigned int i = 0; i < 4; ++i) {
			_histogram[i].GenerateBuckets(_quadrantPixels[i], _quadrantSize);
			_histogram[i].Normalize();
		}
		break;
	}

}

double Images::Compare(const Images & _image)
{
	double result = 0;
	for (unsigned int i = 0; i < _size; ++i) {
		float diff = _pixels[i] - _image._pixels[i];
		result += (diff * diff);
	}

	result = 1 / (result + 1);
	return result;
}

void Images::Copy(const Images & _image) {
	_fileName = _image._fileName;
	_pixels = _image._pixels;
	_size = _image._size;
}

void Images::Add(const Images & _image) {
	for (unsigned int i = 0; i < _size; ++i) {
		_pixels[i] += _image._pixels[i];
	}
}

void Images::Average(unsigned int denominator) {
	for (unsigned int i = 0; i < _size; ++i) {
		_pixels[i] /= denominator;
	}
}

void Images::SetFileName(string Filename)
{
	_fileName = Filename;
}

string Images::GetFileName()
{
	return _fileName;
}

vector<Histogram> Images::getHistogram()
{
	return _histogram;
}


