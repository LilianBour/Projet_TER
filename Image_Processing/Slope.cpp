#include "Slope.h"
#include "Pattern.h"
#include <numeric>
#include <algorithm>
void Slope::Set_X_Y(string folderNb, string Name) {
	Pattern pt(folderNb, Name);
	pt.load_imgs();
	pt.cube();
	pt.sorting();
	pt.Set_LogRank_LogCounter();
	Slope::X = pt.Get_LogRank();
	Slope::Y = pt.Get_LogCounter();
}
vector<float> Slope::Get_X() {
	return Slope::X;
}
vector<float> Slope::Get_Y() {
	return Slope::Y;
}

pair<float, float> Slope::Slope_Intercept() {
	vector<float> x = Slope::X;
	vector<float> y = Slope::Y;
	int n = x.size();
	float xm = accumulate(x.begin(), x.end(), 0.0) / n;
	float ym = accumulate(y.begin(), y.end(), 0.0) / n;
	float sx = 0;
	float sy = 0;
	float sxy = 0;

	for (int i = 0; i < x.size(); i++) {
		sx = sx + ((x[i] - xm) * (x[i] - xm));
		sy = sy + ((y[i] - ym)* (y[i] - ym));
		sxy = sxy + ((x[i] - xm) * (y[i] - ym));
	}

	float r = sxy / (sqrt(sx * sy));
	//float Sy = sqrt((1/n)*sy);
	//float Sx = sqrt((1/n)*sx);
	//Slope::a = r * (Sy / Sx);
	Slope::a = sxy / sx;
	Slope::b = ym - a * xm;
	cout << "y=" << Slope::a << "x+" << Slope::b << endl;
	return make_pair(a, b);
}

pair<float, int> Slope::Furthest_from_line() {
	vector<float> x = Slope::X;
	vector<float> y = Slope::Y;
	pair<float, int> dist = make_pair(0.0, 0); //pair -> (distance,point position)
	for (int i = 0; i < y.size(); i++) {
		float y_calc = Slope::a * x[i] + Slope::b;
		float y_real = y[i];
		float d = abs(y_calc - y_real);
		if (d > dist.first) {
			dist.first = d;
			dist.second = i;
		}
	}
	Slope::distance = dist;
	return dist;
}

void Slope::Find_slope() {
	float seuil = 0.29;
	if (Slope::distance.first < seuil or Slope::distance.first == seuil) {
		Slope::s1 = Slope::a;
		Slope::s2 = Slope::a;
	}
	pair<float, pair<float, float>> distance_slope1_slope2 = make_pair(1000000.0, make_pair(0.0, 0.0));
	if (Slope::distance.first > seuil) {
		for (int i = 2; i < Slope::X.size() - 3; i++) {
			vector<float> part1_x (i);
			copy(Slope::X.begin(), Slope::X.begin()+i, part1_x.begin());
			vector<float> part1_y (i);
			copy(Slope::Y.begin(), Slope::Y.begin()+i, part1_y.begin());
			vector<float> part2_x (Slope::X.size()-i);
			copy(Slope::X.begin()+i, Slope::X.begin()+Slope::X.size(),part2_x.begin());
			vector<float> part2_y(Slope::Y.size() - i);
			copy(Slope::Y.begin() + i, Slope::Y.begin() + Slope::Y.size(), part2_y.begin());
			float d = 0;
			
			Slope p1(part1_x, part1_y,0);
			float s1 = p1.Slope_Intercept().first;
			d = d + p1.Furthest_from_line().first;
			
			Slope p2(part2_x, part2_y,0);
			float s2 = p2.Slope_Intercept().first;
			d = d + p2.Furthest_from_line().first;
				if (d < distance_slope1_slope2.first) {
					distance_slope1_slope2 = make_pair(d, make_pair(s1, s2));
			}
		}
		Slope::s1 = distance_slope1_slope2.second.first;
		Slope::s2 = distance_slope1_slope2.second.second;
	}
	
}

float Slope::Get_s1() {
	return Slope::s1;
}
float Slope::Get_s2() {
	return Slope::s2;
}
float Slope::Get_nb_pattern() {
	return Slope::nb_pattern;
}
int Slope::Get_classe() {
	return Slope::classe;
}
