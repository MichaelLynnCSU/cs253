# Overview
This program does two things. First, it uses the training images (i.e. the images listed in the
first argument file) to train perceptrons, similar to PA8. You will train one perceptron for every
class label in the training set. In other words, if all the training samples are from class1 or class2,
you will train 2 perceptrons, one for each class. If the training samples divide into class1, class 2
and class 3, then you will train 3 perceptrons, and so on. Note: it is an error if there are not at least
two classes in the training data. You will train each perceptron for 100 epochs.
Once it has trained the perceptrons, your program will cluster the images in the test set into K
clusters using these perceptrons. In particular, assume that the training data has N classes, and
that therefore your program has trained N perceptrons. 

Using a similarity measure, your program should use agglomerative clustering (i.e. the
clustering algorithm from PA6 and PA7) to cluster the test images into K clusters.

## Usage
program will take three arguments. The first is the training set, expressed as a file of
depth image file names. The second is the test set, also expressed as a file of (usually different)
depth image names. The third argument is K, the number of clusters for your program to make.
(K, as in PA7, must be an integer greater than zero.)
