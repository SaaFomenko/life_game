#include <iostream>
#include <fstream>

/*
int* getTerms(std::string path)
{

}
*/

int main() {
  const std::string msg[] = {
    "Не удалось прочитать файл, проерьте его наличие и праава доступа: ",
  };
/*
  const int arr[][6] = {
    0, -24, 4, 10, 11, 22,
    33, 32, 44, 56, 67, 78,
    89, -12, 25, 99, 100, 128,
  };
  const int rows = sizeof(arr) / sizeof(arr[0]);
  const int colls = sizeof(arr[0]) / sizeof(arr[0][0]);
  const int first_index = 0;
  const int last_index = colls - 1;
  std::cout << max_element_index[1] << std::endl;
*/  

	const char* path = { "./in.txt" };

	std::ifstream fin (path);

	if (!fin.is_open())
	{
		std::cout << msg[0] << path << std::endl;

		return 1;
	}

	int rows_size = 0;
	int cols_size = 0;
	int val = 0;
	int stat[] = {0, 0};

	fin >> rows_size;
	fin >> cols_size;

	bool** arr_back = new bool*[rows_size];
	
	for (int i = 0; i < rows_size; ++i)
	{
		arr_back[i] = new bool[cols_size];
//		std::cout << arr_back[i][i] << std::endl;
	}

	int i = 0;
	while (fin >> val)
	{
		if (i%2)
		{
			stat[1] = val;
			arr_back[stat[0]][stat[1]] = true;
		}
		else
		{
			stat[0] = val;
		}

		++i;
	}

	for (int i = 0; i < rows_size; ++i)
	{
		for (int j = 0; j < cols_size; ++j)
		{
			char s = arr_back[i][j] ? '*' : '-';

			std::cout << s << " ";
		}

		std::cout << std::endl;
	}


  return 0;
}
