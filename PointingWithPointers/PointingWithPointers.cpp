// Showcases examples of pointers in a fun, short fighting game

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

bool quitOrPlayAgain();
bool whoLost(int* const pPlayerHealth); // Takes in a pointer pointing at the player's health

int main()
{
    srand(time(0));
    chrono::duration<int, milli> timespan(2000);
    bool repeat = true; // Used to replay the game
    bool notAnOption = false; // Gives the player another chance to input a correct value
    int wins = 0; // Keeps track of the # of wins if the player plays again
    int turn = 0; // When turn = 4 or more, the player's special move becomes available
    string playerName;
    int moveSelected;
    bool playerLost = false;

    string fightingMoves[4] = {"Uppercut", "Sweeping Kick", "Karate Chop", "Hadouken"};
    // Uppercut has a chance not to connect but it does solid damage
    // Sweeping Kick does constistant but low damage
    // Karate Chop has a wide range of potential damage
    // Hadouken does insane damage but has a cooldown

    string* pFightingMoves = fightingMoves; // Pointer that points to fighting moves so that I can pull the name of the move depending on the player's input

    cout << "In this game, input the number corresponding with a move to use it.\n";
    this_thread::sleep_for(timespan);
    cout << "A match does not end until somebody is knocked out.\n";
    this_thread::sleep_for(timespan);
    cout << "Make it through three matches to be crowned champion.\n";
    this_thread::sleep_for(timespan);
    cout << "Welcome, new contestant! What's your name?\n";
    this_thread::sleep_for(timespan);
    cout << "Name: ";
    cin >> playerName;

    do
    {
        int playerHealth = 20;
        int joeHealth = 15;
        int bryanHealth = 25;
        int carlHealth = 30;
        int joeDamage = rand() % 4; // 0-3 damage
        int bryanDamage = rand() % 2 + 2; // 2-4 damage
        int carlDamage = rand() % 3 + 3; // 3-6 damage
        int uppercutChance = rand() % 2; // Will be a 50% chance, deals 7 damage
        int karateChopDamage = rand() % 6 + 1; // 1-6 damage
        cout << "\nFeeling nervous on your first match, " << playerName << "?\n"; // Beginning of first match
        this_thread::sleep_for(timespan);
        cout << "Don't worry, everyone feels that way.\n";
        this_thread::sleep_for(timespan);
        cout << "For your first match, you'll be up against Joe Shmo.\n";
        this_thread::sleep_for(timespan);
        cout << "I wouldn't fret. Joe loses the majority of his bouts.\n\n";
        this_thread::sleep_for(timespan);

        while (playerHealth > 0 && joeHealth > 0) // Exits loop if either fighter is knocked out
        {
            joeDamage = rand() % 4;
            uppercutChance = rand() % 2;
            karateChopDamage = rand() % 6 + 1;
            ++turn;
            cout << "Your health: " << playerHealth;
            cout << "\nJoe's health: " << joeHealth << "\n\n";
            if (turn >= 4) // Special move has become available
            {
                cout << "1 -> Uppercut\n";
                cout << "2 -> Sweeping Kick\n";
                cout << "3 -> Karate Chop\n";
                cout << "4 -> Special\n\n";
            }
            else
            {
                cout << "1 -> Uppercut\n";
                cout << "2 -> Sweeping Kick\n";
                cout << "3 -> Karate Chop\n\n";
            }
            cout << "Select your move: ";
            cin >> moveSelected;
            cout << "\n";
            do
            {
                if (turn >= 4 && moveSelected == 4) // Player uses special move
                {
                    cout << "You used: " << *(fightingMoves + 3) << "\n";
                    cout << "Joe had no time to attack.\n";
                    this_thread::sleep_for(timespan);
                    cout << "You dealt 10 damage.\n\n";
                    this_thread::sleep_for(timespan);
                    joeHealth = joeHealth - 10;
                    turn = 0;
                    notAnOption = false;
                }
                else if (moveSelected == 3) // Player uses karate chop
                {
                    cout << "You used: " << *(fightingMoves + 2) << "\n";
                    cout << "Joe dealt " << joeDamage << " damage.\n";
                    this_thread::sleep_for(timespan);
                    cout << "You dealt " << karateChopDamage << " damage.\n\n";
                    this_thread::sleep_for(timespan);
                    joeHealth = joeHealth - karateChopDamage;
                    playerHealth = playerHealth - joeDamage;
                    notAnOption = false;
                }
                else if (moveSelected == 2) // Player uses sweeping kick
                {
                    cout << "You used: " << *(fightingMoves + 1) << "\n";
                    cout << "Joe dealt " << joeDamage << " damage.\n";
                    this_thread::sleep_for(timespan);
                    cout << "You dealt 3 damage.\n\n";
                    this_thread::sleep_for(timespan);
                    joeHealth = joeHealth - 3;
                    playerHealth = playerHealth - joeDamage;
                    notAnOption = false;
                }
                else if (moveSelected == 1) // Player uses uppercut
                {
                    if (uppercutChance > 0) // Uppercut lands
                    {
                        cout << "You used: " << *(fightingMoves) << "\n";
                        cout << "Joe dealt " << joeDamage << " damage.\n";
                        this_thread::sleep_for(timespan);
                        cout << "You dealt 7 damage.\n\n";
                        this_thread::sleep_for(timespan);
                        joeHealth = joeHealth - 7;
                        playerHealth = playerHealth - joeDamage;
                        notAnOption = false;
                    }
                    else // Uppercut misses
                    {
                        cout << "You used: " << *(fightingMoves) << "\n";
                        cout << "Your uppercut missed!\n";
                        this_thread::sleep_for(timespan);
                        cout << "Joe dealt " << joeDamage << " damage.\n\n";
                        this_thread::sleep_for(timespan);
                        playerHealth = playerHealth - joeDamage;
                        notAnOption = false;
                    }
                }
                else // Player entered invalid input
                {
                    cout << "Input one of the available numbers: ";
                    cin.clear();
                    cin.ignore(1);
                    cin >> moveSelected;
                    notAnOption = true;
                    cout << "\n";
                }
            } while (notAnOption);
        }
        playerLost = whoLost(&playerHealth); // Only player health needs to be input, as either they've been knocked out or they haven't

        if (playerLost)
        {
            goto gameOver;
        }
        turn = 0;

        cout << "I'm not surprised, " << playerName << ". It's practically impossible to lose to Joe.\n"; // Beginning of second match
        this_thread::sleep_for(timespan);
        cout << "But don't underestimate your next opponent.\n";
        this_thread::sleep_for(timespan);
        cout << "For your second match, you'll be up against Bryan Kennedy.\n";
        this_thread::sleep_for(timespan);
        cout << "He strikes fast, but I can tell you hit hard.\n\n";
        this_thread::sleep_for(timespan);

        while (playerHealth > 0 && bryanHealth > 0)
        {
            bryanDamage = rand() % 2 + 2;
            uppercutChance = rand() % 2;
            karateChopDamage = rand() % 6 + 1;
            ++turn;
            cout << "Your health: " << playerHealth;
            cout << "\nBryan's health: " << bryanHealth << "\n\n";
            if (turn >= 4)
            {
                cout << "1 -> Uppercut\n";
                cout << "2 -> Sweeping Kick\n";
                cout << "3 -> Karate Chop\n";
                cout << "4 -> Special\n\n";
            }
            else
            {
                cout << "1 -> Uppercut\n";
                cout << "2 -> Sweeping Kick\n";
                cout << "3 -> Karate Chop\n\n";
            }
            cout << "Select your move: ";
            cin >> moveSelected;
            cout << "\n";
            do
            {
                if (turn >= 4 && moveSelected == 4)
                {
                    cout << "You used: " << *(fightingMoves + 3) << "\n";
                    cout << "Bryan had no time to attack.\n";
                    this_thread::sleep_for(timespan);
                    cout << "You dealt 10 damage.\n\n";
                    this_thread::sleep_for(timespan);
                    bryanHealth = bryanHealth - 10;
                    turn = 0;
                    notAnOption = false;
                }
                else if (moveSelected == 3)
                {
                    cout << "You used: " << *(fightingMoves + 2) << "\n";
                    cout << "Bryan dealt " << bryanDamage << " damage.\n";
                    this_thread::sleep_for(timespan);
                    cout << "You dealt " << karateChopDamage << " damage.\n\n";
                    this_thread::sleep_for(timespan);
                    bryanHealth = bryanHealth - karateChopDamage;
                    playerHealth = playerHealth - bryanDamage;
                    notAnOption = false;
                }
                else if (moveSelected == 2)
                {
                    cout << "You used: " << *(fightingMoves + 1) << "\n";
                    cout << "Bryan dealt " << bryanDamage << " damage.\n";
                    this_thread::sleep_for(timespan);
                    cout << "You dealt 3 damage.\n\n";
                    this_thread::sleep_for(timespan);
                    bryanHealth = bryanHealth - 3;
                    playerHealth = playerHealth - bryanDamage;
                    notAnOption = false;
                }
                else if (moveSelected == 1)
                {
                    if (uppercutChance > 0)
                    {
                        cout << "You used: " << *(fightingMoves) << "\n";
                        cout << "Bryan dealt " << bryanDamage << " damage.\n";
                        this_thread::sleep_for(timespan);
                        cout << "You dealt 7 damage.\n\n";
                        this_thread::sleep_for(timespan);
                        bryanHealth = bryanHealth - 7;
                        playerHealth = playerHealth - bryanDamage;
                        notAnOption = false;
                    }
                    else
                    {
                        cout << "You used: " << *(fightingMoves) << "\n";
                        cout << "Your uppercut missed!\n";
                        this_thread::sleep_for(timespan);
                        cout << "Bryan dealt " << bryanDamage << " damage.\n\n";
                        this_thread::sleep_for(timespan);
                        playerHealth = playerHealth - bryanDamage;
                        notAnOption = false;
                    }
                }
                else
                {
                    cout << "Input one of the available numbers: ";
                    cin.clear();
                    cin.ignore(1);
                    cin >> moveSelected;
                    notAnOption = true;
                    cout << "\n";
                }
            } while (notAnOption);
        }
        playerLost = whoLost(&playerHealth);

        if (playerLost)
        {
            goto gameOver;
        }

        cout << "Well, " << playerName << ", that was quite impressive.\n"; // Beginning of third match
        this_thread::sleep_for(timespan);
        cout << "Bryan is no cake walk, but this is the ultimate challenge.\n";
        this_thread::sleep_for(timespan);
        cout << "For your last match, you'll be up against Carl Pines.\n";
        this_thread::sleep_for(timespan);
        cout << "Just so you know, Carl hasn't lost a match his whole career.\n\n";
        this_thread::sleep_for(timespan);

        while (playerHealth > 0 && carlHealth > 0)
        {
            carlDamage = rand() % 3 + 3;
            uppercutChance = rand() % 2;
            karateChopDamage = rand() % 6 + 1;
            ++turn;
            cout << "Your health: " << playerHealth;
            cout << "\nCarl's health: " << carlHealth << "\n\n";
            if (turn >= 4)
            {
                cout << "1 -> Uppercut\n";
                cout << "2 -> Sweeping Kick\n";
                cout << "3 -> Karate Chop\n";
                cout << "4 -> Special\n\n";
            }
            else
            {
                cout << "1 -> Uppercut\n";
                cout << "2 -> Sweeping Kick\n";
                cout << "3 -> Karate Chop\n\n";
            }
            cout << "Select your move: ";
            cin >> moveSelected;
            cout << "\n";
            do
            {
                if (turn >= 4 && moveSelected == 4)
                {
                    cout << "You used: " << *(fightingMoves + 3) << "\n";
                    cout << "Carl had no time to attack.\n";
                    this_thread::sleep_for(timespan);
                    cout << "You dealt 10 damage.\n\n";
                    this_thread::sleep_for(timespan);
                    carlHealth = carlHealth - 10;
                    turn = 0;
                    notAnOption = false;
                }
                else if (moveSelected == 3)
                {
                    cout << "You used: " << *(fightingMoves + 2) << "\n";
                    cout << "Carl dealt " << carlDamage << " damage.\n";
                    this_thread::sleep_for(timespan);
                    cout << "You dealt " << karateChopDamage << " damage.\n\n";
                    this_thread::sleep_for(timespan);
                    carlHealth = carlHealth - karateChopDamage;
                    playerHealth = playerHealth - carlDamage;
                    notAnOption = false;
                }
                else if (moveSelected == 2)
                {
                    cout << "You used: " << *(fightingMoves + 1) << "\n";
                    cout << "Carl dealt " << carlDamage << " damage.\n";
                    this_thread::sleep_for(timespan);
                    cout << "You dealt 3 damage.\n\n";
                    this_thread::sleep_for(timespan);
                    carlHealth = carlHealth - 3;
                    playerHealth = playerHealth - carlDamage;
                    notAnOption = false;
                }
                else if (moveSelected == 1)
                {
                    if (uppercutChance > 0)
                    {
                        cout << "You used: " << *(fightingMoves) << "\n";
                        cout << "Carl dealt " << carlDamage << " damage.\n";
                        this_thread::sleep_for(timespan);
                        cout << "You dealt 7 damage.\n\n";
                        this_thread::sleep_for(timespan);
                        carlHealth = carlHealth - 7;
                        playerHealth = playerHealth - carlDamage;
                        notAnOption = false;
                    }
                    else
                    {
                        cout << "You used: " << *(fightingMoves) << "\n";
                        cout << "Your uppercut missed!\n";
                        this_thread::sleep_for(timespan);
                        cout << "Carl dealt " << carlDamage << " damage.\n\n";
                        this_thread::sleep_for(timespan);
                        playerHealth = playerHealth - carlDamage;
                        notAnOption = false;
                    }
                }
                else
                {
                    cout << "Input one of the available numbers: ";
                    cin.clear();
                    cin.ignore(1);
                    cin >> moveSelected;
                    notAnOption = true;
                    cout << "\n";
                }
            } while (notAnOption);
        }
        playerLost = whoLost(&playerHealth);

        if (playerLost)
        {
            goto gameOver;
        }

        ++wins;
        cout << "You've done it, " << playerName << ", you beat them all.\n"; // You've won
        this_thread::sleep_for(timespan);
        cout << "Joe, Bryan, and Carl have all met their maker.\n";
        this_thread::sleep_for(timespan);
        cout << "For this feat, you will be rewarded.\n";
        this_thread::sleep_for(timespan);
        cout << "But the three of these guys will challenge you again, if you let them.\n\n";
        this_thread::sleep_for(timespan);
        cout << "Wins: " << wins << "\n\n";
        this_thread::sleep_for(timespan);

        gameOver:
        repeat = quitOrPlayAgain();
    } while (repeat);
}

