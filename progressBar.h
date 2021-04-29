#include<limits>
#ifndef PROGESSBAR_H
#define PROGESSBAR_H
class ProgressBar {
private:
	bool start = false;
	int BAR_count = 0;
	float parcent = 0;
	const char BAR = '#';
	const char BLANK = ' ';
	const int LEN = 40;
	const int SPEED = 20;
	int max = INT_MIN; // �۾���
	float tick = (float)100 / LEN; // 5%���� �߰� ���
	int count = 0; // �۾� ����
	ProgressBar();
	void isDone();
	void isStart();
public:
	ProgressBar(int max);
	bool printProgress(int count);
};
#endif // !PROGESSBAR_H
