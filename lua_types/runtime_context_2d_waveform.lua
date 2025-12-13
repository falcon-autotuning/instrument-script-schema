---@meta

---@class InstrumentChannel
---@field [1] string Instrument identifier
---@field [2] number Channel number

---@class RuntimeContext_2DWaveform
---@field getters table<number, InstrumentChannel> Instruments to acquire from
---@field setters table<number, InstrumentChannel> Instruments to configure
---@field triggerChannel integer Channel to use for triggering
---@field triggerLevel number Trigger level in volts
---@field sampleRate number Sampling rate in Hz
---@field numPoints integer Number of points per channel
---@field numChannels integer Number of channels to acquire
---@field call fun(funcName: string, ...): any Call an instrument command or system function
---@field parallel fun(block: function) Execute a block of commands in parallel
---@field log fun(msg: string) Log a message
local RuntimeContext_2DWaveform = {}

return RuntimeContext_2DWaveform
