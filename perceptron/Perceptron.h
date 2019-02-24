#include "Histogram.h"

class Perceptron
{
public:
	Perceptron();	
	void train(string _target, vector<Histogram> _clusterAverage, string source);
	double evaluate(vector<Histogram> _clusterAverage);
	void DisplayWeights();
	double bias;
	double weights[64];
private:



};

