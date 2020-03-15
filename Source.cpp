#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm> 
#include "Pattern.h"

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
		cout << "Parcel : 221 - 1486\n";
		cin.ignore();
		Pattern pt;
		return pt;
	}
}

int main()
{
	Pattern pt = welcome_fun();
	pt.load_imgs();
	pt.cube();
	pt.sorting();
	pt.writing_and_deleting_solid_patterns();
	
	return 0;
}