Entity = dofile("./scripts/Entity.lua")
Bullet = dofile("./scripts/Bullet.lua")

function setup()
    raylua.SetWindowTitle("This is a test")

    player = Entity(40, 20, 20, 20, raylua.WHITE, 5)

    bullets = {}  -- List to store bullet instances

    -- Add bullets to the list as needed

	player.move = function()
	    local speed = 5

	    if raylua.IsKeyDown(raylua.KEY_W) then
	        player.y = player.y - speed
	    end
	    if raylua.IsKeyDown(raylua.KEY_S) then
	        player.y = player.y + speed
	    end
	    if raylua.IsKeyDown(raylua.KEY_A) then
	        player.x = player.x - speed
	    end
	    if raylua.IsKeyDown(raylua.KEY_D) then
	        player.x = player.x + speed
	    end
	end
end

function loop()
    player:move()

    for _, bullet in ipairs(bullets) do
        bullet:move()
        bullet:draw()
    end

    raylua.DrawFPS(0, 0)
    raylua.DrawRectangle(player.x, player.y, player.width, player.height, player.color)
end
