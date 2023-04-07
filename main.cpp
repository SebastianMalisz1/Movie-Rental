#include <iostream>
#include <filesystem>

#include "RentalShop.h"

namespace
{
    RentalShop rental(".//movies.txt", ".//clients.txt");
    Client* user;

    bool isMenuDrawn = false;
    bool isLogged = false;
}

void AddMovieToShop()
{
    std::string title;
    std::string director;
    int genre;
    int yearOfProductrion;

    std::cout << "Podaj tytul filmu: \n";
    std::cin.ignore();
    std::getline(std::cin, title);

    std::cout << "Podaj rezysera filmu: ";
    std::getline(std::cin, director);

    std::cout << "Podaj rok wyprodukowania filmu: ";
    std::cin >> yearOfProductrion;

    std::cout << "Podaj garunek filmu: ";
    rental.ShowGenres();
    std::cin >> genre;


    if (rental.AddNewMovie(title, (Genre)genre, director, yearOfProductrion))
        std::cout << "Film zostal poprawnie dodany!" << '\n';
    else
        std::cout << "Cos poszlo nie tak, film moze byc juz na stanie sklepu!" << '\n';
}

void Login()
{
    std::string login;
    std::string password;

    std::cout << "Podaj login: ";
    std::cin >> login;

    std::cout << "Podaj haslo: ";
    std::cin >> password;

    user = rental.Login(login, password);

    if (user != nullptr)
    {
        std::cout << "Zalogowales sie jako " << login << '\n';
        isLogged = true;
    }
    else
        std::cout << "Niepoprawny login lub haslo!" << '\n';
}

void Register()
{
    std::string login;
    std::string password;

    std::cout << "Podaj login: ";
    std::cin >> login;

    std::cout << "Podaj haslo: ";
    std::cin >> password;

    user = rental.RegisterNewClient(login, password);

    if (user != nullptr)
    {
        std::cout << "Zarejestrowales sie jako " << login << '\n';
        isLogged = true;
    }
    else
        std::cout << "Cos poszlo nie tak!" << '\n';
}

void RentMovie()
{
    if (isLogged)
    {
        int index;

        std::cout << "Podaj index filmu ktory chcesz wypozyczyc: ";
        std::cin >> index;

        if (rental.GetMovieByIndex(index)->IsRented())
            std::cout << "Ten film jest juz wypozyczony, lub nie ma filmu o tym index'ie!\n";
        else
            rental.RentMovie(user, rental.GetMovieByIndex(index));
    }
}

void ReturnMovie()
{
    if (isLogged)
    {
        int index;

        std::cout << "Podaj index filmu ktory chcesz oddac: ";
        std::cin >> index;

        if (user->ReturnMovie(index))
            std::cout << "Oddales film do sklepu!\n";
        else
            std::cout << "Nie masz wypozyczonego filmu o tym index'ie!\n";
    }
}

void DrawMenu()
{
    std::cout << "\n\n";
    if (!isLogged)
    {
        std::cout << "1. Zaloguj sie\n";
        std::cout << "2. Zarejestruj sie\n";
        std::cout << "3. Zakoncz program\n";

        isMenuDrawn = true;
    }
    else
    {
        std::cout << "1. Dodaj film\n";
        std::cout << "2. Pokaz filmy w sklepie\n";
        std::cout << "3. Wypozycz film\n";
        std::cout << "4. Zwroc film\n";
        std::cout << "5. Pokaz wypozyczone filmy\n";
        std::cout << "6. Zakoncz program\n";

        isMenuDrawn = true;
    }
}

bool MakeAction(int action)
{
    if (!isLogged)
    {
        if (action == 1)
        {
            Login();
            return true;
        }
        if (action == 2)
        {
            Register();
            return true;
        }
        if (action == 3)
        {
            return false;
        }
    }
    else
    {
        if (action == 1)
        {
            AddMovieToShop();
            return true;
        }
        if (action == 2)
        {
            rental.ShowMovies();
            return true;
        }
        if (action == 3)
        {
            RentMovie();
            return true;
        }
        if (action == 4)
        {
            ReturnMovie();
            return true;
        }
        if (action == 5)
        {
            rental.ShowRentedMovies();
            return true;
        }
        if (action == 6)
        {
            return false;
        }
    }
}

int main()
{
    int action = 0;

    while (true)
    {
        if (!isMenuDrawn)
        {
            DrawMenu();
        }

        std::cout << "\n\nWybierz co chcesz zrobic: ";
        std::cin >> action;

        if (action != 0)
        {
            if (!MakeAction(action))
                return 0;

            isMenuDrawn = false;
            action = 0;
        }
    }

	return 0;
}