--createGameObject("temp", "boxy_the_player", 52, "boxy.lua")

createGameGroup("temp")
local G = GameObject.new("temp", "boxy_the_player", 52, "..\\media\\boxy.lua")
local name = G.name
log("G's name is: '" .. tostring(name) .. "'")

setGravity(0, -1000, 0)

createGameGroup("physics")
--local S = GameObject.new("physics", "pobj", 10)
--S:setPosition(-800, 400, 0)
--S:setScale(50, 50, 50)

-- Note: I'm doing the "automated" way of getting extents / scale -- you may have to 
--      call these a bit differently if not doing the bonus.
--S:createMesh("crate.mesh")
--S:createPhysics("box", 150.0, true)
--S:createMesh("earth.mesh")
--S:createPhysics("sphere", 150.0, true)

for i = 1, 50 do
	local S = GameObject.new("physics", "pobj" .. tostring(i), 10, "..\\media\\boxy.lua")
	S:setPosition(1600 * math.random() - 800, 2000 * math.random() + 200, 1600 * math.random() - 800)
	local sfactor = 35 * math.random() + 25
	S:setScale(sfactor, sfactor, sfactor)
	if math.random() > 0.5 then
		S:createMesh("crate.mesh")
		S:createPhysics("box", sfactor * sfactor * sfactor, true)
	else
		S:createMesh("earth.mesh")
		S:createPhysics("sphere", 4 * 3.1416 * sfactor * sfactor * sfactor / 3, true)
	end
end