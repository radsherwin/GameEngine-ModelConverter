//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"
#include "MathApp.h"

//----------------------------------------------------------------------------- 
// Mutates result to be a slerp between the source and target by the
// specified factor.
// For a factor of 0.0, result == source.
// For a factor of 1.0, result == target.
//----------------------------------------------------------------------------- 

namespace Azul
{
	void QuatApp::Slerp(Quat &result, const Quat &src, const Quat &tar, const float slerpFactor)
	{
		// Do your magic here
		Quat target;

		const float QUAT_EPSILON = 0.001f;

		float tmpCos = src.dot(tar);
		if(tmpCos >= 1.0f)
		{
			result = src;
		}
		else
		{
			if(tmpCos < 0.0f)
			{
				tmpCos = -tmpCos;
				target = -tar;
			}
			else
			{
				target = tar;
			}

			float tarFactor = slerpFactor;
			float srcFactor = 1.0f - slerpFactor;

			if(tmpCos < (1.0f - QUAT_EPSILON))
			{
				//Quat not close enough for lerp
				const float omega = acosf(tmpCos);
				const float sinom = 1.0f / sinf(omega);

				srcFactor = sinf(srcFactor * omega) * sinom;
				tarFactor = sinf(tarFactor * omega) * sinom;
			}

			result.set(	src[x] * srcFactor + target[x] * tarFactor,
						src[y] * srcFactor + target[y] * tarFactor,
						src[z] * srcFactor + target[z] * tarFactor,
						src[w] * srcFactor + target[w] * tarFactor);
		}
	};

	void QuatApp::SlerpArray(Quat *out, const Quat *source, const Quat *target, const float slerpFactor, const int numQuats)
	{

		for(int i = 0; i < numQuats; i++)
		{
			Quat targets;

			const float QUAT_EPSILON = 0.001f;

			float tmpCos = source[i].dot(target[i]);
			if (tmpCos >= 1.0f)
			{
				out[i] = source[i];
			}
			else
			{
				if (tmpCos < 0.0f)
				{
					tmpCos = -tmpCos;
					targets = -target[i];
				}
				else
				{
					targets = target[i];
				}

				float tarFactor = slerpFactor;
				float srcFactor = 1.0f - slerpFactor;

				if (tmpCos < (1.0f - QUAT_EPSILON))
				{
					//Quat not close enough for lerp
					const float omega = acosf(tmpCos);
					const float sinom = 1.0f / sinf(omega);

					srcFactor = sinf(srcFactor * omega) * sinom;
					tarFactor = sinf(tarFactor * omega) * sinom;
				}

				out[i].set(source[i][x] * srcFactor + targets[x] * tarFactor,
					source[i][y] * srcFactor + targets[y] * tarFactor,
					source[i][z] * srcFactor + targets[z] * tarFactor,
					source[i][w] * srcFactor + targets[w] * tarFactor);
			}
		}
	};
}

// ---  End of File ---------------
