#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <opencv2/imgcodecs.hpp>
#include<iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;
using namespace cv;

int main()
{

	//Get list of all files in folder
	vector<string> liste_img;
	std::string path = "C:/Users/lilia/Desktop/Parcels/220/1176.0";
	for (const auto& entry : fs::directory_iterator(path)){liste_img.push_back(entry.path().string()); }// liste_img.push_back(entry.path());
		
	//For each file in folder
	for (size_t i = 0; i < liste_img.size(); i++)
	{
		cout << "Image : " << liste_img[i] << endl ;
		Mat img = imread(liste_img[i]);
		
		//If image not loading
		if (!img.data)
		{
			cout << "Image not loaded";
			return -1;
		}

		//Show image
		//imshow("image", img);
		//waitKey(0);


		//Set parameters for calcHist
		Mat histogram;
		int channels[] = { 0 };
		int histSize[] = { 5 };
		int histsize = 5;
		float range[] = { 0, 5 };
		const float* ranges[] = { range };

		//Get hist
		calcHist(&img, 1, channels, Mat(), histogram, 1, histSize, ranges, true, false);

		int hist_w = 512; int hist_h = 400;
		int bin_w = cvRound((double)hist_w / histsize);
		Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

		// Normalize the result 
		normalize(histogram, histogram, 0, histImage.rows, NORM_MINMAX, -1, Mat());

		// Draw hist with line()
		for (int i = 1; i < histsize; i++)
		{
			line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
				Scalar(255, 255, 255), 2, 8, 0);
		}

		//Show hist
		imshow("Hist line", histImage);
		waitKey(0);
		
	}	
	return 0;
}