#include "custom_loop_function.h"
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/plugins/simulator/entities/box_entity.h>
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
CPatternLoopFunctions::CPatternLoopFunctions(){
   // Constructor
   std::cout << "Cstor Called" << std::endl;
}

void CPatternLoopFunctions::Init(TConfigurationNode& t_tree) {
   std::cout << "Init Called" << std::endl;
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
}

/****************************************/
/****************************************/

// CColor CPatternLoopFunctions::GetFloorColor(const CVector2& c_pos) {
//    /* Make sure position is within arena limits */
//    if(c_pos.GetX() >= m_fArenaSide ||
//       c_pos.GetY() >= m_fArenaSide) {
//       return CColor::GRAY50;
//    }
//    /* Calculate cell index from position */
//    UInt32 unI = m_unNumCellsOnSide * c_pos.GetX() / m_fArenaSide;
//    UInt32 unJ = m_unNumCellsOnSide * c_pos.GetY() / m_fArenaSide;
//    UInt32 unIdx = unJ * m_unNumCellsOnSide + unI;
//    /* Return color */
//    return (m_unPattern & (1 << unIdx)) ? CColor::WHITE : CColor::BLACK;
// }

/****************************************/
/****************************************/

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
  return false;
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

// void CPatternLoopFunctions::PlaceRobots(UInt32 un_robots,
//                                         UInt32 un_liars,
//                                         Real f_commrange,
//                                         Real f_density,
//                                         const std::string& str_good_fun,
//                                         const std::string& str_bad_fun,
//                                         Real f_noise_prob,
//                                         UInt32 un_comm_period) {
//    try {
//       /* Calculate area covered by the communication range */
//       Real fCommArea = CRadians::PI.GetValue() * Square(f_commrange);
//       /* Calculate side of the region in which the robots are scattered */
//       m_fArenaSide = Sqrt((fCommArea * un_robots) / f_density);
//       m_fExptTime = 600*m_fArenaSide;
//       CRange<Real> cAreaRange(0.0, m_fArenaSide);
//       /* Place walls */
//       Real fArenaSide2 = m_fArenaSide / 2.0;
//       AddEntity(*new CBoxEntity("wall_south", CVector3( fArenaSide2,            0, 0), CQuaternion(), false, CVector3(m_fArenaSide, WALL_THICKNESS, WALL_HEIGHT)));
//       AddEntity(*new CBoxEntity("wall_north", CVector3( fArenaSide2, m_fArenaSide, 0), CQuaternion(), false, CVector3(m_fArenaSide, WALL_THICKNESS, WALL_HEIGHT)));
//       AddEntity(*new CBoxEntity("wall_west",  CVector3(           0,  fArenaSide2, 0), CQuaternion(), false, CVector3(WALL_THICKNESS, m_fArenaSide, WALL_HEIGHT)));
//       AddEntity(*new CBoxEntity("wall_east",  CVector3(m_fArenaSide,  fArenaSide2, 0), CQuaternion(), false, CVector3(WALL_THICKNESS, m_fArenaSide, WALL_HEIGHT)));
//       /* Place robots */
//       UInt32 unTrials;
//       CKheperaIVEntity* pcKhIV;
//       std::ostringstream cKhIVId;
//       CVector3 cKhIVPos;
//       CQuaternion cKhIVRot;
//       /* For each robot */
//       for(size_t i = 0; i < un_robots; ++i) {
//          /* Make the id */
//          cKhIVId.str("");
//          cKhIVId << "kh" << i;
//          /* Create the robot in the origin and add it to ARGoS space */
//          pcKhIV = new CKheperaIVEntity(
//             cKhIVId.str(),
//             THECONTROLLER,
//             CVector3(),
//             CQuaternion(),
//             f_commrange,
//             500);
//          AddEntity(*pcKhIV);
//          /* Try to place it in the arena */
//          unTrials = 0;
//          bool bDone;
//          do {
//             /* Choose a random position */
//             ++unTrials;
//             cKhIVPos.Set(m_pcRNG->Uniform(cAreaRange),
//                          m_pcRNG->Uniform(cAreaRange),
//                          0.0f);
//             cKhIVRot.FromAngleAxis(m_pcRNG->Uniform(CRadians::UNSIGNED_RANGE),
//                                    CVector3::Z);
//             bDone = MoveEntity(pcKhIV->GetEmbodiedEntity(), cKhIVPos, cKhIVRot);
//          } while(!bDone && unTrials <= MAX_PLACE_TRIALS);
//          if(!bDone) {
//             THROW_ARGOSEXCEPTION("Can't place " << cKhIVId.str());
//          }
//          /* Placement successful */
//          /* Save the VM */
//          buzzvm_t tBuzzVM =
//             dynamic_cast<CBuzzController&>(
//                pcKhIV->GetControllableEntity().GetController()).
//             GetBuzzVM();
//          if(i >= un_liars) {
//          //if(i >= 0) {
//             m_vecGoodAnchors.push_back(&pcKhIV->GetEmbodiedEntity().GetOriginAnchor());
//             m_vecGoodVMs.push_back(tBuzzVM);
//          }
//          /* Set noise probability */
//          RegisterFloat(tBuzzVM, "noise_prob", f_noise_prob);
//          /* Set communication period */
//          RegisterInt(tBuzzVM, "comm_period", un_comm_period);
//          /* Set number of liars */
//          RegisterInt(tBuzzVM, "num_liars", un_liars);
//          /* Set number of patterns */
//          // RegisterInt(tBuzzVM, "num_patterns", 30);
//          RegisterInt(tBuzzVM, "num_patterns", 1 << (m_unNumCellsOnSide * m_unNumCellsOnSide));
//          /* Set correct pattern */
//          RegisterInt(tBuzzVM, "pattern", m_unPattern);
//          /* Set wrong pattern */
//          RegisterInt(tBuzzVM, "wrong_pattern", m_unWrongPattern);
//          /* Set frequency of change of wrong pattern */
//          RegisterInt(tBuzzVM, "wrong_frequency", m_unWrongFrequency);
//          /* Set scripts */
//          /* Set arena_side */
//          RegisterFloat(tBuzzVM, "arena_side", m_fArenaSide);
//          /* Set total experiment time */
//          RegisterFloat(tBuzzVM, "experiment_time", m_fExptTime);
//          /* Set cells_on_side */
//          RegisterInt(tBuzzVM, "cells_on_side", m_unNumCellsOnSide);
//          /* Good/bad robots functions */
//          RegisterFunction(tBuzzVM, "good_fun_init", "good_fun_" + str_good_fun + "_init");
//          RegisterFunction(tBuzzVM, "good_fun_step", "good_fun_" + str_good_fun + "_step");
//          RegisterFunction(tBuzzVM, "bad_fun_init", "bad_fun_" + str_bad_fun + "_init");
//          RegisterFunction(tBuzzVM, "bad_fun_step", "bad_fun_" + str_bad_fun + "_step");
//          buzzvm_function_call(tBuzzVM, "lf_init", 0);
//       }
//    }
//    catch(CARGoSException& ex) {
//       THROW_ARGOSEXCEPTION_NESTED("While placing robots", ex);
//    }
// }

/****************************************/
/****************************************/

REGISTER_LOOP_FUNCTIONS(CPatternLoopFunctions, "custom_loop_function")