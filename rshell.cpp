#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <cstring>

using namespace std;

int main(){
	bool execute = true;
	while(execute){
		vector<char*> blop;
		string hold;
		char* token;
		char* pew;
		pew = new char[600];

		cout << "$ ";
		getline(cin, hold);
		memcpy(pew, hold.c_str(), hold.size()+1);
		token = strtok (pew, ";NULL");
		while(token != NULL){
			blop.push_back(token);
			token = strtok (NULL, ";NULL");
		}

		char* tocken;
		string check;
		tocken = new char[300];
		char** argv;
		argv = (char**) malloc (blop.size()+1);
		bool hash = false;
		for(unsigned i = 0; i < blop.size(); i++){
			tocken = strtok (blop.at(i), " ");
			int j = 0;
			for(; tocken != NULL && !(hash); j++){
				check = tocken;
				if(check == "exit" || check == "Exit"){
					return 0;
				}
				for(unsigned o = 0; o < check.size(); o++){
					if(check.at(o) == '#'){
						hash = true;
						j++;
					}
				}
				if(!(hash)){
					int du = check.size()+2;
					argv[j] = new char[du];
					argv[j] = tocken;
					tocken = strtok(NULL, " ");
				}
			}
			argv[j] = new char[5];
			argv[j] = NULL;
			
			int pid = fork();

			if(pid == -1){
				perror("fork");
				exit(1);
			}
			
			else if(pid == 0){
				int ex= execvp(argv[0],argv);
				if(ex == -1){
					perror("execvp");
					exit(1);
				}
				break;
			}
			
			else{
				if( -1 == wait(NULL)){
					perror("wait");
				}
				
			}
		}
	}	
	return 0;
}
