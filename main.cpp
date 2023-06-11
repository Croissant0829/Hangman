#include <iostream>
#include <fstream>
#include <vector> 

using namespace std;

int chance;

void display();

int main()
{
    cout<<"     ==============\n";
    cout<<"      HANGMAN GAME\n";
    cout<<"     ==============\n";
    cout<<"!!!Welcome to Hangman Game!!!\n";
    
    vector<string> words;
    ifstream file("words.txt");
    if (file.is_open())
    {
        string word;
        while(getline(file, word))
        {
            words.push_back(word);
        }
        file.close();
    }
    else
    {
        cout<<"Cannot open the file!\n";
    }
    
    char choice;
    do
    {
        srand(time(0));
        int random= rand()% words.size();
        string question= words[random];
        string ans;
        for (int i=0;i<question.length(); i++)
        {
            ans += "_";
        }
        
        chance = 6;
        int miss = 0;
        vector<char> guessed;
        bool correct = false;
        char letter;
        
        while (ans!=question && miss<6)
        {
            display();
            cout<<"Remaining chance: "<<chance<<endl;
            cout<<"Guessed letter: ";
            for (int i = 0; i < guessed.size(); i++)
            {
                cout<<guessed[i]<<" ";
            }
            cout<<endl;
            cout<<"Word: ";
            for (int i =0; i < ans.length(); i++)
            {
                cout<<ans[i]<<" ";
            }
            cout<<endl;
            cout<<"\nPlease enter you guess: ";
            cin>>letter;
            
            for(int i = 0; i<question.length(); i++)
            {
                if(letter == question[i])
                {
                    ans[i] = letter;
                    correct = true;
                }
            }
            if (correct)
            {
                cout<<"That is a correct letter!\n";
            }
            else
            {
                cout<<"Sorry it is incorrect!\n";
                guessed.push_back(letter);
                miss++;
                chance--;
            }
            correct = false;
            
            
        }
        
        if(ans==question)
            {
                cout<<"Congratulations! You save the person!\n"
                <<"The answer is: "<<question<<endl;
            }
            else
            {
                cout<<"The man is hanged!\n";
            }
        
        cout << "Do you want to play again? (Y/N): ";
        cin>>choice;
    }while(choice=='y' || choice=='Y');
    
    cout << "Thank you for playing Hangman Game!" << endl;

    return 0;
}

void display()
{
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
