#include "stdio.h"
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>

#ifndef PORTSETTER_H
#define PORTSETTER_H

using namespace std;

//FUNCTION DECLARATIONS
//main
int main(int argc, char* args[]);
//valid
int validHelp();
int validAbout();
int validVersion();
int validPort(int portNumber);
//invalid
void invalidHelp();
int invalidArguements();
int invalidFlag();
int invalidPortRange();
int invalidEnvVar();
void checkLanguage();
void checkFormatting(string envString, string whichEnv);

//MEMBER VARIABLES
string* languageArray;
char* langEnv;
//The language defaults to English
string firstTwo = "en";


enum {
   VALID_PORT, 
   INVALID_ARGUEMENT,
   INVALID_FLAG,
   INVALID_RANGE,
   INVALID_ENVVAR
};

// en
string en[] = {		//TODO: Make this go to a file
    "Listening on port",
    "invalid arguement \n"
	"Please check that only the help flag OR the port flag has been entered \n"
	"Only one space between the flag and the port will be accepted \n \n",
    "invalid flag \n"
	"Please only input the listed valid flags \n"
	"The valid flags are listed in the following help screen \n"
	"After the port flag there is one space and then a real integer\n",
    "Please make sure that the port is in the accepted port range from 0 to 65000\n"
	"Only integer input is accepted, no characters are accpeted \n \n",
    "invalid environment variable \n"
	"the specified environment variable does not exist \n \n"
};
	
// es
string es[] = {
	"Escuchando en el puerto",
	"Argumento no válido \n"
	"Por favor, compruebe que sólo se ha entrado en el indicador de la ayuda o la bandera de puerto \n"
	"Sólo un espacio entre la bandera y el puerto será aceptada \n \n",
	"Bandera no válido \n"
	"Por favor, solamente las banderas de entrada válidas que se indican \n"
	"Las banderas válidos se enumeran en la siguiente pantalla de ayuda \n"
	"Después de la bandera del puerto hay un espacio y luego un verdadero número entero \n",
	"Por favor, asegúrese de que el puerto está en el rango de puertos aceptado 0-65000\n"
	"Sólo entrada de número entero es aceptado, no hay ningún carácter accpeted\n \n",
	"Variable de entorno no válido \n"
	"La variable de entorno especificado no existe \n \n"
};

//main
int main(int argc, char* args[]) {
	//Initialize the needed variables
	string flag = "";
	string port = "";
	string eFlag = "";
	char* customEnv;
	int portNumber = -1337;
	string envVar;
	int envVal;	
	
	//Check the language
	checkLanguage();
	if (firstTwo == "es"){	//TODO: Time allowing write this to a file
		languageArray = es;
	} else {
		languageArray = en;
	}

	//If there are no arguements return the help screen
	if (argc == 1) {
		return validHelp();
	}
	//If there are more than 1 args inputted then set the 2nd arg (args[1]) to be the string flag
	if (argc > 1) {
		flag = args[1];
	}
	//If there are more than 2 args inputted then set the 3rd arg (arg[2]) to be the port
	if (argc > 2) {
		port = args[2];
	}
	//If there are more than 3 arguements and the args[2] is not the -e flag throw errors
	if (argc > 3) {
		eFlag = args[2];
		customEnv = args[3];
		if(eFlag.compare("-e") != 0){
			return invalidArguements();	
		}
	}
	//If there are more than 4 arguements the user entered too much input	
	if (argc > 4){
		return invalidArguements();	
	}
	
	if ((eFlag.compare("-e") == 0) && (flag.compare("-p") == 0 || flag.compare("--port") == 0)){
		//Default case where the PORT environment variable is used
		if (argc == 3){
			envVar = getenv("PORT");
			//If PORT does not exist
			if (envVar.c_str() == nullptr){
				return invalidEnvVar();
			} else {
				envVal = atoi(envVar.c_str());	
				return validPort(envVal);				
			}
		}
		//Case where a custom, specified, environment variable is used
		if (argc == 4){
			envVar = getenv(customEnv);
			//if the custom environment variable does not exist
			if (envVar.c_str() == nullptr){
				return invalidEnvVar();
			} else {
				envVal = atoi(envVar.c_str());	
				return validPort(envVal);
			}
		}
	}

	//HELP CONDITIONS 
	//Only the help flag has been entered
	if ((argc == 2) && (flag.compare("-h") == 0 || flag.compare("--help") == 0 || flag.compare("-?") == 0)) {
		return validHelp();
	}
	
	//ABOUT CONDITIONS 
	//Only the about flag has been entered
	if ((argc == 2) && (flag.compare("-!") == 0 || flag.compare("--about") == 0)) {
		return validAbout();
	}

	//VERSION CONDITIONS
	if ((argc == 2) && (flag.compare("-v") == 0 || flag.compare("--version") == 0)) {
		return validVersion();
	}

	//PORT CONDITIONS
	//Only the flag and port number have been entered
	if ((argc == 3) && (flag.compare("-p") == 0 || flag.compare("--port") == 0)) {

		//If it is not a valid integer it may be a flag and that is checked for here
		for (int i = 0; i < port.size(); ++i){
			if (!isdigit(port[i])) {		
				return invalidPortRange();
			}			
		}

		//Convert the string input to an int
		portNumber = stoi(port);
		//Another int variable is created so that the portNumber variable is not reset to 0
		int tempPortNumber = portNumber;

		//Calculate the number of digits of the converted number
		int numberOfDigits = 0;
		while (tempPortNumber) {
			numberOfDigits++;
			tempPortNumber = tempPortNumber / 10;
		}
		//if chars are hidden in numbers
		if (numberOfDigits != port.length()) {
			return invalidPortRange();
		}

		//if the port is outside of the accepted port range		
		if ((0 >= portNumber) || (portNumber > 65000)) {
			return invalidPortRange();
		}
		return validPort(portNumber);
	}
	else {
		//Once this far if there are any other errors they must be invalid Flag errors
		return invalidFlag();
	}
}

