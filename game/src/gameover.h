#pragma once
#include <engine.h>
#include "game_fsm.h"

class gameover : public game_fsm
{
public:
	gameover(GameState state);
	~gameover();

	void init() override;
	void on_update(const engine::timestep& time_step) override;
	void on_render() override;
	void on_event(engine::event& event) override;

private:

};
