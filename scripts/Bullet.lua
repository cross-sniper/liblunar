function Bullet(x, y, target, color, speed)
    local bullet = {
        x = x,
        y = y,
        target = target,
        speed = speed,
        width = 5,
        height = 5,
        color = color,
    }

    function bullet:move()
        -- Calculate direction based on the difference between current position and target position
        local angle = math.atan2(self.target.y - self.y, self.target.x - self.x)
        self.dx = self.speed * math.cos(angle)
        self.dy = self.speed * math.sin(angle)

        -- Update the bullet position
        self.x = self.x + self.dx
        self.y = self.y + self.dy
    end

    function bullet:draw()
        raylua.DrawRectangle(self.x, self.y, self.width, self.height, self.color)
    end

    return bullet
end
