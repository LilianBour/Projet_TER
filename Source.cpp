#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <opencv2/imgcodecs.hpp>
#include<iostream>

using namespace std;
using namespace cv;


//Function to get histogram with Mat

Mat computeHistogram(Mat input_image) {

	Mat histogram;
	int channels[] = { 0 };
	int histSize[] = { 5 };
	float range[] = { 0, 5 };
	const float* ranges[] = { range };

	calcHist(&input_image, 1, channels, Mat(), histogram, 1, histSize, ranges, true, false);

	return histogram;

}


int main()
{
	//Mat img = imread("shapes.jpg");
	//Mat img = imread("shapes.jpg", IMREAD_GRAYSCALE);
	Mat img = imread("20170103.tif");

	//If image not loading
	if (!img.data)
	{
		cout << "Image not loaded";
		return -1;
	}

	//Show image
	imshow("image", img);
	waitKey(0);

	/*
	//Stocking greyvalue of each px
	int rows = img.rows;
	int cols = img.cols;
	cout << rows <<endl;
	cout << "Number of columns : " <<cols <<endl;
	vector<int> grey_values(255, 0);
	for (int i=0; i < rows; i++) {
		for (int j=0; j < cols; j++) {
			grey_values[(int)img.at<uchar>(i, j)]= grey_values[(int)img.at<uchar>(i, j)]+1;
		}
	}
	//Printing greyvalue for each px
	cout << grey_values.size();
	for (int i = 0; i < 255; i++) {
		cout<<grey_values[i]<<endl;
	}*/
		

	/*Mat histogram = computeHistogram(img);
	imshow("hist", histogram);
	waitKey(0);*/




	/// Establish the number of bins
	int histSize = 5;
	Mat histogram = computeHistogram(img);


	

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	/// Normalize the result to [ 0, histImage.rows ]
	normalize(histogram, histogram, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
			Scalar(255, 255, 255), 2, 8, 0);
	}

	/// Display
	imshow("calcHist Demo", histImage);

	waitKey(0);
	return 0;
}