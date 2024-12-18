﻿// Roni Suvanto harjoitustyö 5p
#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <limits>
#include <clocale>

std::vector<std::vector<int>> generateRooms(std::vector<std::vector<int>> rooms) {
    // lisätään huoneet vektoriin
    for (int i = 0; i < rooms.size(); i++) {
        // lisätään huneen numero ensinmäiseen kenttään
        rooms[i][0] = i + 1;

        // tarkistetaan onko huono ensinmäisessä puolessa ja merkitään huoneen koko
        if (i < rooms.size() / 2) {
            rooms[i][1] = 1;
        }
        else {
            rooms[i][1] = 2;
        }
        // huone on aluksi vapaa
        rooms[i][2] = 0;
    }

    // palautetaan huoneet
    return rooms;
}

std::vector<std::vector<int>> bookRooms(std::vector<std::vector<int>> rooms) {
    int chosenRoomtype;
    int chosenRoom;
    int freeRooms = 0;

    // kysytään käyttäjältä kumman kokoisen huoneen hän haluaa tulostettavan
    std::cout << "yhden vai kahden hengen huone?" << std::endl;
    std::cout << "1. yhden hengen huone" << std::endl;
    std::cout << "2. kahden hengen huone" << std::endl;
    // tarkistetaan syöte
    while (!(std::cin >> chosenRoomtype) || chosenRoomtype < 1 || chosenRoomtype > 2) {
        std::cout << "Virheellinen syöte" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // tulostetaan vapaat yhden hengen huoneet syötteen perusteella
    if (chosenRoomtype == 1) {
        std::cout << "vapaat yhden hengen huoneet:";
        for (int i = 0; i < rooms.size() / 2; i++) {
            if (rooms[i][2] == 0) {
                std::cout << "  " << rooms[i][0];
            }
            else {
                freeRooms++;
            }
        }
    }
    else if (chosenRoomtype == 2) {
        // tulostetaan vapaat kahden hengen huoneet syötteen perusteella
        std::cout << "vapaat kahden hengen huoneet:";
        for (int i = rooms.size() / 2; i < rooms.size(); i++) {
            if (rooms[i][2] == 0) {
                std::cout << "  " << rooms[i][0];
            }
            else {
                freeRooms++;
            }
        }
    }
    // jos kaikki huoneet ovat varattuja palataan takaisin pääohjelmaan
    if (freeRooms == 0) {
        std::cout << "Kaikki tämän tyypin huoneet ovat varattuja" << std::endl;
    }
    else {
        int bookingDuration;
        double bookingPrice;
        // arvotaan alennus
        int discount = rand() % 3;
        std::cout << std::endl;

        // kysytään käyttäjältä huonetta sen numeron perusteella
        std::cout << "Valitse huone" << std::endl;
        while (!(std::cin >> chosenRoom) || chosenRoom < 1 || chosenRoom > rooms.size()) {
            // tarkistetaan syöte
            std::cout << "Virheellinen syöte" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        // tarkistetaan onko huone jo varattu
        if (rooms[chosenRoom - 1][2] != 0) {
            std::cout << "Huone on jo varattu" << std::endl;
        }
        else {
            // kysytään käyttäjältä varauksen kesto
            std::cout << "Varauksen kesto päivinä" << std::endl;
            while (!(std::cin >> bookingDuration)) {
                std::cout << "Virheellinen syöte" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            // jos valittu huone oli yhden hengen huone lasketaan hinta alennuksen ja päivien perusteella
            if (chosenRoomtype == 1) {
                switch (discount) {
                case 0:
                    std::cout << "Ei alennusta" << std::endl;
                    bookingPrice = 100 * bookingDuration;
                    break;
                case 1:
                    std::cout << "10% alennus" << std::endl;
                    bookingPrice = 100 * bookingDuration * 0.9;
                    break;
                case 2:
                    std::cout << "20% alennus" << std::endl;
                    bookingPrice = 100 * bookingDuration * 0.8;
                    break;
                }
            }
            else if (chosenRoomtype == 2) {
                // jos valittu huone oli kahden hengen huone lasketaan hinta alennuksen ja päivien perusteella
                switch (discount) {
                case 0:
                    std::cout << "Ei alennusta" << std::endl;
                    bookingPrice = 150 * bookingDuration;
                    break;
                case 1:
                    std::cout << "10% alennus" << std::endl;
                    bookingPrice = 150 * bookingDuration * 0.9;
                    break;
                case 2:
                    std::cout << "20% alennus" << std::endl;
                    bookingPrice = 150 * bookingDuration * 0.8;
                    break;
                }
            }
            // tulostetaan varauksen hinta
            std::cout << "Varauksen hinta: " << bookingPrice << std::endl;
            // varataan huone satunnaisella varausnumerolla
            rooms[chosenRoom - 1][2] = rand() % 89999 + 10000;
            // tulostetaan varatun huoneen tiedot
            std::cout << "Huoneen numero " << rooms[chosenRoom - 1][0] << " Huoneen koko: " << rooms[chosenRoom - 1][1] << " Varausnumero: " << rooms[chosenRoom - 1][2] << std::endl;
        }
    }
    return rooms;
}

void bookingSearch(std::vector<std::vector<int>> rooms) {
    int bookingNumber;
    // kysytään käyttäjältä varausnumeroa varauksen etsimistä varten
    std::cout << "Anna varausnumero etsiäksesi varausta" << std::endl;
    // tarkistetaan syöte
    while (!(std::cin >> bookingNumber) || bookingNumber < 10000 || bookingNumber > 99999) {
        std::cout << "Virheellinen syöte" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // etsitään varausnumerollista huonetta
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i][2] == bookingNumber) {
            // tulostetaan varatun huoneen tiedot
            std::cout << "Huone numero: " << rooms[i][0] << " huoneen koko " << rooms[i][1] << ":lle hengelle  " << std::endl;
        }
    }
}

int main() {
    std::setlocale(LC_ALL, "fi-FI");

    srand(time(0));
    // arvotaan huoneiden määrä
    int roomAmount = rand() % 260 + 40;
    // tarkistetaan onko huoneiden määrä parillinen
    if (roomAmount % 2 != 0) {
        // jos huoneiden määrä ei ole parillinen, lisätään yksi huone
        roomAmount++;
    }
    // ilmoittaa luotujen huoneiden määrän
    std::cout << "Hotellin huoneiden määrä: " << roomAmount << std::endl;

    // luodaan huoneet vektoriin
    std::vector<std::vector<int>> rooms(roomAmount, std::vector<int>(3));

    rooms = generateRooms(rooms);

    // kysytään käyttäjältä mitä hän haluaa tehdä
    while (true) {
        int choice;
        std::cout << "1. Varaa huone" << std::endl;
        std::cout << "2. Hae varausta" << std::endl;
        std::cout << "3. Lopeta" << std::endl;
        // tarkistetaan syöte
        while (!(std::cin >> choice) || choice < 1 || choice > 3) {
            std::cout << "Virheellinen syöte" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (choice == 1) {
            // kutsutaan varaus funktiota
            rooms = bookRooms(rooms);
        }
        else if (choice == 2) {
            // kutsutaan varausten etsintä funktiota
            bookingSearch(rooms);
        }
        // lopetetaan ohjelma
        else if (choice == 3) {
            break;
        }
    }

    return 0;
}
