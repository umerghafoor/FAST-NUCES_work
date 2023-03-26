#include <iostream>
using namespace std;

int getCharCount(const char* ptr, char c)
{
    static int count = 0;
    if (*ptr == c)
    {
        count++;
    }
    if (*ptr == '\0')
    {
        return count;
    }
    ptr++;
    getCharCount(ptr, c);
}

int main() {
    char ch[] = "wavelength";
    cout<<getCharCount(ch, 'e');

    return 0;
}