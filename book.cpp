// Michael Mullings
// COP 3330-0001
// Assignment 4 - The Store class
/* book.cpp is the implementation file for the Book 
   class. book.cpp defines the functions for creating
   a Book object. 
*/ 

#include <cstring>
#include <cctype>
#include <iostream>
#include <iomanip>
#include "book.h"

using namespace std;

Book::Book()
{ // default constructor, sets blank book object 
 strcpy(title, " "); 
 strcpy(author, " ");
 type = FICTION;
 price = 0;
}

void Book::Set(const char* t, const char* a, Genre g, double p)
{ // sets the title, author, genre, and price of the book
  strcpy(title, t);
  strcpy(author, a);
  type = g;
  if (p >= 0)
  price = p;
}

const char* Book::GetTitle() const
{ // returns the book's title
  return title;
}

const char* Book::GetAuthor() const
{ // returns the book's author
  return author;
}

double Book::GetPrice() const
{ // returns the price of a book
   return price;
}

Genre Book::GetGenre() const
{ // returns the genre of a book
   return type;
}

void Book::Display() const
{ // Prints the details of a book in a formatted table
  cout << left << setw(31) << GetTitle(); // prints title
  cout << left << setw(21)<< GetAuthor(); // prints author
   switch (GetGenre()) // prints the appropriate genre
   {
     case 0:
       cout << "Fiction ";
       break;
     case 1:
       cout << "Mystery ";
       break;
     case 2:
       cout << "Sci-Fi  ";
       break;
     case 3:
       cout << "Computer";
       break;

   }
   cout <<right<<setw(3)<<'$';
   cout << right
   // prints price as formatted currency
   <<setw(8)<<showpoint<<fixed<<setprecision(2)<<GetPrice(); 
}

