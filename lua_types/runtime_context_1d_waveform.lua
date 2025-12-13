---@meta

---@class InstrumentChannel
---@field [1] string Instrument identifier
---@field [2] number Channel number

---@class VoltageDomain
---@field [1] number Minimum voltage
---@field [2] number Maximum voltage

---@class RuntimeContext_1DWaveform
---@field getters table<number, InstrumentChannel> Instruments to acquire from
---@field setters table<number, InstrumentChannel> Instruments to configure
---@field setVoltageDomains table<number, VoltageDomain> Voltage ranges per channel
---@field sampleRate number Sampling rate in Hz
---@field numPoints integer Number of points to acquire
---@field call fun(funcName: string, ... ): any Call an instrument command or system function
---@field parallel fun(block: function) Execute a block of commands in parallel
---@field log fun(msg: string) Log a message
local RuntimeContext_1DWaveform = {}

return RuntimeContext_1DWaveform
