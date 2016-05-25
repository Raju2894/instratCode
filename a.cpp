#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip> 

using namespace std;

//I am taking the directory name as default wc_input
//if not we can scan that and send into the function
void getFilesInDir(vector<string> &files){
	DIR *dir;
	struct dirent *entry;
	struct stat info;
	string dir_name = "wc_input";

	//open
	dir = opendir(dir_name.c_str());
	if(!dir){
		cout << "Please provide the directory...!!" << endl;
		return;
	}

	//read
	while( (entry=readdir(dir)) != NULL){
		if(entry->d_name[0] != '.'){
			string path = dir_name + '/' + string(entry->d_name);
			stat(path.c_str(), &info);
			if(S_ISREG(info.st_mode))
				files.push_back(string(path));
		}
	}
	//close
	closedir(dir);
	sort(files.begin(), files.end());
}

double getMedian(std::vector<float> &v, int s){
	sort(v.begin(), v.end());
	if(s%2){
		return v[s/2];
	}
	else{
		return (v[s/2] + v[s/2-1])/2;
	}
}


int main(){
	vector<string> files;
	getFilesInDir(files);
	int size = files.size();
	
	mkdir("wc_output", 0777);
	ofstream out_file;
	out_file.open("./wc_output/med_result.txt");
	double Median = 0.0;
	vector<float> input;
	int s = 0;
	
	for(int i=0;i<size;i++){
		ifstream in_file(files[i].c_str());
		string num;

		if(!in_file.is_open()){
			cout << "Error: Not Entering The File" << endl;
		}

		float f;
		while(getline(in_file, num)){
			istringstream ss(num);
			ss >> f;
			input.push_back(f);
			s++;
			Median = getMedian(input, s);
			out_file << setprecision(1) << fixed << Median << endl;
		}
		in_file.close();
	}

	
	return 0;
}
