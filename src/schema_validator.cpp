#include "instrument_script/schema_validator.hpp"
#include <yaml-cpp/yaml.h>

namespace instrument_script {

// Forward declarations for embedded schemas
extern const char *INSTRUMENT_API_SCHEMA;
extern const char *SYSTEM_CONTEXT_SCHEMA;
extern const char *RUNTIME_CONTEXTS_SCHEMA;

ValidationResult
SchemaValidator::validate_instrument_api(const std::string &yaml_path) {
  ValidationResult result;
  result.valid = true;

  try {
    YAML::Node doc = YAML::LoadFile(yaml_path);

    // Check required fields
    if (!doc["api_version"]) {
      result.valid = false;
      result.errors.push_back(
          {"/api_version", "Missing required field 'api_version'", 0, 0});
    }

    if (!doc["instrument"]) {
      result.valid = false;
      result.errors.push_back(
          {"/instrument", "Missing required field 'instrument'", 0, 0});
    }

    if (!doc["protocol"]) {
      result.valid = false;
      result.errors.push_back(
          {"/protocol", "Missing required field 'protocol'", 0, 0});
    }

    if (!doc["commands"]) {
      result.valid = false;
      result.errors.push_back(
          {"/commands", "Missing required field 'commands'", 0, 0});
    }

    // Validate instrument
    if (doc["instrument"]) {
      auto inst = doc["instrument"];
      if (!inst["vendor"]) {
        result.valid = false;
        result.errors.push_back(
            {"/instrument/vendor", "Missing required field", 0, 0});
      }
      if (!inst["model"]) {
        result.valid = false;
        result.errors.push_back(
            {"/instrument/model", "Missing required field", 0, 0});
      }
      if (!inst["identifier"]) {
        result.valid = false;
        result.errors.push_back(
            {"/instrument/identifier", "Missing required field", 0, 0});
      }
    }

    // Validate protocol
    if (doc["protocol"]) {
      auto proto = doc["protocol"];
      if (!proto["type"]) {
        result.valid = false;
        result.errors.push_back(
            {"/protocol/type", "Missing required field", 0, 0});
      }
    }

    // Validate commands
    if (doc["commands"] && doc["commands"].IsMap()) {
      for (const auto &cmd : doc["commands"]) {
        std::string cmd_name = cmd.first.as<std::string>();
        auto cmd_node = cmd.second;

        if (!cmd_node["template"]) {
          result.valid = false;
          result.errors.push_back({"/commands/" + cmd_name + "/template",
                                   "Missing required field 'template'", 0, 0});
        }
      }
    }

  } catch (const YAML::Exception &e) {
    result.valid = false;
    result.errors.push_back(
        {"", std::string("YAML parse error: ") + e.what(), 0, 0});
  }

  return result;
}

ValidationResult
SchemaValidator::validate_system_context(const std::string &yaml_path) {
  ValidationResult result;
  result.valid = true;

  try {
    YAML::Node doc = YAML::LoadFile(yaml_path);

    if (!doc["version"]) {
      result.valid = false;
      result.errors.push_back({"/version", "Missing required field", 0, 0});
    }

    if (!doc["special_functions"]) {
      result.valid = false;
      result.errors.push_back(
          {"/special_functions", "Missing required field", 0, 0});
    }

  } catch (const YAML::Exception &e) {
    result.valid = false;
    result.errors.push_back(
        {"", std::string("YAML parse error: ") + e.what(), 0, 0});
  }

  return result;
}

InstrumentAPI
SchemaValidator::parse_instrument_api(const std::string &yaml_path) {
  YAML::Node doc = YAML::LoadFile(yaml_path);

  InstrumentAPI api;
  api.api_version = doc["api_version"].as<std::string>();

  // Parse instrument metadata
  auto inst = doc["instrument"];
  api.instrument.vendor = inst["vendor"].as<std::string>();
  api.instrument.model = inst["model"].as<std::string>();
  api.instrument.identifier = inst["identifier"].as<std::string>();

  if (inst["description"]) {
    api.instrument.description = inst["description"].as<std::string>();
  }
  if (inst["firmware_version"]) {
    api.instrument.firmware_version =
        inst["firmware_version"].as<std::string>();
  }

  // Parse protocol
  auto proto = doc["protocol"];
  api.protocol.type = proto["type"].as<std::string>();

  if (proto["config"]) {
    for (const auto &cfg : proto["config"]) {
      api.protocol.config[cfg.first.as<std::string>()] =
          cfg.second.as<std::string>();
    }
  }

  // Parse commands
  if (doc["commands"]) {
    for (const auto &cmd : doc["commands"]) {
      std::string cmd_name = cmd.first.as<std::string>();
      auto cmd_node = cmd.second;

      Command command;
      command.name = cmd_name;
      command.template_str = cmd_node["template"].as<std::string>();

      if (cmd_node["description"]) {
        command.description = cmd_node["description"].as<std::string>();
      }

      if (cmd_node["returns"]) {
        command.returns = cmd_node["returns"].as<std::string>();
      } else {
        command.returns = "void";
      }

      command.query = cmd_node["query"] ? cmd_node["query"].as<bool>() : false;

      // Parse parameters
      if (cmd_node["parameters"]) {
        for (const auto &param_node : cmd_node["parameters"]) {
          Parameter param;
          param.name = param_node["name"].as<std::string>();
          param.type = param_node["type"].as<std::string>();

          if (param_node["description"]) {
            param.description = param_node["description"].as<std::string>();
          }
          if (param_node["precision"]) {
            param.precision = param_node["precision"].as<double>();
          }
          if (param_node["min"]) {
            param.min = param_node["min"].as<double>();
          }
          if (param_node["max"]) {
            param.max = param_node["max"].as<double>();
          }
          if (param_node["unit"]) {
            param.unit = param_node["unit"].as<std::string>();
          }

          command.parameters.push_back(param);
        }
      }

      api.commands[cmd_name] = command;
    }
  }

  return api;
}

std::map<std::string, RuntimeContext>
SchemaValidator::parse_runtime_contexts(const std::string &yaml_path) {
  YAML::Node doc = YAML::LoadFile(yaml_path);
  std::map<std::string, RuntimeContext> contexts;

  if (doc["contexts"]) {
    for (const auto &ctx : doc["contexts"]) {
      std::string ctx_id = ctx.first.as<std::string>();
      auto ctx_node = ctx.second;

      RuntimeContext context;
      context.name = ctx_node["name"].as<std::string>();
      context.description = ctx_node["description"].as<std::string>();

      if (ctx_node["fields"]) {
        for (const auto &field_node : ctx_node["fields"]) {
          ContextField field;
          field.name = field_node["name"].as<std::string>();
          field.type = field_node["type"].as<std::string>();

          if (field_node["description"]) {
            field.description = field_node["description"].as<std::string>();
          }

          field.optional = field_node["optional"]
                               ? field_node["optional"].as<bool>()
                               : false;

          context.fields.push_back(field);
        }
      }

      contexts[ctx_id] = context;
    }
  }

  return contexts;
}

std::string SchemaValidator::get_instrument_api_schema() {
  return INSTRUMENT_API_SCHEMA;
}

std::string SchemaValidator::get_system_context_schema() {
  return SYSTEM_CONTEXT_SCHEMA;
}

std::string SchemaValidator::get_runtime_contexts_schema() {
  return RUNTIME_CONTEXTS_SCHEMA;
}

} // namespace instrument_script
