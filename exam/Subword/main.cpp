#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

bool CompareSets(set<char> const &lhs, set<char> const &rhs)
{
    return lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin());
}

std::set<char> StrToCharSet(std::string& targetStr)
{
    std::set<char> charSet;
    for(char& ch : targetStr)
    {
        charSet.insert(ch);
    }
    return charSet;
}

// Возвращает true, если из символов строки word можно составить строку subWord
// Каждый символ строки word может быть использован только один раз
// Если строка subword пустая или совпадает с word, функция возвращает false
// Например, из слова "машина" можно составить слово "шина", а слово "мама" нельзя, т.к. буква "м" в исходном слове только одна

bool CanMakeSubword(string& word, string& subWord) // lull: убрал const с аргументов
{
    if (subWord.empty() || word == subWord)
    {
        return false;
    }

    set<char> wordSet = StrToCharSet(word);
    set<char> subWordSet = StrToCharSet(subWord);
    set<char> resultSet;
    std::set_intersection(wordSet.begin(), wordSet.end(), subWordSet.begin(), subWordSet.end(),
                        std::inserter(resultSet, resultSet.begin()));

    return CompareSets(resultSet, subWordSet);
}

int main()
{
	/*
	Написать программу, в начале которой запрашивается "слово" из которого надо будет составлять слова
	Почередно игрок 1 и игрок 2 вводят слова, которые они составили из букв этого слова (программа полагается на честность игроков)
	Каждому игроку начисляется столько баллов, сколько букв в его слове
	Если игрок ввел пустую строку, он пропускает ход
	Если оба игрока последовательно ввели пустую строку, игра завершается
	Если игрок ввел слово, которое составить нельзя из букв исходного, он должен ввести другое слово
	Если игрок ввел слово, которое уже было принято, он должен ввести другое слово
	Перед выходом программа выводит слова, введенные каждым игроком и сумму набранных им баллов, и объявляет победителя
	Пример диалога:
		Enter a word: телеграмма
		Player 1> грамм
		Player 2> рама
		Player 1> грамм
		  This word has already been entered. Enter another
		Player 1> лама
		Player 2> телега
		Player 1> телефон
		  You can't make this word from "телеграмма". Enter another
		Player 1>
		Player 2>
		Game over.
		Player 1 words (9 points):
		  грамм 5
		  лама 4
		Player 2 words (10 points):
		  рама 4
		  телега 6
		Player 2 have won!
	*/

    string inputWord;
    cout << "Enter a word:";
    getline(cin, inputWord);

    string inputPlayer1Word;
    string inputPlayer2Word;
    string inputNextVariantWord;

    size_t player1Score = 0;
    size_t player2Score = 0;
    vector<string> player1Words;
    vector<string> player2Words;
    vector<string> playerUsedWords;

    bool isFirstPlayerInputWord = true;
    cout << "Player 1>";

    while(getline(cin, inputNextVariantWord))
    {
        if (inputNextVariantWord.empty() && (inputPlayer1Word.empty() || inputPlayer2Word.empty()))
        {
            break;
        }

        if (!isFirstPlayerInputWord)
        {
            isFirstPlayerInputWord = true;
            cout << "Player 1>";

            inputPlayer1Word = inputNextVariantWord;


            if (std::find(playerUsedWords.begin(), playerUsedWords.end(), inputPlayer1Word) != playerUsedWords.end())
            {
                cout << "\n  This word has already been entered. Enter another" << endl;
                isFirstPlayerInputWord = false;
            }
            else
            {
                if (CanMakeSubword(inputWord, inputPlayer1Word))
                {
                    player1Words.push_back(inputPlayer1Word);
                    playerUsedWords.push_back(inputPlayer1Word);
                    player1Score += inputPlayer1Word.size();
                }
                else
                {
                    isFirstPlayerInputWord = false;
                    cout << "\n  You can't make this word from '" << inputWord << "'. Enter another" << endl;
                }
            }
        }
        else
        {
            cout << "Player 2>";
            isFirstPlayerInputWord = false;
            inputPlayer2Word = inputNextVariantWord;

            if (inputNextVariantWord.empty() && inputPlayer1Word.empty())
            {
                break;
            }

            if (std::find(playerUsedWords.begin(), playerUsedWords.end(), inputPlayer2Word) != playerUsedWords.end())
            {
                cout << "\n  This word has already been entered. Enter another" << endl;
                isFirstPlayerInputWord = true;
            }
            else
            {
                if (CanMakeSubword(inputWord, inputPlayer2Word))
                {
                    player2Words.push_back(inputPlayer2Word);
                    playerUsedWords.push_back(inputPlayer2Word);
                    player2Score += inputPlayer2Word.size();
                }
                else
                {
                    isFirstPlayerInputWord = true;
                    cout << "\n  You can't make this word from '" << inputWord << "'. Enter another" << endl;

                }
            }

        }

    }

    cout << "\nGame over!" << endl;

    cout << "Player 1 word (" << player1Score << ")" << endl;
    for (auto &word : player1Words)
    {
        cout << "  " << word << " " << word.length() << endl;
    }

    cout << "Player 2 word (" << player2Score << ")" << endl;
    for (auto &word : player2Words)
    {
        cout << "  " << word << " " << word.length() << endl;
    }

    cout << endl;

    if (player1Score > player2Score)
    {
        cout << "Player1 won!" << endl;
    }
    else if (player1Score < player2Score)
    {
        cout << "Player2 won!" << endl;
    }
    else
    {
        cout << "No winners!" << endl;
    }

	return 0;
}