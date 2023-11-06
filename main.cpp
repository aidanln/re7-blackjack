// program that emulates resident evil's blackjack (RE7)
//
// By Aidan Lalonde-Novales
// Last Updated 1/23/2023

// files
#include "deck.cpp"
#include "player.cpp"

// libraries
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

// namespaces
using namespace std;

/**
 * REVEALS THE CARDS OF THE OPPONENT, SHOWS WHO WON, SUBTRACTS LIVES
 */
void revealCards(Deck &deck, Player &user, Opponent &opp, int target) {
  cout << "\nFinal Hands:" << endl;
  cout << "\n=============================================\n" << endl;
  // print opp info
  cout << "Oppenents Deck: " << opp.getSum() << " / 21" << endl;
  opp.printHand();
  cout << endl;

  // print user info
  cout << "Your Deck: " << user.getSum() << " / 21" << endl;
  user.printHand();
  cout << endl;
  cout << "=============================================\n" << endl;

  cout << "Result...\n" << endl;

  // check if win condition is fulfilled, else if tie, else lose
  if (user.getSum() > opp.getSum() && user.getSum() <= target) {
    cout << "★ You Win! ★" << endl;
  } else if (user.getSum() <= target && opp.getSum() > target) {
    cout << "★ You Win! ★" << endl;
  } else if (user.getSum() < opp.getSum() &&
    user.getSum () > target && opp.getSum() > target) {
    cout << "★ You Win! ★" << endl;
  } else if (user.getSum() == opp.getSum()) {
    cout << "★ You Tied! ★" << endl;
  } else {
    cout << "★ You Lost! ★" << endl;
  }
  cout << endl;
}

/**
 * PRINTS OUT THE CARDS OF THE OPPONENT AND USER
 */
void printCards(Deck &deck, Player &user, Opponent &opp) {
  cout << "\n=============================================\n" << endl;
  // print opp info
  cout << "Oppenents Deck: ? + " << opp.discreteGetSum() << " / 21" << endl;
  opp.discretePrintHand();
  cout << endl;

  // print user info
  cout << "Your Deck: " << user.getSum() << " / 21" << endl;
  user.printHand();
  cout << endl;
  cout << "=============================================\n" << endl;
}

/**
 * GETS THE USERS INPUT
 */
void getInput(bool gameStarted, Deck &deck, Player &user) {
  string inputStr;
  int input;
  while (true) {
    cout << "Input: ";
    cin >> inputStr;
    try {
      input = stoi(inputStr);
      // help
      if (input == 0) {
        cout << "0 for help, 1 to start a game, 2 to hit, 3 to stay." << endl;
      // start game
      } else if (input == 1) {
	if (gameStarted) {
          cout << "Game already in progress!" << endl;
	} else {
	  break;
	}
      // hit
      } else if (input == 2) {
	if (gameStarted) {
          int dealtCard = deck.dealCard();
          user.getCard(dealtCard);
	  cout << "\nYou Hit." << endl;
	  break;
	} else {
	  cout << "Game has not started!" << endl;
	}
      // stay
      } else if (input == 3) {
        if (gameStarted) {
	  cout << "\nYou Stayed." << endl;
	  break;
	} else {
          cout << "Game has not started!" << endl;
	}
      } else {
	cout << "Unrecognized Command. Enter '0' for help." << endl;
      }
    } catch (invalid_argument) {
      cout << "Unrecognized Command. Enter '0' for help." << endl;
    }
  }
}

/**
 * STARTS BOTH PLAYERS OFF WITH TWO CARDS
 */
void initialCardDeal(Deck &deck, Player &user, Opponent &opp) {
  for (int count = 0; count < 2; count++) {
    int dealtCard1 = deck.dealCard();
    user.getCard(dealtCard1);
    int dealtCard2 = deck.dealCard();
    opp.getCard(dealtCard2);
  }
}

/**
 * MAIN STUB
 */
int main() {
  // initialize variables and classes
  bool gameStarted = false;
  const int target = 21;
  Deck deck;
  Player user;

  // initialize opponents risk tolerance
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(12, 18);
  Opponent opp(dis(gen));

  // start screen
  cout << "\n\n" << endl;
  cout << "          -=- Welcome to Twenty-One! -=-\n" << endl;
  cout << "Enter '0' at anytime to access a list of commands.\n" << endl;

  // first input prompt to start the game
  getInput(gameStarted, deck, user);
  cout << "\n\n" << endl;
  
  // shuffle, deal cards
  gameStarted = true;
  deck.shuffleCards();
  initialCardDeal(deck, user, opp);

  // game loop
  for (int turns = 3; turns >= 0; turns--) {
    printCards(deck, user, opp);
    // user's turn
    getInput(gameStarted, deck, user);
    // opps turn
    if (opp.getSum() <= opp.getRiskTolerance()) {
      cout << "Opponent Hit." << endl;
      int dealtCard = deck.dealCard();
      opp.getCard(dealtCard);
    } else {
      cout << "Opponent Stayed." << endl;
    }
    // report turns remaining
    cout << turns << " Turns Remaining." << endl;
  }
  revealCards(deck, user, opp, target);

  cout << "Done." << endl;

  return 0;
}
