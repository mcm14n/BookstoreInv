// Michael Mullings
// COP 3330-0001
// Assignment 4 - The Store class
/* store.cpp is the implementation file that defines the Store class and its
   interface. 
*/ 

#include "store.h"

Store::Store()
{// default constructor, sets starting cash in register
    // and creates a inventory list of blank books.
  max = 5;
  current = 0;
  inventory = new Book[max];
  revenue = 0;
}

Store::~Store()
{ // Destructor
    // deletes inventory list
   if (inventory != 0)
      {
        delete [] inventory;
      }
}

bool Store::SetRevenue(double r)
{ // sets starting amount of money in register as a positive 
  if (r >= 0)
   {
     revenue = r;
     return true;
   }
  return false;
}

void Store::Header() const
{ // Displays a formatted Header for inventory list
   cout << left << setw(34) << "   Title";
   cout << left << setw(21) << "Author";
   cout << "Genre";
   cout << '\t' << ' ' << setw(8) << " Price\n";
   cout << endl;
}

bool Store::Compare(const char* f, const char* s) const
{ // Allows the comparison of cstrings, ignores case
   if (strlen(f) != strlen(s)) // Are the cstrings the same length
     {
        return false; // not identical
     }
   for (unsigned int i = 0; i<=strlen(f); i++) 
     {// compares each character, ignores case
        if (toupper(f[i]) != toupper(s[i]))
           {
              return false; // not identical
           }
     }
   return true; // identical string
}

Genre Store::Selection(const char g) const
{ // interprets character as genre
    // returns appropriate genre
  switch (toupper(g))
  {
    case 'F':
     return FICTION;
    case 'M':
     return MYSTERY;
    case 'S':
     return SCIFI;
    case 'C':
     return COMPUTER;
    default:
     return FICTION;
  }
}

void Store::Reallocate()
{ // Resizes the array so that no more than 5 unused slots are allocated
   max = current+5;
   cout << "*** \nOne Moment Please! ***";
   cout << "\n*** Resizing Inventory Array to " << max
   << " allocated slots. ***";

   Book* shelf = new Book[max]; // temporary array

   for (int i = 0; i<current; i++)
      { // copies inventory into temporary array
        shelf[i] = inventory[i];
      }
   delete [] inventory; // deletes old array
   inventory = shelf; // sets the old array to new array
   // informs user 
   cout << "\n*** Resizing Complete! ***\n";
}

// Adds a book to the inventory using title, author, genre, and price
void Store::AddBook(const char* t, const char* a, char g, double p)
{ // if the inventory is full, resize the array
  if (current == max)
    {
       Reallocate();
    }
    // sets book to the appropriate slot
  (*this).inventory[current++].Set(t,a,Selection(g),p);
  // informs the user that the book has been added
  cout << "*** "<<"\""<< t << "\""<<" by [" << a
  <<"] has been added to your inventory ***\n";
}

// Finds book by author or title
bool Store::FindBook(const char* s) const
{  int count = 1;
   bool f = false;
   cout << "*** Locating Books! ***\n";
   for (int i = 0; i < current; i++)
     { // compares the requested string with the titles or authors
         // in the inventory
       if (Compare(s,this->inventory[i].GetTitle()) == true || Compare(s,this->inventory[i].GetAuthor()) == true)
         {
           if (count == 1)
             {
                Header(); // prints header before inventory list
             }
           cout << left << setw(2) << count++ << ". "; // numbers list
           (*this).inventory[i].Display(); // display each book 
           cout << '\n';
           f = true; // book found 
         }
     }
     if (f == false) // book not found, prints message
        cout << "Book Not Found!\n";
   return f; // return success or failure
}

// Sells a particular title from inventory 
bool Store::SellBook(const char* s)
{ 
   double sale = 0;
   for (int i = 0; i < current; i++)
       { // finds a title from the inventory
         if (Compare(s,this->inventory[i].GetTitle()) == true)
           {
             cout << "*** This title has been sold and removed from "
             <<"inventory. ***";
             // saves the the book's price
             sale = this->inventory[i].GetPrice();
             for (int j = i; j < current-1; j++)
                {// removes book from inventory
                  this->inventory[j] = this->inventory[j+1];
                }
             current--; // decreases number of books
             Reallocate(); // resizes array
             revenue = revenue+sale; // adds sale to register
             return true; // success
           }
       }
   // No sale made    
   cout << "\n*** Title Selection Not Found. No Sale Made! ***\n";
   return false;
}

