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

	//init Spawnpoints
	Init_Spawnpoints();

	Create_Effects();
	Create_Environment_Objects();
	Create_Player();

	m_HUD.init();

	m_physics_manager = engine::bullet_manager::create(m_game_objects);
	m_text_manager = engine::text_manager::create();

}
void gameplay_manager::Init_Spawnpoints()
{
	//spawn points of Pickups
	m_pickups_Spawnpoints.push_back(glm::vec3(5.f, 0.f, 0.f));
	m_pickups_Spawnpoints.push_back(glm::vec3(9.f, 0.f, -5.f));
	m_pickups_Spawnpoints.push_back(glm::vec3(-12.f, 0.f, 16.f));
	m_pickups_Spawnpoints.push_back(glm::vec3(-9.f, 0.f, -14.f));
	m_pickups_Spawnpoints.push_back(glm::vec3(15.f, 0.f, 7.f));

	//Spawn points for Enemies
	m_enemy_spawnpoints.push_back(glm::vec3(5.f, 0.f, 0.f));
	m_enemy_spawnpoints.push_back(glm::vec3(5.f, 0.f, 0.f));
	m_enemy_spawnpoints.push_back(glm::vec3(5.f, 0.f, 0.f));
	m_enemy_spawnpoints.push_back(glm::vec3(5.f, 0.f, 0.f));
	m_enemy_spawnpoints.push_back(glm::vec3(5.f, 0.f, 0.f));
	m_enemy_spawnpoints.push_back(glm::vec3(5.f, 0.f, 0.f));
}
void gameplay_manager::Create_Effects()
{
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
}
void gameplay_manager::Create_Environment_Objects()
{
	// Skybox texture from http://www.vwall.it/wp-content/plugins/canvasio3dpro/inc/resource/cubeMaps/
	m_skybox = engine::skybox::create(50.f,
		{ engine::texture_2d::create("assets/textures/sky_box/SkyFront.bmp", true),
		  engine::texture_2d::create("assets/textures/sky_box/SkyRight.bmp", true),
		  engine::texture_2d::create("assets/textures/sky_box/SkyBack.bmp", true),
		  engine::texture_2d::create("assets/textures/sky_box/SkyLeft.bmp", true),
		  engine::texture_2d::create("assets/textures/sky_box/SkyTop.bmp", true),
		  engine::texture_2d::create("assets/textures/sky_box/SkyBottom.bmp", true)
		});

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

	//load pinetree
	engine::ref <engine::model> tree_model = engine::model::create("assets/models/static/pine.obj");
	engine::game_object_properties tree_props;
	tree_props.meshes = tree_model->meshes();
	tree_props.textures = { engine::texture_2d::create("assets/textures/pine.png", false) };
	float tree_scale = glm::max(tree_model->size().x, glm::max(tree_model->size().y, tree_model->size().z));
	tree_props.scale = glm::vec3(tree_scale);
	tree_props.bounding_shape = tree_model->size() / 3.f * tree_scale;
	for (int x = 0; x < 5; x++)
	{
			float PosX = (float)((std::rand() % (40 + 40)) - 40);
			float PosZ = (float)((std::rand()  % (40 + 40)) - 40);
			tree_props.position = { PosX , 1.f, PosZ};
			m_tree.push_back(engine::game_object::create(tree_props));
			engine::bounding_box	tree_box;
			tree_box.set_box(tree_props.bounding_shape.x * tree_props.scale.x, tree_props.bounding_shape.y * tree_props.scale.x, tree_props.bounding_shape.z * tree_props.scale.x, tree_props.position);
			m_tree_boxes.push_back(tree_box);
	} 
	//Load Health_Pickup (Primitive Shape 1)
	std::vector<glm::vec3> Health_Pickup_vertices;
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 3.f, 0.f));		//0
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 3.f, 0.f));		//1
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 3.f, 1.f));		//2
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 3.f, 1.f));		//3
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 2.f, 1.f));		//4
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 2.f, 0.f));		//5
	Health_Pickup_vertices.push_back(glm::vec3(-1.f, 2.f, 0.f));	//6
	Health_Pickup_vertices.push_back(glm::vec3(-1.f, 1.f, 0.f));	//7
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 1.f, 0.f));		//8
	Health_Pickup_vertices.push_back(glm::vec3(0.f, .5f, 0.f));		//9
	Health_Pickup_vertices.push_back(glm::vec3(1.f, .5f, 0.f));		//10
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 1.f, 0.f));		//11
	Health_Pickup_vertices.push_back(glm::vec3(2.f, 1.f, 0.f));		//12
	Health_Pickup_vertices.push_back(glm::vec3(2.f, 2.f, 0.f));		//13
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 2.f, 0.f));		//14
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 2.f, 1.f));		//15
	Health_Pickup_vertices.push_back(glm::vec3(2.f, 2.f, 1.f));		//16
	Health_Pickup_vertices.push_back(glm::vec3(2.f, 1.f, 1.f));		//17
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 1.f, 1.f));		//18
	Health_Pickup_vertices.push_back(glm::vec3(1.f, .5f, 1.f));		//19
	Health_Pickup_vertices.push_back(glm::vec3(0.f, .5f, 1.f));		//20
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 1.f, 1.f));		//22
	Health_Pickup_vertices.push_back(glm::vec3(-1.f, 1.f, 1.f));	//23
	Health_Pickup_vertices.push_back(glm::vec3(-1.f, 2.f, 1.f));	//24

	engine::ref<engine::Plus_shape> Health_Pickup_shape = engine::Plus_shape::create(Health_Pickup_vertices);
	std::vector<engine::ref<engine::texture_2d>> Health_Pickup_textures =
	{ engine::texture_2d::create("assets/textures/Green.bmp", false) };
	engine::game_object_properties Health_Pickup_props;
	Health_Pickup_props.meshes = { Health_Pickup_shape->mesh() };
	Health_Pickup_props.textures = Health_Pickup_textures;
	Health_Pickup_props.position = { 2, .5f, -5 };
	m_Health_Pickup = engine::game_object::create(Health_Pickup_props);


	//Load Bullets(Primitive Shape 2)
	std::vector<glm::vec3> Bullet_vertices;
	Bullet_vertices.push_back(glm::vec3(.5f, .5f, 1.f));	//0
	Bullet_vertices.push_back(glm::vec3(.75f, 0.f, 1.f));	//1
	Bullet_vertices.push_back(glm::vec3(.25f, 0.f, 1.f));	//2
	Bullet_vertices.push_back(glm::vec3(0.f, .5f, 1.f));	//3
	Bullet_vertices.push_back(glm::vec3(.5f, 1.f, 1.f));	//4
	Bullet_vertices.push_back(glm::vec3(1.f, .5f, 1.f));	//5
	Bullet_vertices.push_back(glm::vec3(1.f, .5f, -1.f));	//6
	Bullet_vertices.push_back(glm::vec3(.75f, 0.f, -1.f));	//7
	Bullet_vertices.push_back(glm::vec3(.25f, 0.f, -1.f));	//8
	Bullet_vertices.push_back(glm::vec3(0.f, .5f, -1.f));	//9
	Bullet_vertices.push_back(glm::vec3(.5f, 1.f, -1.f));	//10
	Bullet_vertices.push_back(glm::vec3(.5f, .5f, -1.f));	//11

	engine::ref<engine::Pentagon_prism> Bullet_shape = engine::Pentagon_prism::create(Bullet_vertices);
	std::vector<engine::ref<engine::texture_2d>> Bullet_textures =
	{ engine::texture_2d::create("assets/textures/Green.bmp", false) };
	engine::game_object_properties Bullet_props;
	Bullet_props.meshes = { Bullet_shape->mesh() };
	Bullet_props.textures = Bullet_textures;
	Bullet_props.position = { 5.f, 6.f, 6.f };
	m_bullets = engine::game_object::create(Bullet_props);

	//load Hut(Primitive Shape 3)
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
	{ engine::texture_2d::create("assets/textures/Wood.bmp", false) };
	engine::game_object_properties hut_props;
	hut_props.meshes = { hut_shape->mesh() };
	hut_props.textures = hut_textures;

	for (int i = 0; i < 6; i++)
	{
		float PosX = (float)((rand() % (30 + 30)) - 30);
		float PosZ = (float)((rand() % (30 + 30)) - 30);
		hut_props.scale = { 0.5f, .5f, .5f };
		hut_props.position = { PosX , 1.f, PosZ };
		engine::bounding_box	hut_box;
		hut_box.set_box(2.f, 3.f, 2.f, hut_props.position);
		m_hut_boxes.push_back(hut_box);
		m_huts.push_back(engine::game_object::create(hut_props));
	}

	engine::ref <engine::sphere> sphere_shape = engine::sphere::create(25, 25, .25f);
	std::vector<engine::ref<engine::texture_2d>> ball_textures =
	{ engine::texture_2d::create("assets/textures/Wood.bmp", false) };
	engine::game_object_properties sphere_props;
	sphere_props.position = { 0.f, 5.f, -5.f };
	sphere_props.meshes = {sphere_shape->mesh()};
	sphere_props.textures = ball_textures;
	sphere_props.bounding_shape = glm::vec3(.25f);
	sphere_props.type = 1;
	sphere_props.restitution = 0.92f;
	sphere_props.mass = 0.6f;
	engine::ref<engine::game_object> _ball = engine::game_object::create(sphere_props);

	m_game_objects.push_back(m_terrain);
	m_game_objects.push_back(_ball);

	m_cannonball.initialise(_ball);

}
void gameplay_manager::Create_Player()
{
	m_car_material = engine::material::create(.0f, glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f);

	//Load player
	engine::ref <engine::model> car_model = engine::model::create("assets/models/static/redcar1.obj");
	engine::game_object_properties car_props;
	car_props.meshes = car_model->meshes();
	car_props.textures = car_model->textures();
	float car_scale = glm::max(car_model->size().x, glm::max(car_model->size().y, car_model->size().z));
	car_props.position = { 0.f, .75f, 10.f };
	car_props.scale = glm::vec3(car_scale);
	car_props.bounding_shape = car_model->size();
	m_car = engine::game_object::create(car_props);

	m_player.initialise(m_car);
	m_car_box.set_box(car_props.bounding_shape.x * car_props.scale.x, car_props.bounding_shape.y * car_props.scale.x, car_props.bounding_shape.z * car_props.scale.x, car_props.position);
}
void gameplay_manager::Create_Enemies()
{
	engine::ref <engine::model> turret_model = engine::model::create("assets/models/static/redcar1.obj");
	engine::game_object_properties turret_props;
	turret_props.meshes = turret_model->meshes();
	turret_props.textures = turret_model->textures();
	float turret_scale = glm::max(turret_model->size().x, glm::max(turret_model->size().y, turret_model->size().z));
	turret_props.position = { -5.f, 0.f, 0.f };
	turret_props.scale = glm::vec3(turret_scale);
	turret_props.bounding_shape = turret_model->size();
	engine::ref<engine::game_object> enemy_object = engine::game_object::create(turret_props);

	m_enemy_player.init(enemy_object);
	m_enemies.push_back(m_enemy_player);
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
	m_HUD.on_update(time_step, m_3d_camera);
	m_player.on_update(time_step);
	m_car_box.on_update(m_player.object()->position(), m_player.object()->forward());
	m_cannonball.on_update(time_step);

	Check_Player_Collision(pos);
	m_physics_manager->dynamics_world_update(m_game_objects, double(time_step));
}

