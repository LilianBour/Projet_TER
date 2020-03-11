#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm> 


namespace fs = std::filesystem;
using namespace std;
using namespace cv;

int main()
{
	string file_number = "221";
	string name = "1489";
	//Get list of all files in folder
	vector<string> liste_img;
	std::string path = "C:/Users/lilia/Desktop/Parcels/"+file_number+"_quantized/"+name+".0";//IF CHANGING FOLDER NEED TO MODIFY EXCEL FILE NAME BELOW
	for (const auto& entry : fs::directory_iterator(path)) { liste_img.push_back(entry.path().string()); }// liste_img.push_back(entry.path());


	int cube_size = 3;
	//vector(pair(pair(T1,T2),T3)) T1=counter / T2=pattern / T3=list of images with this pattern
	vector<pair<pair<int, vector<int>>, vector<vector<int>>>> counter_pattern_imgs;
	//same vector to erase elements with all the same pixels to do k means
	vector<pair<pair<int, vector<int>>, vector<vector<int>>>> counter_pattern_imgs_bis;

	//Init vector
	vector<int> vec = { 0,0,0,0,0 };
	vector<vector<int>> vec2 = { {0000,0000,0000},{0000,0000,0000} };
	counter_pattern_imgs.push_back(make_pair(make_pair(1, vec),vec2));


	//For each file in folder
	for (size_t i = 1; i < liste_img.size()-1; i++)
	{
		//Taking only the date from the file name 
		int date0 = stoi(liste_img[i - 1].substr(liste_img[i - 1].length() - 12, 8));
		int date1 = stoi(liste_img[i].substr(liste_img[i].length() - 12, 8));
		int date2 = stoi(liste_img[i + 1].substr(liste_img[i + 1].length() - 12, 8));

		cout << "Images : " << endl << date0 << endl << date1 << endl << date2 << endl;
		int img_nb = 3;
		Mat img0 = imread(liste_img[i]);
		Mat img1 = imread(liste_img[i]);
		Mat img2 = imread(liste_img[i]);
		bool boolean;
		
		//If image not loading
		if (!img0.data|| !img1.data|| !img2.data)
		{
			cout << "Image not loaded";
			return -1;
		}


		//Create cube (vector of 3x3 pixels from 3 images)
		int rows = img0.rows;
		int cols = img0.cols;
		int x = 0;
		for (int a=0; a < rows - cube_size;a++){
			int y = 0;
			x = x +1;
			for (int b = 0; b < cols - cube_size; b++) {
				y = y+1;
				vector<int> cube;
				for (int i = x; i < x + cube_size; i++) {
					for (int j = y; j < y + cube_size; j++) {
						cube.push_back((int)img0.at<uchar>(i, j));
						cube.push_back((int)img1.at<uchar>(i, j));
						cube.push_back((int)img2.at<uchar>(i, j));
					}
				}
				
				//Compare to all patterns in vector 
				for (int i = 0; i < counter_pattern_imgs.size(); i++) {
					//If pattern in patterns add +1 to counter
					if (counter_pattern_imgs[i].first.second == cube) {
						counter_pattern_imgs[i].first.first = counter_pattern_imgs[i].first.first + 1;
						counter_pattern_imgs[i].second.push_back({ date0,date1,date2 });
						boolean = false;
						break;
					}
					//If pattern not in patterns set true 
					else {
						boolean = true;
					}
				}
				//if true add pair (1,pattern) 
				if (boolean == true) {
					vector<vector<int>> dates = { {date0,date1,date2} };
					counter_pattern_imgs.push_back(make_pair(make_pair(1, cube), dates));
				}
			}
		}
	}


	//Sorting and reversing counter_pattern_imgs by highest counter of pattern
	sort(counter_pattern_imgs.begin(), counter_pattern_imgs.end());
	reverse(counter_pattern_imgs.begin(), counter_pattern_imgs.end());
	//Deletin last element 
	counter_pattern_imgs.pop_back();


	//Writting on csv file + Printing infos 
	ofstream MyExcelFile; // ";" -> new cell // endl -> new row
	MyExcelFile.open("C:/Users/lilia/github/Projet_ter/Parcels_"+file_number+"_quantized_"+name+".0.csv");//MODIFY HERE
	MyExcelFile << "Counter;Images" << endl;
	cout << "\nDone2.\n";
	for (int j = 0; j < counter_pattern_imgs.size(); j++) {
		bool to_skip=false;
		//If pattern appearing more than 10 times add to csv file 
		if (counter_pattern_imgs[j].first.first > 10) {
			vector<pair<int,int>> verification_values;
			//init verification_values;
			verification_values.push_back(make_pair(0, -1));
			bool verification_bool = false;

			//Check if pattern is not all equal pixels 
			for (int i = 0; i < counter_pattern_imgs[j].first.second.size(); i++) {
				bool verification_add;
				cout << counter_pattern_imgs[j].first.second[i] << " ";
				for (int k = 0; k < verification_values.size(); k++) {
					if (verification_values[k].second == counter_pattern_imgs[j].first.second[i]) {
						verification_values[k].first = verification_values[k].first + 1;
						verification_add = false;
						break;
					}
					else {
						verification_add = true;
					}
				}
				if (verification_add == true) {
					verification_values.push_back(make_pair(1, counter_pattern_imgs[j].first.second[i]));
				}
			}

			
			//if px all the same skip/don't write it on csv file elem of vector
			sort(verification_values.begin(), verification_values.end());
			if (verification_values.back().first == cube_size*cube_size*3) {
				to_skip = true;
				continue;
			}
			//if not write on csv file + copy in vector bis 
			if (to_skip == false) {
				counter_pattern_imgs_bis.push_back(counter_pattern_imgs[j]);
				cout << "Pattern " << j << " appearing " << counter_pattern_imgs[j].first.first << " times" << endl;
				MyExcelFile << counter_pattern_imgs[j].first.first << ";";
				for (int i = 0; i < counter_pattern_imgs[j].second.size(); i++) {
					for (int k = 0; k < counter_pattern_imgs[j].second[i].size(); k++) {
						MyExcelFile << counter_pattern_imgs[j].second[i][k] << ",";
					}
					MyExcelFile << ";";
				}
				MyExcelFile << endl;
			}
		}
	}
	MyExcelFile.close();
	return 0;
}