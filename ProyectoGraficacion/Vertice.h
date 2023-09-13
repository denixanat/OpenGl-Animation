#pragma once
#include <vector>
#include <string>

class Vertice
{
public:
	void leervertice(const char* nombre);
	std::vector<float> getvd();
	std::vector<float> getfvd();
	int nvertices();
	std::vector<float> mvd;
	std::vector<float> fmvd;
	struct V { float x, y, z; };
	bool empiezacon(std::string& linea, const char* t);
	void addvd(int a, int c, std::vector<V>& vs);
	void addvvd(int a, int b, int c, std::vector<V>& vs);
};



