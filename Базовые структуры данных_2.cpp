// Зеленский Александр
//2_1. Жадина. Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
//Определить за сколько подходов Вовочка съест все фрукты в корзине.
//Формат входных данных. Вначале вводится n - количество фруктов и n строк с массами фруктов.
//n ? 50000.
//Затем K - "грузоподъемность". K ? 1000.
//Формат выходных данных. Неотрицательное число - количество подходов к корзине.

#include <iostream>
#include <vector>
using namespace std;
using std::cout;
using std::endl;

class Heap {
public:
	vector<int> candies;
	void addelement (int a);
  void popmax();
	bool empty() const;

private:
  void siftUp(vector<int>& candies);
  void siftDown(vector<int>& candies);
};

void Heap::addelement (int a) {
    candies.push_back(a);
    siftUp(candies);
  }

void Heap::siftUp(vector<int>& candies) {
  int j = candies.size() - 1;
  while (j > 0) {
    if (candies[(j - 1)/2] < candies[j]){
      int c = candies[(j - 1)/2];
      candies[(j - 1)/2] = candies[j];
      candies[j] = c;
      j = (j - 1)/2;
    } else {
      j = 0;
    }
  }
}

void Heap::popmax() {
  siftDown(candies);
}

void Heap::siftDown(vector<int>& candies) {
  if (candies.size() > 1) {
    int j = 0;
    candies[0] = candies[candies.size() - 1];
    candies.pop_back();
    while (2 * j + 1 <= candies.size() - 1) {
      if (2 * j + 2 <= candies.size() - 1) {
        if (candies[2 * j + 1] >= candies[2 * j + 2] and candies[2 * j + 1] >= candies[j]) {
          int c = candies[2 * j + 1];
          candies[2 * j + 1] = candies[j];
          candies[j] = c;
          j = 2 * j + 1;
        } else if (candies[2 * j + 2] >= candies[2 * j + 1] and candies[2 * j + 2] >= candies[j]) {
          int c = candies[2 * j + 2];
          candies[2 * j + 2] = candies[j];
          candies[j] = c;
          j = 2 * j + 2;
        } else {
          j = candies.size();
        }
      } else {
        if (candies[2 * j + 1] > candies[j]) {
          int c = candies[2 * j + 1];
          candies[2 * j + 1] = candies[j];
          candies[j] = c;
          j = 2 * j + 1;
        } else {
          j = candies.size();
        }
      }
    }
  } else {
    candies.pop_back();
  }
}

bool Heap::empty() const { return candies.size() == 0; }

int main() {
	int n = 0;
	cin >> n;
  Heap candy;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    candy.addelement(x);
  }
  int m;
  cin >> m;
  int x = 0;
  while (candy.candies.size() > 0) {
    x++;
    int delta = m;
    vector<int> Vova_candy;
    while (candy.candies[0] <= delta and candy.candies.size() > 0) {
      delta = delta - candy.candies[0];
      Vova_candy.push_back(candy.candies[0]);
      candy.popmax();
    }
    for (int i = 0; i < Vova_candy.size(); i++) {
      int new_mass = Vova_candy[i] / 2;
      if (new_mass > 0) {
        candy.addelement(new_mass);
      }
    }
  }
  cout << x << endl;
	return 0;
}
