#include "Cara.h"
#include <iostream>//
#include <fstream>//

std::vector<float> Cara::carga(Vertice obj)
{
	std::vector<float> vertices = obj.getvd();
	int nvertices = obj.nvertices();
	std::vector<float> copia = obj.getvd();
	std::vector<float>::const_iterator i = copia.begin();
	int x = 1, b = 0, y = 0, c = 0, d = 0, e = 0;
	//cout << nvertices << " " << endl;
	while (i != copia.end())
	{
		//cout << *i << " ";
		bool band = true;
		float vertex[5][3];
		float cara[5][3];
		vertex[d][e] = *i / 8;
		//cout << "vertice "<< d<<" "<< e <<" : "<< vertex[d][e] << "\n";
		++c;
		if (x == 3)
		{
			e = 0;
			band = false;
			d++;
			c = 0;
			y++;
			//cout << "\n";
			x = 0;
		}
		++i;
		++x;
		if (band == true)
		{
			++e;
		}
		band = true;

		if (y == 4)
		{
			for (int j = 0;j < 4;j++)
			{
				//cout << "orig";
				for (int k = 0;k < 3;k++)
				{
					cara[j][k] = vertex[j][k];
					//cout << vertex[j][k];
					caras.push_back(cara[j][k]);

				}
			}
			y = 0;d = 0;e = 0;
			//cout << "" << endl;
		}
		
	}
caras.push_back(0);
caras.push_back(0);
caras.push_back(0);
	return caras;
}