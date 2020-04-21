#include "Pattern.h"

void Pattern::load_imgs() {
	string path = "C:/Users/lilia/github/Projet_ter/Parcels/" + folder_nb + "_quantized/" + name + ".0";
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
	sort(counter_pattern_imgs.begin(), counter_pattern_imgs.end());
	reverse(counter_pattern_imgs.begin(), counter_pattern_imgs.end());
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
				//Remplace . in floats by , for excel
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


void Pattern::cube_220_221(string nb_f1, string nb_f2) {
	vector<string> liste_img_a;
	string path = "C:/Users/lilia/github/Projet_ter/Parcels/" + nb_f1 + "_quantized/" + nb_f2 + ".0";
	for (const auto& entry : fs::directory_iterator(path)) { liste_img_a.push_back(entry.path().string()); }

		for (size_t i = 1; i < liste_img_a.size() - 1; i++)
		{
			Mat img0 = imread(liste_img_a[i - 1]);
			Mat img1 = imread(liste_img_a[i]);
			Mat img2 = imread(liste_img_a[i + 1]);

			bool boolean;
			Pattern ptrn(folder_nb, name);
			ptrn.load_check(img0, img1, img2);


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

					for (int i = 0; i < counter_pattern_class.size(); i++) {
						//If pattern in patterns and from the same class (Intensive or Traditional) add +1 to counter 
						if (counter_pattern_class[i].first.second == cube and counter_pattern_class[i].second == nb_f1) {//CLASS ADD and counter_pattern_class[i].second == nb_f1
							counter_pattern_class[i].first.first = counter_pattern_class[i].first.first + 1;
							boolean = false;
							break;
						}
						//If pattern not in patterns set true 
						else {
							boolean = true;
						}
					}
					//if true add pair (1,pattern),and Class 
					if (boolean == true) {
						counter_pattern_class.push_back(make_pair(make_pair(1, cube), nb_f1));//CLASS nb_f1 instead of 2
					}
				}
			}
		}
}

void Pattern::load_imgs_and_cubes_220_221() {
	vector<string> folders_220_221 = { "220","221" };
	vector<string> folders_220;
	vector<string> folders_221;
	string path = "C:/Users/lilia/github/Projet_ter/Parcels/220_quantized/";
	for (const auto& entry : fs::directory_iterator(path)) { folders_220.push_back(entry.path().string().substr(entry.path().string().length() - 6, 4)); }
	string path_ = "C:/Users/lilia/github/Projet_ter/Parcels/221_quantized/";
	for (const auto& entry : fs::directory_iterator(path_)) { folders_221.push_back(entry.path().string().substr(entry.path().string().length() - 6, 4)); }

	Pattern pattern;
	float count_per = 0;

	//Writting on csv file imgs for histo and test kmeans 
	ofstream MyExcelFile1; 
	ofstream MyExcelFile2;
	MyExcelFile1.open("C:/Users/lilia/github/Projet_ter/data_histo_comparison.csv");
	MyExcelFile2.open("C:/Users/lilia/github/Projet_ter/data_kmeans_test.csv");


	//Loop through all parcels (Intensive and Traditional)
	for (int i = 0; i < folders_220_221.size(); i++) {
		if (folders_220_221[i] == "220") {
			for (int j = 0; j < folders_220.size(); j++) {
				if (j < folders_220.size() - 24) {
					cout << folders_220_221[i] << " " << folders_220[j] << " " << endl;
					//Add patterns for this parcels
					pattern.cube_220_221(folders_220_221[i], folders_220[j]);
					
				}
				if (j > folders_220.size() - 24 and j < folders_220.size() - 12) {
					cout << folders_220_221[i] << " " << folders_220[j] << " " << endl;
					//Write in csv comapr_histo
					MyExcelFile1 <<folders_220_221[i] << ";" << folders_220[j] << endl;

				}
				if (j < folders_220.size() - 12) {
					cout << folders_220_221[i] << " " << folders_220[j] << " " << endl;
					//Write in csv test
					MyExcelFile2 << folders_220_221[i] << ";" << folders_220[j] << endl;
				}
			}
		}
		if (folders_220_221[i] == "221") {
			for (int j = 0; j < folders_221.size(); j++) {
				if (j < folders_221.size() - 52) {
					cout << folders_220_221[i] << " " << folders_221[j] << " " << endl;
					//Add patterns for this parcels
					pattern.cube_220_221(folders_220_221[i], folders_221[j]);

				}
				if (j > folders_221.size() - 52 and j < folders_221.size() - 26) {
					cout << folders_220_221[i] << " " << folders_221[j] << " " << endl;
					//Write in csv comapr_histo
					MyExcelFile1 << folders_220_221[i] << ";" << folders_221[j] << endl;
				}
				if (j < folders_221.size() - 26) {
					cout << folders_220_221[i] << " " << folders_221[j] << " " << endl;
					//Write in csv test
					MyExcelFile2 << folders_220_221[i] << ";" << folders_221[j] << endl;
				}


				cout << folders_220_221[i] << " " << folders_221[j] << " ";
				//Add patterns for this parcels
				pattern.cube_220_221(folders_220_221[i], folders_221[j]);
				count_per = count_per + 1;
				cout << "Progression : " << (count_per / 30) * 100 << "%" << endl;

			}
		}
	}

	MyExcelFile1.close();
	MyExcelFile2.close();

	//Delete initializer, sort and reverse vector 
	pattern.counter_pattern_class.erase(pattern.counter_pattern_class.begin());
	sort(pattern.counter_pattern_class.begin(), pattern.counter_pattern_class.end());
	reverse(pattern.counter_pattern_class.begin(), pattern.counter_pattern_class.end());

	
	pattern.writing_and_deleting_solid_patterns_220_221();
}

