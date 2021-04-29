#include<string>
#ifndef PROCESSFILE_H
#define PROCESSFILE_H
using namespace std;
class ProcessFile {
private:
	const string SELFIE = "Selfie";
	const string SCREENSHOT = "ScreenShot";
	const string JPG = ".jpg";
	int size;
	string* fileNameList;
	string* filePathList;
	string* fileDateList;
	string* newFileList;
	string screenshotPath = ""; // 경로 저장
	string outputPath = "";
	ProcessFile();
	void bringDateAndNewName();
	int getFilecount();
	void setFileInfo(); // return [path, name]
	void setDirectory();
	void moveFile();
public:
	~ProcessFile();
	ProcessFile(string path);
	void setOutput(string output);
	void start();
};
#endif // !PROCESSFILE_H
