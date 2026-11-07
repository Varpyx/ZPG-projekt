#include "SceneBuilder.h"

#include <cstdio>
#include <cstdlib>

#include "Models/suzi_smooth.h"
#include "Models/sphere.h"
#include "Models/bushes.h"
#include "Models/login.h"
#include "Models/tree.h"
#include "Models/login2.h"
#include "Models/sun.h"
#include "Models/earth.h"	
#include "Models/moon.h"
#include "Models/clock.h"
#include "Models/plain.h"
#include "Models/plain2.h"
#include "Models/ufo.h"



Material SceneBuilder::createMaterial(ShaderProgram* shaderProgram, const char* path, int textureUnit, glm::vec3 color)
{
	Material material(shaderProgram, color);

	if(path != nullptr)
	{
		Texture texture(path);
		material.setTexture(&texture, textureUnit);
	}

	return material;
}

std::vector<std::unique_ptr<Scene>> SceneBuilder::buildScenes(float aspect)
{
	std::vector<std::unique_ptr<Scene>> scenes;

	// Scene 1: suzi
	Scene* scene1 = scenes.emplace_back(std::make_unique<Scene>(Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), aspect))).get();
	ShaderProgram* mesh1 = scene1->addShaderProgram("shaders/basic.vert", "shaders/basic.frag");
	ShaderProgram* loginShader1 = scene1->addShaderProgram("shaders/basic.vert", "shaders/login.frag");
	scene1->addDrawableObject(
		Model(suziSmooth, sizeof(suziSmooth) / (6 * sizeof(float))), createMaterial(mesh1, nullptr, 0, glm::vec3(1.0f, 0.7f, 0.2f)),
		0.4f, glm::vec3(0.0f), 15.0f, glm::vec3(0.1f, 0.0f, 0.0f));
	scene1->addDrawableObject(
		Model(login2, sizeof(login2) / (6 * sizeof(float))), createMaterial(loginShader1, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)),
		0.1f, glm::vec3(0.8f, -0.8f, 0.0f));

	// Scene 2: sphere
	Scene* scene2 = scenes.emplace_back(std::make_unique<Scene>(Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), aspect))).get();
	ShaderProgram* mesh2 = scene2->addShaderProgram("shaders/basic.vert", "shaders/basic.frag");
	ShaderProgram* loginShader2 = scene2->addShaderProgram("shaders/basic.vert", "shaders/login.frag");
	//scene2->addDrawableObject(Model(sphere, 2880), createMaterial(mesh2, nullptr, 0, glm::vec3(0.4f, 0.6f, 1.0f)), 0.4f, glm::vec3(0.3f, 0.0f, 0.0f));
	scene2->addDrawableObject(
		Model(login2, sizeof(login2) / (6 * sizeof(float))), createMaterial(loginShader2, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)),
		0.1f, glm::vec3(0.8f, -0.8f, 0.0f));

	ShaderProgram* uvShader2 = scene2->addShaderProgram("shaders/uv.vert", "shaders/uv.frag");
	Material uvMaterial = createMaterial(uvShader2, "Textures/wooden_fence.jpg", 0, glm::vec3(1.0f));

	DrawableObject& uvPlane = scene2->addDrawableObject(
		Model(plain2, sizeof(plain2) / (8 * sizeof(float)), 8, true, false, false, true), uvMaterial,
		0.5f, glm::vec3(0.0f, -0.5f, 0.0f));
	uvPlane.addTransformation(std::make_unique<Rotation>(glm::vec3(1.0f, 0.0f, 0.0f), -90.0f));

	auto etp = std::make_unique<CompositeTransformation>();
	etp->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 10.0f));
	etp->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 30.0f));
	etp->addTransformation(std::make_unique<Scale>(0.5f));
	uvPlane.setTransformation(std::move(etp));


	// Scene 3: bushes and trees
	Scene* scene3 = scenes.emplace_back(std::make_unique<Scene>(Camera(glm::vec3(1.0f, 0.5f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), aspect))).get();
	Light* light3 = scene3->addLight(glm::vec3(3.0f, 0.2f, -3.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec4(0.02f, 0.02f, 0.02f, 1.0f));
	ShaderProgram* mesh3 = scene3->addShaderProgram("shaders/basic.vert", "shaders/basic.frag");
	ShaderProgram* flat3 = scene3->addShaderProgram("shaders/basic.vert", "shaders/basic2.frag");
	ShaderProgram* loginShader3 = scene3->addShaderProgram("shaders/basic.vert", "shaders/login.frag");
	ShaderProgram* treeShader = scene3->addShaderProgram("shaders/tree.vert", "shaders/tree.frag");
	ShaderProgram* bushShader = scene3->addShaderProgram("shaders/bush.vert", "shaders/tree.frag");
	ShaderProgram* ambient = scene3->addShaderProgram("shaders/bush.vert", "shaders/diffuse.frag");
	ShaderProgram* clock3 = scene3->addShaderProgram("shaders/clock.vert", "shaders/clock.frag");

	srand(3);
	for (int i = 0; i < 180; i++)
	{
		float bx = 7.0f * rand() / RAND_MAX;
		float bz = 7.0f * rand() / RAND_MAX;
		DrawableObject& bush = scene3->addDrawableObject(Model(bushes, 8730, 6, true, false), createMaterial(bushShader, nullptr, 0, glm::vec3(0.6f, 1.0f, 0.5f)));
		auto bt = std::make_unique<CompositeTransformation>();
		bt->addTransformation(std::make_unique<Translation>(glm::vec3(bx, 0.1f, -bz)));
		bt->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 360.0f * rand() / RAND_MAX));
		bt->addTransformation(std::make_unique<Scale>(0.3f));
		bush.setTransformation(std::move(bt));

		bx = 7.0f * rand() / RAND_MAX;
		bz = 7.0f * rand() / RAND_MAX;

		//get random green
		float r = 0.2f + 0.3f * (rand() / (float)RAND_MAX); // 0.2 - 0.5
		float g = 0.6f + 0.4f * (rand() / (float)RAND_MAX); // 0.6 - 1.0
		float b = 0.1f + 0.2f * (rand() / (float)RAND_MAX); // 0.1 - 0.3
		glm::vec3 randomGreen(r, g, b);

		DrawableObject& trees = scene3->addDrawableObject(Model(tree, 92814, 6, true, false), createMaterial(treeShader, nullptr, 0, randomGreen));
		auto tt = std::make_unique<CompositeTransformation>();
		tt->addTransformation(std::make_unique<Translation>(glm::vec3(bx, 0.1f, -bz)));
		tt->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 360.0f * rand() / RAND_MAX));
		tt->addTransformation(std::make_unique<Scale>(0.05f));
		trees.setTransformation(std::move(tt));

	}
	scene3->addDrawableObject(Model(plain, sizeof(plain) / (6 * sizeof(float))), createMaterial(ambient, nullptr, 0, glm::vec3(0.45f, 0.29f, 0.13f)), 10.0f, glm::vec3(0.0f, 0.1f, 0.0f));

	scene3->addDrawableObject(Model(sphere, 2880), createMaterial(flat3, nullptr, 0, glm::vec3(1.0f, 0.6f, 0.0f)), 0.02f, glm::vec3(3.0f, 0.2f, -3.0f));
	scene3->addDrawableObject(Model(login2, sizeof(login2) / (6 * sizeof(float))), createMaterial(loginShader3, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)), 0.5f, glm::vec3(0.8f, 1.0f, -3.0f));

	DrawableObject& clock1 = scene3->addDrawableObject(Model(clockModel, 44826, 9), createMaterial(clock3, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)), 0.05f, glm::vec3(2.0f, 0.3f, -4.0f));
	clock1.addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f));

	DrawableObject& clock2 = scene3->addDrawableObject(Model(clockModel, 44826, 9), createMaterial(clock3, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)), 0.06f, glm::vec3(3.4f, 0.3f, -3.8f));
	clock2.addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f));

	//Scene 4: login
	Scene* scene4 = scenes.emplace_back(std::make_unique<Scene>(Camera(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), aspect))).get();
	ShaderProgram* loginShader4 = scene4->addShaderProgram("shaders/basic.vert", "shaders/login.frag");
	scene4->addDrawableObject(
		Model(login2, sizeof(login2) / (6 * sizeof(float))), createMaterial(loginShader4, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)),
		1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	//Scene 5: planets
	Scene* scene5 = scenes.emplace_back(std::make_unique<Scene>(Camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f), aspect))).get();
	scene5->addLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
	ShaderProgram* planets5 = scene5->addShaderProgram("shaders/light.vert", "shaders/phong_use_color.frag");
	ShaderProgram* planets_mesh = scene5->addShaderProgram("shaders/basic.vert", "shaders/basic.frag");
	ShaderProgram* login5 = scene5->addShaderProgram("shaders/basic.vert", "shaders/login.frag");

	DrawableObject& Sun = scene5->addDrawableObject(
		Model(sun, 11520, 9), createMaterial(planets_mesh, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)),
		0.2f, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f);


	DrawableObject& Earth = scene5->addDrawableObject(
		Model(earth, 11520, 9, true, true, true), createMaterial(planets5, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)),
		0.1f, glm::vec3(0.0f, 0.0f, 0.0f));

	auto et = std::make_unique<CompositeTransformation>();
	et->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 10.0f));
	et->addTransformation(std::make_unique<Translation>(glm::vec3(-0.7f, 0.0f, 0.0f)));
	et->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 100.0f));
	et->addTransformation(std::make_unique<Scale>(0.1f));
	Earth.setTransformation(std::move(et));

	DrawableObject& Moon = scene5->addDrawableObject(
		Model(moon, 11520, 9, true, true, true), createMaterial(planets5, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)),
		0.05f, glm::vec3(0.0f, 0.0f, 0.0f));

	auto earthPom = std::make_unique<CompositeTransformation>();
	earthPom->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 10.0f));
	earthPom->addTransformation(std::make_unique<Translation>(glm::vec3(-0.7f, 0.0f, 0.0f)));

	auto mt = std::make_unique<CompositeTransformation>();
	mt->addTransformation(std::move(earthPom));
	mt->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 60.0f));
	mt->addTransformation(std::make_unique<Translation>(glm::vec3(-0.2f, 0.0f, 0.0f)));
	mt->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 50.0f));
	mt->addTransformation(std::make_unique<Scale>(0.05f));
	Moon.setTransformation(std::move(mt));

	scene5->addDrawableObject(
		Model(login2, sizeof(login2) / (6 * sizeof(float))), createMaterial(login5, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)),
		0.1f, glm::vec3(0.8f, -0.8f, 0.0f));

	DrawableObject& Ufo = scene5->addDrawableObject(
		Model(ufo, sizeof(ufo) / (9 * sizeof(float)), 9, true, true, false), createMaterial(planets5, nullptr, 0, glm::vec3(0.4f, 0.5f, 1.0f)),
		0.1f, glm::vec3(0.0f, 0.0f, 0.0f));

	auto ut = std::make_unique<CompositeTransformation>();
	ut->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 20.0f));
	ut->addTransformation(std::make_unique<Translation>(glm::vec3(0.4f, 0.0f, 0.0f)));
	ut->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 100.0f));
	ut->addTransformation(std::make_unique<Scale>(0.02f));
	Ufo.setTransformation(std::move(ut));

	//scene 6: clock
	Scene* scene6 = scenes.emplace_back(std::make_unique<Scene>(Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), aspect))).get();
	ShaderProgram* clock6 = scene6->addShaderProgram("shaders/clock.vert", "shaders/clock.frag");
	ShaderProgram* login6 = scene6->addShaderProgram("shaders/basic.vert", "shaders/login.frag");

	scene6->addDrawableObject(
		Model(login2, sizeof(login2) / (6 * sizeof(float))), createMaterial(login6, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)),
		0.1f, glm::vec3(0.8f, -0.8f, 0.0f));

	DrawableObject& clock = scene6->addDrawableObject(
		Model(clockModel, 44826, 9), createMaterial(clock6, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)),
		1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	clock.addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f));


	//scene 7: light
	Scene* scene7 = scenes.emplace_back(std::make_unique<Scene>(Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), aspect))).get();
	scene7->addLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
	ShaderProgram* ball1 = scene7->addShaderProgram("shaders/light.vert", "shaders/diffuse.frag");
	ShaderProgram* ball2 = scene7->addShaderProgram("shaders/light.vert", "shaders/phong.frag");
	ShaderProgram* ball3 = scene7->addShaderProgram("shaders/light.vert", "shaders/ambient.frag");
	ShaderProgram* ball4 = scene7->addShaderProgram("shaders/light.vert", "shaders/blinn.frag");
	ShaderProgram* login7 = scene7->addShaderProgram("shaders/basic.vert", "shaders/login.frag");

	scene7->addDrawableObject(Model(sphere, 2880), createMaterial(ball1, nullptr, 0, glm::vec3(0.385, 0.647, 0.812)), 0.3f, glm::vec3(0.0f, 1.0f, 0.0f));
	scene7->addDrawableObject(Model(sphere, 2880), createMaterial(ball2, nullptr, 0, glm::vec3(0.385, 0.647, 0.812)), 0.3f, glm::vec3(1.0f, 0.0f, 0.0f));
	scene7->addDrawableObject(Model(sphere, 2880), createMaterial(ball3, nullptr, 0, glm::vec3(0.385, 0.647, 0.812)), 0.3f, glm::vec3(0.0f, -1.0f, 0.0f));
	scene7->addDrawableObject(Model(sphere, 2880), createMaterial(ball4, nullptr, 0, glm::vec3(0.385, 0.647, 0.812)), 0.3f, glm::vec3(-1.0f, 0.0f, 0.0f));
	scene7->addDrawableObject(Model(login2, sizeof(login2) / (6 * sizeof(float))), createMaterial(login7, nullptr, 0, glm::vec3(1.0f, 1.0f, 1.0f)), 0.3f, glm::vec3(1.8f, -0.8f, 0.0f));

	printf("Created %zu scenes, change them with 1-%zu\n", scenes.size(), scenes.size());

	return scenes;
}