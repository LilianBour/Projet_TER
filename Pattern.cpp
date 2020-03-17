#include "Pattern.h"


void Pattern::load_imgs() {
	string path = "C:/Users/lilia/Desktop/Parcels/" + folder_nb + "_quantized/" + name + ".0";
	for (const auto& entry : fs::directory_iterator(path)) { liste_img.push_back(entry.path().string()); }
}

int Pattern::load_check(Mat img0, Mat img1, Mat img2) {
	if (!img0.data || !img1.data || !img2.data)
	{
		cout << "Image not loaded";
		return -1;
	}
}

void Pattern::sorting() {
	////Triage et inversement du vecteur en fonction du nombre d'apparition d'un motif pour avoir les motifs qui se r�p�tent le mieux en premier
	sort(counter_pattern_imgs.begin(), counter_pattern_imgs.end());
	reverse(counter_pattern_imgs.begin(), counter_pattern_imgs.end());
	////Suppression du dernier �l�ment car inutile (c'est l'�l�ment avec lequel on initialise le vecteur)
	counter_pattern_imgs.pop_back();
}

void Pattern::cube() {
	for (size_t i = 1; i < liste_img.size() - 1; i++)
	{
		//Taking only the date from the file name 
		int date0 = stoi(liste_img[i - 1].substr(liste_img[i - 1].length() - 12, 8));
		int date1 = stoi(liste_img[i].substr(liste_img[i].length() - 12, 8));
		int date2 = stoi(liste_img[i + 1].substr(liste_img[i + 1].length() - 12, 8));

		//Set imgs
		Mat img0 = imread(liste_img[i - 1]);
		Mat img1 = imread(liste_img[i]);
		Mat img2 = imread(liste_img[i + 1]);

		bool boolean;

		Pattern ptrn(folder_nb,name);
		ptrn.load_check(img0, img1, img2);


		//Create cube (vector of 3x3 pixels from 3 images)
		int rows = img0.rows;
		int cols = img0.cols;
		int x = 0;
		for (int a = 0; a < rows - cube_size; a++) {
			int y = 0;
			x = x + 1;
			for (int b = 0; b < cols - cube_size; b++) {
				y = y + 1;
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
}

void Pattern::writing_and_deleting_solid_patterns() {
	int rank = 1;
	vector<pair<pair<int, vector<int>>, vector<vector<int>>>> cou_pat_imgs_bis;
	//Writting on csv file + Printing infos 
	ofstream MyExcelFile; // ";" -> new cell // endl -> new row
	MyExcelFile.open("C:/Users/lilia/github/Projet_ter/Parcels_" + folder_nb + "_quantized_" + name + ".0.csv");//MODIFY HERE
	MyExcelFile << "LogR;LogC;Rank;Counter;Images" << endl;
	cout << "\nDone2.\n";
	for (int j = 0; j < counter_pattern_imgs.size(); j++) {
		bool to_skip = false;
		//If pattern appearing more than 10 times add to csv file 
		if (counter_pattern_imgs[j].first.first > 10) {
			vector<pair<int, int>> verification_values;
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
			if (verification_values.back().first == cube_size * cube_size * 3) {
				to_skip = true;
				continue;
			}
			//if not write on csv file + copy in vector bis 
			if (to_skip == false) {
				cou_pat_imgs_bis.push_back(counter_pattern_imgs[j]);
				cout << "Pattern " << j << " appearing " << counter_pattern_imgs[j].first.first << " times" << endl;
				////Remplacement des . dans les floats par des , pour que ce soit adapt� au format excel
				string LogR = to_string(log10(rank));
				replace(LogR.begin(), LogR.end(), '.', ',');
				MyExcelFile << LogR << ";";
				string LogC = to_string(log10(counter_pattern_imgs[j].first.first));
				replace(LogC.begin(), LogC.end(), '.', ',');
				MyExcelFile << LogC << ";";
				MyExcelFile << rank << ";";
				MyExcelFile << counter_pattern_imgs[j].first.first << ";";
				rank = rank + 1;
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
	counter_pattern_imgs= cou_pat_imgs_bis;
}
