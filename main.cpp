#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <armadillo>
#include "gnuplot-iostream.h"

using namespace std;
using namespace arma;

struct Data
{
	int index;
	string date;
	double value;
	void print() {
		std::cout << index << ", " << date << ", " << value << std::endl;
	}
	Data(int index, string date, double value) {
		this->index = index;
		this->date = date;
		this->value = value;
	}
};

std::vector<string> split(string str, string sep) {
	char* cstr=const_cast<char*>(str.c_str());
    char* current;

    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

vector<Data> readData(string path) {
	string line;
	ifstream myfile (path);
	vector<Data> datas;

	// Check if file is open
	if (myfile.is_open())
	{
		vector<string> arr;
		while ( getline (myfile,line) )
		{
	  		cout << "Read line: " << line << '\n';
	  		std::vector<string> lineitems;
	  		arr=split(line,",");
	  		Data d(stoi(arr[0]), arr[1], stod(arr[2]));
	  		datas.push_back(d);
		}
		// Close file
		myfile.close();
		
	}
	// File is not open, error
	else
	{
		cout << "Unable to open file";
	}

	return datas;
}

bool checkArgs(int argc, char const *argv[]) {
	if (argc == 2)
	{
		return true;
	}
	else if (argc > 2)
	{
		cout << "To many arguments. Correct format: ./test path/to/datafile." << endl;
	}
	else 
	{
		cout << "To few arguments. Correct format: ./test path/to/datafile." << endl;
	}
	return false;

}

void plotData() {
	Gnuplot gp;
	gp << "set terminal xterm\n";
	// For debugging or manual editing of commands:
	//Gnuplot gp(std::fopen("plot.gnu"));
	// or
	//Gnuplot gp("tee plot.gnu | gnuplot -persist");

	std::vector<std::pair<double, double> > xy_pts_A;
	for(double x=-2; x<2; x+=0.01) {
		double y = x*x*x;
		xy_pts_A.push_back(std::make_pair(x, y));
	}

	std::vector<std::pair<double, double> > xy_pts_B;
	for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
		double theta = alpha*2.0*3.14159;
		xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
	}

	gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
	gp << "plot '-' with lines title 'cubic', '-' with points title 'circle'\n";
	gp.send1d(xy_pts_A);
	gp.send1d(xy_pts_B);
}


int main(int argc, char const *argv[])
{
	// if (checkArgs(argc, argv))
	// {
	// 	string path = argv[1];
	// 	vector<Data> data = readData(path);

	// 	for (int i = 0; i < data.size(); ++i)
	// 	{
	// 		data[i].print();
	// 	}
	// }

	// mat A = randu<mat>(3,3);
	// cout << A << endl;
	// A.save("A.mat", csv_ascii);
	// mat B;
	// B.load("Data/sp500.mat");
	// cout << B << endl;

	plotData();

	return 0;
}