#pragma once
#include "../config.h"

unsigned int make_shader_module(const std::string& filepath, unsigned int module_type);

unsigned int make_shader_program(const std::string& vertex_filepath, const std::string& fragment_filepath);