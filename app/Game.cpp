#pragma once
#include "Game.h"
#include "Piccolo.h"
#include "Goomba.h"
#include "Jason.h"
#include "Haunter.h"
#include "Zombie.h"
#include "PowerUp.h"

using namespace graphics;

Game::Game()
{
}

Game::~Game() {
	clearCollections();
	delete player;
}

void Game::init() {
	timer = 0.f;
	timerLimit = 4000.f;
	score = 0;
	prevScore = 0;
	button_timer = .0f;
	arrow_offset = 0.f;
	if (state == MAIN_MENU) {
		stopMusic();
		playMusic(string(POKEMON_THEME_SONG), 0.05f);
	}

	if (state == CHOOSE_LEVEL) {
		playSound(string(MAKE_YOUR_SELECTION_NOW), 0.3f);
		level_button = BEACH;
	}

		
	if (state == PLAYING) {
		stopMusic();
		playMusic(string(JOJOS_MAIN_MUSIC), 0.05f);
	}

	if (player)
		delete player;
	player = new Player(CHARACTER_WIDTH -10, CHARACTER_HEIGHT, CANVAS_WIDTH/2,CANVAS_HEIGHT - CHARACTER_HEIGHT / 2, 200, string(GOKU_NEW), this);
	player->init();

	pu = nullptr;
}

