#pragma once
#include "Config.h"

class NetworkTrainer
{
private:
	float startingStates[NETWORK_NODES];
	float stateBiases[NETWORK_NODES];
	float outputBiases[NETWORK_NODES];
	float inputWeights[NETWORK_NODES][INPUT_NODES];
	float stateWeights[NETWORK_NODES][NETWORK_NODES];
	float outputWeights[OUTPUT_NODES][NETWORK_NODES];

	vector<array<float, NETWORK_NODES>> prestate;
	vector<array<float, NETWORK_NODES>> state;

	float Binary(float x)
	{
		return x < -1 ? -1 : (x < 1 ? x : 1);
	}

public:
	NetworkTrainer()
	{
		Initialize();
		Reset();
	}

	void Initialize()
	{
		int parentNode, childNode;

		for (parentNode = 0; parentNode < NETWORK_NODES; parentNode++)
		{
			startingStates[parentNode] = random.DoubleRandom();
			stateBiases[parentNode] = random.DoubleRandom();

			for (childNode = 0; childNode < INPUT_NODES; childNode++)
			{
				inputWeights[parentNode][childNode] = random.DoubleRandom();
			}

			for (childNode = 0; childNode < NETWORK_NODES; childNode++)
			{
				stateWeights[parentNode][childNode] = random.DoubleRandom();
			}
		}

		for (parentNode = 0; parentNode < OUTPUT_NODES; parentNode++)
		{
			outputBiases[parentNode] = random.DoubleRandom();

			for (childNode = 0; childNode < NETWORK_NODES; childNode++)
			{
				outputWeights[parentNode][childNode] = random.DoubleRandom();
			}
		}
	}

	void Reset()
	{
		int parentNode, childNode;

		for (parentNode = 0; parentNode < NETWORK_NODES; parentNode++)
		{
			state[parentNode][0] = startingStates[parentNode];
			for (childNode = 1; childNode < NETWORK_NODES; childNode++)
			{
				state[parentNode][childNode] = 0;
			}
		}
	}

	void ForwardPropagate(int iterations, float* input, float* output)
	{
		int iteration, node, parentNode, childNode;
		float sum;

		for (iteration = 0; iteration < iterations; iteration++)
		{
			for (node = 0; node < NETWORK_NODES; node++)
			{
				sum = 0;

				for (parentNode = 0; parentNode < INPUT_NODES; parentNode++)
				{
					sum += input[parentNode] * inputWeights[node][parentNode];
				}

				for (parentNode = 0; parentNode < NETWORK_NODES; parentNode++)
				{
					sum += state[iteration][parentNode] * stateWeights[node][parentNode];
				}

				sum += stateBiases[node];
				state[iteration + 1][node] = Binary(sum);
			}
		}

		for (node = 0; node < OUTPUT_NODES; node++)
		{
			sum = 0;

			for (parentNode = 0; parentNode < NETWORK_NODES; parentNode++)
			{
				sum += state[iterations][parentNode] * outputWeights[node][parentNode];
			}

			sum += outputBiases[node];
			output[node] = Binary(sum);
		}
	}
};