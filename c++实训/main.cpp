#include"Click.h"

int main()
{	
	//创建必要存档文件
	for (int i = 1; i <= 4; i++)
	{
		bool flag = true;
		char record[20];
		sprintf_s(record, sizeof(record), "maxscore%d.txt", i);
		std::ifstream file(record);
		if (!file.is_open()) {
			flag = false;
		}
		file.close();
		if (!flag) {
			std::ofstream file2(record);
			file2 << 0 << '\n';
			file2.close();
		}
	}

	Click c;
	c.update();

	return 0;
}