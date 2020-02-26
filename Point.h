#pragma once
#include <iostream>
#include <ctime>
#include "Point.h"

using namespace std;


class Point {
private:
	double x, y;
	int id;

public:
	Point() {
		x = rand() % 100;
		y = rand() % 100;
	}
	Point(int nID)	{
		x = rand() % 100;
		y = rand() % 100;
		id = nID;
	}
	double getX() const {
		return x;
	}
	double getY() const{
		return y;
	}
	int getID() const {
		return id;
	}
	const double distance(Point second) {
		return sqrt(pow(this->x - second.x, 2) + pow(this->y - second.y, 2));
	}
	Point& operator=(const Point& second) {
		if (this != &second) {
			this->x = second.x;
			this->y = second.y;
			this->id = second.id;
		}
		return *this;
	}
	bool operator==(Point& second) {
		if (this->x == second.getX() && this->y == second.getY())
			return true;
		return false;
	}
	friend ostream& operator<<(ostream &output, const Point &p) {
		output << "x = " << p.x << ", " << "y = " << p.y << endl;
		return output;
	}
};