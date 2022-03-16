//Martin Rendahl Wordle Assignment


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#define FOREGROUND(color, text) "\x1B[" << static_cast<int>(color) << "m" << text << "\033[0m"
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"

using namespace std;

enum class ForegroundColor : int {
    Red = 31,
    Green = 32,
    Yellow = 33,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93
};

enum class BackgroundColor : int {
    Red = 41,
    Green = 42,
    Yellow = 43,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103
};



class WordleGame
{
public:

    WordleGame() {
        cout << "Constructor called" << endl;     
    }

    void StartGame() 
    {
        amountOfGuesses = 0;
        wordToGuess = "";
        GetNewGuessWord();
        StartGuessWord();
    }

private:

    int amountOfGuesses = 0;
    string wordToGuess = "";

    void StartGuessWord()
    {
        string guess;
        cout << "\nGuess the 5 letter word, you have 6 tries.  " << endl;

        do {
            amountOfGuesses++;
            cout << "guess number " << amountOfGuesses << ", Enter your guess: ";
            while (!(cin >> guess) || guess.size() != 5)
            {
                cout << "Must be a 5 letter word. Enter your guess:" << endl;
                cin.clear();
                cin.ignore(100, '\n');
            }
            for (int i = 0; i < guess.length(); i++)
            {
                guess[i] = toupper(guess[i]);
            }

            if (guess != wordToGuess)
            {
                for (int i = 0; i < guess.size(); i++)
                {
                    if (guess[i] == wordToGuess[i])
                    {
                        cout << BACKGROUND(BackgroundColor::Green, guess[i]);
                    }
                    else if (wordToGuess.find(guess[i]) != string::npos)
                    {
                        cout << BACKGROUND(BackgroundColor::Yellow, guess[i]);
                    }
                    else
                    {
                        cout << guess[i];
                    }
                }
                cout << " " << endl;

            }
            else if (guess == wordToGuess)
            {
                for (int i = 0; i < guess.size(); i++)
                {
                    cout << BACKGROUND(BackgroundColor::Green, guess[i]);
                }
                cout << "\nYou guess it right on guess number " << amountOfGuesses << endl;
            }

        } while (guess != wordToGuess && amountOfGuesses < 6);

        if (guess != wordToGuess)
        {
            cout << "You did not guess the word." << endl;
        }
        cout << "The word was " << wordToGuess << endl;

        AskRestart();
    }

    void GetNewGuessWord() {
        string line;
        int randomNumber;

        srand(time(NULL));
        randomNumber = rand() % 8596 + 1;
        cout << randomNumber << endl;

        ifstream wordFile("words.txt");
        if (wordFile.is_open())
        {
            for (int lineno = 0; getline(wordFile, line) && lineno < randomNumber + 1; lineno++)
                if (lineno == randomNumber)
                {
                    cout << line << endl;
                    wordToGuess = line;
                    break;
                }
            wordFile.close();
        }
    }

    void AskRestart()
    {
        char answer;
        cout << "\nDo you wanna restart the game (Y/N)";
        while (!(cin >> answer))
        {
            cout << "Must be Y or N" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (answer == 'Y')
        {
            StartGame();
        }
        else if (answer == 'N')
        {
            cout << "Closing Game" << endl;
        }
    }


};





int main()
{
    WordleGame myGame;
    myGame.StartGame();

    return 0;
}
