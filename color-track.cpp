#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//Program for tracking colors

using namespace std;
using namespace cv;


int main(int argc, char** argv) 
{
	VideoCapture video_load(0);/*loading video from default camera*/ 
	namedWindow("Adjust", CV_WINDOW_AUTOSIZE); /*declaring window to show image*/
	int Hue_low = 0; /*lower range of hue*/ 
	int Hue_high = 22; /*upper range of hue*/ 
	int Sat_low = 99; /*lower range of saturation*/ 
	int Sat_high = 255; /*upper range of saturation*/ 
	int Val_low = 0; /*lower range of value*/ 
	int Val_high = 255; /*upper range of value*/
	createTrackbar("LowH", "Adjust", &Hue_low, 179); /*track-bar for min hue*/

	createTrackbar("HighH", "Adjust", &Hue_high, 179); /*track-bar for max hue*/ 
	createTrackbar("LowS", "Adjust", &Sat_low, 255); /*track-bar for min saturation*/ 
	createTrackbar("HighS", "Adjust", &Sat_high, 255); /*track-bar for max saturation*/ 
	createTrackbar("LowV", "Adjust", &Val_low, 255); /*track-bar for min value*/ 
	createTrackbar("HighV", "Adjust", &Val_high, 255); /*track-bar for max value*/
	int Horizontal_Last = -1; /*initial horizontal position*/ 
	int Vertical_Last = -1; /*initial vertical position*/
	Mat temp; /*declaring a matrix to load frames from video stream*/ 
	video_load.read(temp); /*loading frames from video stream*/
	Mat track_motion = Mat::zeros(temp.size(), CV_8UC3); /*creating a black matrix for detection*/ 
	while (true) {
		Mat actual_image; /*declaring a matrix for actual image*/ 
		bool temp_load = video_load.read(actual_image); /*loading frames from video to the matrix*/
		Mat converted_to_HSV; /*declaring a matrix to store converted image*/ 
		cvtColor(actual_image, converted_to_HSV, COLOR_BGR2HSV); /*converting BGR image to HSV*/ 
		Mat adjusted_frame; /*declaring a matrix to detected color*/
		inRange(converted_to_HSV, Scalar(Hue_low, Sat_low, Val_low), Scalar(Hue_high, Sat_high, Val_high), adjusted_frame); /*applying change of values of track-bars*/
		erode(adjusted_frame, adjusted_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5))); /*morphological opening for removing small objects from foreground*/ 
		dilate(adjusted_frame, adjusted_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5))); /*morphological opening for removing small objects from foreground*/
		dilate(adjusted_frame, adjusted_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5))); /*morphological closing for filling up small holes in foreground*/ 
		erode(adjusted_frame, adjusted_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5))); /*morphological closing for filling up small holes in foreground*/
		Moments detecting_object = moments(adjusted_frame); /*creating an object from detected color frame*/
		double vertical_moment = detecting_object.m01; /*getting value of vertical position*/
		double horizontal_moment = detecting_object.m10; /*getting value of horizontal position*/
		double tracking_area = detecting_object.m00; /*getting area*/
		if (tracking_area > 10000) /*when area of the object is greater than 10000 pixels*/ 
		{ 
			int posX = horizontal_moment / tracking_area; /*calculate the horizontal position of the object*/ 
			int posY = vertical_moment / tracking_area; /*calculate the vertical position of the object*/ 
			if (Horizontal_Last >= 0 && Vertical_Last >= 0 && posX >= 0 && posY >= 0) /*when the detected object moves*/ 
			{ 
				line(track_motion, Point(posX, posY), Point(Horizontal_Last, Vertical_Last), Scalar(0, 0, 255), 2); /*draw lines of red color on the path of detected object's motion*/ 
			} Horizontal_Last = posX; /*getting new horizontal position*/ Vertical_Last = posY; /*getting new vertical position value*/ 
		}
		imshow("Detected_Object", adjusted_frame); /*showing detected object*/ 
		actual_image = actual_image + track_motion; /*drawing continuous line in original video frames*/ 
		imshow("Actual", actual_image); /*showing original video*/
		cout << "position of the object is : " << Horizontal_Last << "," << Vertical_Last << endl; /*showing tracked co-ordinate values*/
		if (waitKey(30) == 27) /*if esc is pressed loop will break*/ 
		{ 
			cout << "esc key is pressed by user" << endl; 
			break; 
		}
	}
	destroyAllWindows(); /*closes all windows and returns allocated memory*/
	return 0;
}
