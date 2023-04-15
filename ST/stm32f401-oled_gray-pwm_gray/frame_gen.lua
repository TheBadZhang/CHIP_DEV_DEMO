function gen_map(iii)
	for i=0,64,1 do
		for j = 0,15,1 do
			if j < iii then
				io.write(string.format("0x%x,", 0x00))
			else
				io.write(string.format("0x%x,", 0xff))
			end
		end
		io.write("\n")
	end
end

gen_map(16)
