#include <minesweeper_engine.h>
#include <minesweeper_engine_config.h>
#include <iostream>
#include <cstdlib> 


#ifdef USE_GUI
#include <SFML/Window.hpp>
#endif

using namespace std;
using namespace minesweeper;

#ifdef USE_GUI

int main(void){

    sf::Window window;
    // Create window
    window.create(sf::VideoMode(sf::Vector2u(800u, 600u)), "Minesweeper");

    // Limit the framerate to 60 frames per second (this step is optional)
    window.setFramerateLimit(60);
    // The main loop - ends as soon as the window is closed
    while (window.isOpen()){
        // Event processing
        sf::Event event;
        while (window.pollEvent(event)){
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Activate the window for OpenGL rendering
        window.setActive();
        // OpenGL drawing commands go here...
        // End the current frame and display its contents on screen
        window.clear();
        window.display();
    }
}

#else

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

            cout << "Insert a position on the grid in the form (x-index) (y-index) [(M)ark or (C)lick]." << endl;
            cout << "The indexes are 0 based" << endl;

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

#endif