#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Vehicle {
private:
    std::string vehicleNumber;
    std::string ownerFirstName;
    std::string ownerLastName;
    int ownerAge;
    std::string ownerGender;
    std::string ownerAddress;

public:
    Vehicle(const std::string& number, const std::string& firstName, const std::string& lastName, int age, const std::string& gender, const std::string& address)
        : vehicleNumber(number), ownerFirstName(firstName), ownerLastName(lastName), ownerAge(age), ownerGender(gender), ownerAddress(address) {}
    void printDetails() const {
        std::cout << "vehicle number: " << vehicleNumber << std::endl;
        std::cout << "owner: " << ownerFirstName << " " << ownerLastName << std::endl;
        std::cout << "owner's age: " << ownerAge << std::endl;
        std::cout << "owner's gender: " << ownerGender << std::endl;
        std::cout << "owner's address: " << ownerAddress << std::endl;
        std::cout << "*****************************" << std::endl;
    }
    std::string getVehicleNumber() const { return vehicleNumber; }
    std::string getOwnerFirstName() const { return ownerFirstName; }
    std::string getOwnerLastName() const { return ownerLastName; }
    int getOwnerAge() const { return ownerAge; }
    std::string getOwnerGender() const { return ownerGender; }
    std::string getOwnerAddress() const { return ownerAddress; }
};

int main() {
    std::vector<Vehicle> vehicles; 
    std::ifstream file("Q1.csv");
    if (!file.is_open()) {
        std::cerr << "error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 7) {
            std::string combinedVehicleNumber = tokens[0] + tokens[1]; 
            int age = 0;
            try {
                age = std::stoi(tokens[4]); 
            } catch (const std::exception& e) {
                std::cerr << "error converting age to integer: " << e.what() << std::endl;
                continue; 
            }

            Vehicle vehicle(combinedVehicleNumber, tokens[2], tokens[3], age, tokens[5], tokens[6]);
            vehicles.push_back(vehicle);
        } else {
            std::cerr << "invalid data format in line: " << line << std::endl;
        }
    }
    file.close();
    for (const auto& v : vehicles) {
        v.printDetails();
    }

    return 0;
}