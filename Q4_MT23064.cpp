#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
struct ReportInfo {
    std::string typeOfReport;
    std::string reportLocation;
};

struct EvidenceInfo {
    std::string witnesses;
    std::string violationDetails;
    std::string personResponse;
};

int main() {
    std::string carNumberToSearch;

    std::cout << "enter car number: ";
    std::cin >> carNumberToSearch;
    std::string q2FilePath = "Q2.csv";
    std::string evidenceFilePath = "4.csv";
    std::unordered_map<std::string, ReportInfo> q2Data;
    std::unordered_map<std::string, EvidenceInfo> evidenceData;
    std::ifstream q2File(q2FilePath);
    if (q2File.is_open()) {
        std::string line;
        std::getline(q2File, line); 

        while (std::getline(q2File, line)) {
            std::stringstream ss(line);
            std::string carNumber, typeOfReport, reportLocation;
            std::getline(ss, carNumber, ',');
            std::getline(ss, typeOfReport, ',');
            std::getline(ss, reportLocation, ',');

            q2Data[carNumber] = {typeOfReport, reportLocation};
        }
        q2File.close();
    } else {
        std::cerr << "unable to open file: " << q2FilePath << std::endl;
        return 1;
    }
    std::ifstream evidenceFile(evidenceFilePath);
    if (evidenceFile.is_open()) {
        std::string line;
        std::getline(evidenceFile, line); 
        while (std::getline(evidenceFile, line)) {
            std::stringstream ss(line);
            std::string carNumber, witnesses, violationDetails, personResponse;
            std::getline(ss, carNumber, ',');
            std::getline(ss, witnesses, ',');
            std::getline(ss, violationDetails, ',');
            std::getline(ss, personResponse, ',');

            evidenceData[carNumber] = {witnesses, violationDetails, personResponse};
        }
        evidenceFile.close();
    } else {
        std::cerr << "unable to open file: " << evidenceFilePath << std::endl;
        return 1;
    }
    if (q2Data.find(carNumberToSearch) != q2Data.end() && evidenceData.find(carNumberToSearch) != evidenceData.end()) {
        std::cout << "--------------------------"<< std::endl;
        std::cout << "type of report: " << q2Data[carNumberToSearch].typeOfReport << std::endl;
        std::cout << "report location: " << q2Data[carNumberToSearch].reportLocation << std::endl;
        std::cout<<std::endl;
        std::cout << "witnesses: " << evidenceData[carNumberToSearch].witnesses << std::endl;
        std::cout << "violation details: " << evidenceData[carNumberToSearch].violationDetails << std::endl;
        std::cout << "person response: " << evidenceData[carNumberToSearch].personResponse << std::endl;
        std::cout << "--------------------------"<< std::endl;

    } else {
        std::cout << "car number not found or incomplete information." << std::endl;
    }

    return 0;
}