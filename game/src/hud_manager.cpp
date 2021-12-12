#include "hud_manager.h"
#include "quad.h"
#include <string>  

hud_manager::hud_manager()
{
}
hud_manager::~hud_manager()
{

}

void hud_manager::init()
{
	auto text_shader = engine::renderer::shaders_library()->get("text_2D");

	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->bind();
	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->set_uniform("projection",
		glm::ortho(0.f, (float)engine::application::window().width(), 0.f,
			(float)engine::application::window().height()));

	m_crosshair = cross_fade::create("assets/textures/Crosshair.png", 2.0f, 1.6f, 0.9f);

	m_text_manager = engine::text_manager::create();
}
void hud_manager::on_update(const engine::timestep& time_step, const engine::perspective_camera& camera)
{
	glm::vec3 healthBarPos = camera.position() + camera.front_vector() * .2f;
	healthBarPos -= camera.right_vector() * .2f;
	m_crosshair->activate();
	m_crosshair->on_update(time_step);
}
void hud_manager::on_render(const engine::ref<engine::shader>& shader, engine::camera& camera)
{
	const auto text_shader = engine::renderer::shaders_library()->get("text_2D");
	m_text_manager->render_text(text_shader, "Health:: " + std::to_string(m_player_health), 15.f, (float)engine::application::window().height() - 50.f, 1.f, glm::vec4(0.f, 1.f, 0.f, 1.f));
	m_text_manager->render_text(text_shader, "Score:: " + std::to_string(m_Score), 15.f, (float)engine::application::window().height() - 110.f, 1.f, glm::vec4(0.f, 1.f, 0.f, 1.f));
	m_text_manager->render_text(text_shader, "Ammo:: " + std::to_string(m_ammoLeft), 10.f, 10.f, 1.f, glm::vec4(0.f, 0.f, 1.f, 1.f));

	engine::renderer::begin_scene(camera, shader);
	m_crosshair->on_render(shader);
	engine::renderer::end_scene();
}
