function Enemy(x, y, w, h, color, speed)
    local self = Entity(x, y, w, h, color, speed)
    self.move = function(player)
        -- calculate where the player will be, by using their X and Y and speed
        local dx = player.x - self.x
        local dy = player.y - self.y
        local angle = math.atan2(dy, dx)
        
        -- calculate the movement in the x and y directions based on speed
        local moveX = math.cos(angle) * self.speed
        local moveY = math.sin(angle) * self.speed

        -- update the position of the enemy
        self.x = math.floor(self.x + moveX)
        self.y = math.floor(self.y + moveY)
    end

    return self
end

return Enemy
