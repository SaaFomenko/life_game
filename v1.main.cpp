#include <iostream>
#include <fstream>

void viewGame(
		bool** arr,
		int* rows, 
		int* cols,
		int* gen,
		int* alive
)
{
	++*gen;

  std::cout << std::endl;

  for (int i = 0; i < *rows; ++i)
	{
		for (int j = 0; j < *cols; ++j)
		{
			char s = arr[i][j] ? '*' : '-';

			*alive = arr[i][j] ? (++*alive) : *alive;

			std::cout << s << " ";
		}

		std::cout << std::endl;
	}
  
  std::cout << std::endl;
  std::cout << "Поколкние: " << *gen << "; " << 
		"Количество живых клеток: " << *alive << std::endl;

	alive = 0;
}

int main() {
  const std::string msg[] = {
    "Не удалось прочитать файл, проерьте его наличие и праава доступа: ",
  };
	const char* path = { "./in.txt" };
	int gen = 0;
	int alive = 0;

	std::ifstream fin (path);

	if (!fin.is_open())
	{
		std::cout << msg[0] << path << std::endl;

		return 1;
	}

	int rows_size = 0;
	int cols_size = 0;

	fin >> rows_size;
	fin >> cols_size;

	bool** arr_back = new bool*[rows_size];
	
	for (int i = 0; i < rows_size; ++i)
	{
		arr_back[i] = new bool[cols_size];
//		std::cout << arr_back[i][i] << std::endl;
	}

  
  for (
    int i = 0,
    j = 0;
    (!fin.eof());
  ) {
    fin >> i;
    fin >> j;
    arr_back[i][j] = true;
  }
  
	viewGame(arr_back, &rows_size, &cols_size, &gen, &alive);

  return 0;
}
