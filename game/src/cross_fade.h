#pragma once
#pragma once
#include <engine.h>

class quad;

class cross_fade
{
public:
	cross_fade(const std::string& path, float max_time, float width, float height);
	~cross_fade();

	void on_update(const engine::timestep& time_step);
	void on_render(engine::ref<engine::shader> shader);
	void activate(bool _loop);

	static engine::ref<cross_fade> create(const std::string& path, float max_time, float width, float height);

private:
	bool s_active;
	bool s_loop;

	float m_timer;
	float m_max_time;

	engine::ref<engine::texture_2d> m_texture;
	float m_transparency;
	engine::ref<quad> m_quad;
};
