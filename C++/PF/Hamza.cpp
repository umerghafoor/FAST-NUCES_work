#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


void setupNewFile();
void addNew();
void printAll();
void buyDragon();
void deleteDragon();
void editDragon();
void searchDragon();

int getFirstBlank();

int main()
{
char option;
while (true)
{
cout << "Please select the option:" << endl;;
cout << "---------------------------------------------" << endl;
cout << "A\tAdd new dragon" << endl;
cout << "P\tPrint all dragons" << endl;
cout << "B\tBuy dragons" << endl;
cout << "S\tSearch dragon" << endl;
cout << "E\tEdit dragon" << endl;
cout << "D\tDelete a dragon" << endl;
cout << "X\tExit" << endl;
cout << "---------------------------------------------" << endl; cin >> option;

if (option == 'a' || option == 'A')
{
addNew();
}
else if (option == 'p' || option == 'P')
{
printAll();
}
else if (option == 'b' || option == 'B')
{
buyDragon();
}
else if (option == 'd' || option == 'D')
{
deleteDragon();
}
else if (option == 's' || option == 'S')
{
searchDragon();
}
else if (option == 'e' || option == 'E')
{
editDragon();
}
else if (option == 'x' || option == 'X')
{
return 0;
}
else
{
cout << "Invlaid input. Try again. " << endl;
}

system("pause");
system("cls");

}



}


int getFirstBlank() {
char data[45];
ifstream fin("dragons.txt");
int id = 1;
while (!fin.eof())
{
fin.getline(data, 43);
//if (strncmp(&data[5], "                         ", 25) == 0)
//{
//return id;
//}
//else
//{
//id++;
//}

}
fin.close();
}

void setupNewFile()
{
ofstream fout("dragons.txt");

for (int i = 1; i <= 100; i++)
{
fout << left << setw(5) << i;
fout << left << setw(25) << "";
fout << left << setw(5) << 0;
fout << left << setw(5) << 0 << endl;
}

fout.close();
}

void printAll()
{
char data[45];
ifstream fin("dragons.txt");

while (!fin.eof())
{
fin.getline(data, 43);
if (strncmp(&data[5], "                         ", 25) != 0)
{
cout << data << endl;
}

}
fin.close();
}



void addNew() {

int newid = getFirstBlank();
int price, qty;
char name[26];
cin.ignore();
cout << "Please enter the new dragon name:";
cin.getline(name, 25);
cout << "Please enter the quantity of this dragon:";
cin >> qty;
cout << "Please enter the unit price of this dragon:";
cin >> price;

fstream f("dragons.txt", ios::out | ios::in);
f.seekp(42 * (newid - 1) + 5);
f << left << setw(25) << name;

f.seekp(42 * (newid - 1) + 30);
f << left << setw(5) << qty;

f.seekp(42 * (newid - 1) + 35);
f << left << setw(5) << price;

f.close();

cout << "New dragon added successfully on id : " << newid << endl;
system("pause");
system("cls");

}

void buyDragon()
{
int id, newqty,oldqty;
cin.ignore();
cout << "Please enter the id of the dragon you just bought:";
cin >> id;
cout << "Pleae enter the new quantity added:";
cin >> newqty;

fstream f("dragons.txt", ios::in | ios::out);
f.seekg(42 * (id - 1) + 30);
f >> oldqty;
newqty = oldqty + newqty;
f.seekp(42 * (id - 1) + 30);
f << left << setw(5) <<  newqty;


f.close();

cout << "Record updated successfully. " << endl;


}





void searchDragon()
{
char searchstring[25];
cin.ignore();
cout << "Please enter your search string: ";
cin.getline(searchstring, 25);


char data[45];
ifstream fin("dragons.txt");

while (!fin.eof())
{
fin.getline(data, 43);
if (strncmp(&data[5], searchstring, strlen(searchstring)) == 0)
{
cout << data << endl;
}

}
fin.close();
}




void editDragon() {

int id, newqty, newprice;
char name[25];

cout << "Please enter the id of the dragon you want to edit:";
cin >> id;
cout << "Please enter the new name of the dragon: ";
cin.ignore();
cin.getline(name, 25);
cout << "Pleae enter the new quantity of the dragon:";
cin >> newqty;
cout << "Pleae enter the new unit price of the dragon:";
cin >> newprice;

fstream f("dragons.txt", ios::in | ios::out);

f.seekp(42 * (id - 1) + 5);
f << left << setw(25) << name;

f.seekp(42 * (id - 1) + 30);
f << left << setw(5) << newqty;

f.seekp(42 * (id - 1) + 35);
f << left << setw(5) << newprice;


f.close();

cout << "Record updated successfully. " << endl;

}



void deleteDragon() {


int id;


cout << "Please enter the id of the dragon you want to delete:";
cin >> id;


fstream f("dragons.txt", ios::in | ios::out);

f.seekp(42 * (id - 1) + 5);
f << left << setw(25) << "";

f.seekp(42 * (id - 1) + 30);
f << left << setw(5) << 0;

f.seekp(42 * (id - 1) + 35);
f << left << setw(5) << 0;


f.close();

cout << "Record deleted successfully. " << endl;

}

