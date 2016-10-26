/*Patrick Weiss
SetPort: Change Order 4
10/9/16
I declare that all code contained within this document is either written by myself or provided for me by the Professor.*/

#include <iostream> //included for string class, cout, etc;
#include <sstream> //included for sstream object to force a string into int (replaces stoi)
#include <fstream> //included for reading from a file
#include <cstdlib> //included for system()
#include <vector> //for Locale variable manipulation
#include <cctype>

using namespace std;

//prototypes
void about();
void error();
void usage();
void version();
string getLang();
string validEnv(string str);
void usingDefaultLang();//helper function for getLang

enum {
LISTENING
};

//Global Consts
const string DEFAULT_LANG = "en";
const int MAX_PORT = 65535; //if port > MAX_PORT : out of range
const int MAX_ARGS = 4; // Max args from the command line

//Global Variables
string lang;

int main(int argc, char *args[]){

    getLang();//get local environment language
   
    vector <string>msg;
    string line;
    ifstream in("setport.messages_" + lang + ".txt");//open correct language file for couts
    while (!in.eof()){
        
        getline(in, line);
        in >> line;
        msg.push_back(line);
    }
    //TEST: cout<< msg[LISTENING] << endl;

    //Case #1: Only One Arg
    if (argc == 1){
        usage();
        return 0;
    }

    //Case #2: Too Many Args
    if (argc > MAX_ARGS){
        error();
        usage();
        return 1;
    }
    
    string argOne(args[1]);//set args[1] in string container; flag
    
    //Case #3: Two Args (setport -h,setport --help,setport -?,setport -v,setport --version,setport -!,setport --about)
    if (argc == 2){//if 2 args were given
        if (argOne.compare("-h") == 0 || argOne.compare("--help") == 0 || argOne.compare("-?") == 0){
            // TEST: cout << "\nsweet!" << endl;
            usage();
            return 0;
        }
        if (argOne.compare("-v") == 0 || argOne.compare("--version") == 0 ){
            version();
            return 0;
        }
        if (argOne.compare("-!") == 0 || argOne.compare("--about") == 0 ){
            about();
            return 0;
        }
        //TEST: cout << "\ndude..." << endl;
        error();
        usage();
        return 1;
    }
    
    string argTwo(args[2]);//set args[2] in string container; port/-e
    
    //Case #4: Three Args (setport -p {int},setport --port {int},setport -p -e,setport --port -e)
    if (argc == 3){
        if (argOne.compare("-p") != 0 && argOne.compare("--port") != 0){
            error();
            usage();
            return 1;
        }
        if (argTwo.compare("-e") == 0){
            //Here it was necessary to do my own string parsing due to a compiler error in C9
            //because 'char* printEnv = "printenv PORT";' is deprecated and can't be used when doing 'make setport' 
            string printenv = "printenv PORT";
            char* printEnv;//container to convert our strings to char* array
            printEnv = (char*)printenv.c_str();//convert our new string back to old stile c-string
            cout << "printenv PORT"<<endl;
            system(printEnv);
            return 0;
        }
        for(int i = 0; i < argTwo.size(); ++i){
            if (!isdigit(argTwo[i])){
                error();
                usage();
                return 1;
            }
        }//check if each char is a digit
        
        //Case #4a: Port Within Range
        //This method used due to compiler error when doing 'make setport' vs using stoi()
        int port;//int container for port
        stringstream ss(argTwo);//stream object
        ss >> port;
    
        if (port < 0 || port > MAX_PORT){//port out of range
            error();
            usage();
            return 1;
        }
    }
    
    //Case #5: Four Args (setport -p -e MY_PORT,)
    if (argc == 4){
        string argThree(args[3]);//set args[3] in string container; port
    
        if (argOne.compare("-p") != 0 && argOne.compare("--port") != 0){
            error();
            usage();
            return 1;
        }
        if (argTwo.compare("-e") != 0){
            error();
            usage();
            return 1;
        }
        if (argThree.compare("MY_PORT") == 0){
            //Here it was necessary to do my own string parsing due to a compiler error in C9
            //because 'char* printEnv = "printenv MY_PORT";' is deprecated and can't be used when doing 'make setport' 
            string printenv = "printenv MY_PORT";
            char* printEnv;//container to convert our strings to char* array
            printEnv = (char*)printenv.c_str();//convert our new string back to old stile c-string
            cout << "printenv MY_PORT\t"<<endl;
            system(printEnv);
            return 0;
        }
        
        //If they dont give either MY_PORT as args[3] or a valid PORT env variable
        error();
        usage();
        return 1;
    }

    cout << msg[LISTENING] << argTwo << endl << endl;
    //cout << "\nListening to port:\t" << argTwo << endl << endl;
    //cout << "string lang was set to:\t" << getLang() << endl;
    return 0;//Success
}

