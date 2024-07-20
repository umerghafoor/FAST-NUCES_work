#include <iostream>
using namespace std;
const int NumPlayers = 10;
struct SoccerPlayer
{
	char playerName[20];
	int PlayerNumber;
	int PointsScored;

	SoccerPlayer()
	{
		PlayerNumber = -1;
		PointsScored = -1;
	}
};
int main()
{
	SoccerPlayer* p = new SoccerPlayer[NumPlayers];
	int indexP = 0;
	int indexT = 0;
	int max = 0;
	int maxIndex;

	int x = 1;
	while (x != 0)
	{
		cout << "1 Add new players" << endl;
		cout << "2 Insert a new player" << endl;
		cout << "3 Delete the player" << endl;
		cout << "4 Display Player information" << endl;
		cout << "5 Display Highest scorer" << endl;
		cout << "0 Exit" << endl;
		cout << "Enter choice : ";cin >> x;
		switch (x)
		{
		case 1:
			/*Add new players’ information: It will add information of a new player.*/
			for (int i = 0;i < NumPlayers;i++)
			{
				if (p[i].PlayerNumber < 0)
				{
					indexP = i;
					break;
				}
			}
			cout << "\tCreating Player at " << indexP << endl;
			cout << "Enter the Name   : ";
			cin.ignore();
			cin.getline(p[indexP].playerName, 20);
			cout << "Enter the Number : ";
			while (p[indexP].PlayerNumber < 0)
			{
				cin >> p[indexP].PlayerNumber;
				if (p[indexP].PlayerNumber < 0)
				{
					cout << "\tInvalid ! \nEnter Again : ";
				}
			}
			cout << "Enter the Points : ";
			while (p[indexP].PointsScored < 0)
			{
				cin >> p[indexP].PointsScored;
				if (p[indexP].PointsScored < 0)
				{
					cout << "\tInvalid ! \nEnter Again : ";
				}
			}
			indexP++;
			cout << "\tPlayer Created at " << indexP << endl;
			break;
		case 2:
			/*Insert a new player: It will insert information at the desired location.(for example at index 2).*/
			cout << "\tInserting Player" << endl;
			cout << "Enter the Index  : ";
			cin >> indexT;
			cout << "Enter the Name   : ";
			cin.ignore();
			cin.getline(p[indexT].playerName, 20);
			cout << "Enter the Number : ";
			while (p[indexT].PlayerNumber < 0)
			{
				cin >> p[indexT].PlayerNumber;
				if (p[indexT].PlayerNumber < 0)
				{
					cout << "\tInvalid ! \nEnter Again : ";
				}
			}
			cout << "Enter the Points : ";
			while (p[indexT].PointsScored < 0)
			{
				cin >> p[indexT].PointsScored;
				if (p[indexT].PointsScored < 0)
				{
					cout << "\tInvalid ! \nEnter Again : ";
				}
			}
			cout << "\tPlayer Inserted" << endl;
			break;
		case 3:
			/*Delete the player’s information (Example: Delete player at index = 5)*/
			cout << "\tDeleting Player" << endl;
			cout << "Enter the Index  : ";cin >> indexT;
			p[indexT].PlayerNumber = -1;
			p[indexT].PointsScored = -1;
			cout << "\tPlayer Deleted at index " << indexT << endl;
			break;
			/*Display Player information: Display information in a tabular format (for all players)*/
		case 4:
			cout << "No." << '\t' << "Name" << '\t' << "Number" << '\t' << "Points" << endl;
			for (int i = 0;i < NumPlayers;i++)
			{
				if (p[i].PlayerNumber > 0)
					cout << i << '\t' << p[i].playerName << '\t' << p[i].PlayerNumber << '\t' << p[i].PointsScored << endl;
			}
			cout << endl;
			break;
		case 5:
			/*Display: The number and name of the player who has earned the most points should also be displayed.*/
			for (int i = 0;i < NumPlayers;i++)
			{
				if (p[i].PointsScored > max)
				{
					max = p[i].PointsScored;
					maxIndex = i;
				}
			}
			cout << "No." << '\t' << "Name" << '\t' << "Number" << '\t' << "Points" << endl;
			cout << maxIndex << '\t' << p[maxIndex].playerName << '\t' << p[maxIndex].PlayerNumber << '\t' << p[maxIndex].PointsScored << endl;
			cout << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}