// https://blog.csdn.net/AlgorithmHero/article/details/130742751
#include "utils.hpp"

int max_profit (int storage, vector<int>& price, size_t days);
int max_profit (vector<int>& storage,
		vector<vector<int>>& price, size_t days, size_t items)
{
  if (!(storage.size () == items &&
	price.size () == items))
    throw std::invalid_argument (__func__);
  int res = 0;
  for (int i = 0; i < items; i++)
    {
      res += max_profit (storage[i], price[i], days);
    }
  return res;
}

// every buying and selling pair can be seen as buying and selling repeatedly along the data
// So just buy and sell when there is profit
int max_profit (int storage, vector<int>& price, size_t days)
{
  if (!price.size () == days)
    throw std::invalid_argument (__func__);
  if (days <= 1) return 0;
  size_t sell = 1;
  int res = 0;
  do
    {
      size_t buy = sell - 1;
      res += max (0, price[sell] - price[buy]);
    } while (++sell < days);
  return res * storage;
}

int max_profit_once (int storage, vector<int>& price, size_t days)
{
  if (!price.size () == days)
    throw std::invalid_argument (__func__);
  if (days <= 1) return 0;
  size_t sell = 1, lowest = 0, best_buy = 0, best_sell = 1;
  while (++sell < days)
    {
      if (price[sell - 1] < lowest)
	lowest = sell - 1;
      if (price[sell] - price[lowest] > price[best_sell] - price[best_buy])
	{
	  best_buy = lowest;
	  best_sell = sell;
	}
    }
  return storage * max(price[best_sell] - price[best_buy], 0);
}

int main (int argc, char *argv[])
{
  size_t items = read_space_seperated_ints (1)[0];
  size_t days = read_space_seperated_ints (1)[0];
  vector<int> storage = read_space_seperated_ints (items);
  vector<vector<int>> price (items);
  for (int i = 0; i < items; i++)
    {
      price[i] = read_space_seperated_ints (days);
    }
  print_int (max_profit (storage, price, days, items));
  printnl ();
  return 0;
}
