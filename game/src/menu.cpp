#include "menu.h"
#include "game_controller.h"
#include<pch.h>

menu::menu(GameState state)
	:m_3d_camera((float)engine::application::window().width(), (float)engine::application::window().height()), m_2d_camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	m_state = state;
	auto mesh_shader = engine::renderer::shaders_library()->get("mesh");
	auto text_shader = engine::renderer::shaders_library()->get("text_2D");
	m_cross_fade = cross_fade::create("assets/textures/Menu.bmp", 2.0f, 1.6f, 0.9f);
	m_material = engine::material::create(.0f, glm::vec3(1.0f, 0.1f, 0.07f),
		glm::vec3(1.0f, 0.1f, 0.07f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f);
	//headLights
	m_pointLight.Color = glm::vec3(1.f, 1.f, 1.f);
	m_pointLight.AmbientIntensity = 0.2f;
	m_pointLight.DiffuseIntensity = 0.5f;
	m_pointLight.Position = glm::vec3(0.0f, 2.0f, 0.0f);

	m_lightsource_material = engine::material::create(1.0f, m_pointLight.Color,
		m_pointLight.Color, m_pointLight.Color, 1.0f);
}

menu::~menu()
{

}

void menu::init()
{
	m_cross_fade->activate(true);
}
void menu::on_update(const engine::timestep& time_step)
{
	m_cross_fade->on_update(time_step);
	m_cross_fade->activate(true);
	m_2d_camera.on_update(time_step);
}

void menu::on_render()
{
	engine::render_command::clear_color({ 0.f, 0.f, 0.f, .0f });
	engine::render_command::clear();

	// Set up  shader. (renders textures and materials)
	const auto mesh_shader = engine::renderer::shaders_library()->get("mesh");
	engine::renderer::begin_scene(m_3d_camera, mesh_shader);

	// Set up some of the scene's parameters in the shader
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gEyeWorldPos", m_3d_camera.position());

	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->
		set_uniform("gNumPointLights", (int)num_point_lights);
	m_pointLight.submit(mesh_shader, 0);
	m_lightsource_material->submit(mesh_shader);

	m_material->submit(mesh_shader);

	engine::renderer::begin_scene(m_2d_camera, mesh_shader);
	m_cross_fade->on_render(mesh_shader);
	engine::renderer::end_scene();

	engine::renderer::end_scene();
}
void menu::on_event(engine::event& event)
{


}
