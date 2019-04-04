#include "custom_loop_function.h"
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/plugins/simulator/entities/box_entity.h>
#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_entity.h>
#include <cmath>
#include <iostream>

/****************************************/
/****************************************/

static const std::string THECONTROLLER = "bc";
static const size_t MAX_PLACE_TRIALS = 100;
static const Real WALL_THICKNESS   = 0.1;
static const Real WALL_HEIGHT      = 0.5;

/****************************************/
/****************************************/
CPatternLoopFunctions::CPatternLoopFunctions():
isSimDone(false)
{
   // Constructor
   std::cout << "Cstor Called" << std::endl;
}

void CPatternLoopFunctions::Init(TConfigurationNode& t_tree) {
   std::cout << "Init Called" << std::endl;
   try
   {
      /* code */
      // buzzvm_t tBuzzVM
      CSpace::TMapPerType& m_KheperaIV = GetSpace().GetEntitiesByType("kheperaiv");
      for (CSpace::TMapPerType::iterator it = m_KheperaIV.begin(); it != m_KheperaIV.end(); ++it)
      {
         CKheperaIVEntity& kheperaIVEntity_ = *any_cast<CKheperaIVEntity*>(it->second);
         buzzvm_t tBuzzVM = dynamic_cast<CBuzzController&>(kheperaIVEntity_.GetControllableEntity().GetController()).GetBuzzVM();
         m_vecVMs.push_back(tBuzzVM);
         robot_opinions.push_back(0);
      }
      std::cout << "Buzz VMs loaded : " << m_vecVMs.size() << std::endl;
   }
   catch(CARGoSException& ex)
   {
      THROW_ARGOSEXCEPTION_NESTED("Error parsing loop functions!", ex);
   }
   
   // try {
   //    /* Create a RNG (it is automatically disposed of by ARGoS) */
   //    m_pcRNG = CRandom::CreateRNG("argos");
   //    /* Parse output file name and attempt to open it */
   //    GetNodeAttribute(t_tree, "output", m_strOutput);
   //    m_cOutput.open(m_strOutput.c_str(), std::ofstream::out);
   //    if(m_cOutput.fail()) {
   //       THROW_ARGOSEXCEPTION("Can't open file '" << m_strOutput << "'");
   //    }
   //    m_cOutput << "Time\t"
   //              << "Robot\t"
   //              << "X\t"
   //              << "Y\t"
   //              << "PickedPatternNum\t"
   //              << "PickedPattern\t"
   //              << "PickedPatternProb\t"
   //              << "CorrectPatternProb\n";
   //    /* Parse pattern-related parameters */
   //    TConfigurationNode& tPatterns = GetNode(t_tree, "patterns");
   //    GetNodeAttribute(tPatterns, "cells_on_side", m_unNumCellsOnSide);
   //    GetNodeAttribute(tPatterns, "pattern", m_unPattern);
   //    GetNodeAttribute(tPatterns, "wrong_pattern", m_unWrongPattern);
   //    GetNodeAttribute(tPatterns, "wrong_frequency", m_unWrongFrequency);

   //    /* Parse robot-related parameters */
   //    TConfigurationNode& tRobots = GetNode(t_tree, "robots");
   //    UInt32 unNumRobots;
   //    GetNodeAttribute(tRobots, "num_robots",  unNumRobots);
   //    UInt32 unNumLiars;
   //    GetNodeAttribute(tRobots, "num_liars",   unNumLiars);
   //    unNumLiars = int(unNumLiars*1.0/100 * unNumRobots);
   //    Real fCommRange;
   //    GetNodeAttribute(tRobots, "comm_range",  fCommRange);
   //    Real fDensity;
   //    GetNodeAttribute(tRobots, "density",     fDensity);
   //    std::string strGoodFun;
   //    GetNodeAttribute(tRobots, "good_fun",    strGoodFun);
   //    std::string strBadFun;
   //    GetNodeAttribute(tRobots, "bad_fun",     strBadFun);
   //    Real fNoiseProb;
   //    GetNodeAttribute(tRobots, "noise_prob",  fNoiseProb);
   //    UInt32 unCommPeriod;
   //    GetNodeAttribute(tRobots, "comm_period", unCommPeriod);
   //    /* Place robots */
   //    PlaceRobots(unNumRobots, unNumLiars,
   //                fCommRange, fDensity,
   //                strGoodFun, strBadFun,
   //                fNoiseProb, unCommPeriod);
   // }
   // catch(CARGoSException& ex) {
   //    THROW_ARGOSEXCEPTION_NESTED("Error parsing loop functions!", ex);
   // }
}

void CPatternLoopFunctions::Destroy() {
   // m_cOutput.close();
   std::cout << "Experiment Done" << std::endl;
}



buzzvm_state FetchInt(buzzvm_t t_vm,
                      const std::string& str_sym,
                      SInt32& n_value) {
   buzzvm_pushs(t_vm, buzzvm_string_register(t_vm, str_sym.c_str(), 0));
   buzzvm_gload(t_vm);
   buzzvm_type_assert(t_vm, 1, BUZZTYPE_INT);
   n_value = buzzvm_stack_at(t_vm, 1)->i.value;
   return BUZZVM_STATE_READY;
}

