#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#define M_PI 3.14159265358979313846

using namespace std;

class Point {
public:
	explicit Point(double x, double y, double z) : x(x), y(y), z(z)
	{}

	double Getx() {
		return x;
	}

	double Gety() {
		return y;
	}

	double Getz() {
		return z;
	}

private:
	double x;
	double y;
	double z;
};

class Circle {
public:
	explicit Circle(double a, Point o) : a(a), o(o)
	{}

	/*virtual ~Circle()
	{
		delete
	};*/

	virtual Point GetPoint(double t) {
		double x = a * cos(t) + o.Getx();
		double y = a * sin(t) + o.Gety();
		Point newPoint(x, y, 0);
		return newPoint;
	}

	virtual Point GetDerivative(double t) {
		double x = a * sin(t);
		double y = a * cos(t);
		Point newPoint(x, y, 0);
		return newPoint;
	}

	double GetR() {
		return a;
	}

protected:
	double a;
	Point o;
};

class Helix : public Circle {
public:
	explicit Helix(double a, Point o, double p) : Circle(a, o), p(p)
	{}

	Point GetPoint(double t) {
		double x = a * cos(t) + o.Getx();
		double y = a * sin(t) + o.Gety();
		double z = p * t / (2 * M_PI);
		Point newPoint(x, y, z);
		return newPoint;
	}

	Point GetDerivative(double t) {
		double x = a * sin(t);
		double y = a * cos(t);
		double z = p / (2 * M_PI);
		Point newPoint(x, y, z);
		return newPoint;
	}

private:
	double p;
};

class Ellipse : public Circle {
public:
	explicit Ellipse(double a, Point o, double b) : Circle(a, o), b(b)
	{}

	Point GetPoint(double t) {
		double x = a * cos(t) + o.Getx();
		double y = b * sin(t) + o.Gety();
		Point newPoint(x, y, 0);
		return newPoint;
	}

	Point GetDerivative(double t) {
		double x = a * sin(t);
		double y = b * cos(t);
		Point newPoint(x, y, 0);
		return newPoint;
	}

private:
	double b;
};

bool comp(Circle* a, Circle* b) {
	return a->GetR() < b->GetR();
}


int main() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> uid(0, 200);
	int Number = uid(gen);
	vector<Circle*> Shapes;
	vector<Circle*> Circles;
	Circle* pCircle = 0;
	Ellipse* pEllipse = 0;
	Helix* pHelix = 0;
	int j = 0;
	for (int i = 0; i < Number; i++) {
		uniform_int_distribution<> uid(0, 2);
		uniform_real_distribution<> urd(0, 30);
		Point NewPoint(urd(gen), urd(gen), urd(gen));
		switch (uid(gen)) {
		case 0:
			pCircle = new Circle(urd(gen), NewPoint);
			Shapes.push_back(pCircle);
			Circles.push_back(pCircle);
			j++;
			break;
		case 1:
			pEllipse = new Ellipse(urd(gen), NewPoint, urd(gen));
			Shapes.push_back(pEllipse);
			break;
		case 2:
			pHelix = new Helix(urd(gen), NewPoint, urd(gen));
			Shapes.push_back(pHelix);
			break;
		}
	}
	for (auto s : Shapes) {
		cout << s->GetPoint(M_PI / 4).Getx() << " " << s->GetPoint(M_PI / 4).Gety() << " " << s->GetPoint(M_PI / 4).Getz() << " " << s->GetDerivative(M_PI / 4).Getx() << " " << s->GetDerivative(M_PI / 4).Gety() << " " << s->GetDerivative(M_PI / 4).Getz() << endl;
	}

	sort(Circles.begin(), Circles.end(), comp);
	/*for (auto c : Circles) {
		cout << c->GetR() << endl;
	}*/
	double SumR = 0;
	for (auto circle : Circles) {
		SumR += circle->GetR();
	}
	cout << "Sum of circle radii = " << SumR;
	for_each(Shapes.begin(), Shapes.end(), default_delete<Circle>());
	return 0;
}