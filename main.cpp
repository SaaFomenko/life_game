#include <iostream>
#include <fstream>

bool** createArr(int* rows, int* cols)
{
  bool** arr = new bool*[*rows];
	
	for (int i = 0; i < *rows; ++i)
	{
		arr[i] = new bool[*cols];
	}

  return arr;
}

void deleteArr(bool** arr, int* rows)
{
  for (int i = 0; i < *rows; ++i)
	{
		delete[] arr[i];
	}
  
  delete[] arr;
}

void viewGame(
		bool** arr,
		int* rows, 
		int* cols
)
{
	const std::string msg[] = {
		"Клетки продолжают жить!",
		"Клетки не меняют состояния. ",
		"Все клетки умерли. ",
		"Игра окончена.",
	};

	std::string final_msg = "";
  
  static int gen = 0;
  int alive = 0;
	int status = 1;

  bool** next_arr = createArr(&*rows, &*cols);

  ++gen;
  
  std::cout << std::endl;

  for (int i = 0; i < *rows; ++i)
	{
		for (int j = 0; j < *cols; ++j)
		{
			char s = arr[i][j] ? '*' : '-';

			alive = arr[i][j] ? (++alive) : alive;
			
			if (i == 0 && j == 0)
			{
				if (arr[i][j])
				{
					next_arr[i][j] = arr[i][j + 1] && (arr[i + 1][j] || arr[i + 1][j + 1] );
					alive = next_arr[i][j] ? alive : --alive;
				}
				else
				{
					next_arr[i][j] = arr[i][j + 1] && arr[i + 1][j] && arr[i + 1][j + 1];
				}

				status = next_arr[i][i] == arr[i][j] ? 1 : 0;
			}

			if (i == 0 && j > 0)
			{
				if (arr[i][j])
				{
					next_arr[i][j] = arr[i][j - 1] ||
				}
			}


		std::cout << std::endl;
	}
  
  std::cout << std::endl;
  std::cout << "Поколкние: " << gen << "; " << 
		"Количество живых клеток: " << alive << std::endl;

	if (status == 0 && alive != 0)
	{
		std::cout << msg[status] << std::endl;
		viewGame(next_arr, &*rows, &*cols);
	}

  std::cout << msg[status] << msg[3] << std::endl;

	deleteArr(next_arr, &*rows);
	next_arr = nullptr;
}

int main() {
  const std::string msg[] = {
    "Не удалось прочитать файл, проерьте его наличие и праава доступа: ",
  };
	const char* path = { "./in.txt" };

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

	bool** arr = createArr(&rows_size, &cols_size);

  for (
    int i = 0,
    j = 0;
    (!fin.eof());
  ) {
    fin >> i;
    fin >> j;
    arr[i][j] = true;
  }

  viewGame(arr, &rows_size, &cols_size);

	deleteArr(arr, &rows_size);
	arr = nullptr;

  return 0;
}