// Displays the complete inventory list 
void Store::DisplayInventory() const
{
   cout << " *** Inventory List ***\n\n";
   Header(); // prints header
   for (int i = 0, j = 0; i < current; i++)
      { // prints formatted inventory list
        cout << left << setw(2) << ++j << ". ";
        (*this).inventory[i].Display();
        cout  << endl;
      }
      // prints total number of books
   cout << "\nThe current inventory has " << current;
   if(current == 1)
    cout << " book\n";
   else
    cout << " books\n";
    // // prints total cash in register
   cout << "The total cash in register: $" << revenue <<'\n';
}

// Displays all books of the same genre
bool Store::GenreSummary(const char c) const
{
  bool f = false;
  int quantity = 0;
  double total = 0;
  // message for user 
  cout << "*** Searching for ";
  switch(Selection(c))
   {
     case FICTION:
       cout << "Fiction";
       break;
     case MYSTERY:
       cout << "Mystery";
       break;
     case SCIFI:
       cout << "Sci-Fi";
       break;
     case COMPUTER:
       cout << "Computer";
       break;
   }
  cout << " books ***\n";

  for (int i = 0, j = 0; i < current; i++)
    { // finds all books of same genre
        if (this->inventory[i].GetGenre() == Selection(c))
          {
             f = true; // genre found
             quantity++; // number of same genre
             // total cost of these books
             total = total + this->inventory[i].GetPrice();
             if (quantity == 1)
               {
                  Header(); // prints header
               }
               // formatted book list
             cout << left << setw(2) << ++j << ". ";
             this->inventory[i].Display();
             cout << '\n';
          }
    }
  if (f == false) // book not found
    {
      cout << "Genre Not Found\n";
      return f;
    }
    // Prints total quantity of books
  cout << "\nQuantity of this Genre: "<< quantity <<'\n';
  // Prints total cost of books
  cout << "Total cost of the books in this Genre: $"
   << showpoint << fixed << setprecision(2) << total <<'\n';
  return f;
}

// Menu for Store Inventory list
void Store::Menu() const
{
  cout << '\t' << "*** Book Inventory Menu ***\n";
  cout << "A:"<< '\t' << "Add a book to inventory\n";
  cout << "F:" << '\t' <<  "Find a book from inventory\n";
  cout << "S:" << '\t' << "Sell a book\n";
  cout << "D:" << '\t' <<  "Display the inventory list\n";
  cout << "G:" << '\t' << "Genre summary\n";
  cout << "M:" << '\t' << "Show this Menu\n";
  cout << "X:" << '\t' <<  "eXit the program\n";

  cout << "O:" << '\t' <<  "Sort Inventory\n";
}

// Exits menu program
void Store::Exit() const
{ // informs user
  cout << "Exiting Menu Program\n";
  // Prints total cash in register 
  cout << "Total cash in register: $"
  << showpoint << fixed << setprecision(2) << revenue;
  cout << "\n ***Program terminated ***";
}

// Sorts inventory 
void Store::Sort(char order)
{
    Book temp; // temporary book
    if (toupper(order) == 'A') // sort by author
        { // informs user
            cout << "*** The Inventory Array will now be sorted by author ***\n";
            for (int j = 0; j <current; j++) // sorts list several times
                { // ensures list is properly sorted
                  for (int i = 0; i < current-1; i++) // sorts each item in array
                    { // if this author is the same or comes after alphabetically 
                    if ((strcmp(inventory[i].GetAuthor(),inventory[i+1].GetAuthor())) >= 0)
                        {  // author is the same 
                            if (strcmp(inventory[i].GetAuthor(),inventory[i+1].GetAuthor()) == 0)
                            {  // sort by author, then title
                                if(strcmp(inventory[i].GetTitle(),inventory[i+1].GetTitle()) > 0)
                                    {
                                        temp = inventory[i];
                                        inventory[i] = inventory[i+1];
                                        inventory[i+1] = temp;
                                    }
                            }
                            else
                                    { // not same author, sort by author
                                        temp = inventory[i];
                                        inventory[i] = inventory[i+1];
                                        inventory[i+1] = temp;
                                    }
                        }
                    }
                }
            // informs user
            cout << "*** Sorting Complete! ***\n";
        }
    else if (toupper(order) == 'T') // sorts by title
        { // informs user
            cout << "*** The Inventory Array will now be sorted by title ***\n";
            for (int j = 0; j <current; j++) // properly sorts inventory
                { 
                   for (int i = 0; i < current-1; i++) // sorts each book in list
                    { // if first comes alphabetically after second
                    if ((strcmp(inventory[i].GetTitle(),inventory[i+1].GetTitle())) > 0)
                        { // swap elements
                            temp = inventory[i];
                            inventory[i] = inventory[i+1];
                            inventory[i+1] = temp;
                        }
                    }
                }
            // informs user
            cout << "*** Sorting Complete! ***\n";
        }
    else
        // informs user that no sort was made.
        cout << "*** Invalid Option. No Sort Done!\n ***";
}


// BlackhatTally
