#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <sstream>
#include <fstream>
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

class ResourceManager {
public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;
	ResourceManager& operator = (ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);
	std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);

private:
	const std::string getFileString(const std::string& relativeFilePath) const;

	using ShaderProgramsMap = std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>>;
	ShaderProgramsMap m_shaderPrograms;

	using TexturesMap = std::map<const std::string, std::shared_ptr<Renderer::Texture2D>>;
	TexturesMap m_textures;

	std::string m_path;
};