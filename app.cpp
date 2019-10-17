#include <iostream>
#include "firethreadpool.h"

using namespace std;

void initThreadPool()
{
    FireThreadPool pool{36};
    cout << "Thread pool initialized" <<endl ;
}

int main()
{
    //print the intro header
    cout << R"(
   🔥  🔥              🔥   🔥                            🔥 
  / _|(_)           | |  | |                          | |
 | |_  _  _ __  ___ | |_ | |__   _ __  ___   __ _   __| |
 |  _|| || '__|/ _ \| __|| '_ \ | '__|/ _ \ / _` | / _` |
 | |  | || |  |  __/| |_ | | | || |  |  __/| (_| || (_| |
 |_|  |_||_|   \___| \__||_| |_||_|   \___| \__,_| \__,_|
                                                 created by JAY                                         
    )" << '\n';

    printf("\x1B[36mUse the following available commands:\033[0m\n\n");

    cout << "🔄  \x1B[32mrestart\033[0m : this cleares the thread pool and re-initializes" << endl;
    cout << "🔢  \x1B[32mprime\033[0m : run prime number example" << endl;
    cout << "🚪  \x1B[32mexit\033[0m : exit program" << endl
         << endl;

    //get user's input
    string command;
    cout << "Please enter a command: " << endl;
    cin >> command;

    //transform to lower case
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    //check command type
    if (command == "restart")
    {
        printf("\nRestarting thread pool..\n\n");
        initThreadPool();
    }
    else if (command == "prime")
    {
        printf("\nStarting Prime number example..\n\n");
    }
    else if (command == "exit")
    {
        printf("\nExiting..\n\n");
        exit(0);
    }
    else
    {
        printf("Unrecognized command. Please try again 👋\n\n");
    }

    return 0;
}