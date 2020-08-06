#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//Program for reading video from the default camera.
using namespace std;
using namespace cv;

void locator(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "Left click has been made, Position: (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		cout << "Right click has been made, position: (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		cout << "Middle click has been made, position: (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		cout << "Current mouse position: (" << x << ", " << y << ")" << endl;
	}
}

int main(int argc, char*argv[]) 
{
	VideoCapture video(0); //capturing video from webcam - use (1),(2), for cameras in different usb ports.

	namedWindow("VideoPlayer", CV_WINDOW_AUTOSIZE);//declaring the window 

	namedWindow("Slider", CV_WINDOW_KEEPRATIO); /*declaring window to show image*/
	int light = 50; /*starting value of the track-bar*/
	createTrackbar("Brightness", "Slider", &light, 100); /*creating a trackbar*/
	int contrast = 50; /*starting value of the track-bar*/
	createTrackbar("Contrast", "Slider", &contrast, 100); /*creating a trackbar*/

	while (true) 
	{ 
		Mat image; //delcaring a Matrix named image 
		video.read(image); //reading frames from camera and loading them in image Matrix 

		int Brightness = light - 50; //interaction with trackbar
		double Contrast = contrast / 50.0; //interaction with trackbar

		setMouseCallback("VideoPlayer", locator, NULL); //Mouse callback function on define window

		image.convertTo(image, -1, Contrast, Brightness); //implement the effect of chnage of trackbar

		imshow("VideoPlayer", image); //showing the image in window named VideoPlayer 
		waitKey(20); //wait for 20 milliseconds 
	} 
	
	return 0; 
}

