// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ROMEA_LOCALISATION_ODO_PLUGIN__ODO_LOCALISATION_PLUGIN_PARAMETERS_HPP_
#define ROMEA_LOCALISATION_ODO_PLUGIN__ODO_LOCALISATION_PLUGIN_PARAMETERS_HPP_

// std
#include <string>

// ros
#include "rclcpp/node.hpp"

namespace romea
{

void declare_restamping(rclcpp::Node::SharedPtr node);

void declare_controller_topic(rclcpp::Node::SharedPtr node);


bool get_restamping(rclcpp::Node::SharedPtr node);

std::string get_controller_topic(rclcpp::Node::SharedPtr node);

}  // namespace romea

#endif  // ROMEA_LOCALISATION_ODO_PLUGIN__ODO_LOCALISATION_PLUGIN_PARAMETERS_HPP_
