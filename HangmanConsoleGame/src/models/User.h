#pragma once
#include <string>

class User {
private:
	std::string mName;
	int mPoints;
public:
	User(std::string& name);

	std::string getName();

	int getPoints() const;

	void addPoint();

	bool operator < (const User& user) const;
};

