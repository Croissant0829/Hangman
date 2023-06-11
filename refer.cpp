#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

vector<string> readWordsFromFile(string filename) {
    vector<string> words;
    ifstream file(filename);
    if (file.is_open()) {
        string word;
        while (getline(file, word)) {
            words.push_back(word);
        }
        file.close();
    } else {
        cout << "Error opening file!" << endl;
    }
    return words;
}

string getRandomWord(vector<string> words) {
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

string getHiddenWord(const string& word) {
    string hiddenWord;
    for (char c : word) {
        if (isalpha(c)) {
            hiddenWord += "_";
        } else {
            hiddenWord += c;
        }
    }
    return hiddenWord;
}

void updateHiddenWord(string& hiddenWord, const string& word, char guess) {
    for (int i = 0; i < word.length(); i++) {
        if (tolower(word[i]) == tolower(guess)) {
            hiddenWord[i] = word[i];
        }
    }
}

void displayHangman(int chance) {
    cout << " ________     " << endl;
    cout << "|        |    " << endl;
    
    if (chance >= 1) {
        cout << "|        O    " << endl;
    } else {
        cout << "|             " << endl;
    }
    
    if (chance == 2) {
        cout << "|       /     " << endl;
    } else if (chance == 3) {
        cout << "|       /|    " << endl;
    } else if (chance >= 4) {
        cout << "|       /|\\  " << endl;
    } else {
        cout << "|             " << endl;
    }
    
    if (chance == 5) {
        cout << "|       /     " << endl;
    } else if (chance >= 6)
    cout << "|       / \\  " << endl;
     else {
        cout << "|             " << endl;
    }
    
    cout << "|             " << endl;
    cout << "|_____________" << endl;
}

void playHangman() {
    vector<string> words = readWordsFromFile("words.txt");
    bool playAgain = true;

    while (playAgain) {
        string word = getRandomWord(words);
        string hiddenWord = getHiddenWord(word);
        int maxGuesses = 6;
        int chance = 6;
        int incorrectGuesses = 0;
        vector<char> guessedLetters;

        cout << "Welcome to Hangman!" << endl;

        while (hiddenWord != word && incorrectGuesses < maxGuesses) {
            cout << "Word: " << hiddenWord << endl;
            cout << "Guesses remaining: " << maxGuesses - incorrectGuesses << endl;
            cout << "Guessed letters: ";
            for (char c : guessedLetters) {
                cout << c << " ";
            }
            cout << endl;
            
            displayHangman(chance);

            char guess;
            cout << "Enter your guess: ";
            cin >> guess;

            if (isalpha(guess)) {
                guess = tolower(guess);

                if (std::find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
                    cout << "You already guessed that letter. Try again." << endl;
                } else {
                    guessedLetters.push_back(guess);

                    if (word.find(guess) != string::npos) {
                        updateHiddenWord(hiddenWord, word, guess);
                        cout << "Correct guess!" << endl;
                    } else {
                        incorrectGuesses++;
                        chance --;
                        cout << "Incorrect guess!" << endl;
                    }
                }
            } else {
                cout << "Invalid guess. Please enter a letter." << endl;
            }

            cout << endl;
        }
        
        displayHangman(chance);

        if (hiddenWord == word) {
            cout << "Congratulations! You guessed the word: " << word << endl;
        } else {
            cout << "You ran out of guesses. The word was: " << word << endl;
        }

        cout << "Do you want to play again? (Y/N): ";
        char playAgainChoice;
        cin >> playAgainChoice;

        if (tolower(playAgainChoice) != 'y') {
            playAgain = false;
        }

        cout << endl;
    }

    cout << "Thank you for playing Hangman!" << endl;
}

int main() {
    playHangman();
    
    return 0;
}
