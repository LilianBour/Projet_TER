#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <math.h>
#include <filesystem>
#include <fstream>
#include <algorithm> 

namespace fs = std::filesystem;
using namespace std;
using namespace cv;

class Pattern {
	public:
		Pattern(string Folder_nb="221", string Name="1489") :folder_nb(Folder_nb), name(Name) {
			//Init vector
			vector<int> vec = { 0,0,0,0,0 };
			vector<vector<int>> vec2 = { {0000,0000,0000},{0000,0000,0000} };
			counter_pattern_imgs.push_back(make_pair(make_pair(1, vec), vec2));
			//Init vector 2 
			counter_pattern_class.push_back(make_pair(make_pair(1, vec), "0"));
		};
		//Get list of all imgs in folder
		void load_imgs();
		//Check if images correctly loaded
		int load_check(Mat img0, Mat img1, Mat img2);
		//Sorting and reversing counter_pattern_imgs by highest counter of pattern + Deleting last element 
		void sorting ();
		//Creating cube from i-1, i, i+1
		void cube();
		//Writing and deleting to avoid solid patterns
		void writing_and_deleting_solid_patterns();


		//Go through all parcels, look for pattern, and create csv file
		void load_imgs_and_cubes_220_221();
		//Same function but Class (intensive or traditional) instead of the names of the 3 imgs
		void cube_220_221(string nb_f1, string nb_f2);
		//Writing LogRank,LogCounter,Rank,Counter,Pattern,and type of orchard in csv file named data.csv
		void writing_and_deleting_solid_patterns_220_221();
		
	private:
		int cube_size=3;
		int img_nb=3;
		string folder_nb;
		string name;
		vector<string> liste_img;////veteur des noms des images dans le dossier
		vector<pair<pair<int, vector<int>>, vector<vector<int>>>> counter_pattern_imgs;
		vector<pair<pair<int, vector<int>>, string >> counter_pattern_class;
};