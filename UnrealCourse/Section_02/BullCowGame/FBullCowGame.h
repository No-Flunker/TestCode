/*The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>
//to make syntax Unreal Friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullcowGame
{
public:
	FBullcowGame();


	int32 GetMaxtries() const ;
	int32 GetCurrentTry() const ;
	int32 GetHiddenWordLength()const;
	bool IsGameWon() const ;
	EGuessStatus CheckGuessValidity(FString)const; 
	void Reset(); 

	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentry ;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString)const;
	bool IsLowercase(FString)const;

};