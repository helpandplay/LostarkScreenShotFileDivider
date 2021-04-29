#include"progressBar.h"
#include<iostream>
#include<windows.h>

using namespace std;

ProgressBar::ProgressBar(int max) {
	this->max = max;
}
void ProgressBar::isStart() {
	cout << fixed;
	cout.precision(2);
	this->start = true;
}
void ProgressBar::isDone() {
	cout.unsetf(ios::fixed);
	cout << " Done!";
}
bool ProgressBar::printProgress(int count) {
	if (!this->start) {
		this->isStart();
	}
	if (count > this->max) {
		this->isDone();
		return false;
	}
	cout << '\r' << " [";
	this->parcent = (float)count / this->max * 100;
	this->BAR_count = this->parcent / this->tick;

	for (int i = 0; i < this->LEN; i++) {
		if (this->BAR_count > i) cout << this->BAR;
		else cout << this->BLANK;
	}

	cout << "] " << this->parcent << "%";
	Sleep(this->SPEED);

	return true;
}