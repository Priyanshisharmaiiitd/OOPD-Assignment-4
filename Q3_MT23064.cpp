#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

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
    std::string getVehicleNumber() const { return vehicleNumber; }
    std::string getOwnerFirstName() const { return ownerFirstName; }
    std::string getOwnerLastName() const { return ownerLastName; }
    int getOwnerAge() const { return ownerAge; }
    std::string getOwnerGender() const { return ownerGender; }
    std::string getOwnerAddress() const { return ownerAddress; }
};

int main() {
    std::vector<Vehicle> vehicles; 
    std::ifstream fileQ1("Q1.csv");
    if (!fileQ1.is_open()) {
        std::cerr << "error opening Q1.csv!" << std::endl;
        return 1;
    }

    std::string lineQ1;
    std::getline(fileQ1, lineQ1); 
    while (std::getline(fileQ1, lineQ1)) {
        std::stringstream ss(lineQ1);
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
            std::cerr << "invalid data format in Q1.csv line: " << lineQ1 << std::endl;
        }
    }
    fileQ1.close();
    std::ifstream fileQ3("Q3.csv");
    if (!fileQ3.is_open()) {
        std::cerr << "error opening Q3.csv!" << std::endl;
        return 1;
    }
    std::unordered_map<std::string, std::string> nameToAddress;
    std::string lineQ3;
    std::getline(fileQ3, lineQ3); 
    while (std::getline(fileQ3, lineQ3)) {
        std::stringstream ss(lineQ3);
        std::string tokenQ3;
        std::vector<std::string> tokensQ3;

        while (std::getline(ss, tokenQ3, ',')) {
            tokensQ3.push_back(tokenQ3);
        }

        if (tokensQ3.size() == 5) {
            std::string fullName = tokensQ3[0] + " " + tokensQ3[1];
            std::string address = tokensQ3[4]; 
            nameToAddress[fullName] = address;
        } else {
            std::cerr << "invalid data format in Q3.csv line: " << lineQ3 << std::endl;
        }
    }
    fileQ3.close();
    bool found = false;
    for (const Vehicle& v : vehicles) {
            std::string ownerFullName = v.getOwnerFirstName() + " " + v.getOwnerLastName();
            auto it = nameToAddress.find(ownerFullName);
            if (it != nameToAddress.end()) {
                std::cout << "owner information:" << std::endl;
                std::cout << "full name: " << ownerFullName << std::endl;
                std::cout << "gender: " << v.getOwnerGender() << std::endl;
                std::cout << "age: " << v.getOwnerAge() << std::endl;
                std::cout << "old address" << v.getOwnerAddress() << std::endl;
                std::cout << "probable address" << it->second << std::endl;
                std::cout<<"***********"<<std::endl;
                found = true;
            } else {
                std::cout << "no address found for the owner in Q3.csv." << std::endl;
            
        }
    }
    if (!found) {
        std::cout << "no vehicle found with the given combined vehicle number." << std::endl;
    }

    return 0;
}