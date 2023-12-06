#include <algorithm>
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
using namespace std;

int getNumber ()
{
  int a;
  cin >> a;
  while (cin.fail())
  {
    cin.clear();
    cin.ignore();
    cin >> a;
  }
  return a;
}

int lenOfNumber(int a)
{
  int i = 0;
  while (a > 0)
  {
    a /= 10;
    i +=1;
  }
  return i;
}

void swapPointers(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void shakerSort(int *array, int length)
{
  int start = 0;
  int end = length - 2;
  while (start <= end)
  {
    for (int i = start; i < length - 1 - start; ++i)
    {
      if (*(array+i) > *(array+i+1))
        swapPointers(array+i, array+i+1);
    }
    for (int i = end ; i > 0 + start; --i)
    {
      if (*(array+i) < *(array+i-1))
        swapPointers((array+i), (array+i-1));
    }
    start += 1;
    end -= 1;
  }
}

int main() 
{
  const int N = 8;
  int A[N][N] =
  {
    {0,1,2,3,4,5,6,7},
    {8,9,10,11,12,13,14,15},
    {16,17,18,19,20,21,22,23},
    {24,25,26,27,28,29,30,31},
    {32,33,34,35,36,37,38,39},
    {40,41,42,43,44,45,46,47},
    {48,49,50,51,52,53,54,55},
    {56,57,58,59,60,61,62,63},
  };
  srand(time(0));
  while (true)
  {
    cout << "#########################" << endl;
    cout << "Выберите опцию программы: " << endl
    << "1.1 Заполнение спиралью" << endl
    << "1.2 Заполнение змейкой" << endl
    << "2.1 Перестановка блоков по часовой стрелке" << endl
    << "2.2 Перестановка по диагонали" << endl
    << "2.3 Перестановка верхние-нижние" << endl
    << "2.4 Перестановка левые-правые" << endl
    << "3 Отсортировать массив" << endl
    << "4 Выполнить операцию над каждым элементом матрицы" << endl
    << "#################################################"<< endl;
    int userChoice;
    userChoice = getNumber();
    switch (userChoice)
    {
      case 11:
      {
        // #1.1
        initscr();
        for (int i = 0; i < N/2; ++i)
        {
          for (int j = 0; j < N-2*i; ++j)
          {
            *((*A+j)+i*N+i) = rand() % (N*N+1);
            move((j+i*N+i)/N, (j+i*N+i)%N*(lenOfNumber(N*N)+1));
            printw("%0*d", lenOfNumber(N*N),  *((*A+j)+i*N+i));
            refresh();
            usleep(100000);
          }
          for (int j = 0; j < N-2 - 2*i  ; ++j)
          {
            *((*A+((i+2)*N-(i+1))+j*N)) = rand() % (N*N+1);
            move(((i+2)*N-(i+1)+j*N)/N, (((i+2)*N-(i+1)+j*N)%N)*(lenOfNumber(N*N)+1));
            printw("%0*d", lenOfNumber(N*N),  *((*A+((i+2)*N-(i+1))+j*N)));
            refresh();
            usleep(100000);
          }
          for (int j = 0; j < N - 2*i; ++j)
          {
            *((*A+((N-i)*N-(i+1)) - j)) = rand() % (N*N+1);
            move(((N-i)*N-(i+1)-j)/N, (((N-i)*N-(i+1)-j)%N)*(lenOfNumber(N*N)+1));
            printw("%0*d", lenOfNumber(N*N),  *((*A+((N-i)*N-(i+1)) - j)));
            refresh();
            usleep(100000);
          }
          for (int j = 0; j < N-2 - 2*i; ++j)
          {
            *((*A+((N-2-i)*N+i) - j*N)) = rand() % (N*N+1);
            move(((N-2-i)*N+i - j*N)/N, (((N-2-i)*N+i - j*N)%N)*(lenOfNumber(N*N)+1));
            printw("%0*d", lenOfNumber(N*N),  *((*A+((N-2-i)*N+i) - j*N)));
            refresh();
            usleep(100000);
          }
        }
        endwin();
        for (int i = 0; i < N*N; ++i)
        {
          printf("%0*d", lenOfNumber(N*N),  *(*A+i));
          cout << (((i + 1) % N == 0) ? '\n':' ');
        }
        break;
      }
      case 12:
      {
        // #1.2
        initscr();
        int i = -1;
        for (; i < N-1;)
        {
          i += 1;
          for (int j = 0; j < N; ++j)
          {
            *(*A+j*N+i) = rand() % (N*N+1);
            move((j*N+i)/N, ((j*N+i)%N)*(lenOfNumber(N*N)+1));
            printw("%0*d", lenOfNumber(N*N),  *(*A+j*N+i));
            refresh();
            usleep(100000);
          }
          i+=1;
          for (int j = N - 1; j >= 0; --j)
          {
            *(*A+j*N+i) = rand() % (N*N+1);
            move((j*N+i)/N, ((j*N+i)%N)*(lenOfNumber(N*N)+1));
            printw("%0*d", lenOfNumber(N*N),  *(*A+j*N+i));
            refresh();
            usleep(100000);
          }
        }
        endwin();
        for (int i = 0; i < N*N; ++i)
        {
          printf("%0*d", lenOfNumber(N*N),  *(*A+i));
          cout << (((i + 1) % N == 0) ? '\n':' ');
        }
        break;
      }
      case 21:
      {
        // #2.1
        int B[N][N];
        for (int i = 0; i < N; ++i)
        {
          for (int j = 0; j < N/2; ++j)
          {
            if (i < N/2)
            {
              *(*B+i*N+N/2+j) = *(*A+i*N+j); // из левой части в правую
              *(*B+i+j*N) = *(*A+i+N/2*N+j*N); // из нижней части в верхнюю
            }
            else
            {
              *(*B+i*N+j) = *(*A+i*N+N/2+j); // из правой части в левую
              *(*B+i+N/2*N+j*N) = *(*A+i+j*N); // из верхней части в нижнюю
            }
          }
        }
        cout << "После преобразования: " << endl;
        for (int i = 0; i < N*N; ++i)
        {
          printf("%0*d", lenOfNumber(N*N),  *(*B+i));
          cout << (((i + 1) % N == 0) ? '\n':' ');
        }
        break;
      }
      case 22:
      {
        // #2.2
        int B[N][N];
        for (int i = 0; i < N/2; ++i)
        {
          for (int j = 0; j < N/2; ++j)
          {
          *(*B+N/2*N+N/2+i+j*N) = *(*A+i+j*N); // правый нижний <- левый верхний 
          
          *(*B+i+j*N) = *(*A+N/2*N+N/2+i+j*N); // левый верхний <- правый нижний
          
          *(*B+N/2*N+i+j*N) = *(*A+N/2+i+j*N); // левый нижний <- правый верхний

          *(*B+N/2+i+j*N) = *(*A+N/2*N+i+j*N); // праый верхний <-левый нижний  
          }
        }
        cout << "После преобразования: " << endl;
        for (int i = 0; i < N*N; ++i)
        {
          printf("%0*d", lenOfNumber(N*N),  *(*B+i));
          cout << (((i + 1) % N == 0) ? '\n':' ');
        }
        break;
      }
      case 23:
      {
        // #2.3
        int B[N][N];
        for (int i = 0; i < N*N/2; ++i)
        {
          *(*B+i) = *(*A+N*N/2+i);
        }
        for (int i = N*N/2; i < N*N; ++i)
        {
          *(*B+i) = *(*A+i-N*N/2);
        }
        cout << "После преобразования: " << endl;
        for (int i = 0; i < N*N; ++i)
        {
          printf("%0*d", lenOfNumber(N*N),  *(*B+i));
          cout << (((i + 1) % N == 0) ? '\n':' ');
        }
        break;
      }
      case 24:
      {
        // #2.4
        int B[N][N];
        for (int i = 0; i < N; ++i)
        {
          for (int j = 0; j < N/2; ++j)
          {
            *(*B+j+i*N) = *(*A+j+N/2+i*N);
            *(*B+j+N/2+i*N) = *(*A+j+i*N);
          }
        }
        cout << "После преобразования: " << endl;
        for (int i = 0; i < N*N; ++i)
        {
          printf("%0*d", lenOfNumber(N*N),  *(*B+i));
          cout << (((i + 1) % N == 0) ? '\n':' ');
        }
        break;
      }
      case 3:
      {
        // #3 
        cout << "Отсортируем матрицу:" << endl;
        shakerSort(*A, N*N);
        for (int i = 0; i < N*N; ++i)
        {
          printf("%0*d", lenOfNumber(N*N),  *(*A+i));
          cout << (((i + 1) % N == 0) ? '\n':' ');
        }
        break;
      }
      case 4:
      {
        // #4
        cout << "Выберите операцию для действий с матрицей:\n" 
          << "0. Прибавить \n"
          << "1. Вычесть \n"
          << "2. Умножить \n"
          << "3. Поделить \n";
        int choice;
        choice = getNumber();
        int userNumber;
        cout << "Введите число, с которым хотите произвести операцию: ";
        userNumber = getNumber();
        switch (choice)
        {
          case 0:
          {
            for (int i = 0; i < N*N; ++i)
            {
              *(*A+i) += userNumber;
            }
            break;
          }
          case 1:
          {
            for (int i = 0; i < N*N; ++i)
            {
              *(*A+i) -= userNumber;
            }
            break;
          }
          case 2:
          {
            for (int i = 0; i < N*N; ++i)
            {
              *(*A+i) *= userNumber;
            }
            break;
          }
          case 3:
          {
            for (int i = 0; i < N*N; ++i)
            {
              *(*A+i) /= userNumber;
            }
            break;
          }
          default:
          {
            cout << "Введите номер операции из предложенных" << endl;
          }
        }
        cout << "После преобразования: " << endl;
        for (int i = 0; i < N*N; ++i)
        {
          printf("%0*d", lenOfNumber(N*N),  *(*A+i));
          cout << (((i + 1) % N == 0) ? '\n':' ');
        }
        break;
      }
    }
  }
}

