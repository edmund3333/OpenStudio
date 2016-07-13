/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#include "EnergyManagementSystemActuator.hpp"
#include "EnergyManagementSystemActuator_Impl.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_EnergyManagementSystem_Actuator_FieldEnums.hxx>

#include "../utilities/core/Assert.hpp"

namespace openstudio {
namespace model {

namespace detail {

  EnergyManagementSystemActuator_Impl::EnergyManagementSystemActuator_Impl(const IdfObject& idfObject,
                                                                           Model_Impl* model,
                                                                           bool keepHandle)
    : ModelObject_Impl(idfObject,model,keepHandle)
  {
    OS_ASSERT(idfObject.iddObject().type() == EnergyManagementSystemActuator::iddObjectType());
  }

  EnergyManagementSystemActuator_Impl::EnergyManagementSystemActuator_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                           Model_Impl* model,
                                                                           bool keepHandle)
    : ModelObject_Impl(other,model,keepHandle)
  {
    OS_ASSERT(other.iddObject().type() == EnergyManagementSystemActuator::iddObjectType());
  }

  EnergyManagementSystemActuator_Impl::EnergyManagementSystemActuator_Impl(const EnergyManagementSystemActuator_Impl& other,
                                                                           Model_Impl* model,
                                                                           bool keepHandle)
    : ModelObject_Impl(other,model,keepHandle)
  {}

  const std::vector<std::string>& EnergyManagementSystemActuator_Impl::outputVariableNames() const
  {
    static std::vector<std::string> result;
    if (result.empty()){
    }
    return result;
  }

  IddObjectType EnergyManagementSystemActuator_Impl::iddObjectType() const {
    return EnergyManagementSystemActuator::iddObjectType();
  }

  std::string EnergyManagementSystemActuator_Impl::actuatedComponentName() const {
    boost::optional<std::string> value = getString(OS_EnergyManagementSystem_ActuatorFields::ActuatedComponentName,true);
    OS_ASSERT(value);
    return value.get();
  }

  std::string EnergyManagementSystemActuator_Impl::actuatedComponentControlType() const {
    boost::optional<std::string> value = getString(OS_EnergyManagementSystem_ActuatorFields::ActuatedComponentControlType,true);
    OS_ASSERT(value);
    return value.get();
  }

  void EnergyManagementSystemActuator_Impl::setActuatedComponentName(const std::string& actuatedComponentName) {
    bool result = setString(OS_EnergyManagementSystem_ActuatorFields::ActuatedComponentName, actuatedComponentName);
    OS_ASSERT(result);
  }

  void EnergyManagementSystemActuator_Impl::setActuatedComponentControlType(const std::string& actuatedComponentControlType) {
    bool result = setString(OS_EnergyManagementSystem_ActuatorFields::ActuatedComponentControlType, actuatedComponentControlType);
    OS_ASSERT(result);
  }

} // detail

EnergyManagementSystemActuator::EnergyManagementSystemActuator(const Model& model)
  : ModelObject(EnergyManagementSystemActuator::iddObjectType(),model)
{
  OS_ASSERT(getImpl<detail::EnergyManagementSystemActuator_Impl>());

  // TODO: Appropriately handle the following required object-list fields.
  // setActuatedComponentName();
  // setActuatedComponentControlType();
}

IddObjectType EnergyManagementSystemActuator::iddObjectType() {
  return IddObjectType(IddObjectType::OS_EnergyManagementSystem_Actuator);
}

std::string EnergyManagementSystemActuator::actuatedComponentName() const {
  return getImpl<detail::EnergyManagementSystemActuator_Impl>()->actuatedComponentName();
}

std::string EnergyManagementSystemActuator::actuatedComponentControlType() const {
  return getImpl<detail::EnergyManagementSystemActuator_Impl>()->actuatedComponentControlType();
}

void EnergyManagementSystemActuator::setActuatedComponentName(const std::string& actuatedComponentName) {
  getImpl<detail::EnergyManagementSystemActuator_Impl>()->setActuatedComponentName(actuatedComponentName);
}

void EnergyManagementSystemActuator::setActuatedComponentControlType(const std::string& actuatedComponentControlType) {
  getImpl<detail::EnergyManagementSystemActuator_Impl>()->setActuatedComponentControlType(actuatedComponentControlType);
}

/// @cond
EnergyManagementSystemActuator::EnergyManagementSystemActuator(std::shared_ptr<detail::EnergyManagementSystemActuator_Impl> impl)
  : ModelObject(impl)
{}
/// @endcond

} // model
} // openstudio
