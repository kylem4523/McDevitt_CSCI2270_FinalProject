#ifndef FRIENDLIST_HPP
#define FRIENDLIST_HPP
#include <string>
#include <vector>
#include "CommonLocations.h"

using namespace std;

struct person;

struct friends{                     //This structure acts as the edges between persons on the graph.
    person *p;                      //Pointer to the adjacent person in the graph.
    int weight;                     //Edge weight for the graph.  Automatically at 1 for friends.
};

struct person{                       //The vertex is going to be the person in the extended friend list.
    std::string name;                //This will be the vertex's identifying trait.
    std::vector <friends> adj;       //This will store the adjacent vertices for the graph.
    CommonLocations citiesList;      //Stores a pointer to the cities list object.
    bool visited;                    //Variable used to flag a visited vertex during graph traversal algorithms.
    int friendsScore;                //Used to return a suggested friend in the suggested friends method.
};

/*  This class is the graph containing people and their friends.  The main functionality of this graph will be to traverse
    and assign a "suggested friends score" to each person in the graph based upon which person we are trying to suggest friends for
    and suggest a friend to the person based on the number of friends they share and the top 3 locations that each person frequents.
*/
class FriendList{
    std::vector<person> people;          //Vector that stores all the people in the graph.

public:
    FriendList();                                                                                       //Constructor for the graph.
    ~FriendList();                                                                                      //Destructor for the graph.
    void addPerson(string name);                                                                        //Adds a person to the graph.
    void addFriend(string firstPerson, string secondPerson);                                            //Adds a friendship between two people.
    void removeFriend(string firstPerson, string secondPerson);                                         //Removes a friendship from the graph.
    void removePerson(string name);                                                                     //Removes a person from the graph.
    void printGraph();                                                                                  //Prints the graph.
    person suggestFriends(string name);                                                                 //Takes in the name of a person in the graph and then returns the person who the highest score between number of mutual friends and frequent locations.
    vector<string> findMutualFriends(string firstPerson, string secondPerson, vector<string> mutualFriends);    //Returns a vector of all the friends that two people share in common.
    int findPerson(string name);                                                                        //Returns the index position of the given person within the people vector.
    void resetFriendScore();
    void setLocationInfo(string name, int);
};

#endif // FRIEND_LIST
