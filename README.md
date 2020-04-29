# SOURCE CODE FOR "REMOVING SHADOWS OF IMAGES OF DOCUMENTS"

This package is a C++ implementation of the algorithm described in:

S. Bako, S. Darabi, E. Shechtman, J. Wang, K. Sunkavalli, P. Sen, "Removing Shadows 
from Images of Documents", Asian Conference on Computer Vision (ACCV), Nov. 2016

More information can also be found on the authors' project webpage:
http://cvc.ucsb.edu/graphics/Papers/ACCV2016_DocShadow/

Initial release implementation by Steve Bako, 2016.

-------------------------------------------------------------------------
I. LICENSE CONDITIONS

Copyright (c) 2016.  The Regents of the University of California.  
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted for non-commercial purposes provided that the following conditions 
are met:

1. Redistributions of source code must retain the above copyright notice, this 
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation and/or 
other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors 
may be used to endorse or promote products derived from this software without 
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
OF THE POSSIBILITY OF SUCH DAMAGE.

-------------------------------------------------------------------------
II. OVERVIEW

This algorithm takes in an image of a document containing a shadow and 
outputs a deshadowed image, where the shadow is removed but the color
and tone of the original document is preserved.

The current code expects to find the input image in the "Input" folder 
and will output the result in the "Results" folder. This folder will 
contain the deshadowed output, the shadow map used to generate the 
output (see original paper for details), and the timing in seconds.

The code was written in C++ and tested on Windows 10 64-bit with Visual
Studio 2013 and OpenCV 3.0.0.

-------------------------------------------------------------------------
III. INSTALLATION

1. Download OpenCV 3.0.0 for Windows from the following link:
   http://opencv.org/downloads.html

2. Extract it and put it in the same folder as the "Input" and "Results" folder. 
   Note the Visual Studio project is already set up to look for the "opencv" 
   folder here (i.e., $ROOT\DocumentShadowRemoval\)   

-------------------------------------------------------------------------
IV. RUNNING THE PACKAGE

Requirements: OpenCV 3.0.0 installed (See "Installation" section)

1. Open the solution (DocumentShadowRemoval.sln) in the root folder with Visual 
   Studio 2013.

2. Make sure Visual Studio is in x64 Release mode. Make sure "opencv" is in the
   $ROOT\DocumentShadowRemoval\ directory.
   
3. Run the code through either Visual Studio or the command line using 
   DocumentShadowRemoval.exe in the $ROOT\x64\Release\ folder. The general command 
   line arguments are as follows:
   
   DocumentShadowRemoval.exe input_file output_prefix 
   
   For example, to run the algorithm on the supplied 001.png image in the "Input" 
   folder, the command (from the $ROOT\DocumentShadowRemoval\ folder) is:
   
   ./../x64/Release/DocumentShadowRemoval.exe Input/001.png Results/001
   
   The three outputs (deshadowed image, shadow map, and timing) will be output in 
   the Results directory with the 001 prefix:
   
   Results/001_Out.png
   Results/001_ShadowMap.png
   Results/001_Timing.txt   

-------------------------------------------------------------------------
V. CODE DETAILS

Below is a brief summary of the code.

Main.cpp: Parses input arguments, creates a ShadowRemover, and calls RemoveShadow() function of Shadow remover.

ShadowRemover.h: Defines the ShadowRemover class

ShadowRemover.cpp: Defines all of the methods of the ShadowRemover class. Main function is RemoveShadow() function. 

	// Primary function of the ShadowRemover class. Start here
	void RemoveShadow(char* out);
	
	// Performs the local clustering using GMM at the block and saves the result in clusterMu
	void ClusterBlock(Mat& block, Mat& clusterMu);

	// Identifies the local cluster belonging to the background and saves it in the shadow map
	// Currently uses max cluster mean.
	void CalculatePaperStatistics(int x, int y, Mat& clusterMu);

	// Finds the block that best represents the background region. Used for constructing the
	// shadow map (gain map)
	void FindReferenceIndex(int& refInd);

	// Apply per pixel gain to do the actual shadow removal
	void ApplyShadowMap();
	
The default algorithm parameters can be changed in the ShadowRemover constructor:

	// Default algorithmic parameters
	stride = 20; // Number of pixels to skip when performing local analysis
	blockSize = 21; // Size of overlapping blocks in local analysis
	numOfClusters = 3; // Number of clusters used for local analysis
	numOfClustersRef = 3; // Number of clusters used for global analysis  
	maxIters = 100; // Maximum number of iterations used as stopping condition for GMM clustering. 
	emEps = 0.1f; // Epsilon threshold used as stopping condition for GMM clustering. 
	dsFactor = 1.0f; // No downsampling is done
	numOfLocalSamples = 150; // Number of samples to take in each block (for local statistics)
	numOfGlobalSamples = 1000; // Number of samples to take throughout entire image (for global statistics)

-------------------------------------------------------------------------
VI. VERSION HISTORY	
	
v1.0 - Initial release   (02/2016)

-------------------------------------------------------------------------

If you find any bugs or have comments/questions, please contact 
Steve Bako (stevebako@umail.ucsb.edu).

Santa Barbara, California
02/2016
