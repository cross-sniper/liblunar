function Entity(x,y,w,h,color,speed)
	self = {
		x=x,
		dx=0,
		y=y,
		speed=speed,
		dy=0,
		width=w,
		height=h,
		color = color,  -- Add this line to assign the color parameter
		draw=function()
			raylua.DrawRectangle(self.x,self.y,self.width,self.height,self.color)
		end,

		move = function(target)
		end
	}
	return self
end

return Entity
