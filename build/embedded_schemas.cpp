// Auto-generated file - do not edit manually

namespace instrument_script {

const char *INSTRUMENT_API_SCHEMA = R"delim({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "$id": "https://falcon. io/schemas/instrument-api.json",
  "title": "Instrument API Definition",
  "description": "Schema for defining a single instrument's communication API",
  "type": "object",
  "required": [
    "api_version",
    "instrument",
    "protocol",
    "commands"
  ],
  "properties": {
    "api_version": {
      "type": "string",
      "pattern": "^[0-9]+\\.[0-9]+\\.[0-9]+$",
      "description": "Semantic version of this API definition"
    },
    "instrument": {
      "type": "object",
      "required": [
        "vendor",
        "model",
        "identifier"
      ],
      "properties": {
        "vendor": {
          "type": "string",
          "description": "Manufacturer name (e.g., Keysight, Tektronix)"
        },
        "model": {
          "type": "string",
          "description": "Model number (e.g., DSO9254A)"
        },
        "identifier": {
          "type": "string",
          "pattern": "^[A-Z][A-Z0-9_]*$",
          "description": "Unique identifier used in scripts (e.g., GPI1, API1)"
        },
        "description": {
          "type": "string"
        },
        "firmware_version": {
          "type": "string"
        }
      }
    },
    "protocol": {
      "type": "object",
      "required": [
        "type"
      ],
      "properties": {
        "type": {
          "type": "string",
          "enum": [
            "VISA",
            "Custom"
          ],
          "description": "Communication protocol type"
        },
        "config": {
          "type": "object",
          "description": "Protocol-specific configuration",
          "properties": {
            "resource_string": {
              "type": "string",
              "description": "VISA resource string (for VISA protocol)"
            },
            "terminator": {
              "type": "string",
              "description": "Command terminator (e.g., \\n, \\r\\n)",
              "default": "\\n"
            },
            "timeout_ms": {
              "type": "integer",
              "default": 5000,
              "description": "Communication timeout in milliseconds"
            }
          }
        }
      }
    },
    "commands": {
      "type": "object",
      "description": "Available commands for this instrument",
      "patternProperties": {
        "^[A-Z][A-Z0-9_]*$": {
          "$ref": "#/definitions/command"
        }
      },
      "additionalProperties": false
    }
  },
  "definitions": {
    "command": {
      "type": "object",
      "required": [
        "template"
      ],
      "properties": {
        "template": {
          "type": "string",
          "description": "Command template with {param} placeholders (e.g., 'SOUR{channel}: VOLT {voltage}')"
        },
        "description": {
          "type": "string",
          "description": "Human-readable description of what this command does"
        },
        "parameters": {
          "type": "array",
          "description": "Ordered list of parameters for this command",
          "items": {
            "$ref": "#/definitions/parameter"
          }
        },
        "returns": {
          "type": "string",
          "enum": [
            "void",
            "int",
            "float",
            "string",
            "bool",
            "array<float>",
            "array<int>"
          ],
          "default": "void",
          "description": "Return type of the command"
        },
        "query": {
          "type": "boolean",
          "default": false,
          "description": "Whether this is a query command (expects response)"
        }
      }
    },
    "parameter": {
      "type": "object",
      "required": [
        "name",
        "type"
      ],
      "properties": {
        "name": {
          "type": "string",
          "pattern": "^[a-z][a-z0-9_]*$",
          "description": "Parameter name (lowercase with underscores)"
        },
        "type": {
          "type": "string",
          "enum": [
            "int",
            "float",
            "string",
            "bool"
          ],
          "description": "Parameter data type"
        },
        "description": {
          "type": "string"
        },
        "precision": {
          "type": "number",
          "minimum": 0,
          "exclusiveMinimum": true,
          "description": "Floating point precision (for float types)"
        },
        "min": {
          "type": "number",
          "description": "Minimum allowed value"
        },
        "max": {
          "type": "number",
          "description": "Maximum allowed value"
        },
        "default": {
          "description": "Default value if not provided"
        },
        "unit": {
          "type": "string",
          "description": "Physical unit (e.g., 'V', 'Hz', 's')"
        }
      }
    }
  }
}
)delim";
const char *SYSTEM_CONTEXT_SCHEMA = R"delim({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "$id": "https://falcon.io/schemas/system-context.json",
  "title": "Falcon System Context",
  "description": "System-provided special functions available in all scripts",
  "type": "object",
  "required": [
    "version",
    "special_functions"
  ],
  "properties": {
    "version": {
      "type": "string",
      "pattern": "^[0-9]+\\.[0-9]+\\.[0-9]+$"
    },
    "special_functions": {
      "type": "object",
      "patternProperties": {
        "^[A-Z][A-Z0-9_]*$": {
          "$ref": "#/definitions/special_function"
        }
      }
    }
  },
  "definitions": {
    "special_function": {
      "type": "object",
      "required": [
        "handler",
        "async"
      ],
      "properties": {
        "handler": {
          "type": "string",
          "description": "C++ process handler name"
        },
        "async": {
          "type": "boolean",
          "description": "Whether function executes asynchronously"
        },
        "description": {
          "type": "string"
        },
        "parameters": {
          "type": "array",
          "items": {
            "type": "object",
            "required": [
              "name",
              "type"
            ],
            "properties": {
              "name": {
                "type": "string"
              },
              "type": {
                "type": "string",
                "enum": [
                  "int",
                  "float",
                  "string",
                  "bool",
                  "array<float>",
                  "array<int>",
                  "DataHandle"
                ]
              },
              "description": {
                "type": "string"
              }
            }
          }
        }
      }
    }
  }
}
)delim";
const char *RUNTIME_CONTEXTS_SCHEMA = R"delim({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "$id": "https://falcon.io/schemas/runtime-contexts.json",
  "title": "Runtime Context Definitions",
  "description": "Defines different program types and their available context fields",
  "type": "object",
  "required": [
    "contexts"
  ],
  "properties": {
    "contexts": {
      "type": "object",
      "patternProperties": {
        "^[a-z][a-z0-9_]*$": {
          "$ref": "#/definitions/context"
        }
      }
    }
  },
  "definitions": {
    "context": {
      "type": "object",
      "required": [
        "name",
        "description",
        "fields"
      ],
      "properties": {
        "name": {
          "type": "string",
          "description": "Display name for this context type"
        },
        "description": {
          "type": "string"
        },
        "fields": {
          "type": "array",
          "description": "Available fields in this runtime context",
          "items": {
            "$ref": "#/definitions/field"
          }
        }
      }
    },
    "field": {
      "type": "object",
      "required": [
        "name",
        "type"
      ],
      "properties": {
        "name": {
          "type": "string",
          "pattern": "^[a-z][a-zA-Z0-9]*$"
        },
        "type": {
          "type": "string"
        },
        "description": {
          "type": "string"
        },
        "optional": {
          "type": "boolean",
          "default": false
        }
      }
    }
  }
}
)delim";

} // namespace instrument_script
