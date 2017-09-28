// Michael Mullings
// COP 3330-0001
// Assignment 4 - The Store class
/* menu.cpp is a driver file that starts the menu program. The 
   menu program grants the user an interface to access the bookstore's 
   inventory.
*/ 

#include <iostream>
#include "store.h"
using namespace std;

int main()
{
    Store b; // creates a store object
    char title[31]; 
    char author [21];
    char genreSelect, menuSelect, order;
    double cash, price;
     
     // Welcome message
    cout << "\t*** Welcome to Your Book Inventory System! ***\n";
    // prompts the user for the starting cash in register
    cout << " Please enter the starting amount of cash in the store's register: $";
    cin >> cash;
    // ensures proper user input for starting cash
    while (b.SetRevenue(cash) == false)
        {
            cout << "Must be a positive number! Please Re-enter: $";
            cin >> cash;
        }
    // Thank you message
    cout << "\n*** Thank You! Here is Your Store Inventory Menu. ***\n";
    cout <<'\n';
    b.Menu(); // Displays menu

    do // starts menu loop program
    { // prompts user for menu selection
        cout << "\nEnter Menu Selection: ";
        cin >> menuSelect;
        cout << '\n';

        switch (toupper(menuSelect)) // activate menu selection
        {
            case 'A': // Add Book
                // prompts user for title
                cout << "Please enter the book's title: ";
                cin.ignore(); // ignore input stream
                cin.getline(title, 31); // get title
                // prompts user for author
                cout << "Please enter the author: ";
                cin.getline(author, 21); // get author
                // prompts user for genre
                cout << "Please enter the genre: ";
                cin >> genreSelect;
                // ensures proper genre is passed 
                while (toupper(genreSelect) != 'F'&& toupper(genreSelect) != 'M'
                       && toupper(genreSelect) != 'C' && toupper(genreSelect) != 'S')
                    {
                        cout << "Invalid genre entry.  Please re-enter: ";
                        cin >> genreSelect;
                    }
                    // prompts user for price
                cout << "Please enter the price: $";
                cin >> price;
                // ensures positive price
                while (price < 0)
                    {
                      cout << "Must be a positive price! Please Re-enter: $";
                      cin >> price;
                    }
                 // Adds book to inventory liat
                b.AddBook(title, author, genreSelect, price);
                break;
            case 'F': // Find book
                // prompts user
                cout << "Please enter a book's title or author: ";
                cin.ignore();
                cin.getline(title, 31); // get input 
                b.FindBook(title); // Finds book 
                break;
            case 'S': // Sell book
                // prompts user
                cout << "Please enter the title of the book: ";
                cin.ignore();
                cin.getline(title, 31); // get input 
                b.SellBook(title); // sell selected title
                break;
            case 'D': // display option
                b.DisplayInventory(); // Displays all books
                break;
            case 'G': // genre summary 
                // prompts user 
                cout << "Please enter a genre: ";
                cin >> genreSelect;
                // ensures proper input 
                while (toupper(genreSelect) != 'F'&& toupper(genreSelect) != 'M'
                       && toupper(genreSelect) != 'C' && toupper(genreSelect) != 'S')
                    {
                        cout << "Invalid genre entry.  Please re-enter: ";
                        cin >> genreSelect;
                    }
                b.GenreSummary(genreSelect); // displays all book of genre
                break;
            case 'M': // menu option
                b.Menu(); // displays menu option
                break;
            case 'X': // exit option
                b.Exit(); // exit menu procedure 
                cout << '\n';
                break;
            case 'O': // sort option
                // prompts user 
                cout << "How would you like to sort the store's inventory: ";
                cin >> order;
                b.Sort(order); // sorts list by provided option
                break;
            default: // selection not valid
                cout << "Not a valid option, choose again.";
                break;
        }

    }while (toupper(menuSelect) != 'X'); // quits menu upon exit



}

