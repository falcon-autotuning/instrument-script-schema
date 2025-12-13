#include "instrument_script/schema_validator.hpp"
#include <filesystem>
#include <iostream>

using namespace instrument_script;
namespace fs = std::filesystem;

int main() {
  std::cout << "Testing Example Files...\n\n";

  int passed = 0;
  int failed = 0;

  // Test all instrument YAML files
  std::string instruments_dir = "examples/instruments";

  if (fs::exists(instruments_dir)) {
    std::cout << "Validating instruments in: " << instruments_dir << "\n";

    for (const auto &entry : fs::directory_iterator(instruments_dir)) {
      if (entry.path().extension() == ".yaml") {
        std::cout << "  Testing: " << entry.path().filename() << "\n";

        auto result =
            SchemaValidator::validate_instrument_api(entry.path().string());

        if (result.valid) {
          std::cout << "    ✓ Valid\n";
          passed++;
        } else {
          std::cout << "    ✗ Invalid\n";
          for (const auto &err : result.errors) {
            std::cout << "      - " << err.path << ": " << err.message << "\n";
          }
          failed++;
        }
      }
    }
  }

  std::cout << "\nResults: " << passed << " passed, " << failed << " failed\n";

  return failed > 0 ? 1 : 0;
}
