#include <iostream>

using namespace std;

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <cstdlib>
#include <stdio.h>
#include <iomanip>
#include <vector>
#include <fcntl.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

#define FLAG_a 1
#define FLAG_l 2
#define FLAG_R 4


void linfo(string befr, string bop){
	string hello = befr + "/" + bop;
	const char* file = hello.c_str();
	struct stat statbuf;
	bool isdir = false;
	int boo = 0;
	if(-1 == stat(file,&statbuf)){
		perror("stat");
		exit(1);
	}	
	if (S_ISDIR(statbuf.st_mode)) {
	cout << "d";
	isdir = true;
	}
	else cout << "-";

	if (statbuf.st_mode & S_IRUSR) {
	cout << "r";
	} else cout << "-";
	if (statbuf.st_mode & S_IWUSR) {
	cout << "w";
	} else cout << "-";
	if (statbuf.st_mode & S_IXUSR) {
	cout << "x";
	boo++;
	} else cout << "-";

	if (statbuf.st_mode & S_IRGRP) {
	cout << "r";
	} else cout << "-";
	if (statbuf.st_mode & S_IWGRP) {
	cout << "w";
	} else cout << "-";
	if (statbuf.st_mode & S_IXGRP) {
	cout << "x";
	boo++;
	} else cout << "-";
	if (statbuf.st_mode & S_IROTH) {
	cout << "r";
	} else cout << "-";
	if (statbuf.st_mode & S_IWOTH) {
	cout << "w";
	} else cout << "-";
	if (statbuf.st_mode & S_IXOTH) {
	cout << "x";
	boo++;
	} else cout << "-";

	struct passwd *hub;
	struct group *dub;
	hub = getpwuid(statbuf.st_uid);
	dub = getgrgid(statbuf.st_gid);
	cout << " " << statbuf.st_nlink << " ";
	cout << hub->pw_name << " " << dub->gr_name << " ";
	cout << statbuf.st_size << " ";
	struct tm *acttime;
	char bufferr[80];
	acttime = localtime(&statbuf.st_atime);
	strftime(bufferr, 80, "%b %d %R", acttime);
	cout << bufferr << " ";
	if(isdir){
		cout << "\033[1;34m" << bop << "\033[0m" << endl;
	}
	else if(boo == 3){
		cout << "\033[1;32m" << bop << "\033[0m" << endl;
	}
	else{
	cout << bop << endl;
	}
}

void reading(int flags, string locate){
	DIR *DIRp;
	const char* locat = locate.c_str();
	DIRp = opendir(locat);
	
	if(DIRp == NULL){
		cerr << locate;
		perror("opendir");
		exit(1);	
	}
	struct dirent *rddir;
	vector<char*> held;
	bool aflg = false;

	if((flags & FLAG_a) == FLAG_a){
		aflg = true;
	}


	while((rddir = readdir(DIRp))){
		int error = errno;
		if(error != 0){
			perror("readdir");
			exit(1);
		} 
		if(aflg || rddir->d_name[0] != '.'){
			held.push_back(rddir->d_name);
		}
	}
	for(unsigned i = 0; i < held.size(); i++){
		for(unsigned j = 0; j < held.size(); j++){
			if(strcmp(held.at(i),held.at(j)) < 0){
				char* bop = held.at(i);
				held.at(i) = held.at(j);
				held.at(j) = bop;
			}
		}
	}
	if((flags & FLAG_l) == FLAG_l){
		for(unsigned i = 0; i < held.size(); i++){
			string hep = held.at(i);
			linfo(locate, hep);
		}
	}
	else{
		for(unsigned i = 0; i < held.size(); i++){
			
			struct stat batbuf; 
			const char* pile = locate.c_str();
			if(-1 == stat(pile,&batbuf)){
				perror("stat2");
				exit(1);
			}	
			if (S_ISDIR(batbuf.st_mode)) {
				cout << "\033[1;34m" << held.at(i) << "\033[0m  ";
			}
			else if((batbuf.st_mode & S_IXUSR) && (batbuf.st_mode & S_IXGRP) && (batbuf.st_mode & S_IXOTH)){
				cout << "\033[1;32m" << held.at(i) << "\033[0m  ";
			}
			else{
				cout << held.at(i) << "  ";
			}
		}
		cout << endl;
	}
	
	
	if(-1 == closedir(DIRp)){
		perror("closedir");
	}
}

int main(int argc, char** argv){
	int flags = 0;
	vector<string> direct;
	bool docurr = true;
	for (int i=1; i<argc; i++) {
		if (argv[i][0] == '-') {
			for (int j=1; argv[i][j] != 0; j++) {
				if (argv[i][j] == 'a')
					flags |= FLAG_a;
				else if (argv[i][j] == 'l')
					flags |= FLAG_l;
				else if (argv [i][j] == 'R')
					flags |= FLAG_R;
			}
		}
		else{
			struct stat dirbuf;
			if(-1 == stat(argv[i],&dirbuf)){
				perror("stat3");
				exit(1);
			}
			if(S_ISDIR(dirbuf.st_mode)){
				string hold = argv[i];
				direct.push_back(hold);
				docurr = false;
			}
			else{
				cout << "Directory name not valid" << endl;
				exit(1);
			}
		}
 	}
	if(docurr){
		direct.push_back(".");
	}
	for(unsigned i = 0; i < direct.size(); i++){
		if(direct.size() > 1){
			cout << direct.at(i) << ":" << endl;
		}
		reading(flags, direct.at(i));
		if(direct.size() > 1 && (i != direct.size() - 1)){
			cout << endl;
		}
	}

return 0;




}
