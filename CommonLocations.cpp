#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include "CommonLocations.h"

using namespace std;

CommonLocations::CommonLocations(){
    head = nullptr;
    tail = nullptr;
}

CommonLocations::~CommonLocations(){
}

/*  This method will prompt the user for the number of cities that the person has visited.  It will then prompt the user to enter
    the number of times that they have visited each city and then build the doubly-linked list with the given information.
*/
void CommonLocations::buildList(){
    int numCities;                  //This is the number of cities a person has visited.

    cout << "Please enter the number of cities that you have visited." << endl;
    cin >> numCities;
    while(! cin >> numCities){
        cin.clear();
        cin.ignore();
        cout << "Invalid input."<< endl;
    }

    for(int i = 0; i < numCities; i++){
        string cityName;
        int numVisited;

        cout << "Enter the name of the city: " << endl;
        cin.ignore();
        getline(cin, cityName);
        cout << "Enter the number of times you have visited the city: " << endl;
        cin >> numVisited;


        if(head == nullptr){
            City *node = new City;
            node->name = cityName;
            node->numVisited = numVisited;
            node->prev = nullptr;
            node->next = nullptr;
            head = node;
        }
        else if(head != nullptr && i == numCities-1){
            City *temp = head;
            City *node = new City;
            node->name = cityName;
            node->numVisited = numVisited;

            while(temp->next != nullptr){
                temp = temp->next;
            }

            temp->next = node;
            node->prev = temp;
            node->next = nullptr;
            tail = node;
        }

        else{
            City *temp = head;
            City *node = new City;
            node->name = cityName;
            node->numVisited = numVisited;

            while(temp->next != nullptr){
                temp = temp->next;
            }

            temp->next = node;
            node->prev = temp;
            node->next = nullptr;
        }
    }


}

/*  This method will take in the city along with the number of times the city has been visited and add it to the end of the
    linked list.  If the list is empty it will be set to the head of the list.
*/
void CommonLocations::addCity(string newCity, int visited){
    City *node = new City;
    node->name = newCity;
    node->numVisited = visited;

    if(head == nullptr){
        node->prev = nullptr;
        node->next = nullptr;
        head = node;
        tail = node;
    }

    else{
        City *temp = tail;
        temp->next = node;
        node->prev = temp;
        node->next = nullptr;
        tail = node;
    }
}


void CommonLocations::printList(){
    City *temp = head;

    if(temp == nullptr){
        cout << "List empty." << endl;
    }

    else{
        cout << "Most common cities: ";

        while(temp!= nullptr){
            cout << temp->name << ": " << temp->numVisited << endl;
            temp = temp->next;
        }
    }
}

// The delete city method will take in the name of a city to be deleted and remove it from the list.
// If the city is not found it will inform the user that their is no city with the given name in the list.
void CommonLocations::deleteCity(string name){
    bool found = false;

    if(name == head->name){
        found = true;
        City *temp = head;

        if(temp->next != nullptr){
            temp->next->prev = nullptr;
        }

        head = temp->next;
        delete temp;
    }

    else if(name == tail->name){
        found = true;
        City *temp =tail;
        temp->prev->next = nullptr;
        tail = temp->prev;
        delete temp;
    }

    else{
        City *temp = head;

        while(temp->next != nullptr){
            if(name == temp->name){
                found = true;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
            }

            temp = temp->next;
        }
    }

    if(found == false){
        cout << "City not in list." << endl;
    }
}


/*  The sort city list method will sort the list in order of the cities most frequently visited.
*/
void CommonLocations::sortCityList(){
    bool sorted = false;


    while(sorted == false){
        sorted = true;
        City *temp = head;

        while(temp->next != nullptr){

            if((temp->numVisited) < (temp->next->numVisited)){
                sorted = false;
                if(temp == head){
                    City *next = temp->next;
                    if(next->next != nullptr){
                        temp->next = next->next;
                        next->next = temp;
                        temp->next->prev = temp;
                        temp->prev = next;
                        next->prev = nullptr;
                        head = next;
                        temp = temp->prev;
                    }
                    else{
                        next->next = temp;
                        temp->prev = next;
                        temp->next = nullptr;
                        next->prev = nullptr;
                        head = next;
                        temp = temp->prev;
                    }
                }

                else if(temp->next == tail){
                    temp->next->prev = temp->prev;
                    temp->prev->next = temp->next;
                    temp->next->next = temp;
                    temp->prev = temp->next;
                    temp->next = nullptr;
                    tail = temp;
                    temp = temp->prev;
                }

                else{
                    City *previous = temp->prev;
                    City *next = temp->next;
                    previous->next = next;
                    temp->next = next->next;
                    next->next = temp;
                    next->prev = previous;
                    temp->prev = next;
                    temp->next->prev = next;
                    temp = temp->prev;


                }
            }
            if(temp->next != nullptr){
                temp = temp->next;
            }

        }
    }


}

/*  Returns a pointer to an array of strings with the three most common locations in a given persons
    location list.  This will be used for comparison against other peoples own frequent locations in order
    to suggest potential friends.
*/
string *CommonLocations::mostCommon(string *common, int size){
    sortCityList();
    City *temp = head;

    if(size >= 3){
        for(int i = 0; i < 3; i++){
            if(temp != nullptr){
                common[i] = temp->name;
            }
            temp = temp->next;
        }
    }

    else{

        for(int i = 0; i < size; i++){
            if(temp != nullptr){
                common[i] = temp->name;
            }
            temp = temp->next;
        }
    }

        return common;


}

int CommonLocations::getListSize(){
    int size = 0;
    City *temp = head;

    while(temp != nullptr){
        size++;
        temp = temp->next;
    }

    return size;
}
