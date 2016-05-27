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

#include <gtest/gtest.h>

#include "../WorkflowJSON.hpp"
#include "../WorkflowStep.hpp"
#include "../WorkflowStep_Impl.hpp"
#include "../WorkflowStepResult.hpp"

#include "../../time/DateTime.hpp"

#include "../../core/Exception.hpp"

#include <resources.hxx>

using namespace openstudio;

TEST(Filetypes, WorkflowJSON_Min)
{
  path p = resourcesPath() / toPath("utilities/Filetypes/min.osw");
  path p2 = resourcesPath() / toPath("utilities/Filetypes/min.out.osw");
  ASSERT_TRUE(WorkflowJSON::load(p));
 
  try{
    WorkflowJSON workflow(p);
    EXPECT_TRUE(workflow.checkForUpdates());
    ASSERT_TRUE(workflow.oswPath());
    EXPECT_EQ(p, workflow.oswPath().get());
    EXPECT_EQ(".", toString(workflow.rootDir()));
    EXPECT_EQ(toString(p.parent_path()), toString(workflow.absoluteRootDir()));
    EXPECT_FALSE(workflow.seedFile());
    EXPECT_FALSE(workflow.weatherFile());

    EXPECT_TRUE(workflow.saveAs(p2));

    std::vector<WorkflowStep> workflowSteps = workflow.workflowSteps();
    ASSERT_EQ(3u, workflowSteps.size());

    ASSERT_TRUE(workflowSteps[0].optionalCast<MeasureStep>());
    MeasureStep measureStep = workflowSteps[0].cast<MeasureStep>();
    EXPECT_EQ("IncreaseWallRValue", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("cost"));
    ASSERT_EQ(VariantType::Double, measureStep.getArgument("cost")->variantType().value());
    EXPECT_EQ(123.321, measureStep.getArgument("cost")->valueAsDouble());
    ASSERT_TRUE(measureStep.getArgument("percent_increase"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_increase")->variantType().value());
    EXPECT_EQ(5, measureStep.getArgument("percent_increase")->valueAsInteger());
    ASSERT_TRUE(measureStep.getArgument("operating_expenses"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("operating_expenses")->variantType().value());
    EXPECT_EQ(0, measureStep.getArgument("operating_expenses")->valueAsInteger());

    ASSERT_TRUE(workflowSteps[1].optionalCast<MeasureStep>());
    measureStep = workflowSteps[1].cast<MeasureStep>();
    EXPECT_EQ("IncreaseRoofRValue", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("cost"));
    ASSERT_EQ(VariantType::Double, measureStep.getArgument("cost")->variantType().value());
    EXPECT_EQ(321.123, measureStep.getArgument("cost")->valueAsDouble());
    ASSERT_TRUE(measureStep.getArgument("percent_increase"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_increase")->variantType().value());
    EXPECT_EQ(15, measureStep.getArgument("percent_increase")->valueAsInteger());
    ASSERT_TRUE(measureStep.getArgument("space_type"));
    ASSERT_EQ(VariantType::String, measureStep.getArgument("space_type")->variantType().value());
    EXPECT_EQ("*All*", measureStep.getArgument("space_type")->valueAsString());

    ASSERT_TRUE(workflowSteps[2].optionalCast<MeasureStep>());
    measureStep = workflowSteps[2].cast<MeasureStep>();
    EXPECT_EQ("DecreaseThermalMass", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("has_bool"));
    ASSERT_EQ(VariantType::Boolean, measureStep.getArgument("has_bool")->variantType().value());
    EXPECT_EQ(true, measureStep.getArgument("has_bool")->valueAsBoolean());
    ASSERT_TRUE(measureStep.getArgument("percent_decrease"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_decrease")->variantType().value());
    EXPECT_EQ(5, measureStep.getArgument("percent_decrease")->valueAsInteger());

  } catch (const std::exception& e){
    EXPECT_TRUE(false) << e.what();
  }

  ASSERT_TRUE(WorkflowJSON::load(p2));
  try{
    WorkflowJSON workflow(p2);
    EXPECT_FALSE(workflow.checkForUpdates());
    ASSERT_TRUE(workflow.oswPath());
    EXPECT_EQ(p2, workflow.oswPath().get());
    EXPECT_EQ(".", toString(workflow.rootDir()));
    EXPECT_EQ(toString(p2.parent_path()), toString(workflow.absoluteRootDir()));
    EXPECT_FALSE(workflow.seedFile());
    EXPECT_FALSE(workflow.weatherFile());

    std::vector<WorkflowStep> workflowSteps = workflow.workflowSteps();
    ASSERT_EQ(3u, workflowSteps.size());

    ASSERT_TRUE(workflowSteps[0].optionalCast<MeasureStep>());
    MeasureStep measureStep = workflowSteps[0].cast<MeasureStep>();
    EXPECT_EQ("IncreaseWallRValue", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("cost"));
    ASSERT_EQ(VariantType::Double, measureStep.getArgument("cost")->variantType().value());
    EXPECT_EQ(123.321, measureStep.getArgument("cost")->valueAsDouble());
    ASSERT_TRUE(measureStep.getArgument("percent_increase"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_increase")->variantType().value());
    EXPECT_EQ(5, measureStep.getArgument("percent_increase")->valueAsInteger());
    ASSERT_TRUE(measureStep.getArgument("operating_expenses"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("operating_expenses")->variantType().value());
    EXPECT_EQ(0, measureStep.getArgument("operating_expenses")->valueAsInteger());

    ASSERT_TRUE(workflowSteps[1].optionalCast<MeasureStep>());
    measureStep = workflowSteps[1].cast<MeasureStep>();
    EXPECT_EQ("IncreaseRoofRValue", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("cost"));
    ASSERT_EQ(VariantType::Double, measureStep.getArgument("cost")->variantType().value());
    EXPECT_EQ(321.123, measureStep.getArgument("cost")->valueAsDouble());
    ASSERT_TRUE(measureStep.getArgument("percent_increase"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_increase")->variantType().value());
    EXPECT_EQ(15, measureStep.getArgument("percent_increase")->valueAsInteger());
    ASSERT_TRUE(measureStep.getArgument("space_type"));
    ASSERT_EQ(VariantType::String, measureStep.getArgument("space_type")->variantType().value());
    EXPECT_EQ("*All*", measureStep.getArgument("space_type")->valueAsString());

    ASSERT_TRUE(workflowSteps[2].optionalCast<MeasureStep>());
    measureStep = workflowSteps[2].cast<MeasureStep>();
    EXPECT_EQ("DecreaseThermalMass", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("has_bool"));
    ASSERT_EQ(VariantType::Boolean, measureStep.getArgument("has_bool")->variantType().value());
    EXPECT_EQ(true, measureStep.getArgument("has_bool")->valueAsBoolean());
    ASSERT_TRUE(measureStep.getArgument("percent_decrease"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_decrease")->variantType().value());
    EXPECT_EQ(5, measureStep.getArgument("percent_decrease")->valueAsInteger());

  } catch (const std::exception& e){
    EXPECT_TRUE(false) << e.what();
  }
}

TEST(Filetypes, WorkflowJSON_Full)
{
  path p = resourcesPath() / toPath("utilities/Filetypes/full.osw");
  path p2 = resourcesPath() / toPath("utilities/Filetypes/full.out.osw");
  EXPECT_TRUE(WorkflowJSON::load(p));

  try{
    WorkflowJSON workflow(p);
    EXPECT_TRUE(workflow.checkForUpdates());
    ASSERT_TRUE(workflow.oswPath());
    EXPECT_EQ(p, workflow.oswPath().get());
    EXPECT_EQ("../../", toString(workflow.rootDir()));
    EXPECT_EQ(toString(resourcesPath()), toString(workflow.absoluteRootDir()));
    ASSERT_TRUE(workflow.seedFile());
    EXPECT_EQ("1_9_0/example.osm", workflow.seedFile().get());
    boost::optional<path> test = workflow.findFile(workflow.seedFile().get());
    ASSERT_TRUE(test);
    EXPECT_EQ(toString(resourcesPath() / toPath("osversion/1_9_0/example.osm")), toString(*test));
    ASSERT_TRUE(workflow.weatherFile());
    EXPECT_EQ("./USA_CO_Golden-NREL.724666_TMY3.epw", workflow.weatherFile().get());
    test = workflow.findFile(workflow.weatherFile().get());
    ASSERT_TRUE(test);
    EXPECT_EQ(toString(resourcesPath() / toPath("utilities/Filetypes/./USA_CO_Golden-NREL.724666_TMY3.epw")), toString(*test));
    test = workflow.findMeasure(toPath("SetWindowToWallRatioByFacade"));
    ASSERT_TRUE(test);
    EXPECT_EQ(toString(resourcesPath() / toPath("utilities/BCL/Measures/v2/SetWindowToWallRatioByFacade")), toString(*test));

    EXPECT_TRUE(workflow.saveAs(p2));

    std::vector<WorkflowStep> workflowSteps = workflow.workflowSteps();
    ASSERT_EQ(3u, workflowSteps.size());

    ASSERT_TRUE(workflowSteps[0].optionalCast<MeasureStep>());
    MeasureStep measureStep = workflowSteps[0].cast<MeasureStep>();
    EXPECT_EQ("IncreaseWallRValue", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("cost"));
    ASSERT_EQ(VariantType::Double, measureStep.getArgument("cost")->variantType().value());
    EXPECT_EQ(123.321, measureStep.getArgument("cost")->valueAsDouble());
    ASSERT_TRUE(measureStep.getArgument("percent_increase"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_increase")->variantType().value());
    EXPECT_EQ(5, measureStep.getArgument("percent_increase")->valueAsInteger());
    ASSERT_TRUE(measureStep.getArgument("operating_expenses"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("operating_expenses")->variantType().value());
    EXPECT_EQ(0, measureStep.getArgument("operating_expenses")->valueAsInteger());

    ASSERT_TRUE(workflowSteps[1].optionalCast<MeasureStep>());
    measureStep = workflowSteps[1].cast<MeasureStep>();
    EXPECT_EQ("IncreaseRoofRValue", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("cost"));
    ASSERT_EQ(VariantType::Double, measureStep.getArgument("cost")->variantType().value());
    EXPECT_EQ(321.123, measureStep.getArgument("cost")->valueAsDouble());
    ASSERT_TRUE(measureStep.getArgument("percent_increase"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_increase")->variantType().value());
    EXPECT_EQ(15, measureStep.getArgument("percent_increase")->valueAsInteger());
    ASSERT_TRUE(measureStep.getArgument("space_type"));
    ASSERT_EQ(VariantType::String, measureStep.getArgument("space_type")->variantType().value());
    EXPECT_EQ("*All*", measureStep.getArgument("space_type")->valueAsString());

    ASSERT_TRUE(workflowSteps[2].optionalCast<MeasureStep>());
    measureStep = workflowSteps[2].cast<MeasureStep>();
    EXPECT_EQ("DecreaseThermalMass", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("has_bool"));
    ASSERT_EQ(VariantType::Boolean, measureStep.getArgument("has_bool")->variantType().value());
    EXPECT_EQ(true, measureStep.getArgument("has_bool")->valueAsBoolean());
    ASSERT_TRUE(measureStep.getArgument("percent_decrease"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_decrease")->variantType().value());
    EXPECT_EQ(5, measureStep.getArgument("percent_decrease")->valueAsInteger());

  } catch (const std::exception& e){
    EXPECT_TRUE(false) << e.what();
  }

  ASSERT_TRUE(WorkflowJSON::load(p2));
  try{
    WorkflowJSON workflow(p2);
    EXPECT_FALSE(workflow.checkForUpdates());
    ASSERT_TRUE(workflow.oswPath());
    EXPECT_EQ(p2, workflow.oswPath().get());
    EXPECT_EQ("../../", toString(workflow.rootDir()));
    EXPECT_EQ(toString(resourcesPath()), toString(workflow.absoluteRootDir()));
    ASSERT_TRUE(workflow.seedFile());
    EXPECT_EQ("1_9_0/example.osm", workflow.seedFile().get());
    boost::optional<path> test = workflow.findFile(workflow.seedFile().get());
    ASSERT_TRUE(test);
    EXPECT_EQ(toString(resourcesPath() / toPath("osversion/1_9_0/example.osm")), toString(*test));
    ASSERT_TRUE(workflow.weatherFile());
    EXPECT_EQ("./USA_CO_Golden-NREL.724666_TMY3.epw", workflow.weatherFile().get());
    test = workflow.findFile(workflow.weatherFile().get());
    ASSERT_TRUE(test);
    EXPECT_EQ(toString(resourcesPath() / toPath("utilities/Filetypes/./USA_CO_Golden-NREL.724666_TMY3.epw")), toString(*test));
    test = workflow.findMeasure(toPath("SetWindowToWallRatioByFacade"));
    ASSERT_TRUE(test);
    EXPECT_EQ(toString(resourcesPath() / toPath("utilities/BCL/Measures/v2/SetWindowToWallRatioByFacade")), toString(*test));

    std::vector<WorkflowStep> workflowSteps = workflow.workflowSteps();
    ASSERT_EQ(3u, workflowSteps.size());

    ASSERT_TRUE(workflowSteps[0].optionalCast<MeasureStep>());
    MeasureStep measureStep = workflowSteps[0].cast<MeasureStep>();
    EXPECT_EQ("IncreaseWallRValue", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("cost"));
    ASSERT_EQ(VariantType::Double, measureStep.getArgument("cost")->variantType().value());
    EXPECT_EQ(123.321, measureStep.getArgument("cost")->valueAsDouble());
    ASSERT_TRUE(measureStep.getArgument("percent_increase"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_increase")->variantType().value());
    EXPECT_EQ(5, measureStep.getArgument("percent_increase")->valueAsInteger());
    ASSERT_TRUE(measureStep.getArgument("operating_expenses"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("operating_expenses")->variantType().value());
    EXPECT_EQ(0, measureStep.getArgument("operating_expenses")->valueAsInteger());

    ASSERT_TRUE(workflowSteps[1].optionalCast<MeasureStep>());
    measureStep = workflowSteps[1].cast<MeasureStep>();
    EXPECT_EQ("IncreaseRoofRValue", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("cost"));
    ASSERT_EQ(VariantType::Double, measureStep.getArgument("cost")->variantType().value());
    EXPECT_EQ(321.123, measureStep.getArgument("cost")->valueAsDouble());
    ASSERT_TRUE(measureStep.getArgument("percent_increase"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_increase")->variantType().value());
    EXPECT_EQ(15, measureStep.getArgument("percent_increase")->valueAsInteger());
    ASSERT_TRUE(measureStep.getArgument("space_type"));
    ASSERT_EQ(VariantType::String, measureStep.getArgument("space_type")->variantType().value());
    EXPECT_EQ("*All*", measureStep.getArgument("space_type")->valueAsString());

    ASSERT_TRUE(workflowSteps[2].optionalCast<MeasureStep>());
    measureStep = workflowSteps[2].cast<MeasureStep>();
    EXPECT_EQ("DecreaseThermalMass", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("has_bool"));
    ASSERT_EQ(VariantType::Boolean, measureStep.getArgument("has_bool")->variantType().value());
    EXPECT_EQ(true, measureStep.getArgument("has_bool")->valueAsBoolean());
    ASSERT_TRUE(measureStep.getArgument("percent_decrease"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_decrease")->variantType().value());
    EXPECT_EQ(5, measureStep.getArgument("percent_decrease")->valueAsInteger());

  } catch (const std::exception& e){
    EXPECT_TRUE(false) << e.what();
  }
}

WorkflowStepResult getWorkflowStepResult(const WorkflowStep& step)
{
  std::string stepName;
  if (step.optionalCast<MeasureStep>()){
    stepName = step.cast<MeasureStep>().measureDirName();
  }

  WorkflowStepResult workflowStepResult;
  workflowStepResult.setStartedAt(DateTime::nowUTC());
  workflowStepResult.setCompletedAt(DateTime::nowUTC());
  workflowStepResult.setStepResult(StepResult::Success);
  workflowStepResult.setInitialCondition(stepName + " Initial Condition");
  workflowStepResult.setFinalCondition(stepName + " Final Condition");
  workflowStepResult.addStepError(stepName + " Error 1");
  workflowStepResult.addStepError(stepName + " Error 2");
  workflowStepResult.addStepError(stepName + " Error 3");
  workflowStepResult.addStepWarning(stepName + " Warning 1");
  workflowStepResult.addStepWarning(stepName + " Warning 2");
  workflowStepResult.addStepWarning(stepName + " Warning 3");
  workflowStepResult.addStepInfo(stepName + " Info 1");
  workflowStepResult.addStepInfo(stepName + " Info 2");
  workflowStepResult.addStepInfo(stepName + " Info 3");
  workflowStepResult.addStepValue(WorkflowStepValue(stepName + " String Value", "String"));
  workflowStepResult.addStepValue(WorkflowStepValue(stepName + " Double Value", 1.1));
  workflowStepResult.addStepValue(WorkflowStepValue(stepName + " Int Value", 1));
  workflowStepResult.addStepValue(WorkflowStepValue(stepName + " Bool Value", true));
  workflowStepResult.addStepFile(stepName + " File.1");
  workflowStepResult.addStepFile(stepName + " File.2");
  workflowStepResult.setStdOut(stepName + " StdOut");
  workflowStepResult.setStdErr(stepName + " StdErr");
  return workflowStepResult;
}

void checkWorkflowStepResult(const WorkflowStep& step)
{
  std::string stepName;
  if (step.optionalCast<MeasureStep>()){
    stepName = step.cast<MeasureStep>().measureDirName();
  }

  ASSERT_TRUE(step.result());
  WorkflowStepResult workflowStepResult = step.result().get();

  ASSERT_TRUE(workflowStepResult.startedAt());
  EXPECT_TRUE(workflowStepResult.startedAt().get() <= DateTime::nowUTC());

  ASSERT_TRUE(workflowStepResult.completedAt());
  EXPECT_TRUE(workflowStepResult.startedAt().get() <= workflowStepResult.completedAt().get());
  EXPECT_TRUE(workflowStepResult.completedAt().get() <= DateTime::nowUTC());

  ASSERT_TRUE(workflowStepResult.stepResult ());
  EXPECT_EQ(StepResult::Success, workflowStepResult.stepResult().get().value());

  ASSERT_TRUE(workflowStepResult.initialCondition());
  EXPECT_EQ(stepName + " Initial Condition", workflowStepResult.initialCondition());

  ASSERT_TRUE(workflowStepResult.finalCondition());
  EXPECT_EQ(stepName + " Final Condition", workflowStepResult.finalCondition());

  ASSERT_EQ(3u, workflowStepResult.stepErrors().size());
  EXPECT_EQ(stepName + " Error 1", workflowStepResult.stepErrors()[0]);
  EXPECT_EQ(stepName + " Error 2", workflowStepResult.stepErrors()[1]);
  EXPECT_EQ(stepName + " Error 3", workflowStepResult.stepErrors()[2]);

  ASSERT_EQ(3u, workflowStepResult.stepWarnings().size());
  EXPECT_EQ(stepName + " Warning 1", workflowStepResult.stepWarnings()[0]);
  EXPECT_EQ(stepName + " Warning 2", workflowStepResult.stepWarnings()[1]);
  EXPECT_EQ(stepName + " Warning 3", workflowStepResult.stepWarnings()[2]);

  ASSERT_EQ(3u, workflowStepResult.stepInfo().size());
  EXPECT_EQ(stepName + " Info 1", workflowStepResult.stepInfo()[0]);
  EXPECT_EQ(stepName + " Info 2", workflowStepResult.stepInfo()[1]);
  EXPECT_EQ(stepName + " Info 3", workflowStepResult.stepInfo()[2]);

  ASSERT_EQ(4u, workflowStepResult.stepValues().size());
  EXPECT_EQ(stepName + " String Value", workflowStepResult.stepValues()[0].name());
  EXPECT_EQ(VariantType::String, workflowStepResult.stepValues()[0].variantType().value());
  EXPECT_EQ(stepName + " Double Value", workflowStepResult.stepValues()[1].name());
  EXPECT_EQ(VariantType::Double, workflowStepResult.stepValues()[1].variantType().value());
  EXPECT_EQ(stepName + " Int Value", workflowStepResult.stepValues()[2].name());
  EXPECT_EQ(VariantType::Integer, workflowStepResult.stepValues()[2].variantType().value());
  EXPECT_EQ(stepName + " Bool Value", workflowStepResult.stepValues()[3].name());
  EXPECT_EQ(VariantType::Boolean, workflowStepResult.stepValues()[3].variantType().value());

  ASSERT_EQ(2u, workflowStepResult.stepFiles().size());
  EXPECT_EQ(stepName + " File.1", toString(workflowStepResult.stepFiles()[0]));
  EXPECT_EQ(stepName + " File.2", toString(workflowStepResult.stepFiles()[1]));

  ASSERT_TRUE(workflowStepResult.stdOut());
  EXPECT_EQ(stepName + " StdOut", workflowStepResult.stdOut().get());

  ASSERT_TRUE(workflowStepResult.stdErr());
  EXPECT_EQ(stepName + " StdErr", workflowStepResult.stdErr().get());

}

TEST(Filetypes, WorkflowJSON_Min_Results)
{
  path p = resourcesPath() / toPath("utilities/Filetypes/min.osw");
  path p2 = resourcesPath() / toPath("utilities/Filetypes/min.results.out.osw");
  ASSERT_TRUE(WorkflowJSON::load(p));

  try{
    WorkflowJSON workflow(p);
    EXPECT_TRUE(workflow.checkForUpdates());
    ASSERT_TRUE(workflow.oswPath());
    EXPECT_EQ(p, workflow.oswPath().get());
    EXPECT_EQ(".", toString(workflow.rootDir()));
    EXPECT_EQ(toString(p.parent_path()), toString(workflow.absoluteRootDir()));
    EXPECT_FALSE(workflow.seedFile());
    EXPECT_FALSE(workflow.weatherFile());

    std::vector<WorkflowStep> workflowSteps = workflow.workflowSteps();
    ASSERT_EQ(3u, workflowSteps.size());

    ASSERT_TRUE(workflowSteps[0].optionalCast<MeasureStep>());
    MeasureStep measureStep = workflowSteps[0].cast<MeasureStep>();
    EXPECT_EQ("IncreaseWallRValue", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("cost"));
    ASSERT_EQ(VariantType::Double, measureStep.getArgument("cost")->variantType().value());
    EXPECT_EQ(123.321, measureStep.getArgument("cost")->valueAsDouble());
    ASSERT_TRUE(measureStep.getArgument("percent_increase"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_increase")->variantType().value());
    EXPECT_EQ(5, measureStep.getArgument("percent_increase")->valueAsInteger());
    ASSERT_TRUE(measureStep.getArgument("operating_expenses"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("operating_expenses")->variantType().value());
    EXPECT_EQ(0, measureStep.getArgument("operating_expenses")->valueAsInteger());

    ASSERT_TRUE(workflowSteps[1].optionalCast<MeasureStep>());
    measureStep = workflowSteps[1].cast<MeasureStep>();
    EXPECT_EQ("IncreaseRoofRValue", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("cost"));
    ASSERT_EQ(VariantType::Double, measureStep.getArgument("cost")->variantType().value());
    EXPECT_EQ(321.123, measureStep.getArgument("cost")->valueAsDouble());
    ASSERT_TRUE(measureStep.getArgument("percent_increase"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_increase")->variantType().value());
    EXPECT_EQ(15, measureStep.getArgument("percent_increase")->valueAsInteger());
    ASSERT_TRUE(measureStep.getArgument("space_type"));
    ASSERT_EQ(VariantType::String, measureStep.getArgument("space_type")->variantType().value());
    EXPECT_EQ("*All*", measureStep.getArgument("space_type")->valueAsString());

    ASSERT_TRUE(workflowSteps[2].optionalCast<MeasureStep>());
    measureStep = workflowSteps[2].cast<MeasureStep>();
    EXPECT_EQ("DecreaseThermalMass", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("has_bool"));
    ASSERT_EQ(VariantType::Boolean, measureStep.getArgument("has_bool")->variantType().value());
    EXPECT_EQ(true, measureStep.getArgument("has_bool")->valueAsBoolean());
    ASSERT_TRUE(measureStep.getArgument("percent_decrease"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_decrease")->variantType().value());
    EXPECT_EQ(5, measureStep.getArgument("percent_decrease")->valueAsInteger());
    
    EXPECT_FALSE(workflow.checkForUpdates());
    workflowSteps[0].setResult(getWorkflowStepResult(workflowSteps[0]));
    workflowSteps[1].setResult(getWorkflowStepResult(workflowSteps[1]));
    workflowSteps[2].setResult(getWorkflowStepResult(workflowSteps[2]));
    EXPECT_TRUE(workflow.checkForUpdates());

    EXPECT_TRUE(workflow.saveAs(p2));

  } catch (const std::exception& e){
    EXPECT_TRUE(false) << e.what();
  }

  ASSERT_TRUE(WorkflowJSON::load(p2));
  try{
    WorkflowJSON workflow(p2);
    EXPECT_FALSE(workflow.checkForUpdates());
    ASSERT_TRUE(workflow.oswPath());
    EXPECT_EQ(p2, workflow.oswPath().get());
    EXPECT_EQ(".", toString(workflow.rootDir()));
    EXPECT_EQ(toString(p2.parent_path()), toString(workflow.absoluteRootDir()));
    EXPECT_FALSE(workflow.seedFile());
    EXPECT_FALSE(workflow.weatherFile());

    std::vector<WorkflowStep> workflowSteps = workflow.workflowSteps();
    ASSERT_EQ(3u, workflowSteps.size());

    ASSERT_TRUE(workflowSteps[0].optionalCast<MeasureStep>());
    MeasureStep measureStep = workflowSteps[0].cast<MeasureStep>();
    EXPECT_EQ("IncreaseWallRValue", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("cost"));
    ASSERT_EQ(VariantType::Double, measureStep.getArgument("cost")->variantType().value());
    EXPECT_EQ(123.321, measureStep.getArgument("cost")->valueAsDouble());
    ASSERT_TRUE(measureStep.getArgument("percent_increase"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_increase")->variantType().value());
    EXPECT_EQ(5, measureStep.getArgument("percent_increase")->valueAsInteger());
    ASSERT_TRUE(measureStep.getArgument("operating_expenses"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("operating_expenses")->variantType().value());
    EXPECT_EQ(0, measureStep.getArgument("operating_expenses")->valueAsInteger());
    checkWorkflowStepResult(workflowSteps[0]);

    ASSERT_TRUE(workflowSteps[1].optionalCast<MeasureStep>());
    measureStep = workflowSteps[1].cast<MeasureStep>();
    EXPECT_EQ("IncreaseRoofRValue", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("cost"));
    ASSERT_EQ(VariantType::Double, measureStep.getArgument("cost")->variantType().value());
    EXPECT_EQ(321.123, measureStep.getArgument("cost")->valueAsDouble());
    ASSERT_TRUE(measureStep.getArgument("percent_increase"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_increase")->variantType().value());
    EXPECT_EQ(15, measureStep.getArgument("percent_increase")->valueAsInteger());
    ASSERT_TRUE(measureStep.getArgument("space_type"));
    ASSERT_EQ(VariantType::String, measureStep.getArgument("space_type")->variantType().value());
    EXPECT_EQ("*All*", measureStep.getArgument("space_type")->valueAsString());
    checkWorkflowStepResult(workflowSteps[1]);

    ASSERT_TRUE(workflowSteps[2].optionalCast<MeasureStep>());
    measureStep = workflowSteps[2].cast<MeasureStep>();
    EXPECT_EQ("DecreaseThermalMass", measureStep.measureDirName());
    ASSERT_TRUE(measureStep.getArgument("has_bool"));
    ASSERT_EQ(VariantType::Boolean, measureStep.getArgument("has_bool")->variantType().value());
    EXPECT_EQ(true, measureStep.getArgument("has_bool")->valueAsBoolean());
    ASSERT_TRUE(measureStep.getArgument("percent_decrease"));
    ASSERT_EQ(VariantType::Integer, measureStep.getArgument("percent_decrease")->variantType().value());
    EXPECT_EQ(5, measureStep.getArgument("percent_decrease")->valueAsInteger());
    checkWorkflowStepResult(workflowSteps[2]);

  } catch (const std::exception& e){
    EXPECT_TRUE(false) << e.what();
  }
}

TEST(Filetypes, WorkflowJSON_Bad)
{
  path p = resourcesPath() / toPath("utilities/Filetypes/nonexistent.osw");
  EXPECT_THROW({ WorkflowJSON workflow(p); }, openstudio::Exception);
  EXPECT_FALSE(WorkflowJSON::load(p));

  p = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3.epw");
  EXPECT_THROW({ WorkflowJSON workflow(p); }, openstudio::Exception);
  EXPECT_FALSE(WorkflowJSON::load(p));
}

TEST(Filetypes, WorkflowStep_EscapeCharacters)
{
  MeasureStep step("\"My Measure\"");

  std::string jsonValue = "\"steps\" : [ {\"arguments\" : {}, \"measure_dir_name\" : \"IncreaseWallRValue\"}]";
  step.setArgument("\"My Argument\"", jsonValue);

  boost::optional<WorkflowStep> temp = WorkflowStep::fromString(step.string());
  ASSERT_TRUE(temp);
  ASSERT_TRUE(temp->optionalCast<MeasureStep>());
  MeasureStep step2 = temp->cast<MeasureStep>();

  std::cout << step.string() << std::endl;

  EXPECT_EQ("\"My Measure\"", step2.measureDirName());

  ASSERT_EQ(1u, step2.arguments().size());

  boost::optional<Variant> value = step2.getArgument("\"My Argument\"");
  ASSERT_TRUE(value);
  ASSERT_EQ(VariantType::String, value->variantType().value());
  EXPECT_EQ(jsonValue, value->valueAsString());

}

TEST(Filetypes, WorkflowStep_EscapeCharacters2)
{
  MeasureStep step(R"("My Measure")");

  std::string jsonValue = R"("steps" : [ {"arguments" : {}, "measure_dir_name" : "IncreaseWallRValue"}])";
  step.setArgument(R"("My Argument")", jsonValue);

  boost::optional<WorkflowStep> temp = WorkflowStep::fromString(step.string());
  ASSERT_TRUE(temp);
  ASSERT_TRUE(temp->optionalCast<MeasureStep>());
  MeasureStep step2 = temp->cast<MeasureStep>();

  std::cout << step.string() << std::endl;

  EXPECT_EQ("\"My Measure\"", step2.measureDirName());

  ASSERT_EQ(1u, step2.arguments().size());

  boost::optional<Variant> value = step2.getArgument("\"My Argument\"");
  ASSERT_TRUE(value);
  ASSERT_EQ(VariantType::String, value->variantType().value());
  EXPECT_EQ(jsonValue, value->valueAsString());

}

TEST(Filetypes, WorkflowStepResult_EscapeCharacters)
{
  WorkflowStepResult result;

  result.setInitialCondition("\"Initial Condition\"");
  result.setFinalCondition("\"Final Condition\"");
  result.addStepError("\"Step Error\"");
  result.addStepWarning("\"Step Warning\"");
  result.addStepInfo("\"Step Info\"");
  result.setStdOut("\"Standard Output\"");
  result.setStdErr("\"Standard Error\"");

  WorkflowStepValue value("\"Value Name\"", 1.1);
  result.addStepValue(value);

  boost::optional<WorkflowStepResult> result2 = WorkflowStepResult::fromString(result.string());
  ASSERT_TRUE(result2);

  std::cout << result.string() << std::endl;

  ASSERT_TRUE(result2->initialCondition());
  EXPECT_EQ("\"Initial Condition\"", result2->initialCondition().get());
  ASSERT_TRUE(result2->finalCondition());
  EXPECT_EQ("\"Final Condition\"", result2->finalCondition().get());
  /*ASSERT_TRUE(result2->initialCondition());
  result2.addStepError("\"Step Error\"");
  ASSERT_TRUE(result2->initialCondition());
  result2.addStepWarning("\"Step Warning\"");
  ASSERT_TRUE(result2->initialCondition());
  result2.addStepInfo("\"Step Info\"");
  ASSERT_TRUE(result2->initialCondition());
    */
  ASSERT_TRUE(result2->stdOut());
  EXPECT_EQ("\"Standard Output\"", result2->stdOut().get());
  ASSERT_TRUE(result2->stdErr());
  EXPECT_EQ("\"Standard Error\"", result2->stdErr().get());

}

TEST(Filetypes, WorkflowStepResult_EscapeCharacters2)
{
  WorkflowStepResult result;

  result.setInitialCondition(R"("Initial Condition")");
  result.setFinalCondition(R"("Final Condition")");
  result.addStepError(R"("Step Error")");
  result.addStepWarning(R"("Step Warning")");
  result.addStepInfo(R"("Step Info")");
  result.setStdOut(R"("Standard Output")");
  result.setStdErr(R"("Standard Error")");

  WorkflowStepValue value(R"("Value Name")", 1.1);
  result.addStepValue(value);

  boost::optional<WorkflowStepResult> result2 = WorkflowStepResult::fromString(result.string());
  ASSERT_TRUE(result2);

  std::cout << result.string() << std::endl;

  ASSERT_TRUE(result2->initialCondition());
  EXPECT_EQ("\"Initial Condition\"", result2->initialCondition().get());
  ASSERT_TRUE(result2->finalCondition());
  EXPECT_EQ("\"Final Condition\"", result2->finalCondition().get());
  /*ASSERT_TRUE(result2->initialCondition());
  result2.addStepError("\"Step Error\"");
  ASSERT_TRUE(result2->initialCondition());
  result2.addStepWarning("\"Step Warning\"");
  ASSERT_TRUE(result2->initialCondition());
  result2.addStepInfo("\"Step Info\"");
  ASSERT_TRUE(result2->initialCondition());
    */
  ASSERT_TRUE(result2->stdOut());
  EXPECT_EQ("\"Standard Output\"", result2->stdOut().get());
  ASSERT_TRUE(result2->stdErr());
  EXPECT_EQ("\"Standard Error\"", result2->stdErr().get());

}
