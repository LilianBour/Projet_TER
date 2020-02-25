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
		


	//vector(pair(counter,motif))
	vector<pair<int, vector<int>>> motifs;
	//Init vector
	vector<int> vec = { 0,0,0,0,0 };
	motifs.push_back(make_pair(1,vec));
	//For each file in folder
	for (size_t i = 1; i < liste_img.size()-1; i++)
	{
		cout << "Images : " << endl << liste_img[i-1] << endl << liste_img[i] << endl << liste_img[i + 1] << endl;
		int img_nb = 3;
		//TODO add loop/vector to do all images in one loop
		Mat img0 = imread(liste_img[i]);
		Mat img1 = imread(liste_img[i]);
		Mat img2 = imread(liste_img[i]);

		vector<int> cube;
		
		//If image not loading
		if (!img0.data|| !img1.data|| !img2.data)
		{
			cout << "Image not loaded";
			return -1;
		}

		int rows = img0.rows;
		int cols = img0.cols;
		cout << "Number of rows : " << rows << endl;
		cout << "Number of columns : " << cols << endl;

		//px of img-1
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cube.push_back((int)img0.at<uchar>(i, j));
			}
		}
		//px of img-i
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cube.push_back((int)img1.at<uchar>(i, j));
			}
		}
		//px of img+1
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cube.push_back((int)img2.at<uchar>(i, j));
			}
		}
		bool boolean;
		//Compare to all motifs
		for (int i = 0; i < motifs.size(); i++) {
			//If motif in motifs add +1 to counter
			if (motifs[i].second == cube) {
				motifs[i].first = motifs[i].first +1;
				boolean = false;
			}
			//If motif not in motifs set true 
			else {
				boolean = true;
			}
		}
		//if true add pair (1,motif) 
		if (boolean==true) {
			motifs.push_back(make_pair(1, cube));
		}
	}	
	for (int j = 0; j < motifs.size(); j++) {
		cout << "Motif " << j << " appearing " << motifs[j].first << " times"<< endl;
		if (motifs[j].first > 1) {
			cout << "Motif : \n";
			for (int i = 0; i < motifs[j].second.size(); i++) {
				cout << motifs[j].second[i] << " ";
			}
			cout << endl;
		}
	}

	//TODO
	//add some kind of vector to get images from motifs
	//ex : if adding in position x in motifs, add list(img0,img1,img2) to new_vector(position x)
	return 0;
}