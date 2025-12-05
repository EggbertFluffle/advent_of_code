local input = io.open("./test.txt", "r")
-- local input = io.open("./input.txt", "r")

--@class 
--@field id number Id of the piece
--@field sides string[] sides of the piece (top, right, left, bottom)
local piece = {}

--@param section stirng
-- local create_piece = function (section)
-- 	local piece = {
-- 	}
-- end

for id, tile in input:read("a"):gmatch("Tile (%d+):[^\n]*\n(.-)\n\n") do
	local piece = { id = tonumber(id), sides = {} }
	
	for line in tile:gmatch("(.-)\n") do
		line
	end
end
