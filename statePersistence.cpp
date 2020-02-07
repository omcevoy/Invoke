/*
* Description: Project 1 (cold calling system)
*
* Author: Owen, Mason, James, Zach, Sam
*
* Date of last update: 2/3/2020
*
* Notes:
*
*/
#include "statePersistence.h"
#include "ColdCallClass.h"
#include <cstring>
#include <ctime>
#include <iomanip>

void deleteClass(std::string filename){
    //deletes whichever filename is passed in
    const char* delFile = filename.c_str();
    if (remove(delFile)){
        std::cerr << "There was an error deleting the file" << std::endl;
    }
    return;
}

void createDir() {
	//Get path to directory where the files will be stored
    std::string meta = getPath(1);
    std::string testFile (meta.begin(), meta.end() - 12);
    testFile = testFile + "test.txt";
    std::ofstream testExp (testFile);
    //Check to see if the directory exists by trying to write a file to it
    if (!testExp.is_open()) {
        //If the directory exists, return
        system("mkdir ~/Documents/Invoke");
    }
    else {
        //If the file was created, delete it
        remove(testFile.c_str());
    }
    //get the path for other 2 directories
    std::string hidden = getPath(1);
    std::string present = getPath(0);
    std::string roster = getPath(2);
    hidden = hidden + "test.txt";
    std::ofstream testHid (hidden);
    if (!testHid.is_open()){
        //If the hidden directory does not exist, create it
        system("mkdir ~/Documents/Invoke/.invokeData");
    }
    else{
        remove(hidden.c_str());
    }
    present = present + "test.txt";
    std::ofstream testPres (present);
    if (!testPres.is_open()){
        //If the user directory does not exist, create it
        system("mkdir ~/Documents/Invoke/InvokeReports");
    }
    else {
        remove(present.c_str());
    }
    roster = roster + "test.txt";
    std::ofstream testRoster(roster);
    if(!testRoster.is_open()){
        system("mkdir ~/Documents/Invoke/Rosters");
    }
    else{
        remove(roster.c_str());
    }
}

std::string getPath(int hidden){
	const char* dir = std::getenv("HOME");
	std::string startPath(dir);
    if (hidden == 2){
        std::string endPath = "/Documents/Invoke/Rosters/";
        std::string fullPath = startPath + endPath;
        return fullPath;
    }
	if (hidden == 1) {
		//get path to hidden directory
		std::string endPath = "/Documents/Invoke/.invokeData/";
		std::string fullPath = startPath + endPath;
		return fullPath;
	}
	else{
		//get path to visible directory
		std::string endPath = "/Documents/Invoke/InvokeReports/";
		std::string fullPath = startPath + endPath;
		return fullPath;
	}
}

void saveClassList(std::vector<std::string> class_names){
    std::string path = getPath(1);
    std::string classList = path + "listOfClasses";
    std::ofstream cList (classList);
    if (!cList.is_open()){
        std::cerr << "There was an error writing to the class list file. Please try again." << std::endl;
        createDir();
        return;
    }
    int numClasses = class_names.size();
    for (int i = 0; i < numClasses; i++){
        cList << class_names[i] << '\n';
    }
    cList.close();
    return;
}
std::vector<std::string>
loadClassList(){
    std::vector<std::string> class_names;
    std::string path = getPath(1);
    std::string filename = path + "listOfClasses";
    std::ifstream classList;
    classList.open(filename);
    if (!classList.is_open()){
        std::cerr << "There was an error reading from the class list file. Please try again." << filename << std::endl;
        createDir();
        return class_names;
    }
    while(classList) {
        std::string line;
        while(getline(classList, line, '\n')) {
            class_names.push_back(line);
        }
    }
    return class_names;
}

void storeClass(std::string class_name, std::vector<struct Student *> roster) {
    char t = '\t';
    std::string path = getPath(1);
    std::string filename = path + class_name;
    std::ofstream saveFile (filename);
    int rosterSize = roster.size();
    if (saveFile.is_open()) {
        for (int i = 0; i < rosterSize; i++){
            int partSize = roster[i]->participation.size();
            saveFile << roster[i]->first_name << t << roster[i]->last_name << t << roster[i]->student_id << t << roster[i]->email << t << roster[i]->phonetic_spelling << t << roster[i]->reveal_code << t;
            for (int j = 0; j < partSize; j++) {
                time_t tEvent;
                char flag;
                std::tie(tEvent, flag) = roster[i]->participation[j];
                char buff [sizeof "2011-10-08T07:07:09Z"];
                time(&tEvent);
                if (strftime(buff, sizeof buff, "%Y-%m-%d", gmtime(&tEvent))) {
                    saveFile << buff << ' ' << flag << '>';
                }
            }
            saveFile << '\n';
        }
        saveFile.close();
    }
    else {
        std::cerr << "There was an error storing the class data. Please try again." << filename << std::endl;
        createDir();
    }
}

std::vector<std::shared_ptr<struct Student>>
loadClass(std::string cName){
    char t = '\t';
    std::string path = getPath(1);
    std::string filename = path + cName;
    std::ifstream storageUnit;
    storageUnit.open(filename);
    std::vector<std::shared_ptr<struct Student>>  roster;
    if(!storageUnit.is_open()){

        //std::cerr << "There was an error reading the file. Please try again. " << filename <<  std::endl;
        createDir();
        return roster;
    }
    else{
        std::string line;
        while(getline(storageUnit, line, '\n')){
            //vector which contains data for each individual entry
			std::vector<std::string> entry;
            //allows us to parse the string
			std::stringstream entries(line);
			std::string key;
            while(getline(entries, key, t)){
                entry.push_back(key);
            }
            std::shared_ptr<struct Student> S (new struct Student());
            (*S).first_name = entry[0];
			(*S).last_name = entry[1];
			(*S).student_id = entry[2];
			(*S).email = entry[3];
			(*S).phonetic_spelling = entry[4];
			(*S).reveal_code = entry[5][0];
            int ultimatum = entry.size();
            if (ultimatum >= 7) {
                std::stringstream records(entry[6]);
                std::string temp;
                std::vector<std::string> events;
                while(getline(records, temp, '>')){
                    events.push_back(temp);
                }
                int numParts = events.size();
                    for (int i = 0; i < numParts; i++){
                    std::tuple<time_t, char> times;
                    std::string base = events[i];
                    std::string date (base.begin(), base.begin() + 10);
                    char flag = base[11];
                    //code below is converting a string to a time_t type
                    std::istringstream ss(date);
                    struct std::tm tm;
                    memset(&tm, 0, sizeof(tm));
                    ss >> std::get_time(&tm, "%Y-%m-%d");
                    std::time_t theTime = mktime(&tm);
                    //create the tuple
                    times = std::make_tuple(theTime, flag);
                    //add the tuple to the students participation vector
                    (*S).participation.push_back(times);
                }
            }
            roster.push_back(S);
        }
        storageUnit.close();
        return roster;
    }
}
