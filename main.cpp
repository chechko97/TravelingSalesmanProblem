#include <iostream>
#include "Point.h"
#include "Road.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;

const int mutationRate = 30;

int n;
vector<Point> points;
vector<int> index;
vector<Road> routes;

bool check(vector<Point> points, Point p) {
	for (int i = 0; i < points.size(); i++) {
		if (points[i] == p)
			return true;
	}
	return false;
}

void createRoute(int n) {
	for (int i = 0; i < n; i++) {
		Point p(i);
		while (check(points, p)) {
			Point q(i);
			p = q;
		}
		points.push_back(p);
	}
	for (int i = 0; i < n; i++) {
		index.push_back(i);
	}
}

vector<Point> crossover(vector<Point> parent1, vector<Point> parent2) {
	int parentSize = parent1.size();
	vector<Point> child;
	unordered_set <int> cityIDs;

	int first = rand() % (parentSize / 2);
	int second = rand() % (parentSize / 2);

	second = parentSize - second;

	for (int i = 0; i < first; i++)	{
		child.push_back(parent1[i]);
		cityIDs.insert(parent1[i].getID());
	}

	for (int i = second; i < parentSize; i++) {
		child.push_back(parent1[i]);
		cityIDs.insert(parent1[i].getID());
	}

	int curIndex = 0;
	while (child.size() != parentSize) {
		if (cityIDs.count(parent2[curIndex].getID()) == 0) {
			child.push_back(parent2[curIndex]);
		}
		curIndex++;
	}

	return child;
}

void mutate(vector<Point> & points) {
	int index1 = rand() % points.size();
	int index2 = rand() % points.size();
	while (index1 == index2) {
		index2 = rand() % points.size();
	}
	swap(points[index1], points[index2]);
}

void evolution(vector<Road> & routes) {
	sort(routes.begin(), routes.end(), less_than_key());

	int halfSize = routes.size() / 2;

	for (int i = 0; i < halfSize; i++) {
		routes.pop_back();
	}
}

int main()
{
	srand(time(NULL));
	cout << "Input n: ";
	cin >> n;
	cout << endl;
	createRoute(n);
	
	for (int i = 0; i < n; i++) {
		Road sofiaSvilengrad(n, points, index);
		routes.push_back(sofiaSvilengrad);
	}
	sort(routes.begin(), routes.end(), less_than_key());
	
	int counter = 0;
	while (counter < n*3) {
		cout << "distance: " << routes[0].getDistance() << endl;
		int candidatesNumber = 0.3 * n + 2;
		for (int i = 0; i < n; i++)	{
			int index1 = rand() % candidatesNumber;
			int index2 = rand() % candidatesNumber;

			while (index2 == index1) {
				index2 = rand() % candidatesNumber;
			}
			vector<Point> parent1;
			for (int k = 0; k < routes[index1].getPoints().size(); k++) {
				parent1.push_back(routes[index1].getPoints()[k]);
			}
			vector<Point> parent2;
			for (int k = 0; k < routes[index2].getPoints().size(); k++) {
				parent2.push_back(routes[index2].getPoints()[k]);
			}
			vector<Point> child = crossover(parent1, parent2);

			int newChanceOfMutation = rand() % 100;
			//cout << "chance%: " << newChanceOfMutation << endl;
			if (newChanceOfMutation <= mutationRate) {
				mutate(child);
			}
			
			Road sofiaSvilengrad(child);
			routes.push_back(sofiaSvilengrad);
		}

		evolution(routes);
		counter++;
	}

	system("pause");
	return 0;
}