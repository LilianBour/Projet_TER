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

class Pattern {
	public:
		Pattern(string Folder_nb="221", string Name="1489") :folder_nb(Folder_nb), name(Name) {
			//Init vector
			vector<int> vec = { 0,0,0,0,0 };
			vector<vector<int>> vec2 = { {0000,0000,0000},{0000,0000,0000} };
			counter_pattern_imgs.push_back(make_pair(make_pair(1, vec), vec2));
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

	private:
		int cube_size=3;
		int img_nb=3;
		string folder_nb;
		string name;
		vector<string> liste_img;////veteur des noms des images dans le dossier
		vector<pair<pair<int, vector<int>>, vector<vector<int>>>> counter_pattern_imgs;
};