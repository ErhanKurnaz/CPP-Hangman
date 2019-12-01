#pragma once
#include <string>

class User {
private:
	std::string mName;
	int mPoints;
public:
	User(std::string& name);

	std::string getName();

	int getPoints();

	void addPoint();

	bool operator < (User& user) const;
};

