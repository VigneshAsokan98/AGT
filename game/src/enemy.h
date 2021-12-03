#pragma once
#include <engine.h>

class enemy
{
public:
	enemy();
	~enemy();

	virtual void on_update(const engine::timestep& time_step) {}
	virtual void on_render() {}
	virtual void on_event(engine::event& event) {}


protected:
	int			m_health;
	int			m_speed;

private:

};
