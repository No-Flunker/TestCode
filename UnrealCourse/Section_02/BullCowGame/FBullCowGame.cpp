#pragma
#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
//to make syntax Unreal friendly
#define TMap std::map

using int32 = int;



int32 FBullcowGame::GetCurrentTry() const
{
	return MyCurrentry;
}

int32 FBullcowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullcowGame::IsGameWon() const
{
	return bGameIsWon;
}

int32 FBullcowGame::GetMaxtries() const
{
	TMap<int32,int32>WordLengthToMaxTries
	{
	{3,4},
	{4,7},
	{5,10},
	{6,16},
	{7,20}
	};
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

FBullcowGame::FBullcowGame()
{
	Reset(); //defult constructor
}

void FBullcowGame::Reset()
{
	const FString HIDDEN_WORD = "planes";//this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentry = 1;
	bGameIsWon = false;

	return;
}



EGuessStatus FBullcowGame::CheckGuessValidity(FString Guess)const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length()!=GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullcowGame::SubmitValidGuess(FString Guess)
{

	// incriment the turn number
	MyCurrentry++;
	//setup a return variable
	FBullCowCount BullCowCount;

	int32 Wordlength = MyHiddenWord.length(); //assuming same length as guess

	//loop through all letters in the guess
	for  ( int32 MHWChar = 0; MHWChar < Wordlength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < Wordlength; GChar++)
		{
			//if they match then
			if (Guess[MHWChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					//if they're in the same place
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	//compare letters against the hidden word
	if (BullCowCount.Bulls == Wordlength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}


	return BullCowCount;
}

bool FBullcowGame::IsIsogram(FString Word) const
{
	//Treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}
	TMap<char, bool>LetterSeen;
	for (auto Letter:Word )
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}

	return true; //for example in cases where /0 is entered
}

bool FBullcowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
