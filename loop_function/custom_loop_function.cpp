#include "custom_loop_function.h"
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/plugins/simulator/entities/box_entity.h>
#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_entity.h>
#include <cmath>
#include <iostream>
#include "buzz_utils.h"


CPatternLoopFunctions::CPatternLoopFunctions():
isSimDone(false)
{
   std::cout << "Custom Loop Function created" << std::endl;
}

void CPatternLoopFunctions::Init(TConfigurationNode& t_tree) {
   std::cout << "Init Called" << std::endl;
   try
   {  
      // Very bad way of parsing XML.. Need Fix
      TConfigurationNodeIterator itDistr;
      for(itDistr = itDistr.begin(&t_tree);
          itDistr != itDistr.end();
          ++itDistr)
          {
            std::cout << "Tree:" << itDistr->Value() << std::endl;
            TConfigurationNode& tDistr = *itDistr;
            
            GetNodeAttribute(tDistr, "output", m_strOutput);
            GetNodeAttribute(tDistr, "hipster_percentage", m_hipster_percentage);//hipster_percentage
            std::cout << "Output file:" << m_strOutput << std::endl;
            std::cout << "Hipster percentage:" << m_hipster_percentage << std::endl;

          }
      
      m_cOutput.open(m_strOutput.c_str(), std::ofstream::out);
      
      if(m_cOutput.fail()) {
         THROW_ARGOSEXCEPTION("Can't open file '" << m_strOutput << "'");
      }

      


      // Get Khepera controllers
      CSpace::TMapPerType& m_KheperaIV = GetSpace().GetEntitiesByType("kheperaiv");
      for (CSpace::TMapPerType::iterator it = m_KheperaIV.begin(); it != m_KheperaIV.end(); ++it)
      {
         CKheperaIVEntity& kheperaIVEntity_ = *any_cast<CKheperaIVEntity*>(it->second);
         buzzvm_t tBuzzVM = dynamic_cast<CBuzzController&>(kheperaIVEntity_.GetControllableEntity().GetController()).GetBuzzVM();
         RegisterFloat(tBuzzVM, "HIPSTER_PERCENTAGE", m_hipster_percentage/100.0);
         m_vecVMs.push_back(tBuzzVM);
         robot_opinions.push_back(0); // Initialize robot opinions         
      }
      std::cout << "Buzz VMs loaded : " << m_vecVMs.size() << std::endl;
   }
   catch(CARGoSException& ex)
   {
      THROW_ARGOSEXCEPTION_NESTED("Error parsing loop functions!", ex);
   }
   
}

void CPatternLoopFunctions::Destroy() {
   
   for(SInt32 opinion_:robot_opinions)
   {
      m_cOutput << opinion_ << " ";
   }
   m_cOutput.close();

   std::cout << "\nExperiment Done" << std::endl;
   std::cout << "Results saved in " << m_strOutput << std::endl;
   
}



bool CPatternLoopFunctions::IsExperimentFinished() {
   return isSimDone;
}


void CPatternLoopFunctions::PostStep() {
   SInt32 robot_opinion;
   bool checkIfDone = true;
   for(size_t i = 0; i< m_vecVMs.size(); i++)
   {
      FetchInt(m_vecVMs[i],"OPINION", robot_opinion);
      robot_opinions[i] = robot_opinion;
      checkIfDone = checkIfDone && (robot_opinion!=0);
      // std::cout << "my_opinion:" << robot_opinion << std::endl;
   }
   isSimDone = checkIfDone;
   std::cout << ".";
}


REGISTER_LOOP_FUNCTIONS(CPatternLoopFunctions, "custom_loop_function")