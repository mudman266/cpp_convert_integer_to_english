// Josh Williams
// 3/12/2020
// CSC - 234 - 81A
// Chapter 11 - Programming Challenge 1 - Check Writing

// Construct a Numbers class that has a constructer and a print function to display the number in english.
// Write a program to gather a number form the user and display the functions of the class.

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <Bits.h>
using namespace std;

// The following constants hold a pointer to each number in word form providing the building blocks to construct our numbers.
const char* DIGITS[] = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
const char* TEENS[] = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
const char* TENS[] = { "", "", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety" };
const char* SUFFIX[] = { "thousand", "hundred", ""};

class Numbers {
// Class Numbers stores the input from the user. It has member functions to convert the input into a vector array holding the individual ints and convert those into an english written number.
public:
    // Constructor
    Numbers(int num) {
        this->number = num;
    }

    void print() {
        // Outputs the number to the screen in word format.
        cout << this->buffer;
    }

    vector<int> toVector(int num) {
        // Accepts a number, explodes each digit into a vector and returns the vector.

        // Variables
        string str = to_string(num);
        vector<int> converted;
        reverse_iterator<string::iterator> ptr;

        // Use the reverse_iterator to explode each digit (in reverse order) into the vector array converted[]
        for (ptr = str.rbegin(); ptr < str.rend(); ptr++) {
            // Convert our string to an int and insert it to the beginning of the vector array
            converted.insert(converted.begin(), (int)(*ptr - '0'));
        }
        return converted;
    }

    void digitToTerm(vector<int> digits, unsigned int position) {
        // Determines the suffix a number should have. Adds the number and suffix on to the end of the buffer.

        int current, next;
        int suffixIndex = 2;

        const char** dictionary;

        // We need to use 2 numbers together, if available.
        current = digits[position];
        // Set next to the digit of position + 1 only if it exists.
        next = ((position + 1) >= digits.size() ? -1 : digits[position + 1]);

        // Thousands
        if (digits.size() > 3) {
            if (position == 2 && digits[2] == 1)
                dictionary = TEENS;
            else if (position < 2 || position == 3)
                dictionary = DIGITS;
            else
                dictionary = TENS;
            if (position == 0)
                suffixIndex = 0;
            else if (position == 1)
                suffixIndex = 1;
        }
        // Hundreds
        else if (digits.size() > 2) {
            if (position == 1) {
                if (digits[position] == 1)
                    dictionary = TEENS;
                else 
                    dictionary = TENS;
                
            }
            else dictionary = DIGITS;
            if (position == 0)
                suffixIndex = 1;
        }
        // Tens
        else if (digits.size() > 1) {
            if (position == 0) {
                if (digits[position] == 1) {
                    dictionary = TEENS;
                }
                else
                    dictionary = TENS;
            }
            else
                dictionary = DIGITS;
        }
        // Ones
        else 
            dictionary = DIGITS;
        buffer += (dictionary[current]);
        buffer += " ";           
        buffer += (SUFFIX[suffixIndex]);
        if (SUFFIX[suffixIndex] != "")
            buffer += " ";
    }

    string intToEnglish(int n) {
        // Converts an integer into words
        vector<int> digits = toVector(n);

        for (int i = 0, max = digits.size(); i < max; i++)
            digitToTerm(digits, i);

        return buffer;
    }

private:
    int number;
    string buffer;


};

int main()
{
    // Variables
    int userInput;
    vector<int> numVector;
    
    // Weclome Message
    cout << "Check Writer!\n\n";

    // Gather number and verify
    do {
        cout << "Input a number 0 - 9999: ";
        cin >> userInput;
    } while (userInput < 0 || userInput > 9999);

    // Create Numbers object and init with userInput
    Numbers check1(userInput);

    // Convert the number to text
   check1.intToEnglish(userInput);

    // Print out the number in words
    check1.print();
}

