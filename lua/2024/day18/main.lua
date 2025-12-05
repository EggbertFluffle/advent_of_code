local input = io.open("./test.txt", "r")
-- local input = io.open("./input.txt", "r")

---@class Coordinate
---@field x number
---@field y number

---@type Coordinate[]
local coords = {}


---@param x number
---@param y number
---@return Coordinate
local create_coordinate = function (x, y)
	return { x = x, y = y }
end

for x, y in string.gmatch(input:read("a"), "(%d+),(%d+)") do
	coords[#coords + 1] = create_coordinate(x + 1, y + 1);
end

local size = 7

---@class Node
---@field h_cost number
---@field f_cost number
---@field coordinate Coordinate
local node = {}

---@type (Node?)[][]
local graph = {}
for col=1,size do
	graph[col] = {}
	for row=1,size do
		graph[col][row] = { coordinate = create_coordinate(col, row), h_cost = 0, f_cost = 0 }
	end
end

local bytes = 12
for i=1, bytes do
	graph[coords[i].x][coords[i].y] = nil
end

-- Preform a* path finding

---@param g boolean[][]
---@param x number
---@param y number
---@return boolean
local in_bounds = function (g, x, y)
	return x > 0 and
		x <= size and
		y > 0 and
		y <= size and
		g[x][y] ~= nil
end

---@param g Node[][]
---@param x number
---@param y number
---@return Node[]
local get_neighbors = function(g, x, y)
	local out = {}

	if in_bounds(g, x + 1, y) then
		out[#out + 1] = g[x + 1][y]
	end

	if in_bounds(g, x, y + 1) then
		out[#out + 1] = g[x][y + 1]
	end

	if in_bounds(g, x - 1, y) then
		out[#out + 1] = g[x - 1][y]
	end

	if in_bounds(g, x, y - 1) then
		out[#out + 1] = g[x][y - 1]
	end

	return out
end

---@type Node
local start = graph[1][1]

---@type Node
local finish = graph[size][size]

local unexplored = {}
local explored = {}

---@param n Node
local explore = function(n) 
	local neighbors = get_neighbors(graph, n.coordinate.x, n.coordinate.y)

	for _, v in ipairs(neighbors) do
		v
	end
end

table.sort(unexplored)
