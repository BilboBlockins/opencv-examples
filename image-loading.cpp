#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//General image loading and processing...
using namespace cv; 
using namespace std;

int main(int argc, const char** argv)
{ 
	Mat myImage; // declaring a matrix named myImage
	Mat myImage_G; // declaring a matrix named myImage
	Mat diff_channels[3]; // declare a data structure with 3 different channels.
	Mat graySquare(480, 640, CV_8UC1, Scalar(100)); //1 channel grey image
	Mat colorSquare(480, 640, CV_8UC3, Scalar(180,140,200)); // 3 channel BGR image

	namedWindow("grayImage100", CV_WINDOW_AUTOSIZE);
	imshow("grayImage100", graySquare);
	namedWindow("colorImage", CV_WINDOW_AUTOSIZE);
	imshow("colorImage", colorSquare);

	namedWindow("PhotoFrame", CV_WINDOW_KEEPRATIO); // declaring the window to show the image. Also can use CV_WINDOW_FULLSCREEN, CV_WINDOW_FREERATIO, CV_WINDOW_AUTOSIZE, CV_WINDOW_KEEPRATIO, CV_WINDOW_OPENGL
	myImage = imread("path-to-image/helloworld.png", CV_LOAD_IMAGE_UNCHANGED); // loading the image named hello CV in the matrix CV_LOAD_IMAGE_UNCHANGED, CV_LOAD_IMAGE_GRAYSCALE, CV_LOAD_IMAGE_ANYDEPTH, CV_LOAD_IMAGE_COLOR

	if (myImage.empty()) // if the image is not loaded, show an error message
	{ 
		cout << "Couldn't load the image." << endl;
		cin.get(); // pause the system and wait for users to press any key 
		return -1; 
	}

	split(myImage, diff_channels); //splits the loaded image into 3 different channels
	Mat b = diff_channels[0]; // this isn't strictly neccessary since we could have simply loaded/displayed the array index.
	Mat g = diff_channels[1];
	Mat r = diff_channels[2];

	imshow("blue channel", diff_channels[0]); // see here - can use array directly instead of variable name.
	imshow("green channel", g);
	imshow("red channel", r);

	cvtColor(myImage, myImage_G, CV_RGB2GRAY); //convert to gray. Can also use CV_RGB2GRAY, CV_RGB2HSV, CV_GRAY2BGR, CV_RGB2HLS ...etc
	imshow("Grey Conversion", myImage_G);

	imwrite("path-to-output/grayScaleHelloWorld.jpg", myImage); // writes the stored image in the specified path.
	imshow("PhotoFrame", myImage); // display the image which is stored in the 'img' in the "MyWindow" window 
	waitKey(0); // wait till user press any key with picture highlighted - other values greater than 0 are in milliseconds
	destroyWindow("MyWindow"); // closes the window and release allocated memory
	
	return 0;
}

