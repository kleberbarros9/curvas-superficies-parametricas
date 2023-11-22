#include <iostream>
#include <fstream>

int main() {
    std::ifstream inputFile("surfaceDemo");

    if (!inputFile.is_open()) {
        std::cout << "Unable to open file";
        return 1;
    }

    int uPoints, vPoints;
    inputFile >> uPoints >> vPoints;
    std::cout << "uPoints: " << uPoints << ", vPoints: " << vPoints << std::endl;

    int length = (uPoints + 1) * (vPoints + 1);
    float* point = new float[3];

    for (int i = 0; i < length; ++i) {
        inputFile >> point[0] >> point[1] >> point[2];
        std::cout << "Point " << i + 1 << ": " << point[0] << " " << point[1] << " " << point[2] << std::endl;
    }

    delete[] point;
    inputFile.close();

    return 0;
}
