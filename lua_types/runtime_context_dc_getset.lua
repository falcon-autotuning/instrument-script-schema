---@meta

---@class InstrumentChannel
---@field [1] string Instrument identifier (e.g., "GPI1", "API1")
---@field [2] number Channel number

---@class RuntimeContext_DCGetSet
---@field getters table<number, InstrumentChannel> Instruments to read from
---@field setters table<number, InstrumentChannel> Instruments to write to
---@field setVoltages table<number, number> Voltages to set (indexed by channel)
---@field sampleRate number Sampling rate in Hz
---@field call fun(funcName: string, ...): any Call an instrument command or system function
---@field parallel fun(block: function) Execute a block of commands in parallel
---@field log fun(msg: string) Log a message
local RuntimeContext_DCGetSet = {}

return RuntimeContext_DCGetSet
