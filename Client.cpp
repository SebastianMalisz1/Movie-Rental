#include <iostream>
#include "Client.h"

Client::Client(std::string login, std::string password)
{
	this->login = login;
	this->password = password;
}

bool Client::Login(std::string login, std::string password)
{
	if (login == this->login && password == this->password)
		return true;

	return false;
}

bool Client::ReturnMovie(int index)
{
	for (auto& movie : rentedMovies)
	{
		if (movie->GetIndex() == index)
		{
			movie->Return();
			rentedMovies.erase(std::remove(rentedMovies.begin(), rentedMovies.end(), movie));
			return true;
		}
	}

	return false;
}

void Client::ShowRentedMovies()
{
	for (auto& movie : rentedMovies)
	{
		std::cout << movie->GetIndex() << ". " << movie->GetTitle() << ", Borrowed: " << movie->IsRented() << '\n';
	}
}

std::string Client::GetUsername()
{
	return this->login;
}

std::string Client::GetPassword()
{
	return this->password;
}

std::vector<Movie*> Client::GetClientMovies()
{
	return rentedMovies;
}

bool Client::RentMovie(Movie* movie)
{
	if (movie == nullptr)
		return false;

	rentedMovies.push_back(movie);
	movie->Rent(this->login);

	return true;
}
