#include <iostream>
#include <string>

using namespace std;

struct node
{
	string name;
	int reg;
	node* next;
};

class Hashing
{
public:
	Hashing();
	void search(int);
	void Display();
private:
	bool Append();
	bool DoubleCheck();
	string name;
	float threshold;
	int index, multiplier, size, reg, counter,searchindex;
	void Resize();
	int Hash1(int);
	int Hash2(int);
	int searchreg(int);
	node* hashtable;
};
void Hashing::Display()
{
	for (int i = 0; i < size; i++)
	{
		if ((hashtable + i)->name != "")
		{
			cout << "Name:\t" << (hashtable + i)->name << endl;
			cout << "Reg:\t" << (hashtable + i)->reg << endl;
		}
	}
}
int main()
{
	cout << "\t\t\t\t\tStudent's Data Management System\n";
	cout << "Entering Student Details\nLeave the name place void to Stop Appending\n";
	Hashing h;
	int reg;
	do
	{
		cout << "Who do you want to search?";
		cin >> reg;
		h.search(reg);
	} while (true);
	h.Display();

}
void Hashing::search(int reg)
{
	searchindex = searchreg(reg);

		if (searchindex != -1)
		{
			cout << "Name:\t" << (hashtable + searchindex)->name << endl;
			cout << "Reg:\t" << (hashtable + searchindex)->reg << endl;
			index = -1;
		}

}
int Hashing::searchreg(int reg)
{
	cout << "Index: " << index << endl;
	if (index == -1)
	{
		index = reg % size;
		multiplier = 1;
	}
	else multiplier++;
	if ((hashtable + index)->reg == reg)
		return index;
	else
	{
		index = (reg * multiplier) % size;
		searchreg(reg);
	}
}
Hashing::Hashing()
{
	index = searchindex = -1;
	size = 11;
	counter = 0;
	multiplier = 1;
	threshold = 0.35;
	hashtable = new node[size];
	do
	{
		while (Append());
	} while (!DoubleCheck());

}
bool Hashing::DoubleCheck()
{
	for (int i = 0; i < size; i++)
	{
		if ((hashtable + i)->name != "")
		for (int j = i + 1; j < size; j++)
		{
			if ((hashtable + i)->reg == (hashtable + j)->reg)
			{

				cout << endl << (hashtable + i)->reg << " is repeated\n";
				cout << "Making new list of\n";
				system("pause");
				cout << "\n\n";
				for (int i = 0; i < size; i++)
					hashtable = NULL;
				hashtable = new node[size];
				threshold = 0.35;
				size = 11;
				counter = 0;
				return false;
			}
		}
	}
	return true;
}
bool Hashing::Append()
{
	cout << "Name:\t";
	getline(cin, name);
	if (name == "")
		return false;
	cout << "Reg:\t";
	cin >> reg;
	index = Hash1(reg);
	(hashtable+index)->name = name;
	(hashtable+index)->reg = reg;
	cout << "Index: " << index << endl;
	counter++;
	index = -1;
	if (float(counter) / float(size) > threshold)
		Resize();
	cin.ignore();
	return true;
}
int Hashing::Hash1(int reg)
{
	do
	{
		if (index == -1)
		{
			index = reg % size;
			multiplier = 1;
		}
		else multiplier++;
		if ((hashtable + index)->name != "")
			index = Hash2(reg);
		else break;
	} while (true);
	return index;
}
int Hashing::Hash2(int reg)
{
	cout << "Collision\n";
	return index = (reg*multiplier) % size;
}
void Hashing::Resize()
{
	threshold *= 2;
	int newsize = size * 2;
	cout << "Resizing...\n";
	system("pause");
	int i = 2;
	while(i <= newsize/2)
	{
		if (newsize % i == 0)
		{
			cout << newsize << " is not a prime number\n";
			newsize++;
			i = 2;
		}
		else i++;
	}
	cout << "New Size: " << newsize << endl;
	node* temp = new node[newsize];
	int oldsize = size;
	size = newsize;
	node* oldhashtable = hashtable;
	hashtable = temp;
	for (int i = 0; i < oldsize; i++)
	{
		if ((oldhashtable + i)->name != "")
		{
			int ix = Hash1((oldhashtable + i)->reg);
			(hashtable + ix)->name = (oldhashtable + i)->name;
			(hashtable + ix)->reg = (oldhashtable + i)->reg;
			cout << "New Index for " << (oldhashtable + i)->name << ": " << ix << endl;
			index = -1;
		}
	}
	system("pause");
}