#include <minesweeper_engine.h>
#include <minesweeper_engine_config.h>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace minesweeper;

#ifdef USE_GUI
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define FONT_PATH "../asserts/Robot_Font.otf"
#define BOMB_TEXTURE_PATH "../asserts/bomb.png"
#define EMPTY_CELL_TEXTURE_PATH "../asserts/empty-cell.png"
#define GRID_CELL_0_TEXTURE_PATH "../asserts/grid-cell-0.png"
#define GRID_CELL_1_TEXTURE_PATH "../asserts/grid-cell-1.png"
#define MARK_TEXTUTE_PATH "../asserts/mark.png"
#define VICTORY_TEXT "Congratilations! You win."
#define DEFEAT_TEXT "Sorry! You lose. Try again."
#define WINDOW_TITTLE "Minesweeper"
#define WINDOW_WIDTH 576u
#define WINDOW_HEIGHT 676u
#define TOPPER_HEIGHT 100u
#define DEFAULT_SPRITE_WIDTH 64
#define DEFAULT_SPRITE_HEIGHT 64
#define FPS 60

sf::RenderWindow window;
sf::Font font;
sf::Texture bomb_texture, grid_cell_0_texture, grid_cell_1_texture, empty_cell_texture, mark_texture;
sf::Sprite bomb_sprite, grid_cell_0_sprite, grid_cell_1_sprite, empty_cell_sprite, mark_sprite;
sf::Text choose_text, easy_text, medium_text, hard_text, number_text, result_text;
mine game;

/**
 * @brief Loads the project asserts
 * @return true if all asserts are loaded and false otherwise
*/
bool load_asserts(){
    // Load asserts

    if(!font.loadFromFile(FONT_PATH)){
        cout << "couldn't load font on font path: " << FONT_PATH << endl;
        return false;
    }

    if(!bomb_texture.loadFromFile(BOMB_TEXTURE_PATH)){
        cout << "couldn't load texture on path: " << BOMB_TEXTURE_PATH << endl;
        return false;
    }
    
    if(!grid_cell_0_texture.loadFromFile(GRID_CELL_0_TEXTURE_PATH)){
        cout << "couldn't load texture on path: " << GRID_CELL_0_TEXTURE_PATH << endl;
        return false;
    }

    if(!grid_cell_1_texture.loadFromFile(GRID_CELL_1_TEXTURE_PATH)){
        cout << "couldn't load texture on path: " << GRID_CELL_1_TEXTURE_PATH << endl;
        return false;
    }
    
    if(!empty_cell_texture.loadFromFile(EMPTY_CELL_TEXTURE_PATH)){
        cout << "couldn't load texture on path: " << EMPTY_CELL_TEXTURE_PATH << endl;
        return false;
    }

    if(!mark_texture.loadFromFile(MARK_TEXTUTE_PATH)){
        cout << "couldn't load texture on path: " << MARK_TEXTUTE_PATH << endl;
        return false;
    }

    return true;
}

/**
 * @brief Loads the game texts
*/
void load_texts(){
    choose_text.setFont(font);
    easy_text.setFont(font);
    medium_text.setFont(font);
    hard_text.setFont(font);
    number_text.setFont(font);
    result_text.setFont(font);

    choose_text.setString("Difficulty");
    easy_text.setString("easy");
    medium_text.setString("medium");
    hard_text.setString("hard");
}

/**
 * @brief Load sprites textures
*/
void load_sprites(){
    bomb_sprite.setTexture(bomb_texture, true);
    grid_cell_0_sprite.setTexture(grid_cell_0_texture, true);
    grid_cell_1_sprite.setTexture(grid_cell_1_texture, true);
    empty_cell_sprite.setTexture(empty_cell_texture, true);
    mark_sprite.setTexture(mark_texture, true);
}

