
-- LuaTools需要PROJECT和VERSION这两个信息
PROJECT = "gpiodemo"
VERSION = "1.0.1"

-- sys库是标配
_G.sys = require("sys")
_G.adc = require("adc")
local LED1 = gpio.setup(16, 0) -- PB0输出模式
local LED2 = gpio.setup(17, 0) -- PB0输出模式
local LED3 = gpio.setup(18, 0) -- PB0输出模式
sys.taskInit(function()
	while 1 do
		-- log.info("LED开启")
		LED1(0)
		sys.wait(1000)
		-- log.info("LED关闭")
		LED1(1)
		sys.wait(1000)
	end
end)
sys.taskInit(function()
	while 1 do
		-- log.info("LED开启")
		LED2(0)
		sys.wait(700)
		-- log.info("LED关闭")
		LED2(1)
		sys.wait(700)
	end
end)sys.taskInit(function()
	while 1 do
		-- log.info("LED开启")
		LED3(0)
		sys.wait(300)
		-- log.info("LED关闭")
		LED3(1)
		sys.wait(300)
	end
end)

sys.taskInit(function ()
	if adc.open(2) then
		log.info("adc", adc.read(2))
	end
	while true do
		sys.wait(string.format("%.3f", adc.read(2)))
	end
end)

sys.run()