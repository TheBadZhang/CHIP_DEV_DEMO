for i=1,96,1 do
	for j = 1,2,1 do
		-- if j < 20 then io.write("0x00,")
		-- else io.write("0x7f,") end
		if i%6 == 0 then io.write("0x00,")
		else io.write(string.format("0x%02x,", math.random(0,127))) end
	end
	io.write("\n")
end