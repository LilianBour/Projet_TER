#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using namespace std;
using namespace cv;

int main()
{

	//Get list of all files in folder
	vector<string> liste_img;
	std::string path = "C:/Users/lilia/Desktop/Parcels/220/1176.0";//IF CHANGING FOLDER NEED TO MODIFY EXCEL FILE NAME BELOW
	for (const auto& entry : fs::directory_iterator(path)) { liste_img.push_back(entry.path().string()); }// liste_img.push_back(entry.path());



	//vector(pair(pair(T1,T2),T3)) T1=counter / T2=pattern / T3=list of images with this pattern
	vector<pair<pair<int, vector<int>>, vector<vector<int>>>> counter_pattern_imgs;
	//Init vector
	vector<int> vec = { 0,0,0,0,0 };
	vector<vector<int>> vec2 = { {0000,0000,0000},{0000,0000,0000} };
	counter_pattern_imgs.push_back(make_pair(make_pair(1, vec),vec2));
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
		//Compare to all patterns
		for (int i = 0; i < counter_pattern_imgs.size(); i++) {
			//If pattern in patterns add +1 to counter
			if (counter_pattern_imgs[i].first.second == cube) {
				counter_pattern_imgs[i].first.first = counter_pattern_imgs[i].first.first +1;
				counter_pattern_imgs[i].second.push_back({ date0,date1,date2 });
				boolean = false;
			}
			//If pattern not in patterns set true 
			else {
				boolean = true;
			}
		}
		//if true add pair (1,pattern) 
		if (boolean==true) {
			vector<vector<int>> dates = { {date0,date1,date2} };
			counter_pattern_imgs.push_back(make_pair(make_pair(1, cube), dates));
		}
	}	
	//Sorting and reversing counter_pattern_imgs by highest counter of pattern
	sort(counter_pattern_imgs.begin(), counter_pattern_imgs.end());
	reverse(counter_pattern_imgs.begin(), counter_pattern_imgs.end());
	//Deletin last element 
	counter_pattern_imgs.pop_back();

	ofstream MyExcelFile;
	MyExcelFile.open("C:/Users/lilia/github/Projet_ter/Parcels_220_1176.0.csv");//MODIFY HERE
	MyExcelFile << "Counter;Images" << endl;
	for (int j = 0; j < counter_pattern_imgs.size(); j++) {
		cout << "Pattern " << j << " appearing " << counter_pattern_imgs[j].first.first << " times"<< endl;
		MyExcelFile << counter_pattern_imgs[j].first.first << ";";
		if (counter_pattern_imgs[j].first.first > 1) {
			cout << "pattern : \n";
			for (int i = 0; i < counter_pattern_imgs[j].first.second.size(); i++) {
				cout << counter_pattern_imgs[j].first.second[i] << " ";
				//MyExcelFile << counter_pattern_imgs[j].first.second[i];
			}
			cout << endl;
		}
		cout << "Images : \n";
		for (int i = 0; i < counter_pattern_imgs[j].second.size(); i++) {
			for (int k = 0; k < counter_pattern_imgs[j].second[i].size(); k++) {
				cout << counter_pattern_imgs[j].second[i][k] << "  ";
				MyExcelFile << counter_pattern_imgs[j].second[i][k] << ",";
			}
			cout << endl;
			MyExcelFile << ";";
		}
		cout << endl;
		MyExcelFile << endl;
	}
	MyExcelFile.close();
	return 0;
}