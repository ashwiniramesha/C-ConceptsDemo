#ifndef __FILE_H_INCLUDED__
#define __FILE_H_INCLUDED__

#include<string>
#include<cstring>
#include<iostream>
#include<memory>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
#include<errno.h>
#include<fstream>

using namespace std;

class file
{
	public:
		string name;
		string extension;
		string linkCount;
		bool exists;
		
		//parametrized constructor with default arguments
		file(string fname1, string ext1="", bool exist=0)
		{
			name = fname1;
			extension = ext1;
			exists = exist;
		}
		
		//default constructor
		file()
		{
			name = "";
			extension = "";
			exists = 0;
		}

		file& operator=(file);
		
		//get-methods are const since they do not alter the object in any manner.
		const string getName();
		const string getExt();
		const string getType();

		virtual void readContents();
		static  string  fetchExt(string);
		static bool doesExist(string);
		static bool checkIfASCII(string);
		static bool checkIfDir(string);
		static void printUsage();
		
		//virtual destructor to avoid undefined behaviour during the run-time polymorphism.
		virtual ~file()
		{}
		
	private:
		string md5sum;
		string getMd5();

};

class dir:public file
{
	public:

		dir(string fname1, bool exist)
		{
			name = fname1;
			exists = exist;
		}
		void readContents();

};

bool checkIfASCII(string fname)
{
	int status;
	struct stat st_buf;

	status = stat (fname.c_str(), &st_buf);
	if (status != 0) {
		printf ("Error, errno = %d\n", errno);
		return 1;
	}

	if (S_ISREG (st_buf.st_mode)) {
		return true; 
	}
	if (S_ISDIR (st_buf.st_mode)) {
		return false; 
	}
}

bool checkIfDir(string fname)
{
	int status;
	struct stat st_buf;

	status = stat (fname.c_str(), &st_buf);
	if (status != 0) 
	{
		printf ("Error, errno = %d\n", errno);
		return 1;
	}

	if (S_ISREG (st_buf.st_mode)) {
		return false;
	}
	if (S_ISDIR (st_buf.st_mode)) {
		return true;
	}
}

void file::readContents()
{
	cout<<"Input is a file. Contents are as follows:"<<endl;
	ifstream filename((this->name).c_str());

	string line;
	if (filename.is_open())
	{
		while ( getline (filename,line) )
		{
			cout << line << '\n';
		}
		filename.close();
	}

	else cout << "Unable to open file"; 
}

void dir::readContents()
{
	cout<<"Input is a directory. Directory contents are listed below:"<<endl;
	string content = "content";

	DIR *directory;
	struct dirent *entry;

	if ((directory = opendir((this->name.c_str()))) != NULL) 
	{
		/* print all the files and directories within directory */
		while ((entry = readdir(directory)) != NULL)
		{
			cout<<entry->d_name<<endl;
		}

		closedir(directory);
	}

	else
	{
		/* could not open directory */
		perror ("failed to open directory");

	}

}

string file::fetchExt(string filename)
{
	std::string::size_type idx;
	std::string ext;
	idx = filename.rfind('.');

	if(idx != std::string::npos)
	{
		ext = filename.substr(idx+1);
	}
	else
	{
		ext = "";
	}
	return ext;
}

file& file::operator=(file fname_src)
{
	cout<<"equating fileptrs."<<endl;
	ifstream doc1;
	ofstream doc2;

	doc1.open((fname_src.name).c_str());
	doc2.open((this->name).c_str());

	string str;
	getline(doc1, str);
	doc2<< str<< endl;
	doc1.close();
	doc2.close();

	return *this; 
}

bool file::doesExist(string name)
{
	struct stat   buffer;
	return (stat (name.c_str(), &buffer) == 0);

}

void file::printUsage()
{
	cout<<"Usage:"<<endl<<"To read the contents of a file/directory: <executable name> read <file-path/directory-path>"<<endl<<"To clone a file: <executable name> <destination-filename> = <source-filepath>";
}

#endif
