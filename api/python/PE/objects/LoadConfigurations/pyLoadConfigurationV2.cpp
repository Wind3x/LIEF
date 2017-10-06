/* Copyright 2017 R. Thomas
 * Copyright 2017 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "pyPE.hpp"

#include "LIEF/visitors/Hash.hpp"
#include "LIEF/PE/LoadConfigurations.hpp"

#include <string>
#include <sstream>

template<class T>
using getter_t = T (LoadConfigurationV2::*)(void) const;

template<class T>
using setter_t = void (LoadConfigurationV2::*)(T);

void init_PE_LoadConfigurationV2_class(py::module& m) {
  py::class_<LoadConfigurationV2, LoadConfigurationV1>(m, "LoadConfigurationV2",
    "" RST_CLASS_REF(lief.PE.LoadConfigurationV1) " enhanced with *code integrity*. \n\n"
    "It is associated with the " RST_CLASS_REF(lief.PE.WIN_VERSION) ": "
    ":attr:`~lief.PE.WIN_VERSION.WIN10_0_9879`")
    .def(py::init<>())

    .def_property_readonly("code_integrity",
        static_cast<CodeIntegrity& (LoadConfigurationV2::*)(void)>(&LoadConfigurationV2::code_integrity),
        "" RST_CLASS_REF(lief.PE.CodeIntegrity) " object",
        py::return_value_policy::reference)


    .def("__eq__", &LoadConfigurationV2::operator==)
    .def("__ne__", &LoadConfigurationV2::operator!=)
    .def("__hash__",
        [] (const LoadConfigurationV2& config) {
          return LIEF::Hash::hash(config);
        })


    .def("__str__", [] (const LoadConfigurationV2& config)
        {
          std::ostringstream stream;
          stream << config;
          std::string str = stream.str();
          return str;
        });


}
