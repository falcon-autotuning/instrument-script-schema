# Instrument Script Schema

Core schema definitions and validation library for the Falcon instrument control system.

## Overview

This library provides:

- JSON schemas for instrument API definitions
- YAML validation
- C++ types and parsers
- Lua type definitions for LSP support
- Runtime context definitions for different program types

## Features

- **One instrument per YAML** - Distributable instrument definitions
- **Protocol-aware** - Supports VISA, TCP, Serial, USB, GPIB
- **Multiple runtime contexts** - DC Get/Set, 1D Waveform, 2D Waveform, etc.
- **Type-safe** - Strong typing for parameters and returns
- **LSP-ready** - Auto-generated Lua type definitions

## Building

```bash
mkdir build && cd build
cmake .. 
make
make test
