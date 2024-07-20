#include<iostream>
class String {
private:
	char* string;
public:
	String();
	String(char* str);
	String(const String&);
	String(int x);
	char operator[](int i) const;
	String& operator+(String str);
	String& operator-(String substr);
	bool operator!();
	String& operator=(const String&);
	bool operator==(const String&);
	int operator()(char);
	String operator*(int a);
	int length() const;
	//istream& operator >>(istream& input, const String);
	//ostream& operator <<(ostream& output, const String);
	void Display()
	{
		std::cout << *string;
	}
};