void Pattern::writing_and_deleting_solid_patterns_220_221() {
	int rank = 1;
	vector<pair<pair<int, vector<int>>, vector<vector<int>>>> cou_pat_imgs_bis;
	//Writting on csv file + Printing infos 
	ofstream MyExcelFile; // ";" -> new cell // endl -> new row
	MyExcelFile.open("C:/Users/lilia/github/Projet_ter/data_0_1.csv");
	MyExcelFile << "LogR;LogC;Rank;Counter;Pattern;Class" << endl;
	for (int j = 0; j < counter_pattern_class.size(); j++) {
		bool to_skip = false;
		//If pattern appearing more than 10 times add to csv file 
		if (counter_pattern_class[j].first.first > 10) {
			vector<pair<int, int>> verification_values;
			//init verification_values;
			verification_values.push_back(make_pair(0, -1));
			bool verification_bool = false;

			//Check if pattern is not all equal pixels 
			for (int i = 0; i < counter_pattern_class[j].first.second.size(); i++) {
				bool verification_add;
				cout << counter_pattern_class[j].first.second[i] << " ";
				for (int k = 0; k < verification_values.size(); k++) {
					if (verification_values[k].second == counter_pattern_class[j].first.second[i]) {
						verification_values[k].first = verification_values[k].first + 1;
						verification_add = false;
						break;
					}
					else {
						verification_add = true;
					}
				}
				if (verification_add == true) {
					verification_values.push_back(make_pair(1, counter_pattern_class[j].first.second[i]));
				}
			}

			//if px all the same skip/don't write it on csv file elem of vector
			sort(verification_values.begin(), verification_values.end());
			if (verification_values.back().first == cube_size * cube_size * 3) {
				to_skip = true;
				continue;
			}

			//if not write on csv file
			if (to_skip == false) {
				cout << "Pattern " << j << " appearing " << counter_pattern_class[j].first.first << " times" << endl;
				////Remplacement des . dans les floats par des , pour que ce soit adapté au format excel
				string LogR = to_string(log10(rank));
				replace(LogR.begin(), LogR.end(), '.', ',');
				MyExcelFile << LogR << ";";
				string LogC = to_string(log10(counter_pattern_class[j].first.first));
				replace(LogC.begin(), LogC.end(), '.', ',');
				MyExcelFile << LogC << ";";
				MyExcelFile << rank << ";";
				MyExcelFile << counter_pattern_class[j].first.first << ";";
				rank = rank + 1;
				for (int i = 0; i < counter_pattern_class[j].first.second.size(); i++) {
					MyExcelFile << counter_pattern_class[j].first.second[i] << ",";
				}
				MyExcelFile << ";";
				//MyExcelFile << "2";
				MyExcelFile << counter_pattern_class[j].second[2]; //CLASS
				MyExcelFile << endl;
			}
		}
	}
	MyExcelFile.close();
}



void Pattern::Set_LogRank_LogCounter() {
	int rank = 1;
	for (int i = 1; i < Pattern::counter_pattern_imgs.size(); i++) {
		Pattern::LogRank.push_back(log10(rank));
		Pattern::LogCounter.push_back(log10(Pattern::counter_pattern_imgs[i].first.first));
		rank = rank + 1;
	}
}
	
vector<float> Pattern::Get_LogRank() {
	return Pattern::LogRank;
}
vector<float> Pattern::Get_LogCounter() {
	return Pattern::LogCounter;
}

int Pattern::Get_Classe() {
	return stoi(Pattern::folder_nb)-220;
}
