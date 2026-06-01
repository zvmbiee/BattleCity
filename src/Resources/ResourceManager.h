#pragma once
#ifndef BATTLECITY_RESOURCEMANAGER_H
#define BATTLECITY_RESOURCEMANAGER_H

#include <iostream>
#include <memory>
#include <map>
#include <sstream>
#include <fstream>
#include "../Renderer/ShaderProgram.h"

class ResourceManager {
public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);

private:
	const std::string getFileString(const std::string& relativeFilePath) const;

	using ShaderProgramsMap = std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>>;
	ShaderProgramsMap m_shaderPrograms;

	std::string m_path;
};


#endif BATTLECITY_RESOURCEMANAGER_H