#include"./fileUtil.h"
using namespace std;

int main(int argc, char* argv[])
{
	bool proceed;
	switch(argc)
	{
/* This case demonstrates dynamic polymorphism. 
   The decision to bind to base class or derived class "readContents()" 	
    happens during the run-time based on the type of object the base class pointer points to.*/
	
		case 3:  if(strcmp(argv[1],"read")==0)
			 {
				 file* srcFptr = NULL;

				 string filename = string(argv[2]);
				 bool isASCIIFile = checkIfASCII(filename);
				 string ext = file::fetchExt(filename); 
				 bool exists = file::doesExist(filename);
				 bool isDir = checkIfDir(filename);

				 if(isASCIIFile)
				 {
					 srcFptr = new file(filename, ext, exists);
				 }
				 else if(isDir)
				 {
					 srcFptr = new dir(filename, exists);                 
				 }               

				 srcFptr->readContents();
			 }
			 break;

		case 4:
            {
				/*This case demonstrates "=" operator overloading by cloning the right hand side file  
				into a new file with a name mentioned on the left of the operator.*/
				
				string srcFile = string(argv[3]); 
				string destFile = string(argv[1]); 
				string ext = file::fetchExt(srcFile); 
				bool exists = file::doesExist(srcFile);
				file srcfileobj(srcFile, ext, exists);
				if(strcmp(argv[2], "=")==0)
				{
					file destfileobj(destFile);
					destfileobj = srcfileobj; 
				}
            }
			break;

		default: 
				{
					cout<<"Invalid command"<<endl;
					file::printUsage();
				}	
				break;

	}
}
