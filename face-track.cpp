#include<iostream>
#include<opencv2/highgui/highgui.hpp> 
#include<opencv2/imgproc/imgproc.hpp> 
#include<opencv2/objdetect/objdetect.hpp>

using namespace cv; 
using namespace std;

int main(int argc, char*argv[]) 
{
	Mat frame; /*declaring a matrix to video frames in it*/
	namedWindow("Detect", CV_WINDOW_KEEPRATIO); /*Declaring a window to show our work*/
	VideoCapture image(0); /*capturing video from default camera*/
	if (!image.isOpened()) /*Error message if video source is not found*/
	{
		cout << "Couldn't load video from the source. Make sure your camera is working properly." << endl;
		system("pause"); 
		return 0;
	}

	double height = image.set(CV_CAP_PROP_FRAME_HEIGHT, 480); /*setting up height of each frame*/ 
	double width = image.set(CV_CAP_PROP_FRAME_WIDTH, 640); /*setting up width of each frame*/

	CascadeClassifier face_cascade; /*declaring a CascadeClassifier object*/ 
	face_cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml");/*loading the cascade classfier*/
	while (true) {
		bool temp = image.read(frame); /*loading video frames from source to our matrix named frame*/
		std::vector<Rect> faces; /*declaring a vector named faces*/ 
		face_cascade.detectMultiScale(frame, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(20, 20)); /*detecting the face*/ 
		for (int i = 0; i < faces.size(); i++) /*for locating the face*/ 
		{ 
			Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);/*getting the center of the face*/ 
			ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0); /*draw an ellipse on the face*/ 
		} 
		imshow("Detect", frame); /*showing result in window named 'Detect'*/ 
		if (waitKey(30) == 27) /*wait time for each frame is 30 milliseconds*/ 
		{ 
			break; 
		} 
	} 
	destroyAllWindows(); /*closes all windows and returns allocated memory*/ 
	return 0;
}

