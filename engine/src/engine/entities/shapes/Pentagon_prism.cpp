#include "pch.h"
#include "Pentagon_prism.h"
#include <engine.h>		

engine::Pentagon_prism::Pentagon_prism(std::vector<glm::vec3> vertices) : m_vertices(vertices)
{

	std::vector<glm::vec3> normals;
	// front normal
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(2), vertices.at(0) - vertices.at(1)));
	//TopRight_qaud normal
	normals.push_back(glm::cross(vertices.at(5) - vertices.at(10), vertices.at(5) - vertices.at(6)));
	//Topleft_qaud normal
	normals.push_back(glm::cross(vertices.at(4) - vertices.at(9), vertices.at(4) - vertices.at(10)));
	//Buttomleft_qaud normal
	normals.push_back(glm::cross(vertices.at(2) - vertices.at(9), vertices.at(2) - vertices.at(8)));
	//buttom_qaud normal
	normals.push_back(glm::cross(vertices.at(1) - vertices.at(8), vertices.at(1) - vertices.at(7)));
	//buttomRight_qaud normal
	normals.push_back(glm::cross(vertices.at(1) - vertices.at(6), vertices.at(1) - vertices.at(7)));


	glm::vec3 m_half_extents = glm::vec3(1.f, 1.f, 1.f);

	std::vector<mesh::vertex> Pentagon_prism_vertices
	{
		//front
		//  position			normal			      tex coord       
		{ vertices.at(0),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(2),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(1),		normals.at(0),		{ 0.5f, 1.f } },

		{ vertices.at(0),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(3),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(2),		normals.at(0),		{ 0.5f, 1.f } },

		{ vertices.at(0),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(4),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(3),		normals.at(0),		{ 0.5f, 1.f } },

		{ vertices.at(0),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(5),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(4),		normals.at(0),		{ 0.5f, 1.f } },

		{ vertices.at(0),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(1),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(5),		normals.at(0),		{ 0.5f, 1.f } },

		//TopRight_quad
		{ vertices.at(5),		normals.at(1),		{ 0.f,  0.f } },
		{ vertices.at(6),		normals.at(1),		{ 1.f,  0.f } },
		{ vertices.at(10),		normals.at(1),		{ 0.5f, 1.f } },
		//TopRight_quad				   
		{ vertices.at(5),		normals.at(1),		{ 0.f,  0.f } },
		{ vertices.at(10),		normals.at(1),		{ 1.f,  0.f } },
		{ vertices.at(4),		normals.at(1),		{ 0.5f, 1.f } },

		//Topleft_quad
		{ vertices.at(4),		normals.at(2),		{ 0.f,  0.f } },
		{ vertices.at(10),		normals.at(2),		{ 1.f,  0.f } },
		{ vertices.at(9),		normals.at(2),		{ 0.5f, 1.f } },
		//Topleft_quad					   
		{ vertices.at(4),		normals.at(2),		{ 0.f,  0.f } },
		{ vertices.at(9),		normals.at(2),		{ 1.f,  0.f } },
		{ vertices.at(3),		normals.at(2),		{ 0.5f, 1.f } },

		//BottomLeft_quad
		{ vertices.at(2),		normals.at(3),		{ 0.f,  0.f } },
		{ vertices.at(9),		normals.at(3),		{ 1.f,  0.f } },
		{ vertices.at(8),		normals.at(3),		{ 0.5f, 1.f } },
		//BottomLeft_quad					  
		{ vertices.at(2),		normals.at(3),		{ 0.f,  0.f } },
		{ vertices.at(3),		normals.at(3),		{ 1.f,  0.f } },
		{ vertices.at(9),		normals.at(3),		{ 0.5f, 1.f } },

		//Bottom_quad
		{ vertices.at(1),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(8),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(7),		normals.at(4),		{ 0.5f, 1.f } },
		//Bottom_quad					   
		{ vertices.at(1),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(2),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(8),		normals.at(4),		{ 0.5f, 1.f } },

		//BottomRight_quad
		{ vertices.at(5),		normals.at(5),		{ 0.f,  0.f } },
		{ vertices.at(7),		normals.at(5),		{ 1.f,  0.f } },
		{ vertices.at(6),		normals.at(5),		{ 0.5f, 1.f } },
		//BottomRight_quad					   
		{ vertices.at(5),		normals.at(5),		{ 0.f,  0.f } },
		{ vertices.at(1),		normals.at(5),		{ 1.f,  0.f } },
		{ vertices.at(7),		normals.at(5),		{ 0.5f, 1.f } },

		//back
		{ vertices.at(11),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(7),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(8),		normals.at(0),		{ 0.5f, 1.f } },

		{ vertices.at(11),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(8),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(9),		normals.at(0),		{ 0.5f, 1.f } },

		{ vertices.at(11),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(9),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(10),		normals.at(0),		{ 0.5f, 1.f } },

		{ vertices.at(11),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(10),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(6),		normals.at(0),		{ 0.5f, 1.f } },

		{ vertices.at(11),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(6),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(7),		normals.at(0),		{ 0.5f, 1.f } }, 

	};

	const std::vector<uint32_t> Pentagon_prism_indices
	{
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		12,13,14,					//FrontPentagon
		15,16,17,18,19,20,			//TopRight_quad
		21,22,23,24,25,26,			//TopLeft_quad
		27,28,29,30,31,32,			//BottomLeft_quad
		33,34,35,36,37,38,			//Bottom_quad
		39,40,41,42,43,44,			//BottomRight_quad
		45,46,47,
		48,49,50,
		51,52,53,
		54,55,56,
		57,58,59,					//BackPentgon		

	};

	m_mesh = engine::mesh::create(Pentagon_prism_vertices, Pentagon_prism_indices);


}

engine::Pentagon_prism::~Pentagon_prism() {}

engine::ref<engine::Pentagon_prism> engine::Pentagon_prism::create(std::vector<glm::vec3> vertices)
{
	return std::make_shared<engine::Pentagon_prism>(vertices);
}
