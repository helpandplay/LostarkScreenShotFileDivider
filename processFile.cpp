#include"processFile.h"
#include"progressBar.h"
#include<string>
#include<filesystem>
#include<iostream>

using namespace std;
namespace fs = filesystem;

ProcessFile::~ProcessFile() {
	if (this->fileNameList) delete[] fileNameList;
	if (this->filePathList) delete[] filePathList;
	if (this->fileDateList) delete[] fileDateList;
	if (this->newFileList) delete[] newFileList;
}
ProcessFile::ProcessFile(string path) {
	this->screenshotPath = path;

	this->size = getFilecount();
	this->fileNameList = new string[size];
	this->filePathList = new string[size];
	this->fileDateList = new string[size];
	this->newFileList = new string[size];

}

void ProcessFile::bringDateAndNewName() {
	cout << "��¥ ������..." << '\n';

	string spliter = "_";
	int pos = 0;
	string token;
	for (int i = 0; i < this->size; i++) {
		string fileName = this->fileNameList[i];

		stringstream stream(fileName);
		string segment;
		vector<string> seglist;

		while (getline(stream, segment, '_'))
		{
			seglist.push_back(segment);
		}
		this->fileDateList[i] = seglist[1];
		this->newFileList[i] = seglist[2] + seglist[3];
	}
	cout << "��¥ ���� ����" << endl;
}
int ProcessFile::getFilecount() {
	int pos = 0;
	int cnt = 0;
	for (const auto& entry : fs::directory_iterator(this->screenshotPath)) {
		string path = entry.path().string();
		if ((pos = path.find(JPG) != string::npos)) cnt++;
	}
	return cnt;
}
void ProcessFile::setFileInfo() {
	cout << "��� �� �̸� ���� ��..." << '\n';
	string spliter = "\\";

	int i = 0;
	for (const auto& entry : fs::directory_iterator(this->screenshotPath)) {
		string path = entry.path().string(); // �۾��� ������ ���� �̸��� �ȴ�.
		string copyPath = path;
		int pos = 0;
		string token;
		string splitPath;
		while ((pos = copyPath.find(spliter)) != string::npos) {
			token = copyPath.substr(0, pos);
			copyPath.erase(0, pos + spliter.length()); // ���ڿ� �� �պ��� pos�� spliter�� ���̸�ŭ �����.

			splitPath += token + spliter;
		}
		string fileName = copyPath;
		if ((pos = fileName.find(JPG)) != string::npos) {
			this->fileNameList[i] = fileName;
			this->filePathList[i] = splitPath;
			i++;
		}
	}
	cout << "��� �� �̸� ���� ����!" << endl;
}
void ProcessFile::setDirectory() {
	string path = this->outputPath;
	string selfie = path + "\\" + SELFIE;
	string screenshot = path + "\\" + SCREENSHOT;
	bool isSuccess = false;
	try {
		isSuccess = fs::create_directories(selfie);
		if (isSuccess) cout << "Selfie ���� ����� ����!" << '\n';
		isSuccess = fs::create_directories(screenshot);
		if (isSuccess) cout << "Screenshot ���� ����� ����!" << '\n';
	}
	catch (fs::filesystem_error& e) {
		std::cout << e.what() << '\n';
	}
}
void ProcessFile::moveFile() {
	ProgressBar processbar(this->size);


	for (int i = 0; i < this->size; i++) {
		bool isSelfie = false;
		bool isScreenShot = false;
		string fileName = this->fileNameList[i];
		string oldPath = this->filePathList[i] + this->fileNameList[i];
		string newPath = this->outputPath;

		stringstream stream(fileName);
		string segment;
		while (getline(stream, segment, '_'))
		{
			if (segment == SELFIE) isSelfie = true;
			if (segment == SCREENSHOT) isScreenShot = true;
		}
		if (isSelfie) {
			newPath += "\\" + SELFIE;
		}
		if (isScreenShot) {
			newPath += "\\" + SCREENSHOT;
		}
		newPath = newPath + "\\" + this->fileDateList[i];

		fs::path p(newPath.c_str());
		if (!fs::exists(p))fs::create_directories(newPath);
		newPath = newPath + "\\" + this->newFileList[i];
		try {

			fs::rename(oldPath.c_str(), newPath.c_str());

		}
		catch (std::filesystem::filesystem_error& e) {
			std::cout << e.code() << e.what() << '\n';
		}
		processbar.printProgress(i + 1);
	}
	cout << "�Ϸ�!" << endl;
}
void ProcessFile::setOutput(string output) {
	this->outputPath = output;
}
void ProcessFile::start() {
	this->setFileInfo();
	this->setDirectory();
	this->bringDateAndNewName();
	this->moveFile();
}