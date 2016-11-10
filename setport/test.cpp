/*Patrick Weiss
SetPort
test.cpp
9/13/16
I declare that all code contained within this document is either written
by myself or provided for me by the Professor within lecture time.*/

#include<iostream>
#include<fstream>

using namespace std;

int main(){
   
    fstream outputStream;   //read from file object
    outputStream.open("tests.txt"); //open file into the from stream object
    if (outputStream.fail()){
        cout << "\nCould not open tests.txt.\n";
        return 1;
    }
    
    string test;//string container
    int statusCode; //int container for each test's statusCode
    char* args;//container to convert our strings to char* array
    
    while (getline(outputStream, test)){
        cout << "\nentered test: " << test << endl;
        args = (char*)test.c_str();//convert our new string back to old stile c-string
        statusCode = system(args) / 256;//system call the command to be run on the commandline (our test); set status code (good/sad)
        cout <<"\nprogram exited with status code:\t"<< statusCode <<endl;
        cout << "_________________________________________________________________________";
    }
    cout << endl;
    
    if (outputStream.eof()){
        outputStream.close();
    }
    
    return 0;
}
