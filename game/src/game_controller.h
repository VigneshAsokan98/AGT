#pragma once
#include <engine.h>
#include "game_fsm.h"

class game_controller : public engine::layer
{
public:
    game_controller();
	~game_controller();

    void on_update(const engine::timestep& time_step) override;
    void on_render() override; 
    void on_event(engine::event& event) override;

private:
	void switch_state(game_fsm::GameState _state);

	game_fsm::GameState					m_current_game_state;
	game_fsm*							m_current_gamestate_object;
	game_fsm*							m_previous_gamestate_object;
	game_fsm*							m_gamestates[3];

	engine::ref<engine::audio_manager>  m_audio_manager{};
	bool								m_mute = false;

	float								m_prev_sphere_y_vel = 0.f;

};
