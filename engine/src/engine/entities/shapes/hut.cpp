#include "pch.h"
#include "hut.h"
#include <engine.h>		

engine::hut::hut(std::vector<glm::vec3> vertices) : m_vertices(vertices)
{

	std::vector<glm::vec3> normals;
	// front normal
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(2), vertices.at(0) - vertices.at(1)));
	// left normal
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(3), vertices.at(0) - vertices.at(2)));
	// back normal
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(1), vertices.at(0) - vertices.at(4)));
	// right normal
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(4), vertices.at(0) - vertices.at(3)));


	//front_quad normal
	normals.push_back(glm::cross(vertices.at(1) - vertices.at(2), vertices.at(1) - vertices.at(5)));
	//front_quad normal
	normals.push_back(glm::cross(vertices.at(1) - vertices.at(5), vertices.at(1) - vertices.at(6)));

	//right_quad normal
	normals.push_back(glm::cross(vertices.at(2) - vertices.at(3), vertices.at(2) - vertices.at(8)));
	//right_quad normal
	normals.push_back(glm::cross(vertices.at(2) - vertices.at(8), vertices.at(2) - vertices.at(5)));

	//left_quad normal
	normals.push_back(glm::cross(vertices.at(3) - vertices.at(4), vertices.at(3) - vertices.at(7)));
	//left_quad normal
	normals.push_back(glm::cross(vertices.at(3) - vertices.at(7), vertices.at(3) - vertices.at(8)));

	//back_quad normal
	normals.push_back(glm::cross(vertices.at(4) - vertices.at(1), vertices.at(4) - vertices.at(6)));
	//back_quad normal
	normals.push_back(glm::cross(vertices.at(4) - vertices.at(6), vertices.at(4) - vertices.at(7)));

	//bottom_quad normal
	normals.push_back(glm::cross(vertices.at(5) - vertices.at(8), vertices.at(5) - vertices.at(7)));
	//bottom_quad normal
	normals.push_back(glm::cross(vertices.at(5) - vertices.at(7), vertices.at(5) - vertices.at(6)));


	glm::vec3 m_half_extents = glm::vec3(1.f, 1.f, 1.f);

	std::vector<mesh::vertex> hut_vertices
	{
		//front
		//  position			normal			      tex coord       
		{ vertices.at(0),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(2),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(1),		normals.at(0),		{ 0.5f, 1.f } },

		//left
		{ vertices.at(0),		normals.at(1),		{ 0.f,  0.f } },
		{ vertices.at(3),		normals.at(1),		{ 1.f,  0.f } },
		{ vertices.at(2),		normals.at(1),		{ 0.5f, 1.f } },

		//right
		{ vertices.at(0),		normals.at(2),		{ 0.f,  0.f } },
		{ vertices.at(4),		normals.at(2),		{ 1.f,  0.f } },
		{ vertices.at(3),		normals.at(2),		{ 0.5f, 1.f } },

		//back
		{ vertices.at(0),		normals.at(3),		{ 0.f,  0.f } },
		{ vertices.at(1),		normals.at(3),		{ 1.f,  0.f } },
		{ vertices.at(4),		normals.at(3),		{ 0.5f, 1.f } },

		//front_quad
		{ vertices.at(1),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(5),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(6),		normals.at(4),		{ 0.5f, 1.f } },

		//front_quad
		{ vertices.at(1),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(2),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(5),		normals.at(4),		{ 0.5f, 1.f } },

		//right_quad
		{ vertices.at(2),		normals.at(6),		{ 0.f,  0.f } },
		{ vertices.at(3),		normals.at(6),		{ 1.f,  0.f } },
		{ vertices.at(8),		normals.at(6),		{ 0.5f, 1.f } },

		//right_quad
		{ vertices.at(2),		normals.at(6),		{ 0.f,  0.f } },
		{ vertices.at(8),		normals.at(6),		{ 1.f,  0.f } },
		{ vertices.at(5),		normals.at(6),		{ 0.5f, 1.f } },

		//left_quad
		{ vertices.at(3),		normals.at(8),		{ 0.f,  0.f } },
		{ vertices.at(4),		normals.at(8),		{ 1.f,  0.f } },
		{ vertices.at(7),		normals.at(8),		{ 0.5f, 1.f } },

		//left_quad
		{ vertices.at(3),		normals.at(8),		{ 0.f,  0.f } },
		{ vertices.at(7),		normals.at(8),		{ 1.f,  0.f } },
		{ vertices.at(8),		normals.at(8),		{ 0.5f, 1.f } },

		//back_quad
		{ vertices.at(4),		normals.at(10),		{ 0.f,  0.f } },
		{ vertices.at(1),		normals.at(10),		{ 1.f,  0.f } },
		{ vertices.at(6),		normals.at(10),		{ 0.5f, 1.f } },

		//back_quad
		{ vertices.at(4),		normals.at(11),		{ 0.f,  0.f } },
		{ vertices.at(6),		normals.at(11),		{ 1.f,  0.f } },
		{ vertices.at(7),		normals.at(11),		{ 0.5f, 1.f } },

		//bottom_quad
		{ vertices.at(5),		normals.at(12),		{ 0.f,  0.f } },
		{ vertices.at(8),		normals.at(12),		{ 1.f,  0.f } },
		{ vertices.at(7),		normals.at(12),		{ 0.5f, 1.f } },

		//bottom_quad
		{ vertices.at(5),		normals.at(13),		{ 0.f,  0.f } },
		{ vertices.at(7),		normals.at(13),		{ 1.f,  0.f } },
		{ vertices.at(6),		normals.at(13),		{ 0.5f, 1.f } },

	};

	const std::vector<uint32_t> hut_indices
	{
		0,  1,  2,	//front
		3,  4,  5,	//left
		6,	7,	8,	//Right
		9,	10,	11,	//Bottom
		12, 13, 14, 15, 16, 17, //front_quad
		18, 19, 20, 21, 22, 23, //right_quad
		24, 25, 26, 27, 28, 29,  //left_quad
		30, 31, 32, 33, 34, 35,  //back_quad
		36, 37, 38, 39, 40, 41,  //bottom_quad
	};

	m_mesh = engine::mesh::create(hut_vertices, hut_indices);


}

engine::hut::~hut() {}

engine::ref<engine::hut> engine::hut::create(std::vector<glm::vec3> vertices)
{
	return std::make_shared<engine::hut>(vertices);
}
