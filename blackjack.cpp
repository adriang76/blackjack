#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <random>
#include <chrono>
#include <thread>

using namespace std;



class Card{
public:
    string rank;
    string suit;
    int vaule;

    Card(string r, string s,int v){
        rank = r;
        suit = s;
        vaule = v;

    }

    void  show_card(){


        cout << rank << " " << suit << "\n";


    }

};

class Deck {

public:
    vector<Card> cards;
    
    Deck(){
        vector<string> rank = {"2", "3", "4", "5", "6", "7", "8" , "9", "10", "J", "Q", "K", "A" };
        vector<string> suit = {"Spades", "Diamonds" ,"Clubs", "Hearts"};
        vector<int> vaule = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

        for (int i = 0; i < suit.size(); i++){
            for(int j = 0; j < vaule.size(); j++){
                cards.push_back(Card(rank[j],suit[i], vaule[j]));
                    
            }
        }


    }
    
    void shuffle_deck(){
        
        random_device rd;
        mt19937 g(rd());
        shuffle(cards.begin(), cards.end(), g);

    }

    void deal(vector<Card>& player, vector<Card>& dealer){
            
            for (int i = 0; i < 4 ;i++){
            if (i % 2 == 0){
                player.push_back(cards.back());
                }
            else{
                dealer.push_back(cards.back());
            }
            cards.pop_back();
    }
    }
 void displayDeck() {
        for (auto &card : cards) {
            card.show_card();
        }
    }




};

class Player{
public: 
    vector<Card> players_hand;
    
    int Score_calc(){
    
        int sum = 0;
        int ace_count = 0;
        for (int i = 0; i < players_hand.size(); i++)
        {   

            if (players_hand[i].rank == "A"){
                ace_count++;
            }
            sum = sum + players_hand[i].vaule;

        }
        
        while (ace_count > 0 && sum > 21){
            sum = sum - 10;
            ace_count--;
        }


        return sum;

    }

    void hit(vector<Card>& cards){
        
        players_hand.push_back(cards.back());
        cards.pop_back();

    }



     void displayDeck() {
        cout << "players hand" << "\n";

        for (auto &card : players_hand) {
            card.show_card();
        }
    }





};

class Dealer{
public:
    vector<Card> Dealer_hand;
    
     int Score_calc(){
    
        int sum = 0;
        int ace_count = 0;
        for (int i = 0; i < Dealer_hand.size(); i++)
        {   

            if (Dealer_hand[i].rank == "A"){
                ace_count++;
            }
            sum = sum + Dealer_hand[i].vaule;

        }
        
        while (ace_count > 0 && sum > 21){
            sum = sum - 10;
            ace_count--;
        }


        return sum;

    }
    void show_first_card(){
        cout << "Dealer card" << "\n";
        Dealer_hand[0].show_card();
    }

    void displayDeck() {
        cout << "Dealers hand" << "\n";

        for (auto &card : Dealer_hand) {
            card.show_card();
        }
    }
     void hit(vector<Card>& cards){
        
        Dealer_hand.push_back(cards.back());
        cards.pop_back();

    }

    void show_new_card(){
        Dealer_hand[Dealer_hand.size() - 1].show_card();

    }

};

class Blackjack{

private: 
    Deck deck;

    Player player;

    Dealer dealer;

public: 

    void start_game(){

        string player_move;
        int player_score;
        int dealer_score;
        int win_check;
        deck.shuffle_deck();
        deck.deal(player.players_hand, dealer.Dealer_hand);
        player.displayDeck();
        dealer.show_first_card();

        while (1)
        {
        player_score = player.Score_calc();
        dealer_score = dealer.Score_calc();
        
        if (player_score == 21 ){
            cout << "player 21 you win!!  " << "\n";
            win_check = 1;
            break;
            }
        
        else if (dealer_score == 21 ){

            cout << "Dealer 21 you lose.  "<< "\n";
            dealer.displayDeck();
            win_check = 1;
            break;
        }
        else if (player_score > 21){

            cout << "you busted :(  "<< "\n";
            win_check = 1;
            break;


        }

        cout << "Do you hit? y/n:";

        cin >> player_move;


            if (player_move == "y"){
                
                player.hit(deck.cards);
                player.displayDeck();
                
            }

            else{
                dealer.displayDeck();
                    break;
            }
        }

        

        while(1){
            this_thread::sleep_for(chrono::seconds(1));
            if (win_check == 1){
                break;
            }

            
            dealer_score = dealer.Score_calc();
            player_score = player.Score_calc();

            if (dealer_score >= 17 && dealer_score < 22){
                if (dealer_score > player_score){ 
                cout << "Dealer wins  "<< "\n";
                    
                break;
                }
                else if (player_score > dealer_score){

                    cout << "player wins" << "\n";
                    break;
                }
                else {

                    cout << "push... tough" << "\n";
                    break;
                    

                }

            }

            else if(dealer_score < 17){
                dealer.hit(deck.cards);
                dealer.show_new_card();
            }

            else {
                cout << "dealer busted, you win!!! :)" << "\n";
                    break;
            }


        }


    }

    


};









 

int main(){



Blackjack blackjack;

blackjack.start_game();






}