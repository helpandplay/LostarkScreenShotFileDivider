#include <filesystem>
#include<string>
#include<iostream>
#include"processFile.h"

using namespace std;
namespace fs = filesystem;


void init();
int main(void) {
	init();
}
void init() {
	string path;
	string output;
	cout << "스크린샷이 있는 파일 경로를 붙여 넣으세요. >> ";
	getline(cin, path, '\n');
	ProcessFile pf(path);
	cout << "저장할 경로를 붙여 넣으세요 (드라이브 내부는 안됩니다) >> ";
	getline(cin, output, '\n');
	pf.setOutput(output);
	pf.start();

}