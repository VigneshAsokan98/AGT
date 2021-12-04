#pragma once
#include <engine.h>

class enemy
{
public:
	enemy();
	~enemy();

	virtual void on_update(const engine::timestep& time_step) {}
	virtual void init(engine::ref<engine::game_object> object) {} 
	virtual void on_render(const engine::ref<engine::shader>& shader, const engine::perspective_camera& camera) {}
	virtual void on_event(engine::event& event) {}

protected:
	int			m_health;
	int			m_speed;

private:

};
