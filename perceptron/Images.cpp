#include "Images.h"

Images::Images()
{
	_width = 0;
	_height = 0;
	_depth = 0;
	_pixels = nullptr;
	for (unsigned int i = 0; i < 4; ++i) {
		_quadrantPixels[i] = nullptr;	// Set to null until 2nd size it known
	}
	for (unsigned int i = 0; i < 9; ++i) {
		_triPixels[i] = nullptr;	// Set to null until 2nd size it known
		_index[9] = 0;
	}


}




int Images::LoadHistogram(string file, ClusteringAlgorithm _algorithm, string path)
{
	_clusteringAlgorithm = _algorithm;
	//	cout << GetFileName() << endl;
	ifstream filopen(path + file);

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

	int count = 0;
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
			_index[0]++;
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
		for (int i = 0; i < 4; ++i) {
			_quadrantPixels[i] = new  int[_quadrantSize];
		}

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < _quadrantSize; j++)
				_quadrantPixels[i][j] = 0;


		//Go thru all the pixels and asign them to the corresponding quadrants.

		for (int x = 0; x < _width; ++x) {
			for (int y = 0; y < _height; ++y) {

				if (x < _quadrantWidth) {
					if (y < _quadrantHeight) {
						//Array 1 (x,y) within 64x64
						filopen >> _quadrantPixels[0][_index[0]];
						_index[0]++;
					}
					else {
						//Array 3 (x,y) within 64x128
						filopen >> _quadrantPixels[2][_index[2]];
						_index[2]++;
					}
				}

				else {
					if (y < _quadrantHeight) {
						//Array2 (x,y) within 128x64
						filopen >> _quadrantPixels[1][_index[1]];
						_index[1]++;
					}
					else {
						//Array4 (x,y) within 128x128
						filopen >> _quadrantPixels[3][_index[3]];
						_index[3]++;
					}
				}
			}
		}
	}
	break;
	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS_Tri:
	{
		//Initalize the vector
		for (unsigned int i = 0; i < 9; ++i) {
			_histogram.push_back(histogram);
		}

		//Calculate Quarant Size
		int _quadrantWidth = ceil(_width / 3.0);
		int _quadrantHeight = ceil(_height / 3.0);


		_quadrantSize = (_quadrantWidth) * (_quadrantHeight); // 43x43

		//Initialize quadrants
		for (int i = 0; i < 9; ++i) {
			_triPixels[i] = new  int[_quadrantSize];
		}

		for (int i = 0; i < 9; i++)
			for (int j = 0; j < _quadrantSize; j++)
				_triPixels[i][j] = 0;


		// Splits 0-42, 43-85, 86-127
			//Go thru all the pixels and asign them to the corresponding quadrants.

		for (int x = 0; x < _width; ++x) {
			for (int y = 0; y < _height; ++y) {
				if (x < _quadrantWidth) {
					if (y < _quadrantHeight) {
						//Array 1 (x,y) within 42x42
						filopen >> _triPixels[0][_index[0]];
						_index[0]++;

					}
					else if (y > _quadrantHeight && y < (_quadrantHeight * 2 + 1)) {
						//Array 4 (x,y) within 42x85
						filopen >> _triPixels[3][_index[3]];
						_index[3]++;
					}
					else {
						//Array 7 (x,y) within 42x127
						filopen >> _triPixels[6][_index[6]];
						_index[6]++;
					}
				}
				else if (x > _quadrantWidth && x < (_quadrantWidth * 2 + 1)) {
					if (y < _quadrantHeight) {
						//Array 2 (x,y) within 85x42
						filopen >> _triPixels[1][_index[1]];
						_index[1]++;
					}
					else if (y > _quadrantHeight && y < (_quadrantHeight * 2 + 1)) {
						//Array 5 (x,y) within 85x85
						filopen >> _triPixels[4][_index[4]];
						_index[4]++;
					}
					else {
						////Array 8 (x,y) within 85x127
						filopen >> _triPixels[7][_index[7]];
						_index[7]++;
					}
				}
				else
				{
					if (y < _quadrantHeight) {
						//Array 3 (x,y) within 127x42
						filopen >> _triPixels[2][_index[2]];
						_index[2]++;
					}
					else if (y > _quadrantHeight && y < (_quadrantHeight * 2 + 1)) {
						//Array 6 (x,y) within 127x85
						filopen >> _triPixels[5][_index[5]];
						_index[5]++;
					}
					else
					{
						//	//Array 9 (x,y) within 127x127
						filopen >> _triPixels[8][_index[8]];
						_index[8]++;

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
		_histogram[0].GenerateBuckets(_pixels, _index[0]);

		//Normalize them
		_histogram[0].Normalize();
		break;

	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS:
		for (unsigned int i = 0; i < 4; ++i) {
			_histogram[i].GenerateBuckets(_quadrantPixels[i], _index[i]);
			_histogram[i].Normalize();
		}
		break;
	case ClusteringAlgorithm::NORM_HISTOGRAM_QUADRANTS_Tri:
		for (unsigned int i = 0; i < 9; ++i) {
			_histogram[i].GenerateBuckets(_triPixels[i], _index[i]);
			_histogram[i].Normalize();
		}
		break;
	}

}

double Images::Compare(const Images & _image)
{
	double result = 0;
	for (unsigned int i = 0; i < _size; i++) {
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
	// return vector of historgrams for "this" object
	return _histogram;
}


