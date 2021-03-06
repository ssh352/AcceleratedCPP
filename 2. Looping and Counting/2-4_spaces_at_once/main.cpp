/// 2-4
/// Change the program so that it writes all the spaces needed in a single output
/// expression
///
#include <iostream>
#include <string>

/// say what standard-library names we use
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    /// ask for the person's name
    cout << "Please enter your first name: ";

    /// read the name
    string name;
    cin >> name;

    /// ask for framing size
    cout << "Please enter the framing size you want: ";
    int frameSize = 0;
    cin >> frameSize;

    /// build the message we intend to write
    const string greeting = "Hello, " + name + "!";

    /// the number of blanks surrounding the greeting
    const int pad = frameSize;


    /// the number of rows and columns to write
    const int rows = pad * 2 + 3;
    const string::size_type cols = greeting.size() + pad * 2 + 2;

    /// write blank line to separate output from the input
    cout << endl;

    /// write rows rows of output
    /// invariant: we have written r rows so far
    for( int r = 0; r != rows; ++r)
    {
        string::size_type c = 0;

        /// invariant:: we have written c characters so far in the current row
        while( c != cols )
        {
            /// is it time to write the greeting
            if (r == pad + 1 && c == static_cast<string::size_type>(pad) + 1)
            {
                cout << greeting;
                c += greeting.size();
            }

            else if (r == 0 || r == rows-1  ||
                     c == 0 || c == cols-1  )
            {
                cout << "*";
                ++c;

            }
            else if( r == pad + 1 &&  (c == 1 || c == greeting.size() + pad + 1))
            {
                cout << string(pad, ' ');
                c += pad;
            }
            else
            {
                cout << string(cols-2, ' ');
                c += cols-2;
            }
        }

        cout << endl;
    }

    return 0;
}