/**
 * @brief Converts the pixel coordenates of the grid in the logical coordenates as a @see grid_click_t struct
 * @param click A vector with the x and y coordenates of the click on the window
 * @param was_mark A flag to say if the click was a mark click or not
 * @return A grid_click_t struct with the logical positions of the click
*/
grid_click_t convert_click_pos_in_grid_click(const sf::Vector2f& click, bool was_mark = false){
    vector<vector<char>> game_state = game.get_grid_as_string();

    //cout << click.x << ", " << click.y << endl;

    int n_cells_height = game_state.size();
    int n_cells_width = game_state[0].size();

    float pixels_per_height = (WINDOW_HEIGHT - TOPPER_HEIGHT) / n_cells_height;
    float pixels_per_width = (WINDOW_WIDTH) / n_cells_width;

    int x_coord = (int) ((click.y - TOPPER_HEIGHT) / pixels_per_height);
    int y_coord = (int) (click.x / pixels_per_width);
    
    //cout << x_coord << ", " << y_coord << endl;

    return grid_click_t{x_coord, y_coord, was_mark};
}

/**
 * @brief draw sprites and texts on the game
*/
void draw_game(){
    // clear window  
    window.clear();

    // set texts

    /*switch(game.get_difficulty()){
        case game_difficulty::easy:{
            number_text.setScale(sf::Vector2f(1.0, 1.0));
        }
        break;
        case game_difficulty::medium:{
            number_text.setScale(sf::Vector2f(0.75, 0.75));
        }
        break;
        case game_difficulty::hard:{
            number_text.setScale(sf::Vector2f(0.5, 0.5));
        }
        break;
        default:{
            number_text.setScale(sf::Vector2f(1.0, 1.0));
        }
        break;
    }*/

    choose_text.setPosition(sf::Vector2f(0, 0));

    float container_width = WINDOW_WIDTH / 3.0; 

    float y_offset = TOPPER_HEIGHT / 2.0;

    sf::FloatRect easy_text_gb = easy_text.getGlobalBounds();

    easy_text.setPosition(sf::Vector2f(container_width / 2 - easy_text_gb.width / 2, y_offset));

    sf::FloatRect medium_text_gb = medium_text.getGlobalBounds();

    medium_text.setPosition(sf::Vector2f(container_width + container_width / 2 - medium_text_gb.width / 2, y_offset));

    sf::FloatRect hard_text_gb = hard_text.getGlobalBounds();

    hard_text.setPosition(sf::Vector2f(2 * container_width + container_width / 2 - hard_text_gb.width / 2, y_offset));

    // draw texts  
    window.draw(choose_text);
    window.draw(easy_text);
    window.draw(medium_text);
    window.draw(hard_text);

    // draw game  

    vector<vector<char>> game_state = game.get_grid_as_string();

    float target_sprite_width = WINDOW_WIDTH / (float) game_state.size();
    float target_sprite_height = (WINDOW_HEIGHT - TOPPER_HEIGHT) / (float) game_state[0].size();

    float width_scale_factor = target_sprite_width / DEFAULT_SPRITE_WIDTH;
    float height_scale_factor = target_sprite_height / DEFAULT_SPRITE_HEIGHT;

    bomb_sprite.setScale(sf::Vector2f(width_scale_factor, height_scale_factor));
    grid_cell_0_sprite.setScale(sf::Vector2f(width_scale_factor, height_scale_factor));
    grid_cell_1_sprite.setScale(sf::Vector2f(width_scale_factor, height_scale_factor));
    empty_cell_sprite.setScale(sf::Vector2f(width_scale_factor, height_scale_factor));
    mark_sprite.setScale(sf::Vector2f(width_scale_factor, height_scale_factor));

    bool cell_type_0 = true;

    for(size_t i = 0; i < game_state.size(); i++){
        for(size_t j = 0; j < game_state[i].size(); j++){
            sf::Vector2f cell_pixel_position(j * target_sprite_width, i * target_sprite_height + TOPPER_HEIGHT);

            switch(game_state[i][j]){
                case '#':{
                    if(cell_type_0){
                        grid_cell_0_sprite.setPosition(cell_pixel_position);
                        window.draw(grid_cell_0_sprite);
                    }else{
                        grid_cell_1_sprite.setPosition(cell_pixel_position);
                        window.draw(grid_cell_1_sprite);
                    }
                }
                break;
                case 'B':{
                    empty_cell_sprite.setPosition(cell_pixel_position);
                    window.draw(empty_cell_sprite);
                    bomb_sprite.setPosition(cell_pixel_position);
                    window.draw(bomb_sprite);
                }
                break;
                case 'M':{
                    if(cell_type_0){
                        grid_cell_0_sprite.setPosition(cell_pixel_position);
                        window.draw(grid_cell_0_sprite);
                    }else{
                        grid_cell_1_sprite.setPosition(cell_pixel_position);
                        window.draw(grid_cell_1_sprite);
                    }

                    mark_sprite.setPosition(cell_pixel_position);
                    window.draw(mark_sprite);
                }
                break;
                case ' ':{
                    empty_cell_sprite.setPosition(cell_pixel_position);
                    window.draw(empty_cell_sprite);
                }
                default:{ // number
                    empty_cell_sprite.setPosition(cell_pixel_position);
                    window.draw(empty_cell_sprite);

                    number_text.setString(sf::String(game_state[i][j]));

                    sf::FloatRect number_text_gb = number_text.getGlobalBounds();

                    sf::Vector2f text_position (cell_pixel_position.x + (target_sprite_width / 2) - (number_text_gb.width / 2) , cell_pixel_position.y + (target_sprite_height / 2) - (number_text_gb.height / 2));

                    number_text.setPosition(text_position);
                    window.draw(number_text);
                }
                break;
            }
            cell_type_0 = !cell_type_0;
        }

        if(!(game_state[i].size() & 1)){
            cell_type_0 = !cell_type_0;
        }
    }

    if(game.get_game_state() == game_state::victory || game.get_game_state() == game_state::defeat){
        if((game.get_game_state() == game_state::victory)) result_text.setString(VICTORY_TEXT);
        else result_text.setString(DEFEAT_TEXT);

        sf::FloatRect result_text_gb = result_text.getGlobalBounds();

        result_text.setPosition(sf::Vector2f((WINDOW_WIDTH / 2) - (result_text_gb.width / 2), (result_text_gb.height / 2)));

        window.draw(result_text);
    }
}

