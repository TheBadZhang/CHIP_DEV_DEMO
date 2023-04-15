file = io.open ("test.hex", "r")
file2 = io.open ("font.hex", "wb")

str = file:read("*a")

for i = 1,#str,2 do
	a = str:sub(i,i)
	b = str:sub(i+1,i+1)
	if (a >= "a") then a = string.byte(a)-string.byte('a')+10
	elseif a >= "A" and a <= "Z" then a = string.byte(a)-string.byte('A')+10
	else a = string.byte (a) - string.byte ('0') end
	if (b >= "a") then b = string.byte(b)-string.byte('a')+10
	elseif b >= "A" and b <= "Z" then b = string.byte(b)-string.byte('A')+10
	else b = string.byte (b) - string.byte ('0') end
	print (a,b,string.format("%x",a*16+b))
	file2:write (string.char(a*16+b))
end

file:close ()
file2:close ()
