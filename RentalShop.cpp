#include <iostream>
#include <filesystem>
#include <fstream>
#include "RentalShop.h"

RentalShop::RentalShop(std::string moviePath, std::string clientPath)
{
	lastIndex = 0;
	this->clientPath = clientPath;
	this->moviePath = moviePath;

	LoadClientsDataBase(clientPath);
	LoadMoviesDataBase(moviePath);
}

RentalShop::~RentalShop()
{
	if (clientPath != "")
		SaveClientsDataBase(clientPath);

	if (moviePath != "")
		SaveMoviesDataBase(moviePath);

	for (auto& movie : ownedMovies)
	{
		delete movie;
	}

	for (auto& client : registeredClients)
	{
		delete client;
	}
}

Client* RentalShop::Login(std::string login, std::string password)
{
	for (auto& client : registeredClients)
	{
		if (client->Login(login, password))
		{
			return client;
		}
	}
	return nullptr;
}

Client* RentalShop::RegisterNewClient(std::string login, std::string password)
{
	if (AlreadyContainsClient(login))
		return nullptr;

	Client* client = new Client(login, password);
	registeredClients.push_back(client);

	return client;
}

Movie* RentalShop::GetMovieByIndex(int index)
{
	for (auto& movie : ownedMovies)
	{
		if (movie->GetIndex() == index)
			return movie;
	}

	return nullptr;
}

Client* RentalShop::GetClientByLogin(std::string login)
{
	for (auto& client : registeredClients)
	{
		if (client->GetUsername() == login)
			return client;
	}

	return nullptr;
}

bool RentalShop::AddNewMovie(std::string title, Genre genre, std::string director, const int yearOfProduction)
{
	if (AlreadyContainsMovie(title))
		return false;

	Movie* movie = new Movie(director, title, genre, lastIndex, yearOfProduction, false);
	ownedMovies.push_back(movie);
	lastIndex++;

	return true;
}

bool RentalShop::RentMovie(Client* client, Movie* movie)
{
	if (movie == nullptr)
		return false;

	if (movie->IsRented() == false)
	{
		client->RentMovie(movie);
		return true;
	}

	return false;
}

void RentalShop::ShowMovies()
{
	for (auto& movie : ownedMovies)
	{
		if (!movie->IsRented())
			std::cout << movie->GetIndex() << ". " << movie->GetTitle() << ", Director: " << movie->GetDirector() << '\n';
	}
}

void RentalShop::ShowRentedMovies()
{
	for (auto& movie : ownedMovies)
	{
		if (movie->IsRented())
			std::cout << movie->GetIndex() << ". " << movie->GetTitle() << ", Director: " << movie->GetDirector() << ", Rented by: " << movie->GetRentedBy() << '\n';
	}

}

void RentalShop::ShowGenres()
{
	std::cout << "\n----GENRES----\n";
	std::cout << "1 - Horror\n";
	std::cout << "2 - Action\n";
	std::cout << "3 - Comedy\n";
	std::cout << "4 - Drama\n";
	std::cout << "5 - Romance\n";
	std::cout << "6 - Mystery\n";
	std::cout << "7 - Thriller\n";
	std::cout << "--------------\n";
}

bool RentalShop::AlreadyContainsClient(const std::string login)
{
	for (auto& client : registeredClients)
	{
		if (client->GetUsername() == login)
			return true;
	}
	return false;
}

bool RentalShop::AlreadyContainsMovie(const std::string title)
{
	for (auto& movie : ownedMovies)
	{
		if (movie->GetTitle() == title)
			return true;
	}
	return false;
}

bool RentalShop::SaveClientsDataBase(const std::string fileName)
{
	std::fstream file;

	if (!std::filesystem::exists(this->clientPath))
	{
		file.open(this->clientPath, std::ios::in | std::ios::out | std::ios::app);
	}

	file.clear();

	for (auto& client : registeredClients)
		file << client->GetUsername().data() << ';' << client->GetPassword().data() << '\n';

	file.close();
	return true;
}

bool RentalShop::SaveMoviesDataBase(const std::string fileName)
{
	std::fstream file;

	if (std::filesystem::exists(this->moviePath))
	{
		file.open(this->moviePath, std::ofstream::out | std::ofstream::trunc);
		file.close();
	}

	file.open(this->moviePath, std::ios::in | std::ios::out | std::ios::app);

	for (auto& movie : ownedMovies)
	{
		if (movie->IsRented())
		{
			file << movie->GetDirector() << ';' << movie->GetTitle() << ';' << (int)(movie->GetGenre())
				<< ";" << movie->GetIndex() << ";" << movie->GetPublishedYear() << ";" << movie->IsRented() 
				<< ";" << movie->GetRentedBy() << '\n';
		}
		else
		{
			file << movie->GetDirector() << ';' << movie->GetTitle() << ';' << (int)(movie->GetGenre())
				<< ";" << movie->GetIndex() << ";" << movie->GetPublishedYear() << ";" << movie->IsRented() << '\n';
		}
	}

	file.close();
	return true;
}

bool RentalShop::LoadClientsDataBase(const std::string fileName)
{
	if (!std::filesystem::exists(this->clientPath))
		return false;

	std::string line;
	std::ifstream file(this->clientPath);

	while (std::getline(file, line))
	{
		if (line.size() < 2)
			return false;

		std::vector<std::string> clientData;
		clientData = Split(line, ';');
		Client* client = new Client(clientData.at(0), clientData.at(1));
		registeredClients.push_back(client);
	}

	file.close();
	return true;
}

bool RentalShop::LoadMoviesDataBase(const std::string fileName)
{
	if (!std::filesystem::exists(this->moviePath))
		return false;

	std::string line;
	std::ifstream file(this->moviePath);

	while (std::getline(file, line))
	{
		if (line.size() < 2)
			return false;

		std::vector<std::string> movieData;
		movieData = Split(line, ';');
		if (movieData.size() == 6)
		{
			Movie* movie = new Movie(movieData.at(0), movieData.at(1), (Genre)(std::stoi(movieData.at(2))), std::stoi(movieData.at(3)),
				std::stoi(movieData.at(4)), std::stoi(movieData.at(5)));
			ownedMovies.push_back(movie);
			lastIndex++;
		}
		else
		{
			Movie* movie = new Movie(movieData.at(0), movieData.at(1), (Genre)(std::stoi(movieData.at(2))), std::stoi(movieData.at(3)),
				std::stoi(movieData.at(4)), std::stoi(movieData.at(5)), movieData.at(6));
			ownedMovies.push_back(movie);
			lastIndex++;
			GetClientByLogin(movieData.at(6))->RentMovie(movie);
		}
	}

	file.close();
	return true;
}

std::vector<std::string> RentalShop::Split(std::string input, const char splitter)
{
	std::stringstream stream(input);
	std::string segment;
	std::vector<std::string> splited;

	while (std::getline(stream, segment, splitter))
	{
		splited.push_back(segment);
	}

	return splited;
}
