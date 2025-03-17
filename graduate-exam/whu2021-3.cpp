#include <bits/stdc++.h>
using namespace std;

int main() {
  char matches[] = { 'X', 'Y', 'Z' };
  auto size = sizeof(matches) / sizeof(matches[0]);
  sort(matches, matches + size);
  do {
    if (matches[0] != 'X'
	&& matches[2] != 'X'
	&& matches[2] != 'Z') {
      cout << "Possible match list:\n"
	   << "A vs " << matches[0] << "\n"
	   << "B vs " << matches[1] << "\n"
	   << "C vs " << matches[2] << "\n";
    }
  } while (next_permutation(matches, matches + size));
  return 0;
}
