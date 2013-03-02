#pragma once

#include <layers/Layer.h>
#include <ActivationFunctions.h>

namespace OpenANN {

/**
 * @class Compressed
 *
 * Fully connected layer with compressed weights.
 *
 * The number of optimizable parameters is reduced due to compressed indirect
 * weight representation. The weight matrix is generated by
 * \f$ W = \alpha \Phi \f$, where \f$ \alpha \f$ is an optimizable parameter
 * matrix with less components than \f$ W \f$ and \f$ \Phi \f$ is a fixed
 * matrix that could e. g. be generated randomly. Note that the compressed
 * representation of weights is equivalent to compressing the input of the
 * layer with \f$ \Phi x \f$ and regarding \f$ \alpha \f$ as the weight
 * matrix.
 *
 * [1] A. Fabisch, Y. Kassahun, H. Wöhrle and F. Kirchner:
 * Learning in compressed space,
 * Neural Networks, accepted, to appear 2013.
 */
class Compressed : public Layer
{
  int I, J, M;
  bool bias;
  ActivationFunction act;
  fpt stdDev;
  fpt dropoutProbability;
  Mt W;
  Mt Wd;
  Mt phi;
  Mt alpha;
  Mt alphad;
  Vt* x;
  Vt a;
  Vt y;
  Vt yd;
  Vt deltas;
  Vt e;

public:
  Compressed(OutputInfo info, int J, int M, bool bias, ActivationFunction act,
             const std::string& compression, fpt stdDev,
             fpt dropoutProbability);
  virtual OutputInfo initialize(std::vector<fpt*>& parameterPointers,
                                std::vector<fpt*>& parameterDerivativePointers);
  virtual void initializeParameters();
  virtual void updatedParameters();
  virtual void forwardPropagate(Vt* x, Vt*& y, bool dropout);
  virtual void backpropagate(Vt* ein, Vt*& eout);
  virtual Vt& getOutput();
};

}