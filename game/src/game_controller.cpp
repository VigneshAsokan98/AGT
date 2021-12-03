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

    if (engine::input::key_pressed(engine::key_codes::KEY_SPACE) && m_current_gamestate_object->getstate() == game_fsm::GameState::GameMenu)
    {
        switch_state(game_fsm::GameState::GamePlay);
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
    if(event.event_type() == engine::event_type_e::key_pressed) 
    { 
        auto& e = dynamic_cast<engine::key_pressed_event&>(event); 
        if(e.key_code() == engine::key_codes::KEY_TAB) 
        { 
            engine::render_command::toggle_wireframe();
        }
        
    } 
}


