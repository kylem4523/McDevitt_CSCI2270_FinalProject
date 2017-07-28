#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "FriendList.h"

using namespace std;

FriendList::FriendList(){
}

FriendList::~FriendList(){
}


/*  This method allows the user to add new people(vertex) to the social network(graph).
*/
void FriendList::addPerson(string name){
    bool found = false;
    int size = people.size();

    for(int i = 0; i < size; i++){
        if(people[i].name == name){
            found = true;
            break;
        }
    }

    if(found == false){
        person current;
        CommonLocations locations = CommonLocations();
        locations.buildList();
        current.name = name;
        current.friendsScore = 0;
        current.citiesList = locations;

        people.push_back(current);
    }

    else{
        cout << "Person already in the network" << endl;
    }
}

/*  The add friend method effectively creates an edge in the graph between two people aka creates a friendship in the social
    network.
*/
void FriendList::addFriend(string firstName, string secondName){
    for(int i = 0; i < people.size(); i++){
        if(people[i].name == firstName){
            for(int k = 0; k < people.size(); k++){
                if((people[k].name == secondName) && (i != k)){
                    friends newFriend;
                    newFriend.p = &people[k];
                    newFriend.weight = 1;
                    people[i].adj.push_back(newFriend);
                }
            }
        }
    }
}

/*  The print graph method will print out the people in the graph and all their friends as well.
*/
void FriendList::printGraph(){
    if(people.size() == 0){
        cout << "No people in the social network" << endl;
    }

    else{
        for(int i = 0; i < people.size();i++){
            cout << "The current person is: " << people[i].name << endl;
            cout << "Their friends are: ";

            if(people[i].adj.size()==0){
                cout << "None" << endl;
            }

            else{
                for(int j = 0; j < people[i].adj.size();j++){
                    cout << people[i].adj[j].p->name << endl;
                }
            }
        }
    }
}


/*  This method will remove a friendship from the social network effectively removing an edge from between two people.
*/
void FriendList::removeFriend(string firstName, string secondName){
    if(people.size()==0){
        cout << "The network is empty" << endl;
    }

    else{
        bool foundFirst = false;
        bool foundSecond = false;

        for(int i = 0; i < people.size();i++){
           if(people[i].name == firstName){
                foundFirst = true;
                for(int j = 0; j <people[i].adj.size();j++){
                    if(people[i].adj[j].p->name == secondName){
                        foundSecond = true;
                        people[i].adj.erase(people[i].adj.begin() + j);
                    }
                }
            }
        }

        if(foundFirst == false){
            cout << "Person not in network" << endl;
        }

        if(foundFirst == true && foundSecond == false){
            cout << "Friendship does not exist" << endl;
        }
    }
}

void FriendList::removePerson(string name){
    if(people.size() != 0){
        int index = findPerson(name);
        for(int i = 0; i < people.size();i++){
            for(int j = 0; j < people[i].adj.size();j++){
               if(name == (people[i].adj[j].p->name)){
                    string removeName = people[i].adj[j].p->name;
                    removeFriend(people[i].name, removeName);
               }
            }
        }

        if(index != -1){
            people.erase(people.begin()+index);
        }

        else{
            cout << "Person not in network" << endl;
        }
    }

    else{
        cout << "Network empty" << endl;
    }
}


int FriendList::findPerson(string name){
    for(int i = 0; i < people.size();i++){
        if(people[i].name == name){
            return i;
        }
    }
    return -1;
}


/*  This method returns a vector of the all the names of the friends that two given people share in common.
*/
vector<string> FriendList::findMutualFriends(string firstName, string secondName, vector<string> mutualFriends){
    int firstIndex = findPerson(firstName);
    int secondIndex = findPerson(secondName);

    if(firstIndex == -1 || secondIndex == -1){
        cout << "One or both people not in list" << endl;
    }

    else{

        for(int i = 0; i < people[firstIndex].adj.size();i++){
            for(int j = 0; j < people[secondIndex].adj.size();j++){
                    if((people[firstIndex].adj[i].p->name) == (people[secondIndex].adj[j].p->name)){
                        mutualFriends.push_back(people[firstIndex].adj[i].p->name);
                    }
            }
        }
    }

    return mutualFriends;
}


/*  This method will take in the name of a person and suggest a friend based on the number of mutual friends they share and
    how often they frequent the same locations.  One point will be assigned per mutual friend and 3 points for each shared top
    location.  The function will return the person who scores the highest in the graph based on these factors.
*/
person FriendList::suggestFriends(string name){
    int index = findPerson(name);

    if(index != -1 && people.size() > 1){
        int locationSize = people[index].citiesList.getListSize();
        string common1[locationSize];

        people[index].citiesList.sortCityList();
        people[index].citiesList.mostCommon(common1, locationSize);

        for(int i = 0; i < people.size(); i++){
            if(people[i].name == name){
                continue;
            }

            else{
                int friendLocationSize = people[i].citiesList.getListSize();
                people[i].friendsScore = 1;
                string common2[friendLocationSize];
                vector <string> mutualFriends;
                people[i].citiesList.sortCityList();
                people[i].citiesList.mostCommon(common2, friendLocationSize);

                for(int j = 0; j < 3; j++){
                    for(int k = 0; k < 3; k++){
                        if(common1[j] == common2[k]){
                            people[i].friendsScore += 2;
                        }
                    }
                }

                mutualFriends = findMutualFriends(people[index].name, people[i].name, mutualFriends);
                int mutualFriendsScore = mutualFriends.size();

                people[i].friendsScore = people[i].friendsScore + mutualFriendsScore;
            }
        }

        person suggested = people[0];

        for(int i = 0; i < people.size(); i++){
            if(suggested.friendsScore < people[i].friendsScore){
                suggested = people[i];
            }
        }
        resetFriendScore();
        return suggested;

    }

    else if(people.size() == 1){
        cout << "No other people in network" << endl;
    }

    else{
        cout << "Person not in network" << endl;
    }
}


/*  This method is called at the end of the suggested friend method in order to reset all the suggested friend scores for
    each person so that the method will work correctly with multiple function calls for different people.
*/
void FriendList::resetFriendScore(){
    for(int i = 0; i < people.size(); i++){
        people[i].friendsScore = 0;
    }
}

void FriendList::setLocationInfo(string name, int input){
    int index = findPerson(name);
    if(index != -1){
        if(input == 1){
            string cityName;
            int numVisited;
            cout << "Enter the name of the city: " << endl;
            cin.ignore();
            getline(cin, cityName);
            cout << "Enter the number of times you have visited the city: " << endl;
            cin >> numVisited;
            people[index].citiesList.addCity(cityName, numVisited);
        }

        else if(input == 2){
            string cityName;
            cout << "Enter the city you wish to remove: " << endl;
            cin.ignore();
            getline(cin, cityName);
            people[index].citiesList.deleteCity(cityName);
        }

        else if(input == 3){
            people[index].citiesList.printList();
        }
    }

    else{
        cout << "Person not in network" << endl;
    }
}
