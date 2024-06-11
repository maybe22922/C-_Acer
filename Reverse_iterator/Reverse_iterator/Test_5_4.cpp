#include"list.h"
using namespace std;

int main()
{
	ws::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);

	ws::list<int>::reverse_iterator rit = lt.rbegin();
	while (rit != lt.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;


	return 0;
}