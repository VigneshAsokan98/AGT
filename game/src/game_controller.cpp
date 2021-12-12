#include "game_controller.h"
#include "platform/opengl/gl_shader.h"

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include "engine/events/key_event.h"
#include "engine/utils/track.h"
#include "menu.h"
#include "gameplay_manager.h"
#include "gameover.h"

game_controller::game_controller() 
{
    // Hide the mouse and lock it inside the window
    //engine::input::anchor_mouse(true);
    engine::application::window().hide_mouse_cursor();

    // Initialise audio and play background music
    m_audio_manager = engine::audio_manager::instance();
    m_audio_manager->init();
    m_audio_manager->load_sound("assets/audio/car.wav", engine::sound_type::spatialised, "car");  //  Royalty free sound from freesound.org
    m_audio_manager->load_sound("assets/audio/BG_Music.wav", engine::sound_type::track, "BG_music");  //  Royalty free sound from freesound.org
    m_audio_manager->play("BG_music");
    m_audio_manager->loop("BG_music", true);

    m_audio_manager->create_high_pass_filter();
    m_audio_manager->set_high_pass_filter(10000.f);
    m_audio_manager->create_low_pass_filter();
    m_audio_manager->set_low_pass_filter(20000.f);


	m_current_game_state = game_fsm::GameState::GameMenu;

	m_gamestates[0] = new menu(game_fsm::GameState::GameMenu);
	m_gamestates[1] = new gameplay_manager(game_fsm::GameState::GamePlay);
	m_gamestates[2] = new gameover(game_fsm::GameState::GameOver);

	m_current_gamestate_object = m_gamestates[(int)game_fsm::GameState::GameMenu];

    m_current_gamestate_object->init();
}

game_controller::~game_controller() {}

void game_controller::on_update(const engine::timestep& time_step) 
{
	m_current_gamestate_object->on_update(time_step);
    m_audio_manager->on_update();
    if (engine::input::key_pressed(engine::key_codes::KEY_SPACE) && m_current_gamestate_object->getstate() == game_fsm::GameState::GameMenu)
    {
        switch_state(game_fsm::GameState::GamePlay);
    }
    if (gameplay_manager::CheckHealth())
    {
        switch_state(game_fsm::GameState::GameOver);
    }
} 

void game_controller::switch_state(game_fsm::GameState _state)
{
    if (m_current_gamestate_object->getstate() == _state)
        return;

    m_previous_gamestate_object = m_current_gamestate_object;
    m_current_gamestate_object = m_gamestates[(int)_state];

    m_previous_gamestate_object->on_disable();
    m_current_gamestate_object->init();
}
void game_controller::on_render() 
{
	m_current_gamestate_object->on_render();
} 

void game_controller::on_event(engine::event& event) 
{
    m_current_gamestate_object->on_event(event);

    if(event.event_type() == engine::event_type_e::key_pressed) 
    {        
        auto& e = dynamic_cast<engine::key_pressed_event&>(event); 
        if(e.key_code() == engine::key_codes::KEY_TAB) 
        { 
            engine::render_command::toggle_wireframe();
        }
        if (e.key_code() == engine::key_codes::KEY_SPACE && m_current_gamestate_object->getstate() == game_fsm::GameState::GameOver)
        {
            switch_state(game_fsm::GameState::GameMenu);
        }
        if (e.key_code() == engine::key_codes::KEY_M)
        {
            if(m_mute)
                m_audio_manager->play("BG_music");
            else
                m_audio_manager->pause("BG_music");

            m_mute = !m_mute;
        }
    } 
}


