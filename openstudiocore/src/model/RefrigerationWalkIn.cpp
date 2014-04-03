/**********************************************************************
 *  Copyright (c) 2008-2014, Alliance for Sustainable Energy.
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

#include <model/RefrigerationWalkIn.hpp>
#include <model/RefrigerationWalkIn_Impl.hpp>
#include <model/RefrigerationWalkInZoneBoundary.hpp>
#include <model/RefrigerationWalkInZoneBoundary_Impl.hpp>

#include <model/Schedule.hpp>
#include <model/Schedule_Impl.hpp>
#include <model/ScheduleTypeLimits.hpp>
#include <model/ScheduleTypeRegistry.hpp>
#include <model/Model.hpp>
#include <model/Model_Impl.hpp>
#include <model/RefrigerationDefrostCycleParameters.hpp>
#include <model/RefrigerationDefrostCycleParameters_Impl.hpp>

#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject.hpp>

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/OS_Refrigeration_WalkIn_FieldEnums.hxx>

#include <utilities/units/Unit.hpp>
#include <utilities/time/Time.hpp>

#include <utilities/core/Assert.hpp>

namespace openstudio {
namespace model {

namespace detail {

  RefrigerationWalkIn_Impl::RefrigerationWalkIn_Impl(const IdfObject& idfObject,
                                                     Model_Impl* model,
                                                     bool keepHandle)
    : ModelObject_Impl(idfObject,model,keepHandle)
  {
    OS_ASSERT(idfObject.iddObject().type() == RefrigerationWalkIn::iddObjectType());
  }

  RefrigerationWalkIn_Impl::RefrigerationWalkIn_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                     Model_Impl* model,
                                                     bool keepHandle)
    : ModelObject_Impl(other,model,keepHandle)
  {
    OS_ASSERT(other.iddObject().type() == RefrigerationWalkIn::iddObjectType());
  }

  RefrigerationWalkIn_Impl::RefrigerationWalkIn_Impl(const RefrigerationWalkIn_Impl& other,
                                                     Model_Impl* model,
                                                     bool keepHandle)
    : ModelObject_Impl(other,model,keepHandle)
  {}

  const std::vector<std::string>& RefrigerationWalkIn_Impl::outputVariableNames() const
  {
    static std::vector<std::string> result;
    if (result.empty()){
    }
    return result;
  }

  IddObjectType RefrigerationWalkIn_Impl::iddObjectType() const {
    return RefrigerationWalkIn::iddObjectType();
  }

  std::vector<ScheduleTypeKey> RefrigerationWalkIn_Impl::getScheduleTypeKeys(const Schedule& schedule) const
  {
    std::vector<ScheduleTypeKey> result;
    UnsignedVector fieldIndices = getSourceIndices(schedule.handle());
    UnsignedVector::const_iterator b(fieldIndices.begin()), e(fieldIndices.end());
    if (std::find(b,e,OS_Refrigeration_WalkInFields::AvailabilityScheduleName) != e)
    {
      result.push_back(ScheduleTypeKey("RefrigerationWalkIn","Availability"));
    }
    if (std::find(b,e,OS_Refrigeration_WalkInFields::HeatingPowerScheduleName) != e)
    {
      result.push_back(ScheduleTypeKey("RefrigerationWalkIn","Heating Power"));
    }
    if (std::find(b,e,OS_Refrigeration_WalkInFields::LightingScheduleName) != e)
    {
      result.push_back(ScheduleTypeKey("RefrigerationWalkIn","Lighting"));
    }
    if (std::find(b,e,OS_Refrigeration_WalkInFields::DefrostScheduleName) != e)
    {
      result.push_back(ScheduleTypeKey("RefrigerationWalkIn","Defrost"));
    }
    if (std::find(b,e,OS_Refrigeration_WalkInFields::DefrostDripDownScheduleName) != e)
    {
      result.push_back(ScheduleTypeKey("RefrigerationWalkIn","Defrost Drip-Down"));
    }
    if (std::find(b,e,OS_Refrigeration_WalkInFields::RestockingScheduleName) != e)
    {
      result.push_back(ScheduleTypeKey("RefrigerationWalkIn","Restocking"));
    }
    return result;
  }

  std::vector<IdfObject> RefrigerationWalkIn_Impl::remove()
  {
    std::vector<IdfObject> result;

    if (boost::optional<RefrigerationDefrostCycleParameters> walkinDefrostCycleParameters = this->optionalWalkinDefrostCycleParameters()) {
      std::vector<IdfObject> removedDefrostCycleParameters = walkinDefrostCycleParameters->remove();
      result.insert(result.end(), removedDefrostCycleParameters.begin(), removedDefrostCycleParameters.end());
    }

    std::vector<RefrigerationWalkInZoneBoundary> zoneBoundaries = this->zoneBoundaries();
    for( std::vector<RefrigerationWalkInZoneBoundary>::iterator it = zoneBoundaries.begin();
         it != zoneBoundaries.end();
         ++it )
    {
      std::vector<IdfObject> removedZoneBoundaries = it->remove();
      result.insert(result.end(), removedZoneBoundaries.begin(), removedZoneBoundaries.end());
    }      

    std::vector<IdfObject> removedRefrigerationWalkIn = ModelObject_Impl::remove();
    result.insert(result.end(), removedRefrigerationWalkIn.begin(), removedRefrigerationWalkIn.end());

    return result;
  }

  ModelObject RefrigerationWalkIn_Impl::clone(Model model) const
  {
    RefrigerationWalkIn modelObjectClone = ModelObject_Impl::clone(model).cast<RefrigerationWalkIn>();

    if (boost::optional<RefrigerationDefrostCycleParameters> walkinDefrostCycleParameters = this->optionalWalkinDefrostCycleParameters()) {
      modelObjectClone.getImpl<RefrigerationWalkIn_Impl>()->setWalkinDefrostCycleParameters(walkinDefrostCycleParameters->clone(model).cast<RefrigerationDefrostCycleParameters>());
    }

    modelObjectClone.removeAllZoneBoundaries();

    std::vector<RefrigerationWalkInZoneBoundary> zoneBoundaries = this->zoneBoundaries();
    for( std::vector<RefrigerationWalkInZoneBoundary>::iterator it = zoneBoundaries.begin();
         it != zoneBoundaries.end();
         ++it )
    {
      RefrigerationWalkInZoneBoundary zoneBoundaryClone = it->clone(model).cast<RefrigerationWalkInZoneBoundary>();
      modelObjectClone.addZoneBoundary(zoneBoundaryClone);
    }

    return modelObjectClone;
  }

  bool RefrigerationWalkIn_Impl::addZoneBoundary(const RefrigerationWalkInZoneBoundary& refrigerationWalkInZoneBoundary)
  {
    WorkspaceExtensibleGroup eg = getObject<ModelObject>().pushExtensibleGroup().cast<WorkspaceExtensibleGroup>();
    bool temp = eg.setPointer(OS_Refrigeration_WalkInExtensibleFields::WalkInZoneBoundary, refrigerationWalkInZoneBoundary.handle());
    if( !temp ) {
      getObject<ModelObject>().eraseExtensibleGroup(eg.groupIndex());
      return temp;
    }
    return temp;
  }

  void RefrigerationWalkIn_Impl::removeZoneBoundary(unsigned index)
  {
    unsigned numberofDataPairs = numExtensibleGroups();
    if(index < numberofDataPairs) {
      getObject<ModelObject>().eraseExtensibleGroup(index);
    }
  }

  void RefrigerationWalkIn_Impl::removeAllZoneBoundaries() 
  {
    getObject<ModelObject>().clearExtensibleGroups();
  }

  std::vector<RefrigerationWalkInZoneBoundary> RefrigerationWalkIn_Impl::zoneBoundaries() const
  {
    std::vector<RefrigerationWalkInZoneBoundary> result;

    std::vector<IdfExtensibleGroup> groups = extensibleGroups();

    for( std::vector<IdfExtensibleGroup>::iterator it = groups.begin();
         it != groups.end();
         ++it )
    {
        if(boost::optional<RefrigerationWalkInZoneBoundary> refrigerationWalkInZoneBoundary = it->cast<WorkspaceExtensibleGroup>().getTarget(OS_Refrigeration_WalkInExtensibleFields::WalkInZoneBoundary)->optionalCast<RefrigerationWalkInZoneBoundary>()) {
          result.push_back( refrigerationWalkInZoneBoundary.get() );
        }
    }

    return result;
  }

  boost::optional<Schedule> RefrigerationWalkIn_Impl::availabilitySchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_Refrigeration_WalkInFields::AvailabilityScheduleName);
  }

  double RefrigerationWalkIn_Impl::ratedCoilCoolingCapacity() const {
    boost::optional<double> value = getDouble(OS_Refrigeration_WalkInFields::RatedCoilCoolingCapacity,true);
    OS_ASSERT(value);
    return value.get();
  }

  double RefrigerationWalkIn_Impl::operatingTemperature() const {
    boost::optional<double> value = getDouble(OS_Refrigeration_WalkInFields::OperatingTemperature,true);
    OS_ASSERT(value);
    return value.get();
  }

  double RefrigerationWalkIn_Impl::ratedCoolingSourceTemperature() const {
    boost::optional<double> value = getDouble(OS_Refrigeration_WalkInFields::RatedCoolingSourceTemperature,true);
    OS_ASSERT(value);
    return value.get();
  }

  double RefrigerationWalkIn_Impl::ratedTotalHeatingPower() const {
    boost::optional<double> value = getDouble(OS_Refrigeration_WalkInFields::RatedTotalHeatingPower,true);
    OS_ASSERT(value);
    return value.get();
  }

  boost::optional<Schedule> RefrigerationWalkIn_Impl::heatingPowerSchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_Refrigeration_WalkInFields::HeatingPowerScheduleName);
  }

  double RefrigerationWalkIn_Impl::ratedCoolingCoilFanPower() const {
    boost::optional<double> value = getDouble(OS_Refrigeration_WalkInFields::RatedCoolingCoilFanPower,true);
    OS_ASSERT(value);
    return value.get();
  }

  bool RefrigerationWalkIn_Impl::isRatedCoolingCoilFanPowerDefaulted() const {
    return isEmpty(OS_Refrigeration_WalkInFields::RatedCoolingCoilFanPower);
  }

  double RefrigerationWalkIn_Impl::ratedCirculationFanPower() const {
    boost::optional<double> value = getDouble(OS_Refrigeration_WalkInFields::RatedCirculationFanPower,true);
    OS_ASSERT(value);
    return value.get();
  }

  bool RefrigerationWalkIn_Impl::isRatedCirculationFanPowerDefaulted() const {
    return isEmpty(OS_Refrigeration_WalkInFields::RatedCirculationFanPower);
  }

  double RefrigerationWalkIn_Impl::ratedTotalLightingPower() const {
    boost::optional<double> value = getDouble(OS_Refrigeration_WalkInFields::RatedTotalLightingPower,true);
    OS_ASSERT(value);
    return value.get();
  }

  boost::optional<Schedule> RefrigerationWalkIn_Impl::lightingSchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_Refrigeration_WalkInFields::LightingScheduleName);
  }

  std::string RefrigerationWalkIn_Impl::defrostType() const {
    boost::optional<std::string> value = getString(OS_Refrigeration_WalkInFields::DefrostType,true);
    OS_ASSERT(value);
    return value.get();
  }

  bool RefrigerationWalkIn_Impl::isDefrostTypeDefaulted() const {
    return isEmpty(OS_Refrigeration_WalkInFields::DefrostType);
  }

  std::string RefrigerationWalkIn_Impl::defrostControlType() const {
    boost::optional<std::string> value = getString(OS_Refrigeration_WalkInFields::DefrostControlType,true);
    OS_ASSERT(value);
    return value.get();
  }

  bool RefrigerationWalkIn_Impl::isDefrostControlTypeDefaulted() const {
    return isEmpty(OS_Refrigeration_WalkInFields::DefrostControlType);
  }

  Schedule RefrigerationWalkIn_Impl::defrostSchedule() const {
    boost::optional<Schedule> value = optionalDefrostSchedule();
    if (!value) {
      LOG_AND_THROW(briefDescription() << " does not have an Defrost Schedule attached.");
    }
    return value.get();
  }

  boost::optional<Schedule> RefrigerationWalkIn_Impl::defrostDripDownSchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_Refrigeration_WalkInFields::DefrostDripDownScheduleName);
  }

  boost::optional<double> RefrigerationWalkIn_Impl::defrostPower() const {
    return getDouble(OS_Refrigeration_WalkInFields::DefrostPower,true);
  }

  boost::optional<double> RefrigerationWalkIn_Impl::temperatureTerminationDefrostFractiontoIce() const {
    return getDouble(OS_Refrigeration_WalkInFields::TemperatureTerminationDefrostFractiontoIce,true);
  }

  boost::optional<Schedule> RefrigerationWalkIn_Impl::restockingSchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_Refrigeration_WalkInFields::RestockingScheduleName);
  }

  double RefrigerationWalkIn_Impl::averageRefrigerantChargeInventory() const {
    boost::optional<double> value = getDouble(OS_Refrigeration_WalkInFields::AverageRefrigerantChargeInventory,true);
    OS_ASSERT(value);
    return value.get();
  }

  bool RefrigerationWalkIn_Impl::isAverageRefrigerantChargeInventoryDefaulted() const {
    return isEmpty(OS_Refrigeration_WalkInFields::AverageRefrigerantChargeInventory);
  }

  double RefrigerationWalkIn_Impl::insulatedFloorSurfaceArea() const {
    boost::optional<double> value = getDouble(OS_Refrigeration_WalkInFields::InsulatedFloorSurfaceArea,true);
    OS_ASSERT(value);
    return value.get();
  }

  double RefrigerationWalkIn_Impl::insulatedFloorUValue() const {
    boost::optional<double> value = getDouble(OS_Refrigeration_WalkInFields::InsulatedFloorUValue,true);
    OS_ASSERT(value);
    return value.get();
  }

  bool RefrigerationWalkIn_Impl::isInsulatedFloorUValueDefaulted() const {
    return isEmpty(OS_Refrigeration_WalkInFields::InsulatedFloorUValue);
  }

  boost::optional<RefrigerationDefrostCycleParameters> RefrigerationWalkIn_Impl::optionalWalkinDefrostCycleParameters() const {
    return getObject<ModelObject>().getModelObjectTarget<RefrigerationDefrostCycleParameters>(OS_Refrigeration_WalkInFields::WalkInDefrostCycleParametersName);
  }

  RefrigerationDefrostCycleParameters RefrigerationWalkIn_Impl::walkinDefrostCycleParameters() {
    boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters();
    if( !defrostCycleParameters ) {
      defrostCycleParameters = RefrigerationDefrostCycleParameters(this->model());
      OS_ASSERT(defrostCycleParameters);
      bool result = setWalkinDefrostCycleParameters(*defrostCycleParameters);
      OS_ASSERT(result);
    }
    return *defrostCycleParameters;
  }

  boost::optional<int> RefrigerationWalkIn_Impl::durationofDefrostCycle() const {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      return defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->durationofDefrostCycle();
    }
    return boost::none;
  }

  boost::optional<int> RefrigerationWalkIn_Impl::dripDownTime() const {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      return defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->dripDownTime();
    }
    return boost::none;
  }

  boost::optional<openstudio::Time> RefrigerationWalkIn_Impl::defrost1StartTime() const {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      return defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->defrost1StartTime();
    }
    return boost::none;
  }

  boost::optional<openstudio::Time> RefrigerationWalkIn_Impl::defrost2StartTime() const {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      return defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->defrost2StartTime();
    }
    return boost::none;
  }

  boost::optional<openstudio::Time> RefrigerationWalkIn_Impl::defrost3StartTime() const {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      return defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->defrost3StartTime();
    }
    return boost::none;
  }

  boost::optional<openstudio::Time> RefrigerationWalkIn_Impl::defrost4StartTime() const {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      return defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->defrost4StartTime();
    }
    return boost::none;
  }

  boost::optional<openstudio::Time> RefrigerationWalkIn_Impl::defrost5StartTime() const {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      return defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->defrost5StartTime();
    }
    return boost::none;
  }

  boost::optional<openstudio::Time> RefrigerationWalkIn_Impl::defrost6StartTime() const {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      return defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->defrost6StartTime();
    }
    return boost::none;
  }

  boost::optional<openstudio::Time> RefrigerationWalkIn_Impl::defrost7StartTime() const {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      return defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->defrost7StartTime();
    }
    return boost::none;
  }

  boost::optional<openstudio::Time> RefrigerationWalkIn_Impl::defrost8StartTime() const {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      return defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->defrost8StartTime();
    }
    return boost::none;
  }

  std::vector<openstudio::Time> RefrigerationWalkIn_Impl::defrostStartTimes() const {
    std::vector<openstudio::Time> result;
    if( boost::optional<openstudio::Time> defrost1StartTime = this->defrost1StartTime() ) {
      result.push_back(*defrost1StartTime);
    }
    if( boost::optional<openstudio::Time> defrost2StartTime = this->defrost2StartTime() ) {
      result.push_back(*defrost2StartTime);
    }
    if( boost::optional<openstudio::Time> defrost3StartTime = this->defrost3StartTime() ) {
      result.push_back(*defrost3StartTime);
    }
    if( boost::optional<openstudio::Time> defrost4StartTime = this->defrost4StartTime() ) {
      result.push_back(*defrost4StartTime);
    }
    if( boost::optional<openstudio::Time> defrost5StartTime = this->defrost5StartTime() ) {
      result.push_back(*defrost5StartTime);
    }
    if( boost::optional<openstudio::Time> defrost6StartTime = this->defrost6StartTime() ) {
      result.push_back(*defrost6StartTime);
    }
    if( boost::optional<openstudio::Time> defrost7StartTime = this->defrost7StartTime() ) {
      result.push_back(*defrost7StartTime);
    }
    if( boost::optional<openstudio::Time> defrost8StartTime = this->defrost8StartTime() ) {
      result.push_back(*defrost8StartTime);
    }
    return result;
  }

  bool RefrigerationWalkIn_Impl::setAvailabilitySchedule(Schedule& schedule) {
    bool result = setSchedule(OS_Refrigeration_WalkInFields::AvailabilityScheduleName,
                              "RefrigerationWalkIn",
                              "Availability",
                              schedule);
    return result;
  }

  void RefrigerationWalkIn_Impl::resetAvailabilitySchedule() {
    bool result = setString(OS_Refrigeration_WalkInFields::AvailabilityScheduleName, "");
    OS_ASSERT(result);
  }

  void RefrigerationWalkIn_Impl::setRatedCoilCoolingCapacity(double ratedCoilCoolingCapacity) {
    bool result = setDouble(OS_Refrigeration_WalkInFields::RatedCoilCoolingCapacity, ratedCoilCoolingCapacity);
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setOperatingTemperature(double operatingTemperature) {
    bool result = setDouble(OS_Refrigeration_WalkInFields::OperatingTemperature, operatingTemperature);
    return result;
  }

  bool RefrigerationWalkIn_Impl::setRatedCoolingSourceTemperature(double ratedCoolingSourceTemperature) {
    bool result = setDouble(OS_Refrigeration_WalkInFields::RatedCoolingSourceTemperature, ratedCoolingSourceTemperature);
    return result;
  }

  void RefrigerationWalkIn_Impl::setRatedTotalHeatingPower(double ratedTotalHeatingPower) {
    bool result = setDouble(OS_Refrigeration_WalkInFields::RatedTotalHeatingPower, ratedTotalHeatingPower);
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setHeatingPowerSchedule(Schedule& schedule) {
    bool result = setSchedule(OS_Refrigeration_WalkInFields::HeatingPowerScheduleName,
                              "RefrigerationWalkIn",
                              "Heating Power",
                              schedule);
    return result;
  }

  void RefrigerationWalkIn_Impl::resetHeatingPowerSchedule() {
    bool result = setString(OS_Refrigeration_WalkInFields::HeatingPowerScheduleName, "");
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setRatedCoolingCoilFanPower(double ratedCoolingCoilFanPower) {
    bool result = setDouble(OS_Refrigeration_WalkInFields::RatedCoolingCoilFanPower, ratedCoolingCoilFanPower);
    return result;
  }

  void RefrigerationWalkIn_Impl::resetRatedCoolingCoilFanPower() {
    bool result = setString(OS_Refrigeration_WalkInFields::RatedCoolingCoilFanPower, "");
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setRatedCirculationFanPower(double ratedCirculationFanPower) {
    bool result = setDouble(OS_Refrigeration_WalkInFields::RatedCirculationFanPower, ratedCirculationFanPower);
    return result;
  }

  void RefrigerationWalkIn_Impl::resetRatedCirculationFanPower() {
    bool result = setString(OS_Refrigeration_WalkInFields::RatedCirculationFanPower, "");
    OS_ASSERT(result);
  }

  void RefrigerationWalkIn_Impl::setRatedTotalLightingPower(double ratedTotalLightingPower) {
    bool result = setDouble(OS_Refrigeration_WalkInFields::RatedTotalLightingPower, ratedTotalLightingPower);
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setLightingSchedule(Schedule& schedule) {
    bool result = setSchedule(OS_Refrigeration_WalkInFields::LightingScheduleName,
                              "RefrigerationWalkIn",
                              "Lighting",
                              schedule);
    return result;
  }

  void RefrigerationWalkIn_Impl::resetLightingSchedule() {
    bool result = setString(OS_Refrigeration_WalkInFields::LightingScheduleName, "");
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setDefrostType(std::string defrostType) {
    bool result = setString(OS_Refrigeration_WalkInFields::DefrostType, defrostType);
    return result;
  }

  void RefrigerationWalkIn_Impl::resetDefrostType() {
    bool result = setString(OS_Refrigeration_WalkInFields::DefrostType, "");
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setDefrostControlType(std::string defrostControlType) {
    bool result = setString(OS_Refrigeration_WalkInFields::DefrostControlType, defrostControlType);
    return result;
  }

  void RefrigerationWalkIn_Impl::resetDefrostControlType() {
    bool result = setString(OS_Refrigeration_WalkInFields::DefrostControlType, "");
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setDefrostSchedule(Schedule& schedule) {
    bool result = setSchedule(OS_Refrigeration_WalkInFields::DefrostScheduleName,
                              "RefrigerationWalkIn",
                              "Defrost",
                              schedule);
    return result;
  }

  bool RefrigerationWalkIn_Impl::setDefrostDripDownSchedule(Schedule& schedule) {
    bool result = setSchedule(OS_Refrigeration_WalkInFields::DefrostDripDownScheduleName,
                              "RefrigerationWalkIn",
                              "Defrost Drip-Down",
                              schedule);
    return result;
  }

  void RefrigerationWalkIn_Impl::resetDefrostDripDownSchedule() {
    bool result = setString(OS_Refrigeration_WalkInFields::DefrostDripDownScheduleName, "");
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setDefrostPower(boost::optional<double> defrostPower) {
    bool result(false);
    if (defrostPower) {
      result = setDouble(OS_Refrigeration_WalkInFields::DefrostPower, defrostPower.get());
    }
    else {
      resetDefrostPower();
      result = true;
    }
    return result;
  }

  void RefrigerationWalkIn_Impl::resetDefrostPower() {
    bool result = setString(OS_Refrigeration_WalkInFields::DefrostPower, "");
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setTemperatureTerminationDefrostFractiontoIce(boost::optional<double> temperatureTerminationDefrostFractiontoIce) {
    bool result(false);
    if (temperatureTerminationDefrostFractiontoIce) {
      result = setDouble(OS_Refrigeration_WalkInFields::TemperatureTerminationDefrostFractiontoIce, temperatureTerminationDefrostFractiontoIce.get());
    }
    else {
      resetTemperatureTerminationDefrostFractiontoIce();
      result = true;
    }
    return result;
  }

  void RefrigerationWalkIn_Impl::resetTemperatureTerminationDefrostFractiontoIce() {
    bool result = setString(OS_Refrigeration_WalkInFields::TemperatureTerminationDefrostFractiontoIce, "");
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setRestockingSchedule(Schedule& schedule) {
    bool result = setSchedule(OS_Refrigeration_WalkInFields::RestockingScheduleName,
                              "RefrigerationWalkIn",
                              "Restocking",
                              schedule);
    return result;
  }

  void RefrigerationWalkIn_Impl::resetRestockingSchedule() {
    bool result = setString(OS_Refrigeration_WalkInFields::RestockingScheduleName, "");
    OS_ASSERT(result);
  }

  void RefrigerationWalkIn_Impl::setAverageRefrigerantChargeInventory(double averageRefrigerantChargeInventory) {
    bool result = setDouble(OS_Refrigeration_WalkInFields::AverageRefrigerantChargeInventory, averageRefrigerantChargeInventory);
    OS_ASSERT(result);
  }

  void RefrigerationWalkIn_Impl::resetAverageRefrigerantChargeInventory() {
    bool result = setString(OS_Refrigeration_WalkInFields::AverageRefrigerantChargeInventory, "");
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setInsulatedFloorSurfaceArea(double insulatedFloorSurfaceArea) {
    bool result = setDouble(OS_Refrigeration_WalkInFields::InsulatedFloorSurfaceArea, insulatedFloorSurfaceArea);
    return result;
  }

  bool RefrigerationWalkIn_Impl::setInsulatedFloorUValue(double insulatedFloorUValue) {
    bool result = setDouble(OS_Refrigeration_WalkInFields::InsulatedFloorUValue, insulatedFloorUValue);
    return result;
  }

  void RefrigerationWalkIn_Impl::resetInsulatedFloorUValue() {
    bool result = setString(OS_Refrigeration_WalkInFields::InsulatedFloorUValue, "");
    OS_ASSERT(result);
  }

  bool RefrigerationWalkIn_Impl::setWalkinDefrostCycleParameters(const RefrigerationDefrostCycleParameters& walkinDefrostCycleParameters) {
    return setPointer(OS_Refrigeration_WalkInFields::WalkInDefrostCycleParametersName, walkinDefrostCycleParameters.handle());
  }

  bool RefrigerationWalkIn_Impl::setDurationofDefrostCycle(boost::optional<int> durationofDefrostCycle) {
      return this->walkinDefrostCycleParameters().getImpl<RefrigerationDefrostCycleParameters_Impl>()->setDurationofDefrostCycle(durationofDefrostCycle);
  }

  void RefrigerationWalkIn_Impl::resetDurationofDefrostCycle() {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->resetDurationofDefrostCycle();
    }
  }

  bool RefrigerationWalkIn_Impl::setDripDownTime(boost::optional<int> dripDownTime) {
      return this->walkinDefrostCycleParameters().getImpl<RefrigerationDefrostCycleParameters_Impl>()->setDripDownTime(dripDownTime);
  }

  void RefrigerationWalkIn_Impl::resetDripDownTime() {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->resetDripDownTime();
    }
  }

  bool RefrigerationWalkIn_Impl::setDefrost1StartTime(const openstudio::Time& defrost1StartTime) {
      return this->walkinDefrostCycleParameters().getImpl<RefrigerationDefrostCycleParameters_Impl>()->setDefrost1StartTime(defrost1StartTime);
  }

  void RefrigerationWalkIn_Impl::resetDefrost1StartTime() {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->resetDefrost1StartTime();
    }
  }

  bool RefrigerationWalkIn_Impl::setDefrost2StartTime(const openstudio::Time& defrost2StartTime) {
      return this->walkinDefrostCycleParameters().getImpl<RefrigerationDefrostCycleParameters_Impl>()->setDefrost2StartTime(defrost2StartTime);
  }

  void RefrigerationWalkIn_Impl::resetDefrost2StartTime() {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->resetDefrost2StartTime();
    }
  }

  bool RefrigerationWalkIn_Impl::setDefrost3StartTime(const openstudio::Time& defrost3StartTime) {
      return this->walkinDefrostCycleParameters().getImpl<RefrigerationDefrostCycleParameters_Impl>()->setDefrost3StartTime(defrost3StartTime);
  }

  void RefrigerationWalkIn_Impl::resetDefrost3StartTime() {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->resetDefrost3StartTime();
    }
  }

  bool RefrigerationWalkIn_Impl::setDefrost4StartTime(const openstudio::Time& defrost4StartTime) {
      return this->walkinDefrostCycleParameters().getImpl<RefrigerationDefrostCycleParameters_Impl>()->setDefrost4StartTime(defrost4StartTime);
  }

  void RefrigerationWalkIn_Impl::resetDefrost4StartTime() {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->resetDefrost4StartTime();
    }
  }

  bool RefrigerationWalkIn_Impl::setDefrost5StartTime(const openstudio::Time& defrost5StartTime) {
      return this->walkinDefrostCycleParameters().getImpl<RefrigerationDefrostCycleParameters_Impl>()->setDefrost5StartTime(defrost5StartTime);
  }

  void RefrigerationWalkIn_Impl::resetDefrost5StartTime() {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->resetDefrost5StartTime();
    }
  }

  bool RefrigerationWalkIn_Impl::setDefrost6StartTime(const openstudio::Time& defrost6StartTime) {
      return this->walkinDefrostCycleParameters().getImpl<RefrigerationDefrostCycleParameters_Impl>()->setDefrost6StartTime(defrost6StartTime);
  }

  void RefrigerationWalkIn_Impl::resetDefrost6StartTime() {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->resetDefrost6StartTime();
    }
  }

  bool RefrigerationWalkIn_Impl::setDefrost7StartTime(const openstudio::Time& defrost7StartTime) {
      return this->walkinDefrostCycleParameters().getImpl<RefrigerationDefrostCycleParameters_Impl>()->setDefrost7StartTime(defrost7StartTime);
  }

  void RefrigerationWalkIn_Impl::resetDefrost7StartTime() {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->resetDefrost7StartTime();
    }
  }

  bool RefrigerationWalkIn_Impl::setDefrost8StartTime(const openstudio::Time& defrost8StartTime) {
      return this->walkinDefrostCycleParameters().getImpl<RefrigerationDefrostCycleParameters_Impl>()->setDefrost8StartTime(defrost8StartTime);
  }

  void RefrigerationWalkIn_Impl::resetDefrost8StartTime() {
    if( boost::optional<RefrigerationDefrostCycleParameters> defrostCycleParameters = this->optionalWalkinDefrostCycleParameters() ) {
      defrostCycleParameters->getImpl<RefrigerationDefrostCycleParameters_Impl>()->resetDefrost8StartTime();
    }
  }

  boost::optional<Schedule> RefrigerationWalkIn_Impl::optionalDefrostSchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_Refrigeration_WalkInFields::DefrostScheduleName);
  }

} // detail

RefrigerationWalkIn::RefrigerationWalkIn(const Model& model, Schedule& walkinDefrostSchedule)
  : ModelObject(RefrigerationWalkIn::iddObjectType(),model)
{
  OS_ASSERT(getImpl<detail::RefrigerationWalkIn_Impl>());

  setRatedCoilCoolingCapacity(4690.0);
  bool ok = setOperatingTemperature(-2.22);
  OS_ASSERT(ok);
  ok = setRatedCoolingSourceTemperature(-6.67);
  OS_ASSERT(ok);
  setRatedTotalHeatingPower(0.0);
  ok = setRatedCoolingCoilFanPower(735.0);
  OS_ASSERT(ok);
  ok = setRatedCirculationFanPower(0.0);
  OS_ASSERT(ok);
  setRatedTotalLightingPower(120.0);
  ok = setDefrostType("Electric");
  OS_ASSERT(ok);
  ok = setDefrostControlType("TimeSchedule");
  OS_ASSERT(ok);
  ok = setDefrostSchedule(walkinDefrostSchedule);
  OS_ASSERT(ok);
  ok = setDefrostPower(5512.0);
  OS_ASSERT(ok);
  ok = setInsulatedFloorSurfaceArea(13.0);
  OS_ASSERT(ok);
  ok = setInsulatedFloorUValue(0.207);
  OS_ASSERT(ok);
  RefrigerationWalkInZoneBoundary zoneBoundary = RefrigerationWalkInZoneBoundary(model);
  ok = addZoneBoundary(zoneBoundary);
  OS_ASSERT(ok);
}

IddObjectType RefrigerationWalkIn::iddObjectType() {
  return IddObjectType(IddObjectType::OS_Refrigeration_WalkIn);
}

std::vector<std::string> RefrigerationWalkIn::defrostTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        OS_Refrigeration_WalkInFields::DefrostType);
}

std::vector<std::string> RefrigerationWalkIn::defrostControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        OS_Refrigeration_WalkInFields::DefrostControlType);
}

bool RefrigerationWalkIn::addZoneBoundary(const RefrigerationWalkInZoneBoundary& refrigerationWalkInZoneBoundary){
  return getImpl<detail::RefrigerationWalkIn_Impl>()->addZoneBoundary(refrigerationWalkInZoneBoundary);
}

void RefrigerationWalkIn::removeZoneBoundary(unsigned index){
  return getImpl<detail::RefrigerationWalkIn_Impl>()->removeZoneBoundary(index);
}

void RefrigerationWalkIn::removeAllZoneBoundaries(){
  return getImpl<detail::RefrigerationWalkIn_Impl>()->removeAllZoneBoundaries();
}

std::vector<RefrigerationWalkInZoneBoundary> RefrigerationWalkIn::zoneBoundaries() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->zoneBoundaries();
}

boost::optional<Schedule> RefrigerationWalkIn::availabilitySchedule() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->availabilitySchedule();
}

double RefrigerationWalkIn::ratedCoilCoolingCapacity() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->ratedCoilCoolingCapacity();
}

double RefrigerationWalkIn::operatingTemperature() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->operatingTemperature();
}

double RefrigerationWalkIn::ratedCoolingSourceTemperature() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->ratedCoolingSourceTemperature();
}

double RefrigerationWalkIn::ratedTotalHeatingPower() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->ratedTotalHeatingPower();
}

boost::optional<Schedule> RefrigerationWalkIn::heatingPowerSchedule() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->heatingPowerSchedule();
}

double RefrigerationWalkIn::ratedCoolingCoilFanPower() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->ratedCoolingCoilFanPower();
}

bool RefrigerationWalkIn::isRatedCoolingCoilFanPowerDefaulted() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->isRatedCoolingCoilFanPowerDefaulted();
}

double RefrigerationWalkIn::ratedCirculationFanPower() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->ratedCirculationFanPower();
}

bool RefrigerationWalkIn::isRatedCirculationFanPowerDefaulted() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->isRatedCirculationFanPowerDefaulted();
}

double RefrigerationWalkIn::ratedTotalLightingPower() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->ratedTotalLightingPower();
}

boost::optional<Schedule> RefrigerationWalkIn::lightingSchedule() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->lightingSchedule();
}

std::string RefrigerationWalkIn::defrostType() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrostType();
}

bool RefrigerationWalkIn::isDefrostTypeDefaulted() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->isDefrostTypeDefaulted();
}

std::string RefrigerationWalkIn::defrostControlType() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrostControlType();
}

bool RefrigerationWalkIn::isDefrostControlTypeDefaulted() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->isDefrostControlTypeDefaulted();
}

Schedule RefrigerationWalkIn::defrostSchedule() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrostSchedule();
}

boost::optional<Schedule> RefrigerationWalkIn::defrostDripDownSchedule() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrostDripDownSchedule();
}

boost::optional<double> RefrigerationWalkIn::defrostPower() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrostPower();
}

boost::optional<double> RefrigerationWalkIn::temperatureTerminationDefrostFractiontoIce() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->temperatureTerminationDefrostFractiontoIce();
}

boost::optional<Schedule> RefrigerationWalkIn::restockingSchedule() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->restockingSchedule();
}

double RefrigerationWalkIn::averageRefrigerantChargeInventory() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->averageRefrigerantChargeInventory();
}

bool RefrigerationWalkIn::isAverageRefrigerantChargeInventoryDefaulted() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->isAverageRefrigerantChargeInventoryDefaulted();
}

double RefrigerationWalkIn::insulatedFloorSurfaceArea() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->insulatedFloorSurfaceArea();
}

double RefrigerationWalkIn::insulatedFloorUValue() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->insulatedFloorUValue();
}

bool RefrigerationWalkIn::isInsulatedFloorUValueDefaulted() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->isInsulatedFloorUValueDefaulted();
}

boost::optional<int> RefrigerationWalkIn::durationofDefrostCycle() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->durationofDefrostCycle();
}

boost::optional<int> RefrigerationWalkIn::dripDownTime() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->dripDownTime();
}

boost::optional<openstudio::Time> RefrigerationWalkIn::defrost1StartTime() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrost1StartTime();
}

boost::optional<openstudio::Time> RefrigerationWalkIn::defrost2StartTime() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrost2StartTime();
}

boost::optional<openstudio::Time> RefrigerationWalkIn::defrost3StartTime() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrost3StartTime();
}

boost::optional<openstudio::Time> RefrigerationWalkIn::defrost4StartTime() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrost4StartTime();
}

boost::optional<openstudio::Time> RefrigerationWalkIn::defrost5StartTime() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrost5StartTime();
}

boost::optional<openstudio::Time> RefrigerationWalkIn::defrost6StartTime() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrost6StartTime();
}

boost::optional<openstudio::Time> RefrigerationWalkIn::defrost7StartTime() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrost7StartTime();
}

boost::optional<openstudio::Time> RefrigerationWalkIn::defrost8StartTime() const {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->defrost8StartTime();
}

bool RefrigerationWalkIn::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setAvailabilitySchedule(schedule);
}

void RefrigerationWalkIn::resetAvailabilitySchedule() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetAvailabilitySchedule();
}

void RefrigerationWalkIn::setRatedCoilCoolingCapacity(double ratedCoilCoolingCapacity) {
  getImpl<detail::RefrigerationWalkIn_Impl>()->setRatedCoilCoolingCapacity(ratedCoilCoolingCapacity);
}

bool RefrigerationWalkIn::setOperatingTemperature(double operatingTemperature) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setOperatingTemperature(operatingTemperature);
}

bool RefrigerationWalkIn::setRatedCoolingSourceTemperature(double ratedCoolingSourceTemperature) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setRatedCoolingSourceTemperature(ratedCoolingSourceTemperature);
}

void RefrigerationWalkIn::setRatedTotalHeatingPower(double ratedTotalHeatingPower) {
  getImpl<detail::RefrigerationWalkIn_Impl>()->setRatedTotalHeatingPower(ratedTotalHeatingPower);
}

bool RefrigerationWalkIn::setHeatingPowerSchedule(Schedule& schedule) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setHeatingPowerSchedule(schedule);
}

void RefrigerationWalkIn::resetHeatingPowerSchedule() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetHeatingPowerSchedule();
}

bool RefrigerationWalkIn::setRatedCoolingCoilFanPower(double ratedCoolingCoilFanPower) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setRatedCoolingCoilFanPower(ratedCoolingCoilFanPower);
}

void RefrigerationWalkIn::resetRatedCoolingCoilFanPower() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetRatedCoolingCoilFanPower();
}

bool RefrigerationWalkIn::setRatedCirculationFanPower(double ratedCirculationFanPower) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setRatedCirculationFanPower(ratedCirculationFanPower);
}

void RefrigerationWalkIn::resetRatedCirculationFanPower() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetRatedCirculationFanPower();
}

void RefrigerationWalkIn::setRatedTotalLightingPower(double ratedTotalLightingPower) {
  getImpl<detail::RefrigerationWalkIn_Impl>()->setRatedTotalLightingPower(ratedTotalLightingPower);
}

bool RefrigerationWalkIn::setLightingSchedule(Schedule& schedule) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setLightingSchedule(schedule);
}

void RefrigerationWalkIn::resetLightingSchedule() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetLightingSchedule();
}

bool RefrigerationWalkIn::setDefrostType(std::string defrostType) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrostType(defrostType);
}

void RefrigerationWalkIn::resetDefrostType() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetDefrostType();
}

bool RefrigerationWalkIn::setDefrostControlType(std::string defrostControlType) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrostControlType(defrostControlType);
}

void RefrigerationWalkIn::resetDefrostControlType() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetDefrostControlType();
}

bool RefrigerationWalkIn::setDefrostSchedule(Schedule& schedule) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrostSchedule(schedule);
}

bool RefrigerationWalkIn::setDefrostDripDownSchedule(Schedule& schedule) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrostDripDownSchedule(schedule);
}

void RefrigerationWalkIn::resetDefrostDripDownSchedule() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetDefrostDripDownSchedule();
}

bool RefrigerationWalkIn::setDefrostPower(double defrostPower) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrostPower(defrostPower);
}

void RefrigerationWalkIn::resetDefrostPower() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetDefrostPower();
}

bool RefrigerationWalkIn::setTemperatureTerminationDefrostFractiontoIce(double temperatureTerminationDefrostFractiontoIce) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setTemperatureTerminationDefrostFractiontoIce(temperatureTerminationDefrostFractiontoIce);
}

void RefrigerationWalkIn::resetTemperatureTerminationDefrostFractiontoIce() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetTemperatureTerminationDefrostFractiontoIce();
}

bool RefrigerationWalkIn::setRestockingSchedule(Schedule& schedule) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setRestockingSchedule(schedule);
}

void RefrigerationWalkIn::resetRestockingSchedule() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetRestockingSchedule();
}

void RefrigerationWalkIn::setAverageRefrigerantChargeInventory(double averageRefrigerantChargeInventory) {
  getImpl<detail::RefrigerationWalkIn_Impl>()->setAverageRefrigerantChargeInventory(averageRefrigerantChargeInventory);
}

void RefrigerationWalkIn::resetAverageRefrigerantChargeInventory() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetAverageRefrigerantChargeInventory();
}

bool RefrigerationWalkIn::setInsulatedFloorSurfaceArea(double insulatedFloorSurfaceArea) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setInsulatedFloorSurfaceArea(insulatedFloorSurfaceArea);
}

bool RefrigerationWalkIn::setInsulatedFloorUValue(double insulatedFloorUValue) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setInsulatedFloorUValue(insulatedFloorUValue);
}

void RefrigerationWalkIn::resetInsulatedFloorUValue() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetInsulatedFloorUValue();
}

bool RefrigerationWalkIn::setDurationofDefrostCycle(int durationofDefrostCycle) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDurationofDefrostCycle(durationofDefrostCycle);
}

void RefrigerationWalkIn::resetDurationofDefrostCycle() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetDurationofDefrostCycle();
}

bool RefrigerationWalkIn::setDripDownTime(int dripDownTime) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDripDownTime(dripDownTime);
}

void RefrigerationWalkIn::resetDripDownTime() {
  getImpl<detail::RefrigerationWalkIn_Impl>()->resetDripDownTime();
}

bool RefrigerationWalkIn::setDefrost1StartTime(const openstudio::Time& defrost1StartTime) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrost1StartTime(defrost1StartTime);
}

bool RefrigerationWalkIn::setDefrost2StartTime(const openstudio::Time& defrost2StartTime) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrost2StartTime(defrost2StartTime);
}

bool RefrigerationWalkIn::setDefrost3StartTime(const openstudio::Time& defrost3StartTime) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrost3StartTime(defrost3StartTime);
}

bool RefrigerationWalkIn::setDefrost4StartTime(const openstudio::Time& defrost4StartTime) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrost4StartTime(defrost4StartTime);
}

bool RefrigerationWalkIn::setDefrost5StartTime(const openstudio::Time& defrost5StartTime) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrost5StartTime(defrost5StartTime);
}

bool RefrigerationWalkIn::setDefrost6StartTime(const openstudio::Time& defrost6StartTime) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrost6StartTime(defrost6StartTime);
}

bool RefrigerationWalkIn::setDefrost7StartTime(const openstudio::Time& defrost7StartTime) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrost7StartTime(defrost7StartTime);
}

bool RefrigerationWalkIn::setDefrost8StartTime(const openstudio::Time& defrost8StartTime) {
  return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrost8StartTime(defrost8StartTime);
}

/// @cond
RefrigerationWalkIn::RefrigerationWalkIn(boost::shared_ptr<detail::RefrigerationWalkIn_Impl> impl)
  : ModelObject(impl)
{}
/// @endcond

} // model
} // openstudio

