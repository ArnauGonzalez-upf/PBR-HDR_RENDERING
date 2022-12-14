#ifndef MATERIAL_H
#define MATERIAL_H

#include "framework.h"
#include "shader.h"
#include "camera.h"
#include "mesh.h"
#include "extra/hdre.h"

class Material {
public:

	Shader* shader = NULL;
	Texture* texture = NULL;
	vec4 color;

	virtual void setUniforms(Camera* camera, Matrix44 model) = 0;
	virtual void render(Mesh* mesh, Matrix44 model, Camera * camera) = 0;
	virtual void renderInMenu() = 0;

	//Added method to change textures
	virtual void setTexture(std::string geometry, int mesh) = 0;
};

class StandardMaterial : public Material {
public:

	StandardMaterial();
	~StandardMaterial();

	void setUniforms(Camera* camera, Matrix44 model);
	void render(Mesh* mesh, Matrix44 model, Camera * camera);
	void renderInMenu();

	//Added method to change textures
	void setTexture(std::string geometry, int mesh);
};

class PhongMaterial : public StandardMaterial {
public:

	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	float shininess;

	PhongMaterial();
	~PhongMaterial();

	void setUniforms(Camera* camera, Matrix44 model);
	void render(Mesh* mesh, Matrix44 model, Camera* camera);
	void renderInMenu();
};

class TexturedMaterial : public StandardMaterial {
public:

	TexturedMaterial();
	~TexturedMaterial();
};

class ReflectiveMaterial : public StandardMaterial {
public:

	ReflectiveMaterial();
	~ReflectiveMaterial();

	void renderInMenu() {}; //Anything to render in menu
};

class SkyboxMaterial : public StandardMaterial {
public:

	//Different HDRe level cubemaps
	Texture* texture_prem_0;
	Texture* texture_prem_1;
	Texture* texture_prem_2;
	Texture* texture_prem_3;
	Texture* texture_prem_4;

	SkyboxMaterial();
	~SkyboxMaterial();

	void renderInMenu() {}; //Anything to render in menu
};

class WireframeMaterial : public StandardMaterial {
public:

	WireframeMaterial();
	~WireframeMaterial();

	void render(Mesh* mesh, Matrix44 model, Camera * camera);
};

class PBRMaterial : public StandardMaterial
{
public:

	//Maps
	Texture* metallic_texture;
	Texture* roughness_texture;

	//Extra maps
	Texture* normal_texture;
	Texture* ao_texture;
	Texture* emissive_texture;
	Texture* opacity_texture;

	//If the metalness and roughness are in the same texture
	bool metallic_roughness;

	//Material factors
	float roughness;
	float metalness;

	PBRMaterial();
	~PBRMaterial();

	void setUniforms(Camera* camera, Matrix44 model);
	void render(Mesh* mesh, Matrix44 model, Camera* camera);
	void renderInMenu();

	//Function to set all the textures
	void setTexture(std::string geometry, int mesh);
};

#endif