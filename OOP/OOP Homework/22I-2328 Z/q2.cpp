#include <iostream>
using namespace std;
const int arraySize = 50;
const int wordSize = 20;
//a) Write a function countWords(char* str) that counts the number
//of words in a null - terminated string using dynamic arrays.
int countWords(char* str)
{
	int wordCount = 1;
	int i;
	for (i = 0;str[i] != '\0';i++)
	{
		if (str[i] == ' ')
		{
			wordCount++;
		}
	}
	if (str[0] == ' ' )
	{
		wordCount--;
	}
	if (str[i -1] == ' ')
	{
		wordCount--;
	}
	return wordCount;
}
//b) Write a function countOccurrences(char* str, char targetChar)
//that counts the number of occurrences of a character in a null -
//terminated string using dynamic arrays.
int countOccurrences(char* str, char targetChar)
{
	int wordCount = 0;
	for (int i = 0;str[i] != '\0';i++)
	{
		if (str[i] == targetChar)
		{
			wordCount++;
		}
	}
	return wordCount;
}
//c) Write a function findLongestWord(char* str) that finds the
//longest word in a null - terminated string using dynamic arrays.
char* findLongestWord(char* str)
{
	int longestWordStart = 0, longestWordLength = 0;
	int currentWordStart = 0, currentWordLength = 0;
	int j = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
		{
			if (currentWordLength > longestWordLength)
			{
				longestWordStart = currentWordStart;
				longestWordLength = currentWordLength;
			}
			currentWordStart = i + 1;
			currentWordLength = 0;
		}
		else
		{
			currentWordLength++;
		}
	}
	if (currentWordLength > longestWordLength)
	{
		longestWordStart = currentWordStart;
		longestWordLength = currentWordLength;
	}
	char* longWrod = new char[longestWordLength + 1];
	for (int i = longestWordStart; i < longestWordStart + longestWordLength; i++)
	{
		longWrod[j] = str[i];
		j++;
	}
	longWrod[j] = '\0';
	return longWrod;
}
//e) char** splitWords(char* str, int& wordCount) - a function
//that splits a null - terminated string into an array of words.The
//function should dynamically allocate memory to store the array
//of words and update the value of wordCount.
char** splitWords(char* str, int& wordCount)
{
	int i;

	for (i = 0;str[i] != '\0';i++)
	{
		if (str[i] == ' ')
		{
			wordCount++;
		}
	}
	if (str[0] == ' ')
	{
		wordCount--;
	}
	if (str[i - 1] != ' ')
	{
		wordCount++;
	}

	char** words = new char* [wordCount + 1];
	for (int i = 0; i < wordCount + 1; i++) {
		words[i] = new char[wordSize];
	}
	int j = 0, k = 0;
	for (i = 0;str[i] != '\0';i++)
	{
		if (str[i] == ' ')
		{
			words[k][j] = '\0';
			j = 0;k++;
		}
		else
		{
			words[k][j] = str[i];
			j++;
		}

	}
	words[k][j] = '\0';
	return words;
}
//d) char* replaceWord(char* str, char* oldWord, char* newWord) -
//a function that replaces all occurrences of a word in a null -
//terminated string with a new word using dynamic arrays.
char* replaceWord(char* str, char* oldWord, char* newWord)
{
	int wordCount = 0;
	char** words = splitWords(str, wordCount);
	for (int i = 0; i < wordCount; i++)
	{
		bool same = true;
		for (int j = 0;words[i][j] != '\0' && oldWord[j] != '\0';j++)
		{
			if (words[i][j] != oldWord[j])
			{
				same = 0;
				j = 0;
				break;
			}
		}
		if (same)
		{
			for (int j = 0;j < wordSize;j++)
			{
				words[i][j] = newWord[j];
			}
		}
	}
	int i;
	int j;
	int k = 0;
	char* newstr = new char[arraySize];
	for (i = 0; i < wordCount; i++)
	{
		for (j = 0;words[i][j] != '\0';j++)
		{
			newstr[k] = words[i][j];
			k++;
		}
		newstr[k] = ' ';k++;
	//	cout << words[i];
	/*	cout << newstr[i];
		cout << endl;*/
	}
	newstr[k] = '\0';
	return newstr;
}


int main()
{
	int wordCount = 0;
	int choice = 1;
	char occur;
	char* str = new char[arraySize];
	char* oldWord = new char[wordSize];
	char* newWord = new char[wordSize];
	cout << "Enter the Sentance : ";
	cin.getline(str,arraySize);

	while (choice!=0)
	{
		cout << str << endl;
		cout << "1. Count the Number of Words" << endl;
		cout << "2. Count Occurrences of Character" << endl;
		cout << "3. Find the Longest Word" << endl;
		cout << "4. Replace Specific Word" << endl;
		cout << "5. Split Words" << endl;
		cout << "6. Enter Sentance Again" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice : ";cin >> choice;
		switch (choice)
		{
		case 1:cout << "Number of Words are " << countWords(str) << endl;break;
		case 2:cout << "Enter The Charcter : ";
			cin >> occur;
			cout << occur << " Occur " << countOccurrences(str, occur) << " Times" << endl;
			break;
		case 3:cout << "The longest word is: " << findLongestWord(str) << endl;break;
		case 4:
		{cout << "Enter the Old Word : ";
		cin.ignore();
		cin.getline(oldWord, wordSize);
		cout << "Enter the New Word : ";
		cin.getline(newWord, wordSize);
		cout << "New String : ";
		cout << replaceWord(str, oldWord, newWord) << endl;
		break;}
		case 5:
		{char** words = splitWords(str, wordCount);
		cout << "Number of Words : " << wordCount << endl;
		cout << "Seprated Words Are" << endl;
		for (int i = 0; i < wordCount; i++)
		{
			cout << words[i] << ' ' << ',';
		}
		cout << endl;
		break;}
		case 6:
			cout << "Enter the Sentance : ";
			cin.ignore();
			cin.getline(str, arraySize);
			break;
		default:cout << "INVALID INPUT !" << endl;
		}
		system("pause");
		system("cls");
	}
	delete[] str;
	delete[] oldWord;
	delete[] newWord;
}