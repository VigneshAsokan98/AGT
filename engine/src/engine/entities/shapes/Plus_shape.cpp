#include "pch.h"
#include "Plus_shape.h"
#include <engine.h>		

engine::Plus_shape::Plus_shape(std::vector<glm::vec3> vertices) : m_vertices(vertices)
{

	std::vector<glm::vec3> normals;

	//Top_normal n0
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(2), vertices.at(0) - vertices.at(1)));

	//Left_normal n1
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(4), vertices.at(0) - vertices.at(3)));

	//Bottom_normal n2
	normals.push_back(glm::cross(vertices.at(7) - vertices.at(8), vertices.at(7) - vertices.at(21)));

	//Right_normal n3
	normals.push_back(glm::cross(vertices.at(10) - vertices.at(19), vertices.at(10) - vertices.at(18)));

	//Front_normal n4
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(14), vertices.at(0) - vertices.at(5)));

	glm::vec3 m_half_extents = glm::vec3(1.f, 1.f, 1.f);

	std::vector<mesh::vertex> Pentagon_prism_vertices
	{
		//Top_quad
		{ vertices.at(0),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(2),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(1),		normals.at(0),		{ 0.5f, 1.f } },
		//Top_quad
		{ vertices.at(0),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(3),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(2),		normals.at(0),		{ 0.5f, 1.f } },

		//Left_quad
		{ vertices.at(0),		normals.at(1),		{ 0.f,  0.f } },
		{ vertices.at(4),		normals.at(1),		{ 1.f,  0.f } },
		{ vertices.at(3),		normals.at(1),		{ 0.5f, 1.f } },
		//Left_quad				   
		{ vertices.at(0),		normals.at(1),		{ 0.f,  0.f } },
		{ vertices.at(5),		normals.at(1),		{ 1.f,  0.f } },
		{ vertices.at(4),		normals.at(1),		{ 0.5f, 1.f } },

		//LeftTop_quad
		{ vertices.at(4),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(6),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(23),		normals.at(0),		{ 0.5f, 1.f } },										   
		//LeftTop_quad1				   
		{ vertices.at(4),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(5),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(6),		normals.at(0),		{ 0.5f, 1.f } },

		//Leftside_quad
		{ vertices.at(6),		normals.at(1),		{ 0.f,  0.f } },
		{ vertices.at(22),		normals.at(1),		{ 1.f,  0.f } },
		{ vertices.at(23),		normals.at(1),		{ 0.5f, 1.f } },
		//Leftside_quad					   
		{ vertices.at(6),		normals.at(1),		{ 0.f,  0.f } },
		{ vertices.at(7),		normals.at(1),		{ 1.f,  0.f } },
		{ vertices.at(22),		normals.at(1),		{ 0.5f, 1.f } },


		//LeftBottom_quad					   
		{ vertices.at(7),		normals.at(2),		{ 0.f,  0.f } },
		{ vertices.at(8),		normals.at(2),		{ 1.f,  0.f } },
		{ vertices.at(21),		normals.at(2),		{ 0.5f, 1.f } },
		//LeftBottom_quad					   
		{ vertices.at(7),		normals.at(2),		{ 0.f,  0.f } },
		{ vertices.at(21),		normals.at(2),		{ 1.f,  0.f } },
		{ vertices.at(22),		normals.at(2),		{ 0.5f, 1.f } },

		//LeftBottomSide_quad					   
		{ vertices.at(8),		normals.at(1),		{ 0.f,  0.f } },
		{ vertices.at(9),		normals.at(1),		{ 1.f,  0.f } },
		{ vertices.at(20),		normals.at(1),		{ 0.5f, 1.f } },
		//LeftBottomSide_quad					   
		{ vertices.at(8),		normals.at(1),		{ 0.f,  0.f } },
		{ vertices.at(20),		normals.at(1),		{ 1.f,  0.f } },
		{ vertices.at(21),		normals.at(1),		{ 0.5f, 1.f } },

		//Bottom_quad					   
		{ vertices.at(9),		normals.at(2),		{ 0.f,  0.f } },
		{ vertices.at(10),		normals.at(2),		{ 1.f,  0.f } },
		{ vertices.at(19),		normals.at(2),		{ 0.5f, 1.f } },
		//Bottom_quad					   
		{ vertices.at(9),		normals.at(2),		{ 0.f,  0.f } },
		{ vertices.at(19),		normals.at(2),		{ 1.f,  0.f } },
		{ vertices.at(20),		normals.at(2),		{ 0.5f, 1.f } },

		//RightBottomSide_quad					   
		{ vertices.at(10),		normals.at(3),		{ 0.f,  0.f } },
		{ vertices.at(18),		normals.at(3),		{ 1.f,  0.f } },
		{ vertices.at(19),		normals.at(3),		{ 0.5f, 1.f } },
		//RightBottomSide_quad					   
		{ vertices.at(10),		normals.at(3),		{ 0.f,  0.f } },
		{ vertices.at(11),		normals.at(3),		{ 1.f,  0.f } },
		{ vertices.at(18),		normals.at(3),		{ 0.5f, 1.f } },

		//RightBottom_quad					   
		{ vertices.at(11),		normals.at(2),		{ 0.f,  0.f } },
		{ vertices.at(12),		normals.at(2),		{ 1.f,  0.f } },
		{ vertices.at(17),		normals.at(2),		{ 0.5f, 1.f } },
		//RightBottom_quad					  
		{ vertices.at(11),		normals.at(2),		{ 0.f,  0.f } },
		{ vertices.at(17),		normals.at(2),		{ 1.f,  0.f } },
		{ vertices.at(18),		normals.at(2),		{ 0.5f, 1.f } },

		//RightSide_quad					   
		{ vertices.at(12),		normals.at(3),		{ 0.f,  0.f } },
		{ vertices.at(16),		normals.at(3),		{ 1.f,  0.f } },
		{ vertices.at(17),		normals.at(3),		{ 0.5f, 1.f } },
		//Rightside_quad					  
		{ vertices.at(12),		normals.at(3),		{ 0.f,  0.f } },
		{ vertices.at(13),		normals.at(3),		{ 1.f,  0.f } },
		{ vertices.at(16),		normals.at(3),		{ 0.5f, 1.f } },

		//RightTop_quad					   
		{ vertices.at(14),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(16),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(13),		normals.at(0),		{ 0.5f, 1.f } },
		//RightTop_quad					   
		{ vertices.at(14),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(15),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(16),		normals.at(0),		{ 0.5f, 1.f } },

		//Right_quad					   
		{ vertices.at(2),		normals.at(3),		{ 0.f,  0.f } },
		{ vertices.at(15),		normals.at(3),		{ 1.f,  0.f } },
		{ vertices.at(14),		normals.at(3),		{ 0.5f, 1.f } },
		//Right_quad					   
		{ vertices.at(2),		normals.at(3),		{ 0.f,  0.f } },
		{ vertices.at(14),		normals.at(3),		{ 1.f,  0.f } },
		{ vertices.at(1),		normals.at(3),		{ 0.5f, 1.f } },

		//Frontttop_quad					   
		{ vertices.at(0),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(1),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(14),		normals.at(4),		{ 0.5f, 1.f } },
		//Fronttop_quad					   
		{ vertices.at(0),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(14),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(5),		normals.at(4),		{ 0.5f, 1.f } },

		//FrontLeft_quad					   
		{ vertices.at(6),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(8),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(7),		normals.at(4),		{ 0.5f, 1.f } },
		//FrontLeft_quad					   
		{ vertices.at(6),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(5),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(8),		normals.at(4),		{ 0.5f, 1.f } },

		//Frontbottom_quad					   
		{ vertices.at(9),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(11),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(10),		normals.at(4),		{ 0.5f, 1.f } },
		//Frontbottom_quad					   
		{ vertices.at(9),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(8),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(11),		normals.at(4),		{ 0.5f, 1.f } },

		//FrontRight_quad					   
		{ vertices.at(11),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(13),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(12),		normals.at(4),		{ 0.5f, 1.f } },
		//FrontRight_quad					   
		{ vertices.at(11),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(14),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(13),		normals.at(4),		{ 0.5f, 1.f } },

		//Frontcenter_quad					   
		{ vertices.at(5),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(14),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(11),		normals.at(4),		{ 0.5f, 1.f } },
		//Frontcenter_quad					   
		{ vertices.at(5),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(11),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(8),		normals.at(4),		{ 0.5f, 1.f } },

		//Backtop_quad					   
		{ vertices.at(2),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(4),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(15),		normals.at(4),		{ 0.5f, 1.f } },
		//Backtop_quad					   
		{ vertices.at(2),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(3),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(4),		normals.at(4),		{ 0.5f, 1.f } },

		//BackLeft_quad					   
		{ vertices.at(4),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(22),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(21),		normals.at(4),		{ 0.5f, 1.f } },
		//BackLeft_quad					   
		{ vertices.at(4),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(23),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(22),		normals.at(4),		{ 0.5f, 1.f } },

		//Backbottom_quad					   
		{ vertices.at(18),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(20),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(19),		normals.at(4),		{ 0.5f, 1.f } },
		//Backbottom_quad					   
		{ vertices.at(18),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(21),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(20),		normals.at(4),		{ 0.5f, 1.f } },

		//BackRight_quad					   
		{ vertices.at(16),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(18),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(17),		normals.at(4),		{ 0.5f, 1.f } },
		//BackRight_quad					   
		{ vertices.at(16),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(15),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(18),		normals.at(4),		{ 0.5f, 1.f } },

		//backcenter_quad					   
		{ vertices.at(15),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(21),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(18),		normals.at(4),		{ 0.5f, 1.f } },
		//backcenter_quad					   
		{ vertices.at(15),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(4),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(21),		normals.at(4),		{ 0.5f, 1.f } },
	};

	const std::vector<uint32_t> Pentagon_prism_indices
	{
		0,1,2,3,4,5,					//Top_quad
		6,7,8,9,10,11,					//Left_quad
		12,13,14,15,16,17,				//LeftTop_quad
		18,19,20,21,22,23,				//Leftside_quad
		24,25,26,27,28,29,				//LeftBottom_quad
		30,31,32,33,34,35,				//LeftBottomSide_quad
		36,37,38,39,40,41,				//Bottom_quad	
		42,43,44,45,46,47,				//RightBottomSide_quad
		48,49,50,51,52,53,				//RightBottom_quad	
		54,55,56,57,58,59,				//Rightside_quad
		60,61,62,63,64,65,				//RightTop_quad		
		66,67,68,69,70,71,				//Right_quad
		72,73,74,75,76,77,				//Fronttop_quad		
		78,79,80,81,82,83,				//FrontLeft_quad
		84,85,86,87,88,89,				//Frontbottom_quad
		90,91,92,93,94,95,				//FrontRight_quad
		96,97,98,99,100,101,			//FrontCenter_quad
		102,103,104,105,106,107,		//Backtop_quad		
		108,109,110,111,112,113,		//BackLeft_quad
		114,115,116,117,118,119,		//Backbottom_quad
		120,121,122,123,124,125,		//BackRight_quad
		126,127,128,129,130,131,		//BackCenter_quad

	};

	m_mesh = engine::mesh::create(Pentagon_prism_vertices, Pentagon_prism_indices);


}

engine::Plus_shape::~Plus_shape() {}

engine::ref<engine::Plus_shape> engine::Plus_shape::create(std::vector<glm::vec3> vertices)
{
	return std::make_shared<engine::Plus_shape>(vertices);
}