buzzvm_state FetchFloat(buzzvm_t t_vm,
                        const std::string& str_sym,
                        Real& f_value) {
   buzzvm_pushs(t_vm, buzzvm_string_register(t_vm, str_sym.c_str(), 0));
   buzzvm_gload(t_vm);
   buzzvm_type_assert(t_vm, 1, BUZZTYPE_FLOAT);
   f_value = buzzvm_stack_at(t_vm, 1)->f.value;
   return BUZZVM_STATE_READY;
}


/****************************************/
/****************************************/

bool CPatternLoopFunctions::IsExperimentFinished() {
//   int flag = 0;
//   if(GetSpace().GetSimulationClock() >= 10){
//     flag = 1;
//     SInt32 nPickedPattern;
//     Real fPickedPatternProb;
//     Real fCorrectPatternProb;
//     SInt32 nPickedPatternNum;
//     /* Go through non-lying robots */
//    for(size_t i = 0; i < m_vecGoodVMs.size(); ++i) {
//       /* Get data from the VM */
//       FetchInt(m_vecGoodVMs[i], "picked_pattern_num", nPickedPatternNum);
//       FetchInt(m_vecGoodVMs[i], "picked_pattern", nPickedPattern);
//       FetchFloat(m_vecGoodVMs[i], "picked_pattern_prob", fPickedPatternProb);
//       FetchFloat(m_vecGoodVMs[i], "correct_pattern_prob", fCorrectPatternProb);
//       if (nPickedPatternNum == 1 && nPickedPattern == m_unPattern && fCorrectPatternProb > 0.99)
//         continue;
//       flag = 0;
//    }
//   }

//   if(GetSpace().GetSimulationClock() >= m_fExptTime || flag == 1){
//     // ResultFile << GetSpace().GetSimulationClock() << std::endl;
//     // ResultFile << correct_belief_num_robot << std::endl;
//     return true;
//   }
//   // if(correct_belief_num_robot == truthfulRobots){
//   //   ResultFile << GetSpace().GetSimulationClock() << std::endl;
//   //   return true;
//   // }
//   return false;
   return isSimDone;
}


void CPatternLoopFunctions::PostStep() {
   // SInt32 nPickedPattern;
   // Real fPickedPatternProb;
   // Real fCorrectPatternProb;
   // SInt32 nPickedPatternNum;
   // /* Go through non-lying robots */
   // for(size_t i = 0; i < m_vecGoodVMs.size(); ++i) {
   //    /* Get data from the VM */
   //    FetchInt(m_vecGoodVMs[i], "picked_pattern_num", nPickedPatternNum);
   //    FetchInt(m_vecGoodVMs[i], "picked_pattern", nPickedPattern);
   //    FetchFloat(m_vecGoodVMs[i], "picked_pattern_prob", fPickedPatternProb);
   //    FetchFloat(m_vecGoodVMs[i], "correct_pattern_prob", fCorrectPatternProb);
   //    /* Save data to disk */
   //    m_cOutput << GetSpace().GetSimulationClock()      << "\t"  // time step
   //              << m_vecGoodVMs[i]->robot               << "\t"  // robot id
   //              << m_vecGoodAnchors[i]->Position.GetX() << "\t"  // pos x
   //              << m_vecGoodAnchors[i]->Position.GetY() << "\t"  // pos y
   //              << nPickedPatternNum                    << "\t"  // num of picked patterns
   //              << nPickedPattern                       << "\t"  // picked pattern code
   //              << fPickedPatternProb                   << "\t"  // picked pattern
   //              << fCorrectPatternProb                  << "\n"; // correct pattern
   // }
   SInt32 robot_opinion;
   bool checkIfDone = true;
   for(size_t i = 0; i< m_vecVMs.size(); i++)
   {
      FetchInt(m_vecVMs[i],"OPINION", robot_opinion);
      robot_opinions[i] = robot_opinion;
      checkIfDone = checkIfDone && (robot_opinion!=0);
      std::cout << "my_opinion:" << robot_opinion << std::endl;
   }
   isSimDone = checkIfDone;
}

/****************************************/
/****************************************/

static void RegisterFunction(buzzvm_t t_vm,
                             const std::string& str_sym,
                             const std::string& str_fun) {
   buzzvm_pushs(t_vm, buzzvm_string_register(t_vm, str_sym.c_str(), 1));
   buzzvm_pushs(t_vm, buzzvm_string_register(t_vm, str_fun.c_str(), 0));
   buzzvm_gload(t_vm);
   if(buzzvm_stack_at(t_vm, 1)->o.type != BUZZTYPE_CLOSURE) {
      THROW_ARGOSEXCEPTION("Buzz script does not contain function '" << str_fun << "'");
   }
   buzzvm_gstore(t_vm);
}

static void RegisterInt(buzzvm_t t_vm,
                        const std::string& str_sym,
                        SInt32 n_value) {
   buzzvm_pushs(t_vm,
                buzzvm_string_register(t_vm,
                                       str_sym.c_str(), 1));
   buzzvm_pushi(t_vm, n_value);
   buzzvm_gstore(t_vm);
}

static void RegisterFloat(buzzvm_t t_vm,
                          const std::string& str_sym,
                          Real f_value) {
   buzzvm_pushs(t_vm,
                buzzvm_string_register(t_vm,
                                       str_sym.c_str(), 1));
   buzzvm_pushf(t_vm, f_value);
   buzzvm_gstore(t_vm);
}



/****************************************/
/****************************************/

REGISTER_LOOP_FUNCTIONS(CPatternLoopFunctions, "custom_loop_function")