#include "opengm/unittests/test.hxx"
#include "opengm/graphicalmodel/graphicalmodel.hxx"
#include "opengm/operations/adder.hxx"
#include "opengm/learning/struct-max-margin.hxx"
#include "opengm/learning/dataset/testdataset.hxx"
#include "opengm/learning/loss/hammingloss.hxx"
#include "opengm/inference/bruteforce.hxx"

template<class T>
struct LearningTest {

	typedef T                                                                  ValueType;
	typedef OPENGM_TYPELIST_2(
			opengm::ExplicitFunction<T>,
			opengm::functions::learnable::LPotts<T>)                           FunctionTypeList;
	typedef opengm::GraphicalModel<ValueType, opengm::Adder, FunctionTypeList> GraphicalModelType;
	typedef opengm::datasets::TestDataset<GraphicalModelType>                  DatasetType;
	typedef typename DatasetType::ModelParameters                              ModelParameters;
	typedef opengm::learning::HammingLoss                                      LossGeneratorType;
	typedef opengm::Bruteforce<GraphicalModelType,opengm::Minimizer>           InferenceType;

	void testStructMaxMargin() {

		// create a dataset
		DatasetType dataset;

		// create a learning algorithm
		opengm::learning::StructMaxMargin<DatasetType, LossGeneratorType> structMaxMargin(dataset);

		// train
		typename InferenceType::Parameter infParams;
		structMaxMargin.template learn<InferenceType>(infParams);

		// get the result
		const ModelParameters& learntParameters = structMaxMargin.getModelParameters();
	}

	void run() {

		this->testStructMaxMargin();
   }
};

int
main() {
   std::cout << "Learning test...  " << std::endl;
   //{
   //   LearningTest<float >t;
   //   t.run();
   //}
   {
      LearningTest<double >t;
      t.run();
   }
   std::cout << "done.." << std::endl;
   return 0;
}

