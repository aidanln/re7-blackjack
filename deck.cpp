// deck class for twenty-one game
//
// by Aidan Lalonde-Novales
// Last Updated 1/23/2023

// libraries
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// namespace
using namespace std;

class Deck {
  // private: cards
  private:
    vector<int> cards;

  // public: card constructor, shuffle the cards, deal a card
  public:
    Deck() {
      for (int count = 1; count <= 11; count++) {
	cards.push_back(count);
      }
    }

    void shuffleCards() {
      random_device rd;
      mt19937 g(rd());
      shuffle(cards.begin(), cards.end(), g);
    }
    
    int dealCard() {
      if (cards.empty()) {
        cout << "No cards left to deal." << endl;
	return 0;
      } else {
        int topCard = cards.back();
	cards.pop_back();
	return topCard;
      }
    }
};
