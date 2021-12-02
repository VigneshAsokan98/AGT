#pragma once
#include <engine.h>

class game_fsm
{
public :
	enum class GameState { GameMenu, GamePlay, GameOver };
	game_fsm();
	~game_fsm();

	virtual void init(){}
	virtual void on_update(const engine::timestep& time_step) {}
	virtual void on_render() {}
	virtual void on_event(engine::event& event) {}
	GameState getstate() { return m_state; }
	virtual void on_disable() {}

protected:
	GameState				m_state{};
private:

};
