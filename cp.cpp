//==========================================================================
// File: cp.cpp
//==========================================================================

#include "Timer.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char** argv)
{

        int inp, outp;
        bool flag = false;
        if (argc == 4)
        {
                int i;
                int inalready = 0;
		for(i = 1; i < argc; i++)
                {
                        if (0 == strcmp(argv[i],"-a"))
                        {
                                if(!flag)
                                {
                                        flag = true;
                                }
                                else{
                                        cout << "Error: too many flags" << endl;
                                        exit(1);
                                }
                        }
                        else if(inalready == 0)
                        {
                                inp = i;
                                inalready++;
                        }
                        else if(inalready == 1)
                        {
                                outp = i;
             			inalready++;
                        }
                        else if(inalready == 2)
                        {
                                cout << "Error: too many files" << endl;
                                exit(1);
                        }
                }
        }
        else if(argc == 3)
        {
                inp = 1;
                outp = 2;
        }
        else
        {
                cout << "Error: incorrect amount of arguements1" << endl;
                exit(1);

        }
        ifstream in(argv[inp]);
        ofstream out(argv[outp]);
        int fd = open(argv[inp], O_RDWR);
        if(fd == -1){
                perror("open");
                exit(1);
        }
        int fd2 = open(argv[outp], O_RDWR|O_CREAT);
        if(fd2 == -1){
                perror("open2");
                exit(1);
        }
	if(!flag){
		char inChar;

		if (!in.good())
		{
		        cout << "Cannot read file.\n";
		        exit(1);
		}
		while (in.good())
		{
		        inChar = in.get();
		        if (in.good())
		        {
		                out.put(inChar);
		        }
		}
        }
	else{	
		Timer t1;
        	double e1UsrTime;
        	double e1SysTime;
        	double e1ClkTime;
		t1.start();
		char inChar;

		if (!in.good())
		{
		        cout << "Cannot read file.\n";
		        exit(1);
		}
		while (in.good())
		{
		        inChar = in.get();
		        if (in.good())
		        {
		                out.put(inChar);
		        }
		}
		cout << "---------------------------------------" << endl;
		cout << "get and put" << endl;
		cout << "---------------------------------------" << endl;
		if (-1 == t1.elapsedWallclockTime(e1ClkTime))
		{
		        cout << "elapsedWallclockTime failed." << endl;
		        exit(1);
		}
		if (-1 == t1.elapsedUserTime(e1UsrTime))
		{
		        cout << "elapsedUserTime failed." << endl;
		        exit(1);
		}
		if (-1 == t1.elapsedSystemTime(e1SysTime))
		{
		        cout << "elapsedSystemTime failed." << endl;
		        exit(1);
		}
		if (-1 == t1.elapsedTime(e1ClkTime, e1UsrTime, e1SysTime))
		{
			cout << "elapsedTime failed." << endl;
		        exit(1);
		}


		cout << "ClockTime:  " << e1ClkTime << endl;
		cout << "UserTime:  " << e1UsrTime << endl;
		cout << "SystemTime:  " << e1SysTime << endl;


		cout << "---------------------------------------" << endl;




		Timer t2;
        	double e2UsrTime;
        	double e2SysTime;
        	double e2ClkTime;


		char cbuff;
		void* buf = &cbuff;
		while(read(fd, buf, 1))
		{
		        if(!write(fd2, buf, 1)){
				perror("write");
				exit(1);
			}
		}

		
		cout << "Read and Write w/o Buffer" << endl;
		cout << "---------------------------------------" << endl;
		if (-1 == t2.elapsedWallclockTime(e2ClkTime))
		{
		        cout << "elapsedWallclockTime failed." << endl;
		        exit(1);
		}
		if (-1 == t2.elapsedUserTime(e2UsrTime))
		{
		        cout << "elapsedUserTime failed." << endl;
		        exit(1);
		}
		if (-1 == t2.elapsedSystemTime(e2SysTime))
		{
		        cout << "elapsedSystemTime failed." << endl;
		        exit(1);
		}
		if (-1 == t2.elapsedTime(e2ClkTime, e2UsrTime, e2SysTime))
		{
			cout << "elapsedTime failed." << endl;
		        exit(1);
		}
		cout << "ClockTime:  " << e2ClkTime << endl;
		cout << "UserTime:  " << e2UsrTime << endl;
		cout << "SystemTime:  " << e2SysTime << endl;


		cout << "---------------------------------------" << endl;


		Timer t3;
        	double e3UsrTime;
        	double e3SysTime;
        	double e3ClkTime;
		char dbuff[BUFSIZ];
		void* dbuf = dbuff;

		
		if(-1 == read(fd, dbuf, BUFSIZ)){
			perror("read");
			exit(1);
		}
		if(!write(fd2, dbuf, BUFSIZ)){
			perror("write");
			exit(1);
		}
		cout << "Read and Write w/Buffer" << endl;
		cout << "---------------------------------------" << endl;
		if (-1 == t3.elapsedWallclockTime(e2ClkTime))
		{
		        cout << "elapsedWallclockTime failed." << endl;
		        exit(1);
		}
		if (-1 == t3.elapsedUserTime(e2UsrTime))
		{
		        cout << "elapsedUserTime failed." << endl;
		        exit(1);
		}
		if (-1 == t3.elapsedSystemTime(e2SysTime))
		{
		        cout << "elapsedSystemTime failed." << endl;
		        exit(1);
		}
		if (-1 == t3.elapsedTime(e2ClkTime, e2UsrTime, e2SysTime))
		{
			cout << "elapsedTime failed." << endl;
		        exit(1);
		}
		cout << "ClockTime:  " << e3ClkTime << endl;
		cout << "UserTime:  " << e3UsrTime << endl;
		cout << "SystemTime:  " << e3SysTime << endl;
		cout << "---------------------------------------" << endl;
		
	}

        in.close();
        out.close();

        if (-1 == close(fd)){
		perror("close");
	}
        if (-1 == close(fd2)){
		perror("close");
	}

        return 0;

}
