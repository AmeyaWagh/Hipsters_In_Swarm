#ifndef CUSTOM_LOOP_FUNCTIONS_H
#define CUSTOM_LOOP_FUNCTIONS_H

#include <buzz/argos/buzz_controller.h>
#include <argos3/core/simulator/loop_functions.h>
#include <argos3/core/simulator/entity/floor_entity.h>
#include <argos3/core/utility/math/range.h>
#include <argos3/core/utility/math/rng.h>
#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_entity.h>

using namespace argos;

class CPatternLoopFunctions : public CLoopFunctions {

public:

   CPatternLoopFunctions();
   virtual ~CPatternLoopFunctions() {}
   virtual void Init(TConfigurationNode& t_tree);
   virtual void Destroy();
   virtual void PostStep();
   bool IsExperimentFinished();



private:

   std::vector<buzzvm_t> m_vecVMs;
   std::vector<SInt32> robot_opinions;

   bool isSimDone;

   /* Output file name */
   std::string m_strOutput;
   /* Output file stream */
   std::ofstream m_cOutput;

   /* Random number generator */
   CRandom::CRNG* m_pcRNG;
};

#endif