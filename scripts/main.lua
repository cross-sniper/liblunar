-- since lua does not have classes, do this
function init(raylibFunctions)
	self = {}
	function self:draw()
		raylibFunctions.DrawRectangle(self.x, self.y, self.width, self.height, self.color)
	end
end