void gameplay_manager::Check_Player_Collision(glm::vec3 player_pos)
{
	for each (engine::bounding_box box in m_hut_boxes)
	{
		if (box.collision(m_car_box))
		{
			m_player.object()->set_position(player_pos);
		}
	}
	for each (engine::bounding_box box in m_tree_boxes)
	{
		if (box.collision(m_car_box))
		{
			m_player.object()->set_position(player_pos);
		}
	}
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
	m_cannonball.on_render(mesh_shader);
	m_car_box.on_render(2.5f, 0.f, 0.f, mesh_shader);

	for each (engine::bounding_box box in m_hut_boxes)
	{
		box.on_render(2.5f, 0.f, 0.f, mesh_shader);
	}
	for each (engine::bounding_box box in m_tree_boxes)
	{
		box.on_render(2.5f, 0.f, 0.f, mesh_shader);
	}
	m_car_material->submit(mesh_shader);
	engine::renderer::submit(mesh_shader, m_player.object());

	//Rendering Primitives 
	for (int idx = 0; idx < m_huts.size(); idx++)
	{
		engine::renderer::submit(mesh_shader, m_huts.at(idx));
	}

	engine::renderer::submit(mesh_shader, m_bullets);
	engine::renderer::submit(mesh_shader, m_Health_Pickup);

	m_material->submit(mesh_shader);
	for (int idx = 0; idx < m_tree.size(); idx++)
	{
		engine::renderer::submit(mesh_shader, m_tree.at(idx));
	}
	engine::renderer::end_scene();

	m_HUD.on_render(mesh_shader, m_3d_camera);
}
void gameplay_manager::on_event(engine::event& event)
{
	if (event.event_type() == engine::event_type_e::key_pressed)
	{
		auto& e = dynamic_cast<engine::key_pressed_event&>(event);
		if (e.key_code() == engine::key_codes::KEY_Q)
		{
			m_cannonball.shoot(m_player, 100.f);
		}
	}
}
