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
	for (const auto& entry : fs::directory_iterator(path)) { liste_img.push_back(entry.path().string()); }// liste_img.push_back(entry.path());



	//vector(pair(pair(T1,T2),T3)) T1=counter / T2=motif / T3=list of images with this motif
	vector<pair<pair<int, vector<int>>, vector<vector<int>>>> counter_motif_imgs;
	//Init vector
	vector<int> vec = { 0,0,0,0,0 };
	vector<vector<int>> vec2 = { {0000,0000,0000},{0000,0000,0000} };
	counter_motif_imgs.push_back(make_pair(make_pair(1, vec),vec2));
	//For each file in folder
	for (size_t i = 1; i < liste_img.size()-1; i++)
	{
		//Take only the date from the file name + ////converting to int?////
		int date0 = stoi(liste_img[i - 1].substr(liste_img[i - 1].length() - 12, 8));
		int date1 = stoi(liste_img[i].substr(liste_img[i].length() - 12, 8));
		int date2 = stoi(liste_img[i + 1].substr(liste_img[i + 1].length() - 12, 8));

		cout << "Images : " << endl << date0 << endl << date1 << endl << date2 << endl;
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
		//cout << "Number of rows : " << rows << endl;
		//cout << "Number of columns : " << cols << endl;

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
		for (int i = 0; i < counter_motif_imgs.size(); i++) {
			//If motif in motifs add +1 to counter
			if (counter_motif_imgs[i].first.second == cube) {
				counter_motif_imgs[i].first.first = counter_motif_imgs[i].first.first +1;
				counter_motif_imgs[i].second.push_back({ date0,date1,date2 });
				boolean = false;
			}
			//If motif not in motifs set true 
			else {
				boolean = true;
			}
		}
		//if true add pair (1,motif) 
		if (boolean==true) {
			vector<vector<int>> dates = { {date0,date1,date2} };
			counter_motif_imgs.push_back(make_pair(make_pair(1, cube), dates));
		}
	}	
	//Sorting and reversing counter_motif_imgs by highest counter of motif
	sort(counter_motif_imgs.begin(), counter_motif_imgs.end());
	reverse(counter_motif_imgs.begin(), counter_motif_imgs.end());
	for (int j = 0; j < counter_motif_imgs.size(); j++) {
		cout << "Motif " << j << " appearing " << counter_motif_imgs[j].first.first << " times"<< endl;
		if (counter_motif_imgs[j].first.first > 1) {
			cout << "Motif : \n";
			for (int i = 0; i < counter_motif_imgs[j].first.second.size(); i++) {
				cout << counter_motif_imgs[j].first.second[i] << " ";
			}
			cout << "\nImages : \n";
			for (int i = 0; i < counter_motif_imgs[j].second.size(); i++) {
				for (int k = 0; k < counter_motif_imgs[j].second[i].size(); k++) {
					cout << counter_motif_imgs[j].second[i][k] << "  ";
				}
				cout << endl;
			}
			cout << endl;
		}
	}
	return 0;
}