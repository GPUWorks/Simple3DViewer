//******************************************************************************
//\par		Simple3DViewer - Simple Intelligent 3D Object Viewer
//\file		ModelDemo.h
//\author	William Nguatem
//\note		Copyright (C) 
//\note		Bundeswehr University Munich
//\note		Institute of Applied Computer Science
//\note		Chair of Photogrammetry and Remote Sensing
//\note		Neubiberg, Germany
//\since		2015/03/26 
//******************************************************************************/


#ifndef _Model_Demo_H_
#define _Model_Demo_H_

#include "DrawableGameComponent.h"
#include "BasicEffect.h"

#include "Model.h"
#include "Mesh.h"

namespace Library
{
	class Mesh;
}

using namespace Library;

namespace Rendering
{
	class ModelDemo : public DrawableGameComponent
	{
		//RTTI_DECLARATIONS(ModelDemo, DrawableGameComponent)

	public:
		ModelDemo(Game& game, Camera& camera);
		~ModelDemo();

		virtual void Initialize() override;
		virtual void Draw(const GameTime& gameTime) override;
        
        //virtual void setInputData(const std::string &input_data) override;
        void setInputData(const std::string &input_data);
        //{
         //   m_input_data = input_data;
        //}

	private:
		enum VertexAttribute
		{
			VertexAttributePosition = 0,
			VertexAttributeColor = 1
		};

		ModelDemo();
		ModelDemo(const ModelDemo& rhs);
		ModelDemo& operator=(const ModelDemo& rhs);

		void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer);
		void CreateVertexBuffer(const pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud, GLuint& vertexBuffer);

		ShaderProgram mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		GLint mWorldViewProjectionLocation;
		glm::mat4 mWorldMatrix;
		GLuint mIndexCount;

		pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr m_cloud;
        std::string m_input_data;
		std::string mContentFolder;
	};
}
#endif//_Model_Demo_H_
