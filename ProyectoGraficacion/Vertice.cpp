#include "Vertice.h"//
#include <iostream>//
#include <fstream>//
#include "Obj3D.h"
void Vertice::leervertice(const char* nombre)
{
	std::vector<V> vs;
	std::ifstream file(nombre);
	if (file) {
		std::string line;
		while (std::getline(file, line)) {
			if (empiezacon(line, "v "))
			{
				V pos;
				sscanf_s(line.c_str(), "v %f %f %f\n", &pos.x, &pos.y, &pos.z);
				vs.push_back(pos);
			}


			if (empiezacon(line, "f"))
			{
				int av1, av2, av3, av4, a1, a2, a3, a4, b1, b2, b3, b4, cv1, cv2, cv3, cv4, a5, a6, a7, a8, a9, a10, c5, c6, c7, c8, c9, c10, c1, c2, c3, c4;
				(void)sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &av1, &b1, &cv1, &av2, &b2, &cv2, &av3, &b3, &cv3, &av4, &b4, &cv4);

				if (b1 > 0 && b4 > 0) {
					addvvd(av1, b1, cv1, vs);
					fmvd.push_back(b1);
					//cout << av1;
					addvvd(av2, b2, cv2, vs);
					fmvd.push_back(b2);
				//	cout << av2;
					addvvd(av3, b3, cv3, vs);
					fmvd.push_back(b3);
				//	cout << av3;
					addvvd(av4, b4, cv4, vs);
					av4 = 0;b4 = 0, cv4 = 0;
				}
				else
				{
					if (b1 >= 0 && b4 <= 0) {
						addvvd(av1, b1, cv1, vs);
						addvvd(av2, b2, cv2, vs);
						addvvd(av3, b3, cv3, vs);
						av4 = 0;b4 = 0, cv4 = 0;
					}
					else {
						av1 = 0;av2 = 0;av3 = 0;av4 = 0;cv1 = 0;cv2 = 0;cv3 = 0;cv4 = 0;
						(void)sscanf_s(line.c_str(), "f %d//%d %d//%d %d//%d %d//%d %d//%d %d//%d %d//%d %d//%d %d//%d %d//%d\n",
							&a1, &c1, &a2, &c2, &a3, &c3, &a4, &c4, &a5, &c5, &a6, &c6, &a7, &c7, &a8, &c8, &a9, &c9, &a10, &c10);
						if (a10 > 0)
						{
							addvd(a1, c1, vs);
							addvd(a2, c2, vs);
							addvd(a3, c3, vs);
							addvd(a4, c4, vs);
							addvd(a5, c5, vs);
							addvd(a6, c6, vs);
							addvd(a7, c7, vs);
							addvd(a8, c8, vs);
							addvd(a9, c9, vs);
							addvd(a10, c10, vs);
							c5 = 0; a5 = 0;a6 = 0;a7 = 0; a8 = 0; a9 = 0; a10 = 0; c6 = 0; c7 = 0; c8 = 0; c9 = 0; c10 = 0;
						}
						else
							if (a8 > 0)
							{
								addvd(a1, c1, vs);
								addvd(a2, c2, vs);
								addvd(a3, c3, vs);
								addvd(a4, c4, vs);
								addvd(a5, c5, vs);
								addvd(a6, c6, vs);
								addvd(a7, c7, vs);
								addvd(a8, c8, vs);
								c5 = 0; a5 = 0;a6 = 0;a7 = 0; a8 = 0; a9 = 0; a10 = 0; c6 = 0; c7 = 0; c8 = 0; c9 = 0; c10 = 0;
							}
							else {
								addvd(a1, c1, vs);
								addvd(a2, c2, vs);
								addvd(a3, c3, vs);
								addvd(a4, c4, vs);
								c5 = 0; a5 = 0;a6 = 0;a7 = 0; a8 = 0; a9 = 0; a10 = 0; c6 = 0; c7 = 0; c8 = 0; c9 = 0; c10 = 0;
							}
					}
				}

			}
		}
	}
	else {
		std::cout << "No se pudo abrir el archivo" << std::endl;
	}

}



bool Vertice::empiezacon(std::string& linea, const char* t)
{
	size_t textLen = strlen(t);
	if (linea.size() < textLen) {
		return false;
	}
	for (size_t i = 0; i < textLen;i++)
	{
		if (linea[i] == t[i]) continue;
		else return false;
	}
	return true;
}

void Vertice::addvd(int a, int c, std::vector<V>& vs) {
	V p = vs[a - 1];
	mvd.push_back(p.x);
	mvd.push_back(p.z);
}


void Vertice::addvvd(int a, int b, int c, std::vector<V>& vs) {
	V p = vs[a - 1];
	
	mvd.push_back(p.x);
	//std::cout << p.x;
	mvd.push_back(p.y);
	//std::cout << p.y;
	mvd.push_back(p.z);
	//std::cout << p.z<<std::endl;
}

std::vector<float> Vertice::getfvd() {
	
	return fmvd;
}

std::vector<float> Vertice::getvd() {
	return mvd;
}

int Vertice::nvertices() {
	return mvd.size() / 9;
}

