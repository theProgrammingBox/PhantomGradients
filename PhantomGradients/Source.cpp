#include "Network.h"

int main()
{
	/*Network network;
	float input[INPUT_NODES];
	float output[OUTPUT_NODES];

	if (!network.Import()) cout << "Differing Network Parameters\n\n";

	for (int iterations = 0; iterations < 10; iterations++)
	{
		for (int i = 0; i < INPUT_NODES; i++)
		{
			input[i] = random.DoubleRandom();
		}

		network.ForwardPropagate(1, input, output);

		for (int i = 0; i < OUTPUT_NODES; i++)
		{
			cout << output[i] << " ";
		}

		cout << endl;
	}

	network.Export();*/

	vector<array<float, 2>> arr;
	array<float, 2> Arr;

	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			Arr[i] = random.DoubleRandom();
			cout << Arr[i] << " ";
		}

		cout << endl;

		arr.push_back(Arr);
	}

	cout << endl;

	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			cout << arr[j][i] << " ";
		}

		cout << endl;
	}

	return 0;
}