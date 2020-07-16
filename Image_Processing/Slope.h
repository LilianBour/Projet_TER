#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <math.h>
#include <filesystem>
#include <fstream>
#include <algorithm> 

using namespace std;
using namespace cv;
class Slope {
	public:
		Slope(vector<float> x, vector<float> y,int c) : X(x),Y(y),nb_pattern(x.size()*0.01),classe(c){}
		void Set_X_Y(string folderNb, string Name);//?
		vector<float> Get_X();//?
		vector<float> Get_Y();//?
		pair<float, float> Slope_Intercept();
		pair<float, int> Furthest_from_line();
		float Find_slope();

		float Get_s1();
		float Get_s2();
		float Get_nb_pattern();
		int Get_classe();

	private:
		vector<float> X;
		vector<float> Y;
		float a;
		float b;
		pair<float, int> distance;
		float s1;
		float s2;
		float nb_pattern;
		int classe;
};