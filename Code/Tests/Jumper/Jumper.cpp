#include "Jumper.h"
#include "../../Input.h"

// by @NoelFB
namespace Jumper
{
	Player::Player(Vector2 pos) 
		: Sprite(pos, -10, "../../../../Content/Jumper/Player.png", 64, 64)
	{
		speed = 100.0f;
		gravity = 0.25f;
		velocity = Vector2(0.0f, 0.0f);
		jump = 8.0f;
		maxSpeed = 4.0f;

		AddTag("Player");
		AddRectangleCollider(40, 64);
	}

	void Player::Update()
	{
		// increase acceleration
		if (Input::IsKeyHeld(keyLeft))
		{
			if(velocity.x > -maxSpeed) { velocity.x -= speed * Monocle::deltaTime; }
		}
		else if (Input::IsKeyHeld(keyRight))
		{
			if(velocity.x < maxSpeed) { velocity.x += speed * Monocle::deltaTime; }
		}
		else
		{
			velocity.x = 0;
		}

		// jump
		if(Input::IsKeyHeld(keyUp) && onGround)
		{
			velocity.y = -jump;
			isJumping = true;
			onGround = false;
		}

		// friction

		// gravity
		velocity.y += gravity;

		
		//move
		Vector2 lastPosition = position;
		float temp = 0.001f;

		position.x += velocity.x;
		if(Collide("Wall"))
		{
			position.x = lastPosition.x;
			velocity.x = 0.0f;
		}

		onGround = false;

		position.y += velocity.y;

		if(Collide("Wall"))
		{
			// small ground collision problem here if falling fast (warps back up too far)
			// could do a line intersection with the collider we hit
			// collider->IntersectsLine()
			// ^ if this gave us the intersection point, we could snap right to the ground instead

			position.y = lastPosition.y;
			velocity.y = 0;
			onGround = true;
			isJumping = false;;
		}
	}

	float Player::Sign(float i, float to)
	{
		return i < 0 ? - to : (i > 0 ? to : 0);
	}


	Wall::Wall(Vector2 pos, float w, float h)
		: Entity()
	{
		position = pos;
		AddTag("Wall");
		AddRectangleCollider(w, h);
		this->width = w;
		this->height = h;
	}

	void Wall::Render()
	{
		Graphics::PushMatrix();
		Graphics::Translate(position);
		Graphics::BindTexture(NULL);
		Graphics::RenderQuad(width, height);
		Graphics::PopMatrix();
	}

	void GameScene::Begin()
	{
		Debug::Log("Jumper::GameScene::Begin()!");
		Scene::Begin();

		Add(new Wall(Vector2(400.0f, 500.0), 200.0f, 10.0f));
		Add(new Wall(Vector2(600.0f, 400.0), 100.0f, 10.0f));
		Add(new Wall(Vector2(200.0f, 400.0), 20.0f, 150.0f));

		player = new Player(Vector2(400.0f, 300.0f));
		player->keyUp = KEY_UP;
		player->keyLeft = KEY_LEFT;
		player->keyRight = KEY_RIGHT;
		Add(player);
	}

	void GameScene::Update()
	{
		Scene::Update();
	}

	void GameScene::End()
	{
		delete player;
		//walls.clear();
	}
}