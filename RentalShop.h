#pragma once
#include "Client.h"

class RentalShop
{
public:
	RentalShop(std::string moviePath, std::string clientPath);
	~RentalShop();

	Client* Login(std::string login, std::string password);
	Client* RegisterNewClient(std::string login, std::string password);
	Movie* GetMovieByIndex(int index);
	Client* GetClientByLogin(std::string login);

	bool AddNewMovie(std::string title, Genre genre, std::string director, const int yearOfProduction);
	bool RentMovie(Client* client, Movie* movie);
	void ShowMovies();
	void ShowRentedMovies();
	void ShowGenres();

private:
	bool AlreadyContainsClient(const std::string login);
	bool AlreadyContainsMovie(const std::string title);
	bool SaveClientsDataBase(const std::string fileName);
	bool SaveMoviesDataBase(const std::string fileName);
	bool LoadClientsDataBase(const std::string fileName);
	bool LoadMoviesDataBase(const std::string fileName);

	std::string clientPath;
	std::string moviePath;
	std::vector<std::string> Split(std::string input, const char splitter);
	std::vector<Client*> registeredClients;
	std::vector<Movie*> ownedMovies;

	int lastIndex;
};