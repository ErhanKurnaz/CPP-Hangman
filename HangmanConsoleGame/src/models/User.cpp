#include "User.h"
#include "User.h"

User::User(std::string& name) {
	User::mName = name;
	User::mPoints = 0;
}

std::string User::getName()
{
	return User::mName;
}

int User::getPoints()
{
	return User::mPoints;
}

void User::addPoint()
{
	User::mPoints++;
}

bool User::operator<(User& user) const
{
	return (user.getPoints() < User::mPoints);
}