int main(void){
    if(!load_asserts()){
        cout << "Couldn't load all asserts";
        return -1;
    }

    load_texts();
    load_sprites(); 

    // Create window
    window.create(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), WINDOW_TITTLE);
    window.setFramerateLimit(FPS);

    // The main loop - ends as soon as the window is closed
    game.set_difficulty(game_difficulty::easy);
    game.start();
    
    while (window.isOpen()){
        // Event processing
        sf::Event event;
        while (window.pollEvent(event)){
            
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                if(game.get_game_state() == game_state::victory || game.get_game_state() == game_state::defeat){
                    game.process_end_game();
                    game.start();
                }
                
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                sf::Vector2f posf(pos.x, pos.y);

                if(easy_text.getGlobalBounds().contains(posf) && game.get_game_state() == game_state::setup){
                    game.set_difficulty(game_difficulty::easy);
                    game.start();
                }
                if(medium_text.getGlobalBounds().contains(posf) && game.get_game_state() == game_state::setup){
                    game.set_difficulty(game_difficulty::medium);
                    game.start();
                }
                if(hard_text.getGlobalBounds().contains(posf) && game.get_game_state() == game_state::setup){
                    game.set_difficulty(game_difficulty::hard);
                    game.start();
                }

                if(posf.y >= TOPPER_HEIGHT){
                    grid_click_t click = convert_click_pos_in_grid_click(posf);

                    game.update(click);
                }
            }

            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                sf::Vector2f posf(pos.x, pos.y);

                if(posf.y >= TOPPER_HEIGHT){
                    grid_click_t click = convert_click_pos_in_grid_click(posf, true);

                    game.update(click);
                }
            }

            // Request for closing the window
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        // Activate the window for OpenGL rendering
        window.setActive();
        // OpenGL drawing commands go here...
        // End the current frame and display its contents on screen
        draw_game();

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