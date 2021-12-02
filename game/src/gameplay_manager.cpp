#include "gameplay_manager.h"
#include "game_controller.h"
#include "platform/opengl/gl_shader.h"

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include "engine/events/key_event.h"
#include "engine/utils/track.h"

gameplay_manager::gameplay_manager(GameState state):
m_3d_camera((float)engine::application::window().width(), (float)engine::application::window().height())
{
	m_state = state;
	// Skybox texture from http://www.vwall.it/wp-content/plugins/canvasio3dpro/inc/resource/cubeMaps/
	m_skybox = engine::skybox::create(50.f,
		{ engine::texture_2d::create("assets/textures/sky_box/SkyFront.bmp", true),
		  engine::texture_2d::create("assets/textures/sky_box/SkyRight.bmp", true),
		  engine::texture_2d::create("assets/textures/sky_box/SkyBack.bmp", true),
		  engine::texture_2d::create("assets/textures/sky_box/SkyLeft.bmp", true),
		  engine::texture_2d::create("assets/textures/sky_box/SkyTop.bmp", true),
		  engine::texture_2d::create("assets/textures/sky_box/SkyBottom.bmp", true)
		});


	// Initialise the shaders, materials and lights
	auto mesh_shader = engine::renderer::shaders_library()->get("mesh");
	auto text_shader = engine::renderer::shaders_library()->get("text_2D");

	m_directionalLight.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_directionalLight.AmbientIntensity = 0.1f;
	m_directionalLight.DiffuseIntensity = 0.4f;
	m_directionalLight.Direction = glm::normalize(glm::vec3(1.0f, -1.0f, 0.0f));

	// set color texture unit
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->bind();
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("lighting_on", true);
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gColorMap", 0);
	m_directionalLight.submit(mesh_shader);
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gMatSpecularIntensity", .5f);
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gSpecularPower", 5.f);
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("transparency", 1.0f);

	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->bind();
	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->set_uniform("projection",
		glm::ortho(0.f, (float)engine::application::window().width(), 0.f,
			(float)engine::application::window().height()));
	m_material = engine::material::create(.0f, glm::vec3(1.0f, 0.1f, 0.07f),
		glm::vec3(1.0f, 0.1f, 0.07f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f);

	// Load the terrain texture and create a terrain mesh. Create a terrain object. Set its properties
	std::vector<engine::ref<engine::texture_2d>> terrain_textures = { engine::texture_2d::create("assets/textures/terrain.bmp", false) };
	engine::ref<engine::terrain> terrain_shape = engine::terrain::create(100.f, 0.5f, 100.f);
	engine::game_object_properties terrain_props;
	terrain_props.meshes = { terrain_shape->mesh() };
	terrain_props.textures = terrain_textures;
	terrain_props.is_static = true;
	terrain_props.type = 0;
	terrain_props.bounding_shape = glm::vec3(100.f, 0.5f, 100.f);
	terrain_props.restitution = 0.92f;
	m_terrain = engine::game_object::create(terrain_props);

	m_car_material = engine::material::create(.0f, glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f);

	//Load player
	engine::ref <engine::model> car_model = engine::model::create("assets/models/static/redcar1.obj");
	engine::game_object_properties car_props;
	car_props.meshes = car_model->meshes();
	car_props.textures = car_model->textures();
	float car_scale = glm::max(car_model->size().x, glm::max(car_model->size().y, car_model->size().z));
	car_props.position = { -5.f, 0.f, 0.f };
	car_props.scale = glm::vec3(car_scale);
	car_props.bounding_shape = car_model->size();
	m_car = engine::game_object::create(car_props);

	m_player.initialise(m_car);
	m_car_box.set_box(car_props.bounding_shape.x * car_props.scale.x, car_props.bounding_shape.y * car_props.scale.x, car_props.bounding_shape.z * car_props.scale.x, car_props.position);

	//load pinetree
	engine::ref <engine::model> tree_model = engine::model::create("assets/models/static/pine.obj");
	engine::game_object_properties tree_props;
	tree_props.meshes = tree_model->meshes();
	tree_props.textures = { engine::texture_2d::create("assets/textures/pine.png", false) };
	float tree_scale = glm::max(tree_model->size().x, glm::max(tree_model->size().y, tree_model->size().z));
	tree_props.scale = glm::vec3(tree_scale);
	tree_props.bounding_shape = tree_model->size() / 2.f * tree_scale;
	for (int x = 10; x < 25; x++)
	{
		for (int z = 10; z < 25; z++)
		{
			tree_props.position = { -5.f + x * 2.f, 1.f, 0.f + z * 2.f};

			m_tree.push_back(engine::game_object::create(tree_props));
		}
	}

	//load spear
	std::vector<glm::vec3> Hut_vertices;
	Hut_vertices.push_back(glm::vec3(0.f, 6.f, 0.f));	//0
	Hut_vertices.push_back(glm::vec3(2.f, 4.f, 2.f));	//1
	Hut_vertices.push_back(glm::vec3(-2.f, 4.f, 2.f));	//2
	Hut_vertices.push_back(glm::vec3(-2.f, 4.f, -2.f));	//3
	Hut_vertices.push_back(glm::vec3(2.f, 4.f, -2.f));	//4
	Hut_vertices.push_back(glm::vec3(-2.f, 0.f, 2.f));	//5
	Hut_vertices.push_back(glm::vec3(2.f, 0.f, 2.f));	//6
	Hut_vertices.push_back(glm::vec3(2.f, 0.f, -2.f));	//7
	Hut_vertices.push_back(glm::vec3(-2.f, 0.f, -2.f));	//8

	engine::ref<engine::hut> hut_shape = engine::hut::create(Hut_vertices);
	std::vector<engine::ref<engine::texture_2d>> hut_textures =
	{ engine::texture_2d::create("assets/textures/wood.jpg", false) };
	engine::game_object_properties hut_props;
	hut_props.meshes = { hut_shape->mesh() };
	hut_props.textures = hut_textures;
	
	for (int i = 0; i < 10; i++)
	{
		hut_props.scale = { 0.5f, .5f, .5f };
		hut_props.position = { 10.f, .5f, -20.f + i * 5};
		engine::bounding_box	hut_box;
		hut_box.set_box(2.f, 3.f, 2.f, hut_props.position);
		m_hut_boxes.push_back(hut_box);
		m_huts.push_back(engine::game_object::create(hut_props));
	}

	m_physics_manager = engine::bullet_manager::create(m_game_objects);

	m_text_manager = engine::text_manager::create();
}
gameplay_manager::~gameplay_manager()
{

}

void gameplay_manager::init()
{
}
void gameplay_manager::on_update(const engine::timestep& time_step)
{
	glm::vec3 pos = m_player.object()->position();
	m_3d_camera.on_update(time_step);

	glm::vec3 camera_position = m_player.object()->position() + (glm::vec3(0.f, 3.f, 0.f) + m_player.object()->forward() * 10.f);
	glm::vec3 camera_lookat_position = m_player.object()->position() - m_player.object()->forward() * 4.f;

	m_3d_camera.set_view_matrix( camera_position, camera_lookat_position);

	m_player.on_update(time_step);
	m_car_box.on_update(m_player.object()->position(), m_player.object()->forward());
	for each (engine::bounding_box box in m_hut_boxes)
	{
		if (box.collision(m_car_box))
		{
			m_player.object()->set_position(pos);
		}
	}
	m_physics_manager->dynamics_world_update(m_game_objects, double(time_step));
}
void gameplay_manager::on_render()
{
	engine::render_command::clear_color({ 0.f, 0.f, 0.f, .0f });
	engine::render_command::clear();

	// Set up  shader. (renders textures and materials)
	const auto mesh_shader = engine::renderer::shaders_library()->get("mesh");
	engine::renderer::begin_scene(m_3d_camera, mesh_shader);

	m_player.on_render(mesh_shader, m_3d_camera);

	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("has_texture",
		true);
	m_terrain->textures().at(0)->bind();
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("has_texture",
		false);
	// Set up some of the scene's parameters in the shader
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gEyeWorldPos", m_3d_camera.position());


	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("lighting_on", false);
	// Position the skybox centred on the player and render it
	glm::mat4 skybox_tranform(1.0f);
	skybox_tranform = glm::translate(skybox_tranform, m_3d_camera.position());
	for (const auto& texture : m_skybox->textures())
	{
		texture->bind();
	}
	engine::renderer::submit(mesh_shader, m_skybox, skybox_tranform);

	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("lighting_on", true);

	engine::renderer::submit(mesh_shader, m_terrain);

	m_car_box.on_render(2.5f, 0.f, 0.f, mesh_shader);


	for each (engine::bounding_box box in m_hut_boxes)
	{
		box.on_render(2.5f, 0.f, 0.f, mesh_shader);
	}
	m_car_material->submit(mesh_shader);
	engine::renderer::submit(mesh_shader, m_player.object());

	for (int idx = 0; idx < m_huts.size(); idx++)
	{
		engine::renderer::submit(mesh_shader, m_huts.at(idx));
	}

	m_material->submit(mesh_shader);
	for (int idx = 0; idx < m_tree.size(); idx++)
	{
		engine::renderer::submit(mesh_shader, m_tree.at(idx));
	}
	engine::renderer::end_scene();
}
void gameplay_manager::on_event(engine::event& event)
{

}
