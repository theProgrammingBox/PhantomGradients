#pragma once
#include "Config.h"

class Network
{
private:
	float startingStates[NETWORK_NODES];
	float stateBiases[NETWORK_NODES];
	float outputBiases[NETWORK_NODES];
	float inputWeights[NETWORK_NODES][INPUT_NODES];
	float stateWeights[NETWORK_NODES][NETWORK_NODES];
	float outputWeights[OUTPUT_NODES][NETWORK_NODES];

	float* pastState = new float[NETWORK_NODES];

	float Binary(float x)
	{
		return x < -1 ? -1 : (x < 1 ? x : 1);
	}

public:
	Network()
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
		for (int node = 0; node < NETWORK_NODES; node++)
		{
			pastState[node] = startingStates[node];
		}
	}

	void ForwardPropagate(int iterations, float* input, float* output)
	{
		int iteration, parentNode, childNode;

		float* state = new float[NETWORK_NODES];

		for (iteration = 0; iteration < iterations; iteration++)
		{
			for (parentNode = 0; parentNode < NETWORK_NODES; parentNode++)
			{
				state[parentNode] = stateBiases[parentNode];

				for (childNode = 0; childNode < INPUT_NODES; childNode++)
				{
					state[parentNode] += input[childNode] * inputWeights[parentNode][childNode];
				}

				for (childNode = 0; childNode < NETWORK_NODES; childNode++)
				{
					state[parentNode] += pastState[childNode] * stateWeights[parentNode][childNode];
				}

				state[parentNode] = Binary(state[parentNode]);
			}

			for (parentNode = 0; parentNode < OUTPUT_NODES; parentNode++)
			{
				output[parentNode] = outputBiases[parentNode];

				for (childNode = 0; childNode < NETWORK_NODES; childNode++)
				{
					output[parentNode] += state[childNode] * outputWeights[parentNode][childNode];
				}
			}

			float* temp = pastState;
			pastState = state;
			state = temp;
		}

		delete[] state;
	}

	void Export()
	{
		ofstream fout("NetworkParameters.txt");
		int parentNode, childNode;

		fout
			<< INPUT_NODES << " "
			<< NETWORK_NODES << " "
			<< OUTPUT_NODES << " ";

		for (parentNode = 0; parentNode < NETWORK_NODES; parentNode++)
		{
			fout << startingStates[parentNode] << " ";
			fout << stateBiases[parentNode] << " ";

			for (childNode = 0; childNode < INPUT_NODES; childNode++)
			{
				fout << inputWeights[parentNode][childNode] << " ";
			}

			for (childNode = 0; childNode < NETWORK_NODES; childNode++)
			{
				fout << stateWeights[parentNode][childNode] << " ";
			}
		}

		for (parentNode = 0; parentNode < OUTPUT_NODES; parentNode++)
		{
			fout << outputBiases[parentNode] << " ";

			for (childNode = 0; childNode < NETWORK_NODES; childNode++)
			{
				fout << outputWeights[parentNode][childNode] << " ";
			}
		}

		fout.close();
	}

	bool Import()
	{
		ifstream fin("NetworkParameters.txt");
		int parameter;
		int parentNode, childNode;

		fin >> parameter;
		if (parameter != INPUT_NODES) return false;

		fin >> parameter;
		if (parameter != NETWORK_NODES) return false;

		fin >> parameter;
		if (parameter != OUTPUT_NODES) return false;

		for (parentNode = 0; parentNode < NETWORK_NODES; parentNode++)
		{
			fin >> startingStates[parentNode];
			fin >> stateBiases[parentNode];

			for (childNode = 0; childNode < INPUT_NODES; childNode++)
			{
				fin >> inputWeights[parentNode][childNode];
			}

			for (childNode = 0; childNode < NETWORK_NODES; childNode++)
			{
				fin >> stateWeights[parentNode][childNode];
			}
		}

		for (parentNode = 0; parentNode < OUTPUT_NODES; parentNode++)
		{
			fin >> outputBiases[parentNode];

			for (childNode = 0; childNode < NETWORK_NODES; childNode++)
			{
				fin >> outputWeights[parentNode][childNode];
			}
		}

		fin.close();
		Reset();

		return true;
	}
};