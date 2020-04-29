#include "ShadowRemover.h"
#include <cstdio>
#include <ctime>

using namespace std;

int main(int argc, char** argv) {

	// Check input
	if (argc != 3) {
		cout << "Usage: DocumentShadowRemoval.exe InputLocation OutputLocation" << endl; 
		getchar();
		return -1;
	}

	// Start timer
	clock_t start;
	double duration;
	start = clock();

	// Remove shadow
	ShadowRemover* sr = new ShadowRemover(argv[1]);
	sr->RemoveShadow(argv[2]);

	// Report timing
	duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	cout << "Total Time: " << duration << " sec" << endl << endl << endl;
	sr->SaveTiming((float) duration, argv[2]);
	delete sr;

	return 0;

}

