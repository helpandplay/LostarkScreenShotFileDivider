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
	string path = "C:\\Program Files (x86)\\Test\\test";
	string output = "C:\\Users\\user\\Desktop\\�� ���� (3)";
	//cout << "��ũ������ �ִ� ���� ��θ� �ٿ� ��������. >> ";
	//getline(cin, path, '\n');
	ProcessFile pf(path);
	//cout << "������ ��θ� �ٿ� �������� (����̺� ���δ� �ȵ˴ϴ�) >> ";
	//getline(cin, output, '\n');
	pf.setOutput(output);
	pf.start();
}