#include <iostream>

using namespace std;

int main()
{
	int eggs;
	cout << "Please, enter the total number of eggs: ";
	cin >> eggs;
	int pack30=0, pack24=0, pack18=0, pack12=0, pack6 = 0;
	if (30 <= eggs)
	{
		pack30 = eggs / 30;
		eggs = eggs - pack30 * 30;
	}
	if (24 <= eggs)
	{
		pack24 = eggs / 24;
		eggs = eggs - pack24 * 24;
	}
	if (18 <= eggs)
	{
		pack18 = eggs / 18;
		eggs = eggs - pack18 * 18;
	}	
	if (12 <= eggs)
	{
		pack12 = eggs / 12;
		eggs = eggs - pack12 * 12;
	}
	if (6 <= eggs)
	{
		pack6 = eggs / 6;
		eggs = eggs - pack6 * 6;
	}
	cout << "We need to use:\n"
		<< pack30 << " of 30 eggs packing\n"
		<< pack24 << " of 24 eggs packing\n"
		<< pack18 << " of 18 eggs packing\n"
		<< pack12 << " of 12 eggs packing\n"
		<< pack6 << " of 6 eggs packing\n";
	if(eggs>0)
		cout << eggs << " eggs left to be packed";
}
