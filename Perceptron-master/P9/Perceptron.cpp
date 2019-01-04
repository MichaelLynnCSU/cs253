#include "Perceptron.h"



Perceptron::Perceptron()
{

	for (unsigned int init = 0; init < 64; init++) {
		weights[init] = 0;
	}
	bias = 0;
}




void Perceptron::train(string _target, vector<Histogram> _clusterAverage, string source) {

	double y = 0;
	double d = 0;        // target class condition

	if (_target == source) {
		d = 1;
	}
	else {
		d = -1;
	}

	y = evaluate(_clusterAverage); // N=1, store this value for each image
	for (int j = 0; j < 64; j++) { // Formula
		weights[j] += (d - y) *
			_clusterAverage[0].GetNormilizedElement(j);
	}

	bias += (d - y);



}

double Perceptron::evaluate(vector<Histogram> _clusterAverage)
{

	double sum = 0;

	for (int j = 0; j < 64; j++) {  // Formula
		sum += _clusterAverage[0].GetNormilizedElement(j) * weights[j];

	}
	return sum + bias;

}

void Perceptron::DisplayWeights()
{

	for (int i = 0; i < 64; i++)
		cout << weights[i] << " ";
	cout << bias;
}


