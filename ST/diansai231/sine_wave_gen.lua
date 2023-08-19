for i = 1,30,1 do
	io.write(string.format("%d,",(math.ceil(2048*math.sin(i/30.0*2*math.pi) + 2048))))
end