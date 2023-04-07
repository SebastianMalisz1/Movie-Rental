#pragma once
#include <string>

enum class Genre
{
	Horror = 1,
	Action,
	Comedy,
	Drama,
	Romance,
	Mystery,
	Thriller
};

struct Movie
{
public:
	Movie(std::string director, std::string title, Genre genre, int index, int yearOfProduction, bool isRented, std::string rentedBy = "")
	{
		this->director = director;
		this->title = title;
		this->genre = genre;
		this->yearOfProduction = yearOfProduction;
		this->index = index;
		this->isRented = isRented;
		if(isRented)
			this->rentedBy = rentedBy;
	}

	bool Rent(std::string memberName)
	{
		this->isRented = true;
		rentedBy = memberName;
		return true;
	}

	bool Return()
	{
		if (this->isRented == false)
			return false;

		this->isRented = false;
		return true;
	}

	std::string GetTitle()
	{
		return this->title;
	}

	int GetIndex()
	{
		return this->index;
	}

	std::string GetDirector()
	{
		return this->director;
	}

	int GetPublishedYear()
	{
		return this->yearOfProduction;
	}

	bool IsRented()
	{
		return this->isRented;
	}

	std::string GetRentedBy()
	{
		return this->rentedBy;
	}

	Genre GetGenre()
	{
		return this->genre;
	}

private:
	Genre genre;
	std::string title;
	std::string director;
	std::string rentedBy;
	int yearOfProduction;
	int index;
	bool isRented;
};