-- local input = io.open("./test.txt", "r")
local input = io.open("./input.txt", "r")

local left = {}
local right = {}

local count = function (l, k)
	local c = 0
	for _,i in ipairs(l) do
		if i == k then
			c = c + 1
		end
	end
	return c
end

for l, r in string.gmatch(input:read("a"), "(%d+),(%d+)") do
	left[#left + 1] = tonumber(l);
	right[#right+ 1] = tonumber(r);
end

local sum = 0
for _,i in ipairs(left) do
	sum = sum + (i * count(right, i))
end

print(sum)