void about(){
    fstream outputStream;
    outputStream.open("setport.about_" + lang + ".txt"); //open file into the from stream object
    //TEST: outputStream.open("setport.about_es.txt");
    
    if (outputStream.fail()){
        usingDefaultLang();
        outputStream.open("setport.about_en.txt");
        if (outputStream.fail()){
            cout << "Could not open setport.about_en.txt!!!\n";
        }//Open Default language file failure
    }//Open Local Language file failure
    
    string text;
    while (getline(outputStream, text)){
        cout << text << endl;
    }
    if (outputStream.eof()){
        outputStream.close();
    }//EOF reached; close
};

void error(){
    fstream outputStream;
    outputStream.open("setport.error_" + lang + ".txt");
    if (outputStream.fail()){
        usingDefaultLang();
        outputStream.open("setport.error_en.txt"); 
        if (outputStream.fail()){
            cout << "Could not open setport.error_en.txt!!!\n";
        }//Open Default language file failure
    }//Open Local Language file failure
    
    string text;
    while (getline(outputStream, text)){
        cout << text << endl;
    }
    if (outputStream.eof()){
        outputStream.close();
    }//EOF reached; close
};

void usage(){
    string file = "setport.usage_" + lang + ".txt";
    fstream outputStream;
    outputStream.open(file);
    if (outputStream.fail()){
        usingDefaultLang();
        outputStream.open("setport.usage_en.txt");
        if (outputStream.fail()){
            cout << "Could not open setport.usage_en.txt!!!\n";
        }//Open Default language file failure
    }//Open Local Language file failure
    
    string text;
    while (getline(outputStream, text)){
        cout << text << endl;
    }
    if (outputStream.eof()){
        outputStream.close();
    }//EOF reached; close
};

void version(){
    cout << "\nVersion:\t1.1.3a\n\n";
};

string getLang(){
    char* envLang;
    envLang = getenv ("LANGUAGE");
    string local(envLang);//parse from char* to string
    //LANGUAGE
    if (local == "" || local == "C" || local == "C.UTF-8"){//If env variable set to these, ignore.
        //TEST:: return lang = "es";
        return lang = DEFAULT_LANG;
    }
    //LC_ALL
    if (envLang == NULL){
        envLang = getenv ("LC_ALL");
        string local(envLang);
        if (local == "" || local == "C" || local == "C.UTF-8"){
            return lang = DEFAULT_LANG;
        }
    }
    //LC_MESSAGES
    if (envLang == NULL){
        envLang = getenv ("LC_MESSAGES");
        string local(envLang);
        if (local == "" || local == "C" || local == "C.UTF-8"){
            return lang = DEFAULT_LANG;
        }
    }
    //LANG
    if (envLang == NULL){
        envLang = getenv ("LANG");
        string local(envLang);
        if (local == "" || local == "C" || local == "C.UTF-8"){
            return lang = DEFAULT_LANG;
        }
    }

    local = validEnv(local);
    return lang = local;
};

string validEnv(string envVar){
    string tempString;
    //Case:(en,es)
    if (envVar.size() == 2){
        if (islower(envVar[0]) && islower(envVar[1])){
            return envVar;
        }
    }
    //Case(en_US,es_MX,es_AG)
    if (envVar.size() == 5){
        if (islower(envVar[0]) && islower(envVar[1])){
            if (envVar[2] == '_'){
                if (isupper(envVar[3] && envVar[4])){
                    return envVar.substr(0,2);
                }
            }
        }
    }
    //Case; (en.UTF-8,es.UTF-8)
     if (envVar.size() == 8){
        if (islower(envVar[0]) && islower(envVar[1])){
            tempString = envVar.substr(2,6);
            if (tempString.compare(".UTF-8") == 0){
                return envVar.substr(0,2);
            }
        }
    }
    //Case:(en_US.UTF-8,en_UK.UTF-8,es_MX.UTF-8,es_AG.UTF-8)
    if (envVar.size() == 11){
        if (islower(envVar[0]) && islower(envVar[1])){
            if (envVar[2] == '_'){
                if (isupper(envVar[3]) && isupper(envVar[4])){
                    tempString = envVar.substr(5,6);
                    if (tempString.compare(".UTF-8") == 0){
                        return envVar.substr(0,2);
                    }
                }
            }
        }
    }
    
    //Default: didn't recognise env Variable
    cout << "\nDidn't recognise environment variable; Using English.\n";
    return DEFAULT_LANG;
};

void usingDefaultLang(){
cout << "\nMissing " << lang << " translation file. Using English.\n\n";
};