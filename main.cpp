#include <fstream>
#include <iostream>
#include <cstdlib>
#include <unistd.h>


bool **createArr(int *rows, int *cols) {
  bool **arr = new bool *[*rows];

  for (int i = 0; i < *rows; ++i) {
    arr[i] = new bool[*cols]();
  }

  return arr;
}

bool stagLife(bool **arr, bool **next_arr, const int *rows,  const int *cols)
{
  for (int i = 0; i < *rows; ++i)
    {
      for (int j = 0; j < *cols; ++j)
      {
        if (arr[i][j] != next_arr[i][j]) 
        {
          return false;
        }
      }
    }
  
  return true;
}

void deleteArr(bool **arr, int *rows) {
  for (int i = 0; i < *rows; ++i) {
    delete[] arr[i];
  }

  delete[] arr;
}

void deadOrLife(bool **arr, bool **next_arr, const int *i, const int *j,
               int *alive, int *nears) {
  if (arr[*i][*j]) {
    next_arr[*i][*j] = *nears > 1 && *nears < 4;

  } else {
    next_arr[*i][*j] = *nears == 3;
  }
}

void lifeOnPoint(bool **arr, bool **next_arr, const int *cols, const int *rows,
                 const int *i, const int *j, int *alive) {
  int nears = 0;
  int position_nears[][2] = {
    *i - 1, *j - 1,
    *i - 1, *j,
    *i - 1, *j + 1,
    *i, *j - 1,
    *i, *j + 1,
    *i + 1, *j - 1,
    *i + 1, *j,
    *i + 1, *j + 1,
  };
  
  const int size_row = sizeof(position_nears) / sizeof(position_nears[0]);

  for (int x = 0; x < size_row; ++x) {
    bool check = position_nears[x][0] >= 0 &&
                 position_nears[x][0] < *rows &&
                 position_nears[x][1] >= 0 &&
                 position_nears[x][0] < *cols;
    
    if (check) {
      nears += static_cast<int>(arr[position_nears[x][0]][position_nears[x][1]]);
    }
  }
  
  *alive = arr[*i][*j] ? (++*alive) : *alive;
  deadOrLife(arr, next_arr, i, j, alive, &nears);
}

std::string viewGame(bool **arr, int *rows, int *cols) {

  int MSG_ALIVE = 0;
  int MSG_STAG = 1;
  int MSG_DEAD = 2;
  int MSG_GAMEOVER = 3;
  
  const std::string msg[] = {
      "Клетки продолжают жить!",
      "Клетки не меняют состояния. ",
      "Все клетки умерли. ",
      "Игра окончена.",
  };

  static int gen = 0;
  int alive = 0;
  int status = 1;
  static bool stag = false;

  bool **next_arr = createArr(rows, cols);

  ++gen;

  std::cout << std::endl;

  for (int i = 0; i < *rows; ++i) {
    for (int j = 0; j < *cols; ++j) {
      char s = arr[i][j] ? '*' : '-';

      std::cout << s << " ";
      
      lifeOnPoint(arr, next_arr, rows, cols, &i, &j, &alive);
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Поколение: " << gen << "; "
            << "Количество живых клеток: " << alive << std::endl;

  status = alive == MSG_ALIVE ? MSG_DEAD : stag ? MSG_STAG : MSG_ALIVE;
 
  std::cout << msg[status];

  if (status == MSG_ALIVE) {

    std::cout << std::endl;
    sleep(3);
    std::system("clear");
    
    stag = stagLife(arr, next_arr, rows, cols);
    
    viewGame(next_arr, rows, cols);
  }

  deleteArr(next_arr, &*rows);
  next_arr = nullptr;

  return msg[MSG_GAMEOVER];
}

int main() {
  const std::string msg_err = "Не удалось прочитать файл, проерьте его наличие и праава доступа: ";
  const char *path = {"./in.txt"};
  std::string game_over = "";

  std::ifstream fin(path);

  if (!fin.is_open()) {
    std::cout << msg_err << path << std::endl;

    return 1;
  }

  int rows_size = 0;
  int cols_size = 0;

  fin >> rows_size;
  fin >> cols_size;

  bool **arr = createArr(&rows_size, &cols_size);

  for (int i = 0, j = 0; (!fin.eof());) {
    fin >> i;
    fin >> j;
    arr[i][j] = true;
  }

  game_over = viewGame(arr, &rows_size, &cols_size);

  std::cout << game_over << std::endl;
  
  deleteArr(arr, &rows_size);
  arr = nullptr;

  return 0;
}
