-- module needed
-- u8g2 with ssd1327_midas_128x128 spi font_6x10_tf
-- hardware spi
-- wifi
-- http


cs  = 8 -- GPIO15, pull-down 10k to GND
dc  = 4 -- GPIO2
res = 0 -->  GPIO16
bus = 1
spi.setup(bus, spi.MASTER, spi.CPOL_LOW, spi.CPHA_LOW, 8, 8)
-- we won't be using the HSP> I /CS line, so disable it again
gpio.mode(8, gpio.INPUT, gpio.PULLUP)

wifi.setmode(wifi.STATION)
wifi.sta.config({
	ssid = "itx",
	pwd = "5872u7ya",
	save = true
})
wifi.sta.connect()


disp = u8g2.ssd1327_midas_128x128(bus, cs, dc, res)
disp:setFont(u8g2.font_6x10_tf)

http.get("http://api.k780.com:88/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json", nil, function(code, data)
	disp:clearBuffer()
	disp:clearBuffer()
	if (code < 0) then
	disp:drawStr(0, 10, "HTTP request failed")
	else
		y = 10
		x = 0
		for ch = 1,#data,21 do
			disp:drawStr(0, y, data:sub(ch,ch+21))
			y = y + 10
		end
	end
	disp:sendBuffer()
end)