bool whoLost(int* const pPlayerHealth)
{
    chrono::duration<int, milli> timespan(2000);
    bool playerLost;
    if (*pPlayerHealth <= 0)
    {
        cout << "You have been knocked out.\n";
        this_thread::sleep_for(timespan);
        cout << "You put up a good fight, but you're always welcome to try again.\n\n";
        this_thread::sleep_for(timespan);
        playerLost = true;
    }
    else
    {
        cout << "Congratulations! You knocked out your opponent.\n\n";
        this_thread::sleep_for(timespan);
        *pPlayerHealth = 20; // Changing the value of the pointer changes the og variable in main so the player is at max health for the next fight
        playerLost = false;
    }
    return playerLost;
}

bool quitOrPlayAgain()
{
    char playAgain;
    bool repeat;
    bool loop;
    chrono::duration<int, milli> timespan(1000);
    do
    {
        cout << "Would you like to play again? y/n: ";
        cin >> playAgain;
        cout << endl;

        switch (playAgain) {
        case 'y':
        case 'Y':
            cout << "Resetting the game...\n\n";
            repeat = true;
            loop = false;
            this_thread::sleep_for(timespan);
            break;

        case 'n':
        case 'N':
            cout << "Goodbye! Thanks for playing.\n\n";
            repeat = false;
            loop = false;
            this_thread::sleep_for(timespan);
            break;

        default:
            cout << "Please respond with y/n.\n\n";
            loop = true;
        }
    } while (loop);
    return repeat;
}
