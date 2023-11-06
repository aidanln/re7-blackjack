// player class for twenty-one game
//
// by Aidan Lalonde-Novales
// Last Updated 1/23/2023

// libraries
#include <iostream>
#include <vector>
#include <algorithm>

// namespace
using namespace std;

class Player {
  public:
    // public: hand vector, constructor, get a card, print the hand, get sum
    vector<int> hand;

    Player() {
      hand.clear();
    }

    void getCard(int card) {
      hand.push_back(card);
    }

    void printHand() {
      for (int count : hand) {
	cout << " " << count << " ";
      }
      cout << endl;
    }
    
    int getSum() {
      int sum = 0;
      for (auto &count : hand) {
        sum += count;
      }
      return sum;
    }
};

class Opponent : public Player {
  // public: new constructor with risk tolerance, get risk tolerance
  public:
    int riskTolerance;

    Opponent(int rt) {
      hand.clear();
      riskTolerance = rt;
    }

    int getRiskTolerance() {
      return riskTolerance;
    }

    void discretePrintHand() {
      cout << " ? ";
      for (int count = 1; count < hand.size(); count++) {
	cout << " " << hand[count] << " ";
      }
      cout << endl;
    }

    int discreteGetSum() {
      int sum = 0;
      for (int count = 1; count < hand.size(); count++) {
        sum += hand[count];
      }
      return sum;
    }
};
