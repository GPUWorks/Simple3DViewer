#include "TexturedOBJMeshloader.h"
#include "GameException.h"
#include "ColorHelper.h"
#include "Camera.h"
#include "Utility.h"
#include "ShaderProgram.h"
#include "VectorHelper.h"
#include "Model.h"
#include "ModelMaterial.h"
#include "Mesh.h"
#include "SOIL.h"
#include <sstream>
#include  <codecvt>
#include "Light.h"

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

#ifdef __APPLE__
const std::string game_content = "/Users/williamnguatem/projects/LODViewer/game_content";
#endif

#ifdef WIN32
const std::string game_content = "C:/williamnguatem/Projects/Simple3DViewer/game_content";
#endif
//
//std::string s2ws1(const std::string& str)
//{
//    typedef std::codecvt_utf8<wchar_t> convert_typeX;
//    std::string_convert<convert_typeX, wchar_t> converterX;
//    
//    return converterX.from_bytes(str);
//}
//
//std::string ws2s1(const std::string& wstr)
//{
//    typedef std::codecvt_utf8<wchar_t> convert_typeX;
//    std::string_convert<convert_typeX, wchar_t> converterX;
//    
//    return converterX.to_bytes(wstr);
//}
//
//
//void readAllImages1(const std::string &im_dir, std::vector<std::string> &img_file_names_)
//{
//    std::string ext1(".JPG");
//    std::string ext2(".jpg");
//    std::string ext3(".png");
//    
//    boost::filesystem::path img_dir(im_dir);
//    std::vector<std::string> img_file_names;
//    if (!boost::filesystem::exists(im_dir)) return;
//    if (boost::filesystem::is_directory(im_dir))
//    {
//        //boost::filesystem::recursive_directory_iterator it(root_postives);
//        //boost::filesystem::recursive_directory_iterator endit;
//        boost::filesystem::directory_iterator it(im_dir);
//        boost::filesystem::directory_iterator endit;
//        while (it != endit)
//        {
//            if (boost::filesystem::is_regular_file(*it) && (it->path().extension() == ext1 || it->path().extension() == ext2 || it->path().extension() == ext3))
//            {
//                img_file_names.push_back(it->path().string());
//            }
//            ++it;
//        }
//    }
//    std::sort(img_file_names.begin(), img_file_names.end());
//    img_file_names_ = img_file_names;
//}
//
//
//
//void LoadFaces1(const std::string g_dir, const std::string &filename, std::vector <Face1> &faces, std::vector<unsigned int> &img_nr)
//{
//    std::ifstream input(filename.c_str());
//    
//    if (!input) {
//        std::cerr << "Error opening " << filename << std::endl;
//        exit(1);
//    }
//    
//    size_t num_faces, num_images;
//    
//    input >> num_faces >> num_images;
//    
//    //g_colours.resize(num_images);
//    
//    //for (size_t i = 0; i < num_images; i++) {
//    //	g_colours[i].r = 55 + 200 * (rand() / (1.0 + RAND_MAX));
//    //	g_colours[i].g = 55 + 200 * (rand() / (1.0 + RAND_MAX));
//    //	g_colours[i].b = 55 + 200 * (rand() / (1.0 + RAND_MAX));
//    //}
//    
//    //g_tex.resize(num_images);
//    //glGenTextures(num_images, &g_tex[0]);
//    //assert(glGetError() == GL_NO_ERROR);
//    
//    //for (size_t i = 0; i < num_images; i++) {
//    //	char file[1024];
//    
//    //	// Check if downsample exist
//    //	//sprintf(file, "%s/%08ds.jpg", g_dir.c_str(), (int)i);
//    
//    //	cv::Mat img = cv::imread(img_file_names.at(i));
//    
//    //	if (!img.data) {
//    //		// Check if original image exist
//    //		// sprintf(file, "%s/%08d.jpg", g_dir.c_str(), (int)i);
//    //		img = cv::imread(img_file_names.at(i));
//    
//    //		if (!img.data) {
//    //			cerr << "Can't find " << file << endl;
//    //			exit(1);
//    //		}
//    
//    //		if (img.cols > DOWNSAMPLE_WIDTH) {
//    //			int new_width = DOWNSAMPLE_WIDTH;
//    //			int new_height = img.rows * DOWNSAMPLE_WIDTH / img.cols;
//    
//    //			cv::resize(img, img, cv::Size(new_width, new_height));
//    
//    //			sprintf(file, "%s/%08ds.jpg", g_dir.c_str(), (int)i);
//    //			cv::imwrite(file, img);
//    
//    //			cout << "Creating down sample image" << endl;
//    //		}
//    //	}
//    
//    //	cout << "Loading " << file << endl;
//    
//    //	cv::flip(img, img, 0);
//    //	glBindTexture(GL_TEXTURE_2D, g_tex[i]);
//    //	assert(glGetError() == GL_NO_ERROR);
//    
//    //	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.cols, img.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
//    //	assert(glGetError() == GL_NO_ERROR);
//    //	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    //	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    //}
//    
//    faces.resize(num_faces);
//    
//    img_nr.reserve(num_faces);
//    for (size_t i = 0; i < num_faces; i++) {
//        for (int j = 0; j < 3; j++) {
//            input >> faces[i].x[j];
//            input >> faces[i].y[j];
//            input >> faces[i].z[j];
//        }
//        
//        input >> faces[i].image_num;
//        
//        img_nr.push_back(faces[i].image_num);
//        
//        for (int j = 0; j < 3; j++) {
//            input >> faces[i].u[j];
//            input >> faces[i].v[j];
//        }
//    }
//    
//    std::sort(img_nr.begin(), img_nr.end());
//    auto last = std::unique(img_nr.begin(), img_nr.end());
//    // v now holds {1 2 3 4 5 6 7 x x x x x x}, where 'x' is indeterminate
//    img_nr.erase(last, img_nr.end());
//    
//}

