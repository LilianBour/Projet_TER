#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm> 
#include "Pattern.h"
#include "Slope.h"

namespace fs = std::filesystem;
using namespace std;
using namespace cv;

Pattern welcome_fun() {
	string answ;
	cout << "Enter propreties of parcel (Yes or No) ?\n";
	cin >> answ;
	if (answ == "Yes" or answ == "yes" or answ == "y" or answ == "Y") {
		string folder_number;
		string name;
		string quantized;
		string ans;
		cout << "Folder number (220 : Traditional orchard  or 221 : Intensive orchard) \n";
		cin >> folder_number;
		cout << "Parcel number (ex : 1489) \n";
		cin >> name;
		Pattern pt(folder_number, name);
		return pt;
	}
	else {
		cout << "Parcel : 220 - 1188\n";
		cin.ignore();
		Pattern pt;
		return pt;
	}
}

void write_slope_csv(vector<float> s1, vector<float>s2, vector<float>nb_pattern, vector<int> classe) {
	ofstream MyExcelFile; // ";" -> new cell // endl -> new row
	MyExcelFile.open("C:/Users/lilia/github/Projet_ter/data_slopes.csv");
	MyExcelFile << "p1;p2;nb_pattern;classe" << endl;
	for (int i = 0; i < s1.size(); i++) {
		cout << "s1 : " << s1[i] << " s2 : " << s2[i] << " Nb_pattern : " << nb_pattern[i] << " class : " << classe[i] << endl;
		MyExcelFile << s1[i] << ";" << s2[i] << ";" << nb_pattern[i] << ";" << classe[i] << endl;
	}
	
}

int main()
{


	//For all traditional parcels only
	//Get the center of all patterns from the first slope it should be the position i,j from the 4th elem of the 9
	//Get the slopes
	//Get the cutting point = first point of the second slope 

	//Cretate a new image where +1 is added at each position i,j for x in LogCounter while x < cutting point 



	//Only one parcel cube and image of sums
	Pattern pt = welcome_fun();
	pt.load_imgs();
	pt.cube();
	pt.sorting();
	pt.writing_and_deleting_solid_patterns();
	pt.print_cube_and_temp_sum();

	/*
	//Only one parcel
	Pattern pt = welcome_fun();
	pt.load_imgs();
	pt.cube();
	pt.sorting();
	pt.writing_and_deleting_solid_patterns();
	pt.Set_LogRank_LogCounter();
	Slope s(pt.Get_LogRank(), pt.Get_LogCounter(), pt.Get_Classe());
	s.Slope_Intercept();
	s.Furthest_from_line();
	s.Find_slope();
	*/



	/*
	//All Parcels slopes
	vector<float> s1s;
	vector<float>s2s;
	vector<float>nb_patterns;
	vector<int> classes;
	Pattern pattern;
	float count_per = 0;
	
	vector<string> folders_220_221 = { "220","221" };
	vector<string> folders_220;
	vector<string> folders_221;
	string path = "C:/Users/lilia/github/Projet_ter/Parcels/220_quantized/";
	for (const auto& entry : fs::directory_iterator(path)) { folders_220.push_back(entry.path().string().substr(entry.path().string().length() - 6, 4)); }
	string path_ = "C:/Users/lilia/github/Projet_ter/Parcels/221_quantized/";
	for (const auto& entry : fs::directory_iterator(path_)) { folders_221.push_back(entry.path().string().substr(entry.path().string().length() - 6, 4));}

	//Loop through all parcels (Intensive and Traditional)
	for (int i = 0; i < folders_220_221.size(); i++) {
		if (folders_220_221[i] == "220") {
			for (int j = 0; j < folders_220.size(); j++) {
				cout << folders_220_221[i] << " " << folders_220[j] << " ";


				Pattern pt(folders_220_221[i], folders_220[j]);
				pt.load_imgs();
				pt.cube();
				pt.sorting();
				pt.writing_and_deleting_solid_patterns();
				pt.Set_LogRank_LogCounter();
				Slope s(pt.Get_LogRank(), pt.Get_LogCounter(), pt.Get_Classe());
				s.Slope_Intercept();
				s.Furthest_from_line();
				s.Find_slope();

				s1s.push_back(s.Get_s1());
				s2s.push_back(s.Get_s2());
				nb_patterns.push_back(s.Get_nb_pattern());
				classes.push_back(s.Get_classe());


				count_per = count_per + 1;
				cout << "Progression : " << (count_per / 150) * 100 << "%" << endl;
			}
		}
		if (folders_220_221[i] == "221") {
			for (int j = 0; j < folders_221.size(); j++) {
				cout << folders_220_221[i] << " " << folders_221[j] << " ";


				Pattern pt(folders_220_221[i], folders_221[j]);
				pt.load_imgs();
				pt.cube();
				pt.sorting();
				pt.writing_and_deleting_solid_patterns();
				pt.Set_LogRank_LogCounter();
				Slope s(pt.Get_LogRank(), pt.Get_LogCounter(), pt.Get_Classe());
				s.Slope_Intercept();
				s.Furthest_from_line();
				s.Find_slope();

				s1s.push_back(s.Get_s1());
				s2s.push_back(s.Get_s2());
				nb_patterns.push_back(s.Get_nb_pattern());
				classes.push_back(s.Get_classe());


				count_per = count_per + 1;
				cout << "Progression : " << (count_per / 150) * 100 << "%" << endl;

			}
		}

	}
	write_slope_csv(s1s, s2s, nb_patterns, classes);
	*/




	/*
	//All parcels
	Pattern pt1;
	pt1.load_imgs_and_cubes_220_221();
	*/


	/*
	//Kmeans Histo_comparison data and Classification data
	//Data will be in main folder, nedd to move data into coresponding folder (hist_comparison_data or classification_data)
	vector<string> folders_220_221 = { "220","221" };
	vector<string> folders_220;
	vector<string> folders_221;
	string path = "C:/Users/lilia/github/Projet_ter/Parcels/220_quantized/";
	for (const auto& entry : fs::directory_iterator(path)) { folders_220.push_back(entry.path().string().substr(entry.path().string().length() - 6, 4)); }
	string path_ = "C:/Users/lilia/github/Projet_ter/Parcels/221_quantized/";
	for (const auto& entry : fs::directory_iterator(path_)) { folders_221.push_back(entry.path().string().substr(entry.path().string().length() - 6, 4)); }

	//Loop through all parcels (Intensive and Traditional)
	for (int i = 0; i < folders_220_221.size(); i++) {
		if (folders_220_221[i] == "220") {
			for (int j = 0; j < folders_220.size(); j++) {
				if (j > folders_220.size() - 12) {//CHANGE HERE to match load_imgs_and_cubes_220_221 
					cout << folders_220_221[i] << " " << folders_220[j] << " ";
					Pattern pt(folders_220_221[i], folders_220[j]);
					pt.load_imgs();
					pt.cube();
					pt.sorting();
					pt.writing_and_deleting_solid_patterns();
				}
				
			}
		}
		if (folders_220_221[i] == "221") {
			for (int j = 0; j < folders_221.size(); j++) {
				if (j > folders_221.size() - 26) {//CHANGE HERE to match load_imgs_and_cubes_220_221 
					cout << folders_220_221[i] << " " << folders_221[j] << " " << endl;
					Pattern pt(folders_220_221[i], folders_221[j]);
					pt.load_imgs();
					pt.cube();
					pt.sorting();
					pt.writing_and_deleting_solid_patterns();
				}
			}
		}

	}
	*/
	return 0;
}





