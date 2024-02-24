function setup()
	raylua.SetWindowTitle("this is a test")
	player = {
		x=40,
		y=20,
		width = 20,
		height= 20,
		move=function()
			if raylua.IsKeyDown(raylua.KEY_W) then
				player.y = player.y - 5
			end
			if raylua.IsKeyDown(raylua.KEY_S) then
				player.y = player.y + 5
			end
			if raylua.IsKeyDown(raylua.KEY_A) then
				player.x = player.x - 5
			end
			if raylua.IsKeyDown(raylua.KEY_D) then
				player.x = player.x + 5
			end
		end
	}
end

function loop()
	player:move()
	raylua.DrawFPS(0,0)
	raylua.DrawRectangle(player.x, player.y, player.width,player.height, raylua.WHITE)
end