using namespace glm;

namespace Rendering
{
    //RTTI_DEFINITIONS(TexturedQuad)
    
    const std::string TexturedOBJMeshloader::FilteringModeNames[] =
    {
        "FilteringModePoint",
        "FilteringModeLinear",
        "FilteringModePointMipMapPoint",
        "FilteringModeLinearMipMapPoint",
        "FilteringModePointMipMapLinear",
        "FilteringModeTriLinear",
    };
    
    TexturedOBJMeshloader::TexturedOBJMeshloader(Game& game, Camera& camera)
    : DrawableGameComponent(game, camera), mShaderProgram(), mVertexArrayObject(0), mVertexBuffer(0), m_faces(0),
    mIndexBuffer(0), mWorldViewProjectionLocation(-1), mWorldMatrix(), mIndexCount(), mColorTexture(0),
    mTextureSamplers(), mTextureSamplersByFilteringMode(), mActiveFilteringMode(FilteringModePoint), mKeyboardHandler(nullptr), mAmbientLight(nullptr)
    {
 //       // Load the model
 //       std::unique_ptr<Model> model(new Model(*mGame, "", true));
 //       // Create the vertex and index buffers
 ////       Mesh* mesh = model->Meshes().at(i);
 //       mMesh = *model->Meshes().at(0);
    }

//    TexturedOBJMeshloader::TexturedOBJMeshloader(Game& game, Camera& camera)
//    : DrawableGameComponent(game, camera), mShaderProgram(), mVertexArrayObject(0), mVertexBuffer(0), m_faces(0),
//    mIndexBuffer(0), mWorldViewProjectionLocation(-1), mWorldMatrix(), mIndexCount(), mColorTexture(0),
//    mTextureSamplers(), mTextureSamplersByFilteringMode(), mActiveFilteringMode(FilteringModePoint), mKeyboardHandler(nullptr), mAmbientLight(nullptr)
//    {
////        mMesh = (meshData);
////        mTextureFilename =(textureFilename);
//    }
    
    
    TexturedOBJMeshloader::~TexturedOBJMeshloader()
    {
        DeleteObject(mAmbientLight);
        mGame->RemoveKeyboardHandler(mKeyboardHandler);
        glDeleteSamplers(mTextureSamplers.size(), &mTextureSamplers[0]);
        
        for (size_t i = 0; i < mIndexCount.size(); i++)
        {
            glDeleteTextures(1, &mColorTexture[i]);
            glDeleteBuffers(1, &mIndexBuffer[i]);
            glDeleteBuffers(1, &mVertexBuffer[i]);
            //glDeleteVertexArrays(1, &mVertexArrayObject[i]);
        }
    }
    
