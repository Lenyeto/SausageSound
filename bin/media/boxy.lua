local mod = {}

function mod.onCreate(self)
	log("in boxy's onCreate method")
	registerListener(self)
	self:createMesh("crate.mesh")
	self:setScale(100, 100, 100)
	self:setPosition(0, 260, 0)
	log("test")
	self.speed = 200					-- testing the __newindex metamethod...
	log("self.speed = " .. tostring(self.speed))
end


function mod.onUpdate(self)
	--log("in boxy's onUpdate method.  self.speed = " .. tostring(self.speed) .. " horizontal = " .. tostring(getAxis("horizontal")))
	local speed = tonumber(self.speed)				-- internally it's a string (for now)
	local dt = getDT()
	self:translateLocal(getAxis("horizontal") * speed * dt, 0, -getAxis("vertical") * speed * dt)
end


function mod.onAction(self)
	if isActionActive("cancel") then
		quit()
	end
	log("got an action (don't know which, though :-( )")
end


return mod