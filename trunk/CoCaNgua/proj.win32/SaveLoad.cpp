#include "SaveLoad.h"
#include "Config.h"
#include <string>
using namespace std;

SaveLoad::SaveLoad(void)
{

}


SaveLoad::~SaveLoad(void)
{
}

bool SaveLoad::checkExist(string fileName)
{
	ifstream ifile(fileName);
	if(ifile.is_open()){
		ifile.close();
		return true;
	}
	return false;
}
Data SaveLoad::loadFromFile(int mode){
	Data data = {CLASSIC, 0, 0, false, false, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, false};
	string fileName = getFileName(mode);
	ifstream ifs(fileName, ios::binary | ios::in);
	if(ifs.is_open()){
		ifs.read((char *)&data, sizeof(data));
		ifs.close();
	}
	return data;
}

void SaveLoad::saveToFile(Data data, int mode){
	string fileName = getFileName(mode);
	ofstream ofs(fileName, ios::binary | ios::out);
	ofs.write((char *)&data, sizeof(data));
}

string SaveLoad::getFileName(int mode){
	string fileName;
	switch(mode){
	case CLASSIC:
	default:
		fileName = "classic.bin";
		break;
	case MODERN:
		fileName = "modern.bin";
		break;
	case RACING:
		fileName = "racing.bin";
		break;
	case AI:
		fileName = "ai.bin";
		break;
	}
	return fileName;
}
