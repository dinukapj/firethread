#include <iostream>
#include <math.h>
#include "firethreadpool.h"

using namespace std;

// FireThreadPool pool;

//initialize a threadpool
void initThreadPool()
{
    // pool = pool(21);
    cout << "Thread pool initialized" << endl;
}

//calculate
void runPrimer(int userInput)
{
    FireThreadPool pool{36};
    auto value = pool.enqueue([&] {
        int count = 0;
        for (int a = 2; a < userInput; a++)
        {
            bool prime = true;
            for (int c = 2; c * c <= a; c++)
            {
                if (a % c == 0)
                {
                    prime = false;
                    break;
                }
            }
            if (prime)
                count++;
        }

        return count;
    });

    cout << "Thread completed its work ✅" << endl;

    cout << "Prime number count: " << value.get() << endl;
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
        cout << "Enter a number: ";
        int number;
        cin >> number;
        runPrimer(number);
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