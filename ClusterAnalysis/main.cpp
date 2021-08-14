#include <iostream>
#include <string>

#include "partOne.h"
#include "linkage.h"
#include "kMeans.h"
#include "dunn.h"

using namespace std;

int main() {
	// Print basic group info
	cout << "Project 2 Group 10" << endl;
	cout << "Carlyn Thomsen, Vi Nguyen, Kay Harris" << endl << endl;

	// Use partOne code to read and store all the data/points
	partOne one = partOne();
	cout << "The total number of k values to be tested is " << one.getKClusters().size() << endl;
	cout << "The total number of points in this file is " << one.getPoints().size() << endl;

	// Perform the different clusterings
	cout << endl << "For k-means clustering:" << endl;
	kMeans(one.getPoints(), one.getKClusters(), 0);

	cout << endl << "For centroid-linkage clustering:" << endl;
	Linkage::cluster(one.getPoints());

	cout << endl << "For k-medoid clustering:" << endl;
	kMeans(one.getPoints(), one.getKClusters(), 2);

	// Print final analysis
	cout << endl << "The final analysis shows that:" << endl;
	Dunn::printAnalysis();

	cout << "Complete!" << endl;
	return 0;
}