    void TexturedOBJMeshloader::ReOrderVetexBuffer(const std::vector<Face1> &faces, const std::vector<unsigned int> &img_nr, std::vector<unsigned int> &nr_p_img, std::vector<VertexPositionTexture> &vertices, std::vector<unsigned int> &ids)
    {
        int idx = 0;
        for (size_t i = 0; i < img_nr.size(); i++)
        {
            int nr_verts_on_im = 0;
            for (size_t f = 0; f < faces.size(); f++)
            {
                if (faces.at(f).image_num == img_nr.at(i))
                {
                    for (int j = 0; j < 3; j++)
                    {
                        float u = faces[f].u[j];
                        float v = faces[f].v[j];
                        float x = faces[f].x[j];
                        float y = faces[f].y[j];
                        float z = faces[f].z[j];
                        
                        VertexPositionTexture tmp(vec4(x, y, z, 1.0f), vec2(u, v));
                        vertices.push_back(tmp);
                        ids.push_back(idx);
                        idx++;
                        nr_verts_on_im++;
                    }
                }
            }
            nr_p_img.push_back(nr_verts_on_im);
        }
    }
    
    void TexturedOBJMeshloader::Initialize()
    {
        // SetCurrentDirectory(Utility::ExecutableDirectory().c_str());
        
        // Build the shader program
        std::vector<ShaderDefinition> shaders;
        //   shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER, "FilteringModesDemo.vert"));
        //   shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER, "FilteringModesDemo.frag"));
		shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER, game_content + "/AmbientLightingDemo.vert"));
		shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER, game_content + "/AmbientLightingDemo.frag"));
		//shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER, game_content + "/FilteringModesDemo.vert"));
		//shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER, game_content + "/FilteringModesDemo.frag"));
		mShaderProgram.BuildProgram(shaders);
        
        float size = 10.0f;
        float halfSize = size / 2.0f;
        
        //// Create the vertex buffer
        //VertexPositionTexture vertices[] =
        //{
        //	VertexPositionTexture(vec4(-halfSize, 1.0f, 0.0, 1.0f), vec2(0.0f, 1.0f)),
        //	VertexPositionTexture(vec4(-halfSize, size + 1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
        //	VertexPositionTexture(vec4(halfSize, size + 1.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)),
        //	VertexPositionTexture(vec4(halfSize, 1.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f))
        //};
        
        std::vector<VertexPositionTexture> vertices;
 








//        std::string mesh_file("/Volumes/Volume/DataSet/LODGEN/trainingData/data101/3.obj");
////        std::string points_file("/Volumes/Volume/DataSet/LODGEN/trainingData/data101/3.point");
//        std::string g_dir("/Volumes/Volume/DataSet/LODGEN/trainingData/data101");
//        
//        // Load the model
//        std::unique_ptr<Model> model(new Model(*mGame, mesh_file, true));
//        
//        // Create the vertex and index buffers
//        Mesh* mesh = model->Meshes().at(6);
        GLuint tmpvertexBuffer;
        CreateVertexBuffer(*mMesh, tmpvertexBuffer);
        mVertexBuffer.push_back(tmpvertexBuffer);
        GLuint tmpIdxBuffer;
        mMesh->CreateIndexBuffer(tmpIdxBuffer);
        mIndexBuffer.push_back(tmpIdxBuffer);
        mIndexCount.push_back(mMesh->Indices().size());
        
//        std::vector<std::string> img_file_names_;
//        readAllImages1(g_dir, img_file_names_);
//        
        std::vector<unsigned int> img_nr;
//        LoadFaces1(g_dir, mesh_file, m_faces, img_nr);
//        
        m_img_nr = img_nr;
