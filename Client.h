#pragma once
#include <string>
#include <vector>

#include "Movie.h"

class Client
{
public:

	Client(std::string login, std::string password);

	bool Login(std::string login, std::string password);
	bool RentMovie(Movie* movie);
	bool ReturnMovie(int index);

	void ShowRentedMovies();

	std::string GetUsername();
	std::string GetPassword();

	std::vector<Movie*> GetClientMovies();

private:

	std::string login;
	std::string password;
	std::vector<Movie*> rentedMovies;

};