//------------------------------------------VALID---------------------------------------------------- 
//validHelp
int validHelp() {
	//Call invalid help to print the help screen
	invalidHelp();
	return 0;
}

//validAbout
int validAbout(){
	string currentLine = "";	
	//Determine whether to use another language file or english about file
		ifstream aboutFile ("portsetter.about_" + firstTwo + ".txt");
		if(aboutFile.is_open()){
			while(getline(aboutFile, currentLine)){
				cout << currentLine << endl;
			}
			aboutFile.close();
		} else {
			printf("Missing %s translation files. Using English. \n", firstTwo.c_str());
			firstTwo = "en";
			validAbout();		
		}
	return 0;
}

//validVersion
int validVersion(){
	//version is 1337AF
	printf("version: 1337AF \n");
	return 0;
}

//validPort
int validPort(int portNumber) {
	std::printf("%s %d\n", languageArray[VALID_PORT].c_str(), portNumber);
	return 0;
}

//------------------------------------------INVALID--------------------------------------------------
//invalidHelp
void invalidHelp() {
	string currentLine = "";	
	//Determine which language to use
		//ENGLISH
		ifstream helpFile ("portsetter.usage_" + firstTwo + ".txt");
		if(helpFile.is_open()){
			while(getline(helpFile, currentLine)){
				cout << currentLine << endl;
			}
			helpFile.close();
		} else {
			printf("Missing %s translation files. Using English. \n", firstTwo.c_str());
			firstTwo = "en";
			invalidHelp();
		}
}

//invalidArguements	
//When too many arguements are entered into the program
int invalidArguements() {
	printf("%s", languageArray[INVALID_ARGUEMENT].c_str());
	invalidHelp();
	return 1;
}

//invalidFlag
int invalidFlag() {
	printf("%s", languageArray[INVALID_FLAG].c_str());
	invalidHelp();
	return 2;
}

//invalidPortRange			
int invalidPortRange() {	
	printf("%s", languageArray[INVALID_RANGE].c_str());
	invalidHelp();
	return 3;
}


//invalidEnvVar
int invalidEnvVar(){	
	printf("%s", languageArray[INVALID_ENVVAR].c_str());
		return 4;
}
//----------------------------checkLanguage and checkFormatting-------------------------------------------
//checkLanguage
void checkLanguage(){
	//LANGUAGE
	langEnv = getenv("LANGUAGE");
	if (langEnv == nullptr || strcmp(langEnv, "") == 0 || strcmp(langEnv, "C") == 0 || strcmp(langEnv, "C.UTF-8") == 0){
		//LC_ALL
		langEnv = getenv("LC_ALL");
		if (langEnv == nullptr || strcmp(langEnv, "") == 0 || strcmp(langEnv, "C") == 0 || strcmp(langEnv, "C.UTF-8") == 0){
			//LC_MESSAGES
			langEnv = getenv("LC_MESSAGES");
			if (langEnv == nullptr || strcmp(langEnv, "") == 0 || strcmp(langEnv, "C") == 0 || strcmp(langEnv, "C.UTF-8") == 0){
				//LANG
				langEnv = getenv("LANG");
					if (langEnv == nullptr || strcmp(langEnv, "") == 0 || strcmp(langEnv, "C") == 0 || strcmp(langEnv, "C.UTF-8") == 0){
					//none of the environment variables are set, default to english	
					firstTwo = "en";
				} else {
					checkFormatting(langEnv, "LANG");	//LANG		
				}	
			} else {
				checkFormatting(langEnv, "LC_MESSAGES");	//LC_MESSAGES
			}
		} else {
			checkFormatting(langEnv, "LC_ALL");		//LC_ALL
		}
	} else {
		checkFormatting(langEnv, "LANGUAGE");	//LANGUAGE
	}	
}

//checkFormatting
void checkFormatting(string envString, string whichEnv){
	bool formatIsCorrect = false;
	string tempString;
	//ex: es
	if(envString.size() == 2){
		if (islower(envString[0]) && islower(envString[1])){
			formatIsCorrect = true;
			firstTwo = envString;
		}
	}
	//ex: es_MX
	if(envString.size() == 5){
		if (islower(envString[0]) && islower(envString[1])){
			if(envString[2] =='_'){
				if(isupper(envString[3]) && isupper(envString[4])){
					formatIsCorrect = true;
					firstTwo = envString.substr(0, 2);
				}
			}
		}
	}
	//ex: es.UTF-8
	if(envString.size() == 8){
		if (islower(envString[0]) && islower(envString[1])){
			tempString = envString.substr(2, 6);
			if(tempString.compare(".UTF-8") ==0){
				formatIsCorrect = true;
				firstTwo = envString.substr(0, 2);
			}
		}
	}
	//ex: es_MX.UTF-8
	if(envString.size() == 11){
		if (islower(envString[0]) && islower(envString[1])){
			if(envString[2] == '_'){
				if(isupper(envString[3]) && isupper(envString[4])){
					tempString = envString.substr(5, 6);
					if(tempString.compare(".UTF-8") ==0){
						formatIsCorrect = true;
						firstTwo = envString.substr(0, 2);
					}
				}
			}
		}
	}
	//If the formatting is incorrect
	if (formatIsCorrect == false){
		printf("Bad language specification in environment variable %s=%s. Using English. \n", whichEnv.c_str(), envString.c_str());
		firstTwo = "en";
	}
}
#endif