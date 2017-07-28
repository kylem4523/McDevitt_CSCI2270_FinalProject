#include <iostream>
#include <string>
#include <vector>
#include "CommonLocations.h"
#include "FriendList.h"

using namespace std;


/* This function will print out the main menu of the program where the user can then decide from several options on what to do
    within the social network.
*/
void mainMenu(){
    cout << "==Main Menu==" << endl;
    cout << "1. Add Person to the Network" << endl;
    cout << "2. Add a friendship" << endl;
    cout << "3. Remove a friendship" << endl;
    cout << "4. Remove a person from the network" << endl;
    cout << "5. Find mutual friends" << endl;
    cout << "6. Suggest a friend" << endl;
    cout << "7. Print network information" << endl;
    cout << "8. Change Location information" << endl;
    cout << "9. Quit" << endl;
}

/*  This menu will be displayed whenever the user chooses option 7 from the main menu.
    From here they can manipulate the location information for a given person.
*/
void locationMenu(){
    cout << "==Location Menu==" << endl;
    cout << "1. Add City" << endl;
    cout << "2. Remove City" << endl;
    cout << "3. Print City list" << endl;
    cout << "4. Return to main menu" << endl;
}


/*  The main program will display a menu with a bevy of options for the user to choose from.  From here they can build the
    social network, creating and removing friendships, as well as gathering information between people within the graph such
    as suggested friends and mutual friends.  They can also decided whether or not they wish to manipulate location information
    for certain people in the network.
*/
int main()
{
    int input;
    FriendList graph = FriendList();
    mainMenu();

    cin >> input;

    while(input != 9){
        if(input == 1){
            string name;
            cout << "Enter the name of the person you wish to add: " << endl;
            cin >> name;
            graph.addPerson(name);
            mainMenu();
            cin >> input;
        }

        else if(input == 2){
            string name1, name2;
            cout << "Enter the name of the first person"  << endl;
            cin >> name1;
            cout << "Enter the name of the second person" << endl;
            cin >> name2;
            graph.addFriend(name1, name2);
            graph.addFriend(name2, name1);
            mainMenu();
            cin >> input;
        }

        else if(input == 3){
            string name1, name2;
            cout << "Enter the name of the first person" << endl;
            cin >> name1;
            cout << "Enter the name of the friend you wish to remove" << endl;
            cin >> name2;
            graph.removeFriend(name1, name2);
            graph.removeFriend(name2, name1);
            mainMenu();
            cin >> input;
        }

        else if(input == 4){
            string name;
            cout << "Enter the name of the person you wish to remove from the network: " << endl;
            cin >> name;
            graph.removePerson(name);
            mainMenu();
            cin >> input;
        }

        else if(input == 5){
            vector<string> mutual;
            string name1, name2;
            cout << "Enter name of the first person you wish to find mutual friends between: " << endl;
            cin >> name1;
            cout << "Enter the name of the second person you wish to find mutual friends between: " << endl;
            cin >> name2;
            mutual = graph.findMutualFriends(name1, name2, mutual);

            if(mutual.size() == 0){
                cout << "No mutual friends" << endl;
            }

            else{
                cout << "Mutual friends:" << endl;
                for(int i = 0; i < mutual.size(); i++){
                    cout << mutual[i] << endl;
                }
            }

            mainMenu();
            cin >> input;
        }

        else if(input == 6){
            string name;
            person suggested;
            cout << "Enter the name you wish to suggest a friend for: " << endl;
            cin >> name;
            suggested = graph.suggestFriends(name);
            cout <<   suggested.name << endl;
            mainMenu();
            cin >> input;
        }

        else if(input == 7){
            graph.printGraph();
            mainMenu();
            cin >> input;
        }

        else if(input == 8){
            int input2;
            locationMenu();
            cin >> input2;

            while(input2 != 4){
                string name;
                cout << "Enter the name of the person who you want to add a city for: " << endl;
                cin >> name;
                graph.setLocationInfo(name, input2);
                locationMenu();
                cin >> input2;
            }

            mainMenu();
            cin >> input;
        }
    }


    return 0;
}
