Entity = dofile("./scripts/Entity.lua")
Enemy = dofile("./scripts/Enemy.lua")

function setup()
    raylua.SetWindowTitle("This is a test")

    player = Entity(40, 20, 20, 20, raylua.WHITE, 5)
    e = Enemy(30,30,20,20,raylua.RED, 4)

	player.draw=function()
		raylua.DrawRectangle(player.x,player.y,player.width,player.height,player.color)
	end

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
    e.move(player)
    e.draw()
    player.move()
    player.draw()
    raylua.DrawFPS(0, 0)
end
