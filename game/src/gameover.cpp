#include "gameover.h"
#include "game_controller.h"
#include "gameplay_manager.h"
#include<pch.h>
#include "engine/core/input.h"

gameover::gameover(GameState state)
	:m_3d_camera((float)engine::application::window().width(), (float)engine::application::window().height()), m_2d_camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	m_state = state;
	auto mesh_shader = engine::renderer::shaders_library()->get("mesh"); auto text_shader = engine::renderer::shaders_library()->get("text_2D");

	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->bind();
	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->set_uniform("projection",
		glm::ortho(0.f, (float)engine::application::window().width(), 0.f,
			(float)engine::application::window().height()));

	m_text_manager = engine::text_manager::create();

	m_Title = cross_fade::create("assets/textures/GameOver.png", 2.0f, 1.6f, 0.9f);
	m_material = engine::material::create(.0f, glm::vec3(1.0f, 0.1f, 0.07f),
		glm::vec3(1.0f, 0.1f, 0.07f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f);

	//headLights
	m_pointLight.Color = glm::vec3(1.f, 1.f, 1.f);
	m_pointLight.AmbientIntensity = 0.2f;
	m_pointLight.DiffuseIntensity = 0.5f;
	m_pointLight.Position = glm::vec3(0.0f, 2.0f, 0.0f);



}

gameover::~gameover()
{

}

void gameover::init()
{
	m_Title->activate();
}
void gameover::on_update(const engine::timestep& time_step)
{
	m_Title->on_update(time_step);
	m_Title->activate();
	m_2d_camera.on_update(time_step);
}

void gameover::on_render()
{
	engine::render_command::clear_color({ 1.f, 1.f, 1.f, 1.0f });
	engine::render_command::clear();

	// Set up  shader. (renders textures and materials)
	const auto mesh_shader = engine::renderer::shaders_library()->get("mesh");
	engine::renderer::begin_scene(m_3d_camera, mesh_shader);

	// Set up some of the scene's parameters in the shader
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gEyeWorldPos", m_3d_camera.position());

	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gNumPointLights", (int)num_point_lights);
	m_pointLight.submit(mesh_shader, 0);

	m_material->submit(mesh_shader);

	engine::renderer::end_scene();

	const auto text_shader = engine::renderer::shaders_library()->get("text_2D");

	m_text_manager->render_text(text_shader, "Score :: " + std::to_string((int)gameplay_manager::m_score), 25, (float)engine::application::window().height() / 2, 1.5f, glm::vec4(0.f, 0.f, 0.f, 1.f));

	engine::renderer::begin_scene(m_2d_camera, mesh_shader);
	//m_menuBG->on_render(mesh_shader);
	m_Title->on_render(mesh_shader);
	engine::renderer::end_scene();
}
void gameover::on_disable()
{
	const auto mesh_shader = engine::renderer::shaders_library()->get("mesh");
	engine::renderer::begin_scene(m_3d_camera, mesh_shader);
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gNumPointLights", 0);
	engine::renderer::end_scene();

}
void gameover::on_event(engine::event& event)
{


}
