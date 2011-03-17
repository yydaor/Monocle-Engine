#include "Sprite.h"
#include "TextureAsset.h"
#include "AssetDatabase.h"
#include "Graphics.h"
#include "Entity.h"

namespace Monocle
{
	bool Sprite::showBounds = false;

	Sprite::Sprite(const char *filename, float width, float height)
		: Graphic(), texture(NULL), isSelected(false), scale(1.0f), width(width), height(height), angle(0.0f)
	{
		texture = AssetDatabase::RequestTexture(filename);
		if (texture != NULL)
		{
			if (width == -1 || height == -1)
			{
				width = texture->width;
				height = texture->height;
			}
		}
	}

	/*
	Sprite::Sprite()
		: Entity(), texture(NULL), scale(1.0f), isSelected(false), angle(0.0f), width(64), height(64)
	{}
	*/

	void Sprite::Render(Entity *entity)
	{
		Graphics::PushMatrix();
		Graphics::Translate(entity->position.x, entity->position.y, entity->depth);
		Graphics::Rotate(angle, 0, 0, 1);
		Graphics::Blend();
		Graphics::SetColor(color);
		Graphics::BindTexture(texture);
		if (texture != NULL)
			Graphics::RenderQuad(width * scale, height * scale);
		Graphics::PopMatrix();

		if (showBounds || isSelected)
		{
			if (texture != NULL)
			{
				if (isSelected)
					Graphics::SetColor(Color::red);
				else
					Graphics::SetColor(Color(0.5f,0.5f,0.5f,0.25f));
				Graphics::BindTexture(NULL);
				Graphics::RenderLineRect(entity->position.x, entity->position.y, width * scale, height * scale);
			}
		}
	}
}