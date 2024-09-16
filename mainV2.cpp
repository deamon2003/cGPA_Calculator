#include <chrono>
#include <iostream>
#include <limits>
#include <thread>

class cGPAcalculator {
private:
  unsigned int total_Subject;
  double total_Marks;
  unsigned int total_max_Marks;

public:
  cGPAcalculator() : total_Subject(0), total_Marks(0), total_max_Marks(0) {}

  void inputMarks() {
    std::cout << "CGPA Calculator:-" << std::endl;
    std::cout << "[$] Enter the total number of subjects: ";
    std::cin >> total_Subject;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (unsigned int i = 0; i < total_Subject; ++i) {
      double obtMarks;
      std::cout << "[$] Enter your marks obtained for subject " << (i + 1)
                << ": ";
      std::cin >> obtMarks;

      total_Marks += obtMarks;
    }
    total_max_Marks = total_Subject * 100;
  }

  void showProgressBar(int progress, int total, int barWidth = 50) {
    float ratio = static_cast<float>(progress) / total;
    int filleWidth = static_cast<int>(ratio * barWidth);

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
      if (i < filleWidth) {
        // std::cout << "\033[32m=\033[0m";
        std::cout << "\033[32m#\033[0m";
      } else {
        std::cout << " ";
      }
    }
    std::cout << "] progress " << int(ratio * 100.0) << "%\r";
    std::cout.flush();
  }

  double calculatePercentage() const {
    if (total_max_Marks == 0) {
      std::cout << "[!] Error: The maximum number can't be zero..."
                << std::endl;
      return 1;
    }
    return (total_Marks / total_max_Marks) * 100;
  }

  double calculateCGPA(double percentage) const { return percentage / 9.5; }

  void displayResults() const {
    double percentage = calculatePercentage();
    if (percentage > 0) {
      std::cout << "[@] The total percentage: " << percentage << "%"
                << std::endl;
      double cgpa = calculateCGPA(percentage);
      std::cout << "[@] The CGPA is: " << cgpa << std::endl;
    }
  }
};

int main() {
  cGPAcalculator calc;
  calc.inputMarks();

  const int total = 100;
  for (int i = 0; i <= total; ++i) {
    calc.showProgressBar(i, total);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  std::cout << std::endl;
  calc.displayResults();

  return 0;
}