//        //  m_img_nr.resize(1);
//        //img_nr.resize(1);
//        std::vector<unsigned int> ids;
//        std::vector<unsigned int> nr_p_img;
//        ReOrderVetexBuffer(m_faces, img_nr, nr_p_img, vertices, ids);
//        CreateVertexBuffer(vertices, nr_p_img, mVertexBuffer);
        
        //// Create the index buffer
        //unsigned int indices[] =
        //{
        //	0, 2, 1,
        //	0, 3, 2
        //};
        
//        //mIndexCount = sizeof(indices) / sizeof(unsigned int);
//        mIndexBuffer.resize(nr_p_img.size());
//        mIndexCount.resize(m_img_nr.size());
//        CreateIndexBuffer(ids, nr_p_img, mIndexBuffer);
        
        // Find the WVP uniform location
        mWorldViewProjectionLocation = glGetUniformLocation(mShaderProgram.Program(), "WorldViewProjection");
        if (mWorldViewProjectionLocation == -1)
        {
            throw GameException("glGetUniformLocation() did not find uniform location.");
        }
        
        
		mAmbientColorLocation = glGetUniformLocation(mShaderProgram.Program(), "AmbientColor");
		if (mAmbientColorLocation == -1)
		{
			throw GameException("glGetUniformLocation() did not find uniform location.");
		}
        
		//std::string img_filename = "C:/williamnguatem/Projects/Simple3DViewer/game_content/EarthComposite.jpg";
		//std::string img_filename = "M:/DataSet/LODGEN/trainingData/data101/3039.jpg";
        
        mColorTexture.resize(mIndexBuffer.size());
        for (size_t i = 0; i < mIndexBuffer.size(); i++)
        {
            // Load the texture
//  std::map<TextureType, std::vector<std::string>*> tmp_tex_file =  mesh->GetMaterial()->Textures();
//            
//            std::string text_filename ;
//            for (std::pair<TextureType, std::vector<std::string>*> textures : tmp_tex_file)
//            {
//               text_filename = textures.second->at(0);
//               //text_filename = *(textures.second);
//            }
            
           std::string img_filename = mTextureFilename ;
            mColorTexture[i] = SOIL_load_OGL_texture(img_filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB);
            if (mColorTexture[i] == 0)
            {
                throw GameException("SOIL_load_OGL_texture() failed.");
            }
            
            //        int img_width1, img_height1;
            //        unsigned char* img1 = SOIL_load_image("EarthComposite.jpg", &img_width1, &img_height1, NULL, 0);
            //        glGenTextures(1, &mColorTexture);
            //        glBindTexture(GL_TEXTURE_2D, mColorTexture);
            //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            //        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width1, img_height1, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
            
        }
        
        
        
        
        // Configure the texture samplers
        mTextureSamplers.resize(FilteringModeEnd);
        glGenSamplers(mTextureSamplers.size(), &mTextureSamplers[0]);
        
        for (FilteringMode mode = (FilteringMode)0; mode < FilteringModeEnd; mode = (FilteringMode)(mode + 1))
        {
            mTextureSamplersByFilteringMode[mode] = mTextureSamplers[mode];
        }
        
        glSamplerParameteri(mTextureSamplersByFilteringMode[FilteringModePoint], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glSamplerParameteri(mTextureSamplersByFilteringMode[FilteringModePoint], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glSamplerParameteri(mTextureSamplersByFilteringMode[FilteringModeLinear], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glSamplerParameteri(mTextureSamplersByFilteringMode[FilteringModeLinear], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glSamplerParameteri(mTextureSamplersByFilteringMode[FilteringModePointMipMapPoint], GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glSamplerParameteri(mTextureSamplersByFilteringMode[FilteringModePointMipMapPoint], GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        
        glSamplerParameteri(mTextureSamplersByFilteringMode[FilteringModeLinearMipMapPoint], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glSamplerParameteri(mTextureSamplersByFilteringMode[FilteringModeLinearMipMapPoint], GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        
        glSamplerParameteri(mTextureSamplersByFilteringMode[FilteringModePointMipMapLinear], GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glSamplerParameteri(mTextureSamplersByFilteringMode[FilteringModePointMipMapLinear], GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        
        glSamplerParameteri(mTextureSamplersByFilteringMode[FilteringModeTriLinear], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glSamplerParameteri(mTextureSamplersByFilteringMode[FilteringModeTriLinear], GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        
        mVertexArrayObject.resize(mIndexBuffer.size());
        
        for (size_t i = 0; i < mIndexBuffer.size(); i++)
        {
            // Create the vertex array object
            glGenVertexArrays(1, &mVertexArrayObject[i]);
            glBindVertexArray(mVertexArrayObject[i]);
            
            glVertexAttribPointer(VertexAttributePosition, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTexture), (void*)offsetof(VertexPositionTexture, Position));
            glEnableVertexAttribArray(VertexAttributePosition);
            
            glVertexAttribPointer(VertexAttributeTextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTexture), (void*)offsetof(VertexPositionTexture, TextureCoordinates));
            glEnableVertexAttribArray(VertexAttributeTextureCoordinate);
        }
        glBindVertexArray(0);
        
        // Attach the keyboard handler
        using namespace std::placeholders;
        mKeyboardHandler = std::bind(&TexturedOBJMeshloader::OnKey, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        mGame->AddKeyboardHandler(mKeyboardHandler);
        
#if defined(DEBUG) || defined(_DEBUG)
        OutputFilteringMode();
#endif
        
        mAmbientLight = new Light(*mGame);
    }
    
    void TexturedOBJMeshloader::Update(const GameTime& gameTime)
    {
        UpdateAmbientLight(gameTime);
    }
    
    void TexturedOBJMeshloader::UpdateAmbientLight(const GameTime& gameTime)
    {
        static float ambientIntensity = 1.0f;
        //static float test_scalar = 0.10f;
        
        if (glfwGetKey(mGame->Window(), GLFW_KEY_L) && ambientIntensity < 1.0f)
        {
            ambientIntensity += (float)gameTime.ElapsedGameTime() / 50.0f;
            ambientIntensity = min(ambientIntensity, 1.0f);
            
            mAmbientLight->SetColor(vec4((vec3)ambientIntensity, 1.0f));
        }
        
        if (glfwGetKey(mGame->Window(), GLFW_KEY_O) && ambientIntensity > 0.0f)
        {
            ambientIntensity -= (float)gameTime.ElapsedGameTime() / 50.0f;
            ambientIntensity = max(ambientIntensity, 0.0f);
            
            mAmbientLight->SetColor(vec4((vec3)ambientIntensity, 1.0f));
        }
    }
    
    
    void TexturedOBJMeshloader::Draw(const GameTime& gameTime)
    {
       
        for (size_t i = 0; i <  mIndexBuffer.size(); i++)
        {
            glBindVertexArray(mVertexArrayObject[i]);
            glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer[i]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer[i]);
            glBindTexture(GL_TEXTURE_2D, mColorTexture[i]);
            
			glBindSampler(0, mTextureSamplersByFilteringMode[mActiveFilteringMode]);

			glUseProgram(mShaderProgram.Program());

			//mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
			//glUniformMatrix4fv(mWorldViewProjectionLocation, 1, GL_FALSE, &wvp[0][0]);

            //glBindSampler(0, mTextureSamplersByFilteringMode[mActiveFilteringMode]);
            //
            //glUseProgram(mShaderProgram.Program());
            //
			mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
			glUniformMatrix4fv(mWorldViewProjectionLocation, 1, GL_FALSE, &wvp[0][0]);
			glUniform4fv(mAmbientColorLocation, 1, &mAmbientLight->Color()[0]);

			//mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
			//glUniformMatrix4fv(mWorldViewProjectionLocation, 1, GL_FALSE, &wvp[0][0]);

            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CCW);
            
            glDrawElements(GL_TRIANGLES, mIndexCount[i], GL_UNSIGNED_INT, 0);
            //glDrawElements(GL_LINES, mIndexCount[i], GL_UNSIGNED_INT, 0);
             glBindVertexArray(0);
        }
        //glBindVertexArray(0);
        //glDisableVertexAttribArray(0);
    }
    
    void TexturedOBJMeshloader::CreateVertexBuffer(const std::vector<VertexPositionTexture> &vertices, const std::vector<unsigned int> &nr_ver_per_img, std::vector<GLuint>& vertexBuffer)
    {
        vertexBuffer.resize(m_img_nr.size());
        int ver_count_indx = 0;
        for (size_t i = 0; i < m_img_nr.size(); i++)
        {
            //GLuint vertexCount = sizeof(nr_ver_per_img.at(i)) / sizeof(VertexPositionTexture);
            GLuint vertexCount = nr_ver_per_img.at(i);// / sizeof(VertexPositionTexture);
            glGenBuffers(1, &vertexBuffer[i]);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionTexture) * vertexCount, &vertices[ver_count_indx], GL_STATIC_DRAW);
            ver_count_indx = ver_count_indx + nr_ver_per_img.at(i);
        }
    }
    
    void TexturedOBJMeshloader::CreateIndexBuffer(const std::vector<unsigned int> &indices, const std::vector<unsigned int> &nr_ver_per_img, std::vector<GLuint>& indexBuffer)
    {
        int ver_count_indx = 0;
        mIndexCount.resize(m_img_nr.size());
        for (size_t i = 0; i < m_img_nr.size(); i++)
        {
            //GLuint indexCount = sizeof(nr_ver_per_img) / sizeof(unsigned int);
            GLuint indexCount = nr_ver_per_img.at(i);// / sizeof(unsigned int);
            glGenBuffers(1, &indexBuffer[i]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, &indices[ver_count_indx], GL_STATIC_DRAW);
            ver_count_indx = ver_count_indx + nr_ver_per_img.at(i);
            mIndexCount[i] = sizeof(unsigned int) * indexCount;
        }
    }
    
    void TexturedOBJMeshloader::CreateVertexBuffer(const Mesh& mesh, GLuint& tmpvertexBuffer) const
    {
        const std::vector<vec3>& sourceVertices = mesh.Vertices();
        
        std::vector<VertexPositionTexture> vertices;
        vertices.reserve(sourceVertices.size());
        
        std::vector<vec3>* textureCoordinates = mesh.TextureCoordinates().at(0);
        assert(textureCoordinates->size() == sourceVertices.size());
        
        const std::vector<vec3>& normals = mesh.Normals();
        //assert(normals.size() == sourceVertices.size());
        
        for (unsigned int i = 0; i < sourceVertices.size(); i++)
        {
            vec3 position = sourceVertices.at(i);
            vec2 uv = (vec2)textureCoordinates->at(i);
            //vec3 normal = normals.at(i);
            vertices.push_back(VertexPositionTexture(vec4(position.x, position.y, position.z, 1.0f), uv));
        }
        
        CreateVertexBuffer(&vertices[0], vertices.size(), tmpvertexBuffer);
    }
    
    void TexturedOBJMeshloader::CreateVertexBuffer(VertexPositionTexture* vertices, GLuint vertexCount, GLuint& tmpvertexBuffer) const
    {
        glGenBuffers(1, &tmpvertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, tmpvertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, VertexSize() * vertexCount, &vertices[0], GL_STATIC_DRAW);
    }
    
    unsigned int TexturedOBJMeshloader::VertexSize() const
    {
        return sizeof(VertexPositionTexture);
    }
    
     
    
    void TexturedOBJMeshloader::OnKey(int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        {
            FilteringMode activeMode = FilteringMode(mActiveFilteringMode + 1);
            if (activeMode >= FilteringModeEnd)
            {
                activeMode = (FilteringMode)(0);
            }
            
            mActiveFilteringMode = activeMode;
            
#if defined(DEBUG) || defined(_DEBUG)
            OutputFilteringMode();
#endif
        }
    }
    
    void TexturedOBJMeshloader::OutputFilteringMode()
    {
        std::wostringstream message;
        message << "Active Filtering Mode: " << FilteringModeNames[mActiveFilteringMode].c_str() << "\n";
        //OutputDebugString(message.str().c_str());
    }
}