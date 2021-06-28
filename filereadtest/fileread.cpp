#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//If you want to avoid reading into character arrays, 
//you can use the C++ string getline() function to read lines into strings
void ReadDataFromFileLBLIntoString()
{
    ifstream fin("data/mref-test.fa");  
    string s;  
    while( getline(fin,s) )
    {    
        cout << "Read from file: " << s << endl; 
    }
}


int main()
{
    ReadDataFromFileLBLIntoString();

    return 0;
}