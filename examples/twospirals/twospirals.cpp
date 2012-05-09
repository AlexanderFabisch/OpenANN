#include "TwoSpiralsVisualization.h"
#include <io/FANNFormatLoader.h>
#include <QApplication>
#include <OpenANN>
#ifdef PARALLEL_CORES
#include <omp.h>
#endif

/**
 * \page TwoSpirals Two Spirals
 *
 * \section DataSet Data Set
 *
 * This is a classification benchmark which is particularly difficult for
 * gradient descent optimization.
 *
 * The two spirals data set was developed by Lang and Witbrock [1]. The data set
 * we use here is taken from the
 * <a href="http://leenissen.dk/fann/wp/" target=_blank>FANN</a> library. It
 * consists of 193 training instances and 193 test instances located on a 2D
 * surface. They belong to one of two spirals:
 *
 * \image html TwoSpirals-DataSet.png
 *
 * \section Architecture Network Architecture
 *
 * It is possible to solve this problem with one or two hidden layers. But
 * architectures with two hidden layers need less connections and can learn
 * faster. The architecture we chose here is 2-20-20-1 with bias. You can solve
 * this problem with different compression setups. the smallest number of
 * parameters that reliably solves this problem is 3-6-1 with orthogonal cosine
 * functions. All activation functions are tangens hyperbolicus (MLP::TANH). The
 * best optimization algorithm is Levenberq-Marquardt (MLP::BATCH_LMA).
 *
 * \section UI User Interface
 *
 * There are no arguments you can pass to the program. Compile and start with
 * \code
./TwoSpirals
\endcode
 * You can use the following keys to control the program:
 *  - Q: Toggle display of training set
 *  - W: Toggle display of test set
 *  - E: Toggle display of predicted classes for the whole surface
 *  - R: Toggle display of smooth prediction transitions (black+white or grey)
 *  - A: Start visible training (with parameters reset)
 *  - S: Start visible training (without parameters reset)
 *  - P: Print current MLP parameters
 *  - Escape: Quit application.
 *
 * A trained model could make these predictions:
 *
 * \image html TwoSpirals-Model.png
 *
 * \section References
 *
 * [1] Kevin J. Lang and Michael J. Witbrock: Learning to Tell Two Spirals
 *    Apart. In: Proceedings of the 1988 Connectionist Models Summer School,
 *    1988. ISBN: 0-55860-015-9
 */

int main(int argc, char** argv)
{
#ifdef PARALLEL_CORES
  omp_set_num_threads(PARALLEL_CORES);
#endif
  OpenANNLibraryInfo::print();
  QApplication app(argc, argv);

  std::string directory = ".";
  if(argc > 1)
    directory = std::string(argv[1]);
  FANNFormatLoader loader(directory + "/two-spiral");
  for(int n = 0; n < loader.testN; n++)
  {
    loader.testOutput(0, n) -= 0.5;
    loader.testOutput(0, n) *= 2.0;
  }
  for(int n = 0; n < loader.trainingN; n++)
  {
    loader.trainingOutput(0, n) -= 0.5;
    loader.trainingOutput(0, n) *= 2.0;
  }

  TwoSpiralsVisualization visual(loader.trainingInput, loader.trainingOutput,
                                 loader.testInput, loader.testOutput);
  visual.show();
  visual.resize(500, 500);

  return app.exec();
}