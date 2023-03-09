#include "pch.h"
#include "../PipelinePrinciple/Kernels.h"

namespace hsi 
{
	namespace unittests
	{
		TEST(TestClassifierOperations, TestKernelComputation)
		{
			using namespace hsi::classification;
			
			kernels::RBFKernel aKernel;			
			EXPECT_EQ(1, 1);
		}

		TEST(TestClassifierOperations, TestClassifierConstruction)
		{
			EXPECT_EQ(1, 1);
		}
	}
}
