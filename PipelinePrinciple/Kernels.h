#pragma once

#include <torch\torch.h>

namespace hsi
{
namespace classification
{
	namespace kernels
	{

		//nb_data = size(Xtrain, 1);
		//if nargin < 3,
		//	XXh = sum(Xtrain. ^ 2, 2)* ones(1, nb_data);
		//omega = XXh + XXh'-2*(Xtrain*Xtrain');
		//omega = exp(-omega. / (2 * sigma2));
		//else
		//	omega = -2 * Xtrain * Xt';
		//	Xtrain = sum(Xtrain. ^ 2, 2) * ones(1, size(Xt, 1));
		//Xt = sum(Xt. ^ 2, 2) * ones(1, nb_data);
		//omega = omega + Xtrain + Xt';
		//	omega = exp(-omega. / (2 * sigma2));
		//end

		struct SAMKernel
		{
			/*n = size(Xtrain, 1);
			m = size(Xt, 1);

			norm1 = sqrt(sum(Xtrain. ^ 2, 2));
			norm2 = sqrt(sum(Xt. ^ 2, 2));

			norm = norm1 * norm2';
			D = Xtrain * Xt';    
			omega = exp(-1 * (acos(D . / norm). ^ 2) . / (2 * abs(sigma2)));*/

		};

		struct RBFKernel 
		{
			void compute(const torch::Tensor &Xpos, const torch::Tensor &Xneg, const double sigma)
			{

			};
		};

		struct LinKernel
		{

		};

		struct PolyKernel
		{

		};

	};

};
};