void Game::draw()
{

	switch(state) {
		case PLAYING: {

			// background
			Brush br;
			br.fill_opacity = 1;
			br.outline_opacity = 0;
			br.texture = level_asset;
			drawRect((CANVAS_WIDTH) / 2, (CANVAS_HEIGHT) / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

			// Score text
			Brush br0;
			br0.fill_opacity = 1;
			br0.outline_opacity = 0;
			br0.texture = "";
			br0.fill_color[0] = .0f;
			br0.fill_color[1] = .0f;
			br0.fill_color[2] = .0f;
			setFont(string(POCOYO_TV_FONT));
			drawText(160, 50, 30, "Score: " + to_string(score), br0);

			// Goku player picture
			Brush br1;
			br1.fill_opacity = 1;
			br1.outline_opacity = 0;
			br1.texture = string(GOKU_PROFILE_PIC);
			drawRect(65, 57, 75, 75, br1);

			// UI Hp bar
			float player_hp = (player->getHp() > 0) ? player->getHp() : 0;
			Brush br3;
			br3.fill_opacity = 1;
			br3.fill_color[0] = 0.f + (200 - player_hp) / 200; // RED
			br3.fill_color[1] = 1.f - (200 - player_hp) / 200; // GREEN
			br3.fill_color[2] = 0.f;					   // BLUE
			br3.texture = "";


			drawRect(236 - (((200 - player_hp) / 200) * 205 / 2), 75, (player_hp / 200) * 205, 27, br3);

			// Player UI
			Brush br2;
			br2.fill_opacity = 1;
			br2.outline_opacity = 0;
			br2.texture = string(PLAYER_UI);
			drawRect(180, 60, 360, 100, br2);

			// PowerUp time left
			
			br0.fill_color[0] = .0f;
			br0.fill_color[1] = .0f;
			br0.fill_color[2] = .0f;
			drawText(CANVAS_WIDTH - 220, 45, 22, "PowerUp", br0);
			
			if (player->getUpgraded()) {
				//drawText(CANVAS_WIDTH - 260, 70, 22, "Time Left: "+to_string((int) player->getUpgradeDuration()/1000), br0);
				
				br2.texture = string(POWER_UP_STAR) + ".png";
				drawRect(CANVAS_WIDTH - 60, 55, 50, 50, br2);

				
				br2.texture = "";

				br2.fill_opacity = 1.f;
				br2.outline_opacity = 0.f;
				br2.fill_color[0] = 1.0f;
				br2.fill_color[1] = 0.84f;
				br2.fill_color[2] = .0f;
				drawRect(CANVAS_WIDTH - 211 + (((15000 - player->getUpgradeDuration()) / 15000) * 205 / 2), 75, (player->getUpgradeDuration()/15000) * 205, 27, br2);

				br2.fill_opacity = .0f;
				br2.outline_opacity = 1;
				br2.outline_width = 4;
				br2.fill_color[0] = .0f;
				br2.fill_color[1] = .0f;
				br2.fill_color[2] = .0f;
				br2.outline_color[0] = .0f;
				br2.outline_color[1] = .0f;
				br2.outline_color[2] = .0f;
				drawRect(CANVAS_WIDTH - 210, 75, 205, 29, br2);

			}

			
			// Draw Power Up cage:
			br2.fill_opacity = 0.f;
			br2.outline_opacity = 1;
			br2.outline_width = 6.f;
			br2.outline_color[0] = .0f;
			br2.outline_color[1] = .0f;
			br2.outline_color[2] = .0f;
			br2.texture = "";
			drawRect(CANVAS_WIDTH - 60, 55, 68, 68, br2);


			// Draw Entities:
			for (list<Enemy*>::iterator it = enemy_list.begin(); it != enemy_list.end(); ++it) {
				(*it)->draw();
			}
			// Draw Player:
			if (player->getActiveStatus()) {
				player->draw();
			}
			// Draw PowerUp:
			if (pu && !pu->getCaptured()) {
				pu->draw();
			}
			break;
		}
		case MAIN_MENU: {

			// background
			Brush br;
			br.fill_opacity = 1;
			br.outline_opacity = 0;
			br.texture = string(MAIN_MENU_BACKGROUND);
			drawRect((CANVAS_WIDTH) / 2, (CANVAS_HEIGHT) / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

			Brush br0;
			br0.fill_opacity = 1;
			br0.outline_opacity = 1;
			br0.texture = "";
			br0.fill_color[0] = .0f;
			br0.fill_color[1] = .0f;
			br0.fill_color[2] = .0f;
			setFont(string(DRAGON_BALL_Z_FONT));
			drawText(CANVAS_WIDTH / 2 - 230, CANVAS_HEIGHT / 2 - 130, 100, "Zbit Arcade", br0);
			br0.fill_color[0] = 1.0f;
			br0.fill_color[1] = 0.84f;
			br0.fill_color[2] = .0f;
			drawText(CANVAS_WIDTH / 2 - 240, CANVAS_HEIGHT / 2 - 120, 105, "Zbit Arcade", br0);

			if (buttonMM == PLAY) {
				br0.fill_color[0] = 1.0f;
				br0.fill_color[1] = 0.84f;
			}
			else {
				br0.fill_color[0] = .0f;
				br0.fill_color[1] = .0f;
			}
			br0.fill_color[2] = .0f;
			drawText(CANVAS_WIDTH/2 - 70, CANVAS_HEIGHT/2 + 20, 50, "PLAY", br0);

			if (buttonMM == ABOUT) {
				br0.fill_color[0] = 1.0f;
				br0.fill_color[1] = 0.84f;
			}
			else {
				br0.fill_color[0] = .0f;
				br0.fill_color[1] = .0f;
			}
			br0.fill_color[2] = .0f;
			drawText(CANVAS_WIDTH/2 - 70, CANVAS_HEIGHT/2 + 90 , 50, "ABOUT", br0);
			

			if (buttonMM == EXIT) {
				br0.fill_color[0] = 1.0f;
				br0.fill_color[1] = 0.84f;
			}
			else {
				br0.fill_color[0] = .0f;
				br0.fill_color[1] = .0f;
			}
			br0.fill_color[2] = .0f;
			drawText(CANVAS_WIDTH/2 - 70, CANVAS_HEIGHT/2 + 160 , 50, "EXIT", br0);

			// ARROW
			Brush br1;
			br1.fill_opacity = 1;
			br1.outline_opacity = 0;
			br1.texture = string(_8BIT_ARROW);
			drawRect(CANVAS_WIDTH/2 - 110, CANVAS_HEIGHT/2 + 5 + arrow_offset, 50, 50, br1);

			break;
		}
		case RETRY:{

			// background
			Brush br;
			br.fill_opacity = 1;
			br.outline_opacity = 0;
			br.texture = level_asset;
			drawRect((CANVAS_WIDTH) / 2, (CANVAS_HEIGHT) / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

			// Draw Entities:
			for (list<Enemy*>::iterator it = enemy_list.begin(); it != enemy_list.end(); ++it) {
				(*it)->draw();
			}
			// Draw Player:
			if (player->getActiveStatus()) {
				player->draw();
			}
			// Draw PowerUp:
			if (pu && !pu->getCaptured()) {
				pu->draw();
			}

			Brush br0;
			br0.fill_opacity = 1;
			br0.outline_opacity = 1;
			br0.texture = "";
			br0.fill_color[0] = 1.0f;
			br0.fill_color[1] = .0f;
			br0.fill_color[2] = .0f;
			setFont(string(DRAGON_BALL_Z_FONT));
			drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT / 2 - 130, 100, "YOU LOST", br0);

			if (retry_choice == AGAIN) {
				br0.fill_color[0] = 1.0f;
				br0.fill_color[1] = 0.84f;
			}
			else {
				br0.fill_color[0] = .0f;
				br0.fill_color[1] = .0f;
			}
			br0.fill_color[2] = .0f;
			drawText(CANVAS_WIDTH/2 - 70, CANVAS_HEIGHT/2 + 20, 50, "RETRY", br0);

			if (retry_choice == BACK_TO_MENU) {
				br0.fill_color[0] = 1.0f;
				br0.fill_color[1] = 0.84f;
			}
			else {
				br0.fill_color[0] = .0f;
				br0.fill_color[1] = .0f;
			}
			br0.fill_color[2] = .0f;
			drawText(CANVAS_WIDTH/2 - 70, CANVAS_HEIGHT/2 + 90 , 50, "MAIN MENU", br0);

			// ARROW
			Brush br1;
			br1.fill_opacity = 1;
			br1.outline_opacity = 0;
			br1.texture = string(_8BIT_ARROW);
			drawRect(CANVAS_WIDTH/2 - 110, CANVAS_HEIGHT/2 + 5 + arrow_offset, 50, 50, br1);


			break;
		}
		case CHOOSE_LEVEL: {
		
			// background
			Brush br;
			br.fill_opacity = 1;
			br.outline_opacity = 0;
			br.texture = string(MAIN_MENU_BACKGROUND);
			drawRect((CANVAS_WIDTH) / 2, (CANVAS_HEIGHT) / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

			// Choose level text:
			Brush br0;
			br0.fill_opacity = 1;
			br0.outline_opacity = 1;
			br0.texture = "";
			br0.fill_color[0] = 1.0f;
			br0.fill_color[1] = 0.84f;
			br0.fill_color[2] = .0f;
			setFont(string(DRAGON_BALL_Z_FONT));
			drawText(CANVAS_WIDTH / 2 - 210, CANVAS_HEIGHT / 2 - 200, 70, "CHOOSE LEVEL:", br0);

			// Levels
			Brush br1;
			br1.fill_opacity = 1;
			br1.outline_opacity = 1;
			br1.outline_width = 4.f;
			if (level_button == BEACH) {
				br1.outline_color[0] = 1.0f;
				br1.outline_color[1] = 0.84f;
			}
			else {
				br1.outline_color[0] = .0f;
				br1.outline_color[1] = .0f;
			}
			br1.outline_color[2] = .0f;
			br1.texture = string(BACKGROUND_BEACH);
			drawRect(CANVAS_WIDTH/2, CANVAS_HEIGHT/2 + 20 - 120, 200, 100, br1);
			
			if (level_button == MOUNTAIN) {
				br1.outline_color[0] = 1.0f;
				br1.outline_color[1] = 0.84f;
			}
			else {
				br1.outline_color[0] = .0f;
				br1.outline_color[1] = .0f;
			}
			br1.texture = string(BACKGROUND_MOUNTAIN);
			drawRect(CANVAS_WIDTH/2, CANVAS_HEIGHT/2 + 20, 200, 100, br1);

			if (level_button == NIGHT) {
				br1.outline_color[0] = 1.0f;
				br1.outline_color[1] = 0.84f;
			}
			else {
				br1.outline_color[0] = .0f;
				br1.outline_color[1] = .0f;
			}
			br1.texture = string(BACKGROUND_NIGHT);
			drawRect(CANVAS_WIDTH/2, CANVAS_HEIGHT/2 + 20 + 120, 200, 100, br1);

			// Arrow
			br1.fill_opacity = 1;
			br1.outline_opacity = 0;
			br1.texture = string(_8BIT_ARROW);
			drawRect(CANVAS_WIDTH/2 - 150, CANVAS_HEIGHT/2 - 100 + arrow_offset, 50, 50, br1);
			break;
		}
		case ABOUT_SCREEN: {
		
			// background
			Brush br;
			br.fill_opacity = 1;
			br.outline_opacity = 0;
			br.texture = string(EMPTY_MAIN_MENU_BACKGROUND);
			drawRect((CANVAS_WIDTH) / 2, (CANVAS_HEIGHT) / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

			br.texture = string(HOW_TO);
			drawRect((CANVAS_WIDTH) / 2, (CANVAS_HEIGHT) / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);


			// How2Play text:
			Brush br0;
			br0.fill_opacity = 1;
			br0.outline_opacity = 1;
			br0.texture = "";
			br0.fill_color[0] = 1.0f;
			br0.fill_color[1] = 0.84f;
			br0.fill_color[2] = .0f;
			setFont(string(DRAGON_BALL_Z_FONT));
			drawText(CANVAS_WIDTH / 2 - 110, CANVAS_HEIGHT / 2 - 250, 50, "How to play", br0);


			
			// Back button
			br0.fill_color[0] = 1.0f;
			br0.fill_color[1] = 0.84f;
			br0.fill_color[2] = .0f;
			setFont(string(DRAGON_BALL_Z_FONT));
			drawText(CANVAS_WIDTH / 2 - 50, CANVAS_HEIGHT - 10, 50,"BACK", br0);


			// ARROW
			Brush br1;
			br1.fill_opacity = 1;
			br1.outline_opacity = 0;
			br1.texture = string(_8BIT_ARROW);
			drawRect(CANVAS_WIDTH/2 - 90, CANVAS_HEIGHT - 25 + arrow_offset, 50, 50, br1);
			break;
		}
			
	}
}

void Game::update()
{	
	switch (state) {

		case PLAYING:
			if (getGlobalTime() > 2000 && timer > timerLimit) {

				int choice = rand() % 5;

				switch (choice) {

				case 0:
					enemy_list.push_back(new Piccolo(CHARACTER_WIDTH, CHARACTER_HEIGHT, (rand() % 2) * CANVAS_WIDTH, CANVAS_HEIGHT - CHARACTER_HEIGHT / 2, 100, string(PICCOLO), this));
					enemy_list.back()->init();
					break;
				case 1:
					if (rand() % 2 == 1) {
						enemy_list.push_back(new Zombie(CHARACTER_WIDTH, CHARACTER_HEIGHT, (rand() % 2) * CANVAS_WIDTH, CANVAS_HEIGHT - CHARACTER_HEIGHT / 2, 150, string(ZOMBIE), this));
						enemy_list.back()->init();
					}
					break;
				case 2:
					if (rand() % 3 == 1) {
						enemy_list.push_back(new Haunter(80, 80, (rand() % 2) * CANVAS_WIDTH, CANVAS_HEIGHT - CHARACTER_HEIGHT / 2 - 50, 100, string(HAUNTER), this));
						enemy_list.back()->init();
					}
					break;
				case 3:
					if (rand() % 2 == 1) {
						enemy_list.push_back(new Goomba(60, 60, (rand() % 2) * CANVAS_WIDTH, CANVAS_HEIGHT - 25, 25, string(GOOMBA), this));
						enemy_list.back()->init();
					}
					break;
				case 4:
					enemy_list.push_back(new Jason(CHARACTER_WIDTH, CHARACTER_HEIGHT, (rand() % 2) * CANVAS_WIDTH, CANVAS_HEIGHT - CHARACTER_HEIGHT / 2, 100, string(JASON), this));
					enemy_list.back()->init();
					break;
				}


				timer = 0.f;
			}


			for (list<Enemy*>::iterator it = enemy_list.begin(); it != enemy_list.end(); ++it) {
				if (*it != nullptr) {
					if ((*it)->getActiveStatus()) {
						(*it)->update();
					}
					else {
						// Spawn power up:
						if (pu == nullptr && !player->getUpgraded() && rand() % 9 == 4) {
							pu = new PowerUp(50, 50, (*it)->position.getX(), (*it)->position.getY() - 20, string(POWER_UP_STAR), this);
							pu->init();
						}


						delete* it;
						it = enemy_list.erase(it);


						if (it == enemy_list.end())
							break;
					}
				}
			}
			player->update();
			if (pu && pu->getActiveStatus()) {
				pu->update();
			}
			else if (pu) {
				delete pu;
				pu = nullptr;
			}
			updateTimers();
			if (score > 0 && score != prevScore && score % waveVariable == 0 && timerLimit > 1500) {
				timerLimit -= 1000;
				prevScore = int(score);
			}
			break;
		case MAIN_MENU:

			if(getKeyState(SCANCODE_DOWN) && button_timer >= BUTTON_DELAY){
				switch (buttonMM) {
				
				case PLAY:
					buttonMM = ABOUT;
					arrow_offset += 70;
					break;
				case ABOUT:
					buttonMM = EXIT;
					arrow_offset += 70;
					break;
				case EXIT:
					buttonMM = PLAY;
					arrow_offset -= 140;
					break;
				}
				playSound(string(BEEP_SOUND_EFFECT), 0.3f);
				button_timer = 0.f;
			}

			if(getKeyState(SCANCODE_UP) && button_timer >=BUTTON_DELAY) {
				switch (buttonMM) {

				case PLAY:
					buttonMM = EXIT;
					arrow_offset += 140;
					break;
				case ABOUT:
					buttonMM = PLAY;
					arrow_offset -= 70;
					break;
				case EXIT:
					buttonMM = ABOUT;
					arrow_offset -= 70;
					break;
				}
				playSound(string(BEEP_SOUND_EFFECT), 0.3f);
				button_timer = 0.f;
			}

			// ENTER
			if (getKeyState(SCANCODE_RETURN) && button_timer >= BUTTON_DELAY) {
				switch (buttonMM) {
				case PLAY:
					state = CHOOSE_LEVEL;
					init();
					break;
				case ABOUT:
					state = ABOUT_SCREEN;
					init();
					break;
				case EXIT:
					delete this;
					destroyWindow();
					break;
				}
				playSound(string(BEEP_ENTER_SOUND_EFFECT), 0.3f);
				button_timer = 0.f;
			}
			button_timer += getDeltaTime();
			if (button_timer > BUTTON_DELAY)
				button_timer = BUTTON_DELAY;
			break;
		case RETRY:

			if(getKeyState(SCANCODE_DOWN) && button_timer >= BUTTON_DELAY){
				switch (retry_choice) {

				case AGAIN:
					retry_choice = BACK_TO_MENU;
					arrow_offset += 70;
					break;
				case BACK_TO_MENU:
					retry_choice = AGAIN;
					arrow_offset -= 70;
					break;
				}
				playSound(string(BEEP_SOUND_EFFECT), 0.3f);
				button_timer = 0.f;
			}

			if(getKeyState(SCANCODE_UP) && button_timer >=BUTTON_DELAY) {
				switch (retry_choice) {

					case AGAIN:
						retry_choice = BACK_TO_MENU;
						arrow_offset += 70;
						break;
					case BACK_TO_MENU:
						retry_choice = AGAIN;
						arrow_offset -= 70;
						break;
				}
				playSound(string(BEEP_SOUND_EFFECT), 0.3f);
				button_timer = 0.f;
			}

			// ENTER
			if (getKeyState(SCANCODE_RETURN) && button_timer >= BUTTON_DELAY) {
				switch (retry_choice) {
				case AGAIN:
					stopMusic();
					state = PLAYING;
					clearCollections();
					init();
					break;
				case BACK_TO_MENU:
					stopMusic();
					state = MAIN_MENU;
					clearCollections();
					init();
					break;
		
				}
				playSound(string(BEEP_ENTER_SOUND_EFFECT), 0.3f);
				button_timer = 0.f;
			}
			button_timer += getDeltaTime();
			if (button_timer > BUTTON_DELAY)
				button_timer = BUTTON_DELAY;
		
			break;

		case CHOOSE_LEVEL:
			if(getKeyState(SCANCODE_DOWN) && button_timer >= BUTTON_DELAY){
				switch (level_button) {

				case BEACH:
					level_button = MOUNTAIN;
					arrow_offset += 120;
					break;
				case MOUNTAIN:
					level_button = NIGHT;
					arrow_offset += 120;
					break;
				case NIGHT:
					level_button = BEACH;
					arrow_offset -= 240;
					break;
				}
				playSound(string(BEEP_SOUND_EFFECT), 0.3f);
				button_timer = 0.f;
			}

			if(getKeyState(SCANCODE_UP) && button_timer >=BUTTON_DELAY) {
				switch (level_button) {

				case BEACH:
					level_button = NIGHT;
					arrow_offset += 240;
					break;
				case MOUNTAIN:
					level_button = BEACH;
					arrow_offset -= 120;
					break;
				case NIGHT:
					level_button = MOUNTAIN;
					arrow_offset -= 120;
					break;
				}
				playSound(string(BEEP_SOUND_EFFECT), 0.3f);
				button_timer = 0.f;
			}

			// ENTER
			if (getKeyState(SCANCODE_RETURN) && button_timer >= BUTTON_DELAY) {
				switch (level_button) {
				case BEACH:
					level_asset = string(BACKGROUND_BEACH);
					state = PLAYING;
					init();
					break;
				case MOUNTAIN:
					level_asset = string(BACKGROUND_MOUNTAIN);
					state = PLAYING;
					init();
					break;
				case NIGHT:
					level_asset = string(BACKGROUND_NIGHT);
					state = PLAYING;
					init();
					break;
				}
				playSound(string(BEEP_ENTER_SOUND_EFFECT), 0.3f);
				button_timer = 0.f;
			}
			button_timer += getDeltaTime();
			if (button_timer > BUTTON_DELAY)
				button_timer = BUTTON_DELAY;
			break;
		
		case ABOUT_SCREEN:

			// ENTER
			if (getKeyState(SCANCODE_RETURN) && button_timer >= BUTTON_DELAY) {
				state = MAIN_MENU;
				buttonMM = PLAY;
				playSound(string(BEEP_ENTER_SOUND_EFFECT), 0.3f);
				button_timer = 0.f;
			}
			button_timer += getDeltaTime();
			if (button_timer > BUTTON_DELAY)
				button_timer = BUTTON_DELAY;
			break;
	}

	
}

void Game::updateTimers() {
	timer += getDeltaTime();
}

void Game::clearCollections() {

	while (!player->projectile_list.empty()) {
		delete player->projectile_list.front();
		player->projectile_list.pop_front();
	}

	while (!enemy_list.empty()) {
		delete enemy_list.front();
		enemy_list.pop_front();
	}

	if (pu) {
		delete pu;
		pu = nullptr;
	}
		
}