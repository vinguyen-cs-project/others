#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int main() {

// Huy and Kwin
// INPUT:
// P to R: request
// R to P: assign/holding
// top right: request
// bottom left: assign/allocate
// only need to read in top right and bottom left of matrix
    
 //----reading file------------
	ifstream inFile;
	string filename;
	cout <<"Enter the file name= ";
	cin >> filename;
	inFile.open(filename);
	

	//-------declare character--------------
	int resources, processes;
	vector<int> AvaiRe;	
	vector<vector<int>> DataMatrix;
	
	//-------reading data from the file

	string filedata;
	while(getline(inFile, filedata))
	{	
	// avoid blank line
		if ((filedata.empty()) || (filedata[0] == '\r')) 
			continue;

	// avoid comment lines
		if (filedata[0] == '%' )	
			continue;

	//----------------- get Processes Number
		if (filedata.find("num_processes=") != string::npos)
		{
			string takevalue;
			takevalue = filedata.substr(filedata.find("=") + 1);
			processes = stoi(takevalue);
			continue;
		}

	//------------------ get Resources Number
		if (filedata.find("num_resources=") != string::npos)
		{
			string takevalue;
			takevalue = filedata.substr(filedata.find("=") + 1);
			resources = stoi(takevalue);
			continue;
		}

	
	//------------------- get Available Resources
		if (AvaiRe.empty())
		{
			size_t PosData = 0;
			while (PosData < filedata.length())
			{
				size_t countcomma = filedata.find(",", PosData);
			
				// exit the loop
				if ( countcomma == string::npos) 
					countcomma = filedata.length();
			
				size_t takenumbersize = countcomma - PosData;
				string takevalue = filedata.substr(PosData, takenumbersize);
				AvaiRe.push_back(stoi(takevalue));
				PosData = countcomma + 1;
			}

		continue;
		}
	//------------------get the matrix
		// first, get the Processs Data
		size_t PosData = 0;
		vector<int> RowMatrix;
		while (PosData < filedata.length())
			{
				size_t countcomma = filedata.find(",", PosData);
			
				// exit the loop
				if ( countcomma == string::npos) 
					countcomma = filedata.length();
			
				size_t takenumbersize = countcomma - PosData;
				string takevalue = filedata.substr(PosData, takenumbersize);
				RowMatrix.push_back(stoi(takevalue));
				PosData = countcomma + 1;
			}
		DataMatrix.push_back(RowMatrix);

	} //------------------- end Reading file loop
	

	//---------display
	cout <<processes << endl;
	cout <<resources << endl;
	for (int i=0; i< AvaiRe.size(); i++)
		cout << AvaiRe[i] << " ";
	cout << endl;
	for (int i=0; i< DataMatrix.size(); i++)
	{
		for (int j =0; j < DataMatrix[0].size(); j++) 
			cout << DataMatrix[i][j] << " ";
		cout << endl;
	}
	
	cout <<endl;

//----------------closing file-----------------------
	inFile.close();

/*------------value we get after reading file
	processes = number of Processor
	resources = number of Resources 
	AvaiRe = Available / units of each resource
	DataMatrix = Matrix

*/
    vector<vector<int>> amatrix;
    vector<vector<int>> rmatrix;
    //amatrix[0][0] means process 1, allocation vector of [1,0]

    vector<int> atemp;
    vector<int> rtemp;
// store into 2 N-dimension arrays : allocation, request

    for(int i=0; i<processes; i++)
    {
        for(int j=processes; j<(processes+resources); j++)
        {
            atemp.push_back(DataMatrix[j][i]);
            rtemp.push_back(DataMatrix[i][j]);
        }
        amatrix.push_back(atemp);
        rmatrix.push_back(rtemp);
        atemp.clear();
        rtemp.clear();
    }


// 	i row for P(i)
// 	j column for R(j)
// 	(N resource might not match N process)
   

// Desere and Manasa
// REDUCTION ALGORITHM:
// available: 0, 0, 0; size = num of request
//    vector<int> available(resources, 0);

//used to keep track of which process that still need to be used
   vector<int> temp_proc;
   for(int i=0; i<processes; i++)
   {
       for(int j=0; j<resources; j++)
       {
			AvaiRe[j]-= amatrix[i][j];
       }
	temp_proc.push_back(i);
   }
   for(int i=0; i<AvaiRe.size(); ++i)
   {
	   if(AvaiRe[i]<0)
	   {
		   cout << "The system is in deadlock state";
		   return 0;
	   }
   }
		
// while loop till out of process
    while(temp_proc.size()!=0){
 // 	check for process that its request <= AvaiRe      
        for(int i=0; i<temp_proc.size(); i++)//looping through the process not taken
        {
	    vector<bool> access(resources,false);
            for(int j=0; j<resources; j++)
            {
                if(AvaiRe[j]>=rmatrix[temp_proc[i]][j])
                {
                    access[j]=true;
                }
            }
            if(find(begin(access), end(access), false) == end(access))//meaning there is all true and can add the allocation to AvaiRe
            {
                for(int k=0; k<resources; k++)//add to the alocation part
                {
                    AvaiRe[k] += amatrix[temp_proc[i]][k];
                }
                temp_proc.erase(temp_proc.begin()+i);
                i=-1;
            }
            else if(i==(temp_proc.size()-1))//deadlock
            {
				cout <<"The given Resource Allocation Graph represents a deadlock state.\n";
				return 0;
            }
        }
        
    }
	
// 	if none, exit	
// 	put back that process's holding resource to AvaiRe
	cout <<"The given Resource Allocation Graph doesn't have any deadlock state.\n";
    return 0;
}
