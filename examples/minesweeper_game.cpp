#include <minesweeper_engine.h>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace minesweeper;

int main(void){
    mine game;

    while(true){
        char option;
        
        do{
            cout << "Select a valid difficulty: (E)asy, (M)edium or (H)ard. " << endl;
            cin >> option;
        }while(option != 'E' && option != 'M' && option != 'H');

        switch(option){
            case 'E':{
                game.set_difficulty(game_difficulty::easy);
            }
            break;
            case 'M':{
                game.set_difficulty(game_difficulty::medium);
            }
            break;
            case 'H':{
                game.set_difficulty(game_difficulty::hard);
            }
            break;
            default:{
                cout << "Difficulty not expected" << endl;
                return -1;
            }
            break;
        }

        game.start();

        system("cls");
        cout << game << endl;

        while(game.get_game_state() != game_state::victory && game.get_game_state() != game_state::defeat){
            int click_x = 0, click_y = 0;
            char mark;

            bool valid_move = true;

            do{
                if(!valid_move){
                    cout << "Insert a valid position on the grid." << endl;
                }

                cin >> click_x >> click_y >> mark;

                if(mark != 'C' && mark != 'M'){
                   valid_move = false;  
                }else{
                    grid_click_t click = {click_x, click_y, (mark == 'M')};

                    game.update(click);
                }
            }while(!valid_move);

            system("cls");
            cout << game << endl;
        }

        if(game.get_game_state() == game_state::victory){
            cout << "Congratilations! You win." << endl;
        }

        if(game.get_game_state() == game_state::defeat){
            cout << "Sorry! You lose. Try again." << endl;
        }
    }
    
    return 0;
}