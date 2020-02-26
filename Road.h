#pragma once
#include <iostream>
#include "Point.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

class Road : public Point {
private:
	int n;
	double distance;
	vector<Point> points;
	vector<int> index;

public:
	Road() {
		n = 0;
		distance = 0;
		points.clear();
		index.clear();
	}
	Road(int n, vector<Point> points, vector<int> index) {
		int distance = 0;
		this->n = n;
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle(index.begin(), index.end(), std::default_random_engine(seed));
		for (int i = 0; i < (n / 2) + 1; i++) {
			if (n % 2 == 0 && i == (n / 2) + 1)
				break;
			swap(points[i], points[index[i]]);
		}
		this->points = points;
		for (int i = 0; i < points.size() - 1; i++) {
			distance += points[i].distance(points[i + 1]);
		}
		this->index = index;
		this->distance = distance;

	}
	Road(vector<Point> points) {
		this->points = points;
		for (int i = 0; i < points.size() - 1; i++) {
			distance += points[i].distance(points[i + 1]);
		}
		this->distance = distance;
	}
	friend ostream& operator<<(ostream &output, const Road &r) {
		for (int i = 0; i < r.points.size(); i++) {
			output << r.points[i];
		}
		output << "distance: " << r.distance << endl;
		return output;
	}
	
	double getDistance() const {
		return distance;
	}

	vector<Point> getPoints() const {
		return this->points;
	}
};

struct less_than_key {
	inline bool operator() (const Road & struct1, const Road & struct2)	{
		return (struct1.getDistance() < struct2.getDistance());
	}
};