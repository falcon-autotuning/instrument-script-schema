#include "instrument_script/schema_validator.hpp"
#include <cassert>
#include <iostream>

using namespace instrument_script;

int main() {
  std::cout << "Testing Schema Validator.. .\n\n";

  // Test 1: Validate Keysight instrument
  std::cout << "Test 1: Validating keysight_dso9254a.yaml\n";
  auto result1 = SchemaValidator::validate_instrument_api(
      "examples/instruments/keysight_dso9254a.yaml");

  if (result1.valid) {
    std::cout << "  ✓ Valid\n";
  } else {
    std::cout << "  ✗ Invalid:\n";
    for (const auto &err : result1.errors) {
      std::cout << "    - " << err.path << ": " << err.message << "\n";
    }
  }

  // Test 2: Parse instrument API
  std::cout << "\nTest 2: Parsing instrument API\n";
  try {
    auto api = SchemaValidator::parse_instrument_api(
        "examples/instruments/keysight_dso9254a.yaml");
    std::cout << "  ✓ Parsed successfully\n";
    std::cout << "    Instrument: " << api.instrument.vendor << " "
              << api.instrument.model << "\n";
    std::cout << "    Identifier: " << api.instrument.identifier << "\n";
    std::cout << "    Protocol: " << api.protocol.type << "\n";
    std::cout << "    Commands:  " << api.commands.size() << "\n";

    for (const auto &[name, cmd] : api.commands) {
      std::cout << "      - " << name << " (" << cmd.parameters.size()
                << " params)\n";
    }
  } catch (const std::exception &e) {
    std::cout << "  ✗ Parse failed: " << e.what() << "\n";
  }

  // Test 3: Validate system context
  std::cout << "\nTest 3: Validating system_context.yaml\n";
  auto result3 =
      SchemaValidator::validate_system_context("examples/system_context.yaml");

  if (result3.valid) {
    std::cout << "  ✓ Valid\n";
  } else {
    std::cout << "  ✗ Invalid:\n";
    for (const auto &err : result3.errors) {
      std::cout << "    - " << err.path << ": " << err.message << "\n";
    }
  }

  // Test 4: Parse runtime contexts
  std::cout << "\nTest 4: Parsing runtime contexts\n";
  try {
    auto contexts = SchemaValidator::parse_runtime_contexts(
        "examples/runtime_contexts.yaml");
    std::cout << "  ✓ Parsed " << contexts.size() << " contexts\n";

    for (const auto &[id, ctx] : contexts) {
      std::cout << "    - " << id << ": " << ctx.name << " ("
                << ctx.fields.size() << " fields)\n";
    }
  } catch (const std::exception &e) {
    std::cout << "  ✗ Parse failed:  " << e.what() << "\n";
  }

  std::cout << "\n✓ All tests completed\n";

  return 0;
}
