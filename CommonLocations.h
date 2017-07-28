#ifndef COMMONLOCATIONS_HPP
#define COMMONLOCATIONS_HPP
#include <string>

struct City{
    std::string name;            //This is the name of the city.
    int numVisited;         //This is the number of times a person visits a certain location.
    City *next;
    City *prev;
};

/*  This class acts as the linked list for all the most common cities that a person in the graph visits.
    It will have all of the standard method's involved in a doubly-linked list as well as a method to sort the list.
    This will be used to suggest mutual friends based on whether or not two people frequent the same locations.
*/
class CommonLocations{
    friend class FriendList;
    City *head;             //Pointer to the head of the cities list.
    City *tail;             //Pointer to the tail of the cities list.

public:
    CommonLocations();                                  //Constructor for the common locations class.
    ~CommonLocations();                                 //Destructor for the common locations class.
    void buildList();                                   //Method will prompt user for number of frequent locations and then ask the user to enter the number of times they visit each location.
    void addCity(std::string newCity, int visited);     //Method that takes in the name of a new city to add to the list and puts it next to the previous city.
    void printList();
    void deleteCity(std::string cityName);              //Deletes the given city from the linked list.
    void sortCityList();                                //Returns the the list sorted by the cities with most frequent visits as the head of the list.
    std::string *mostCommon(std::string common[], int size);      //Returns an array of strings with the three most common cities within the list.
    int getListSize();                                  //Returns the size of the list.
};

#endif // COMMONLOCATIONS_HPP
