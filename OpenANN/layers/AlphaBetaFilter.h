#pragma once

#include <layers/Layer.h>
#include <io/Logger.h>
#include <ActivationFunctions.h>

namespace OpenANN {

class AlphaBetaFilter : public Layer
{
  Logger debugLogger;
  int I, J;
  fpt deltaT;
  bool bias;
  fpt stdDev;
  Vt gamma;
  Vt gammad;
  Vt alpha;
  Vt beta;
  bool first;
  Vt* x;
  Vt y;

public:
  AlphaBetaFilter(OutputInfo info, fpt deltaT, bool bias, fpt stdDev);
  virtual OutputInfo initialize(std::vector<fpt*>& parameterPointers, std::vector<fpt*>& parameterDerivativePointers);
  virtual void initializeParameters();
  virtual void updatedParameters();
  virtual void reset();
  virtual void forwardPropagate(Vt* x, Vt*& y, bool dropout);
  virtual void backpropagate(Vt* ein, Vt*& eout);
  virtual Vt& getOutput();
};

}
