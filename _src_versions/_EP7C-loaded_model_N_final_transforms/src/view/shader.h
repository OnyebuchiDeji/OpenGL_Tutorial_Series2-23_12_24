#pragma once
#include "../config.h"


unsigned int make_shader_module(const std::string& filePath, unsigned int moduleType);

unsigned int make_shader_program(const std::string& vertex_filepath, const std::string& fragment_filepath);
