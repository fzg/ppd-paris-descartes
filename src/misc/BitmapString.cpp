#include "BitmapString.hpp"


BitmapString::BitmapString(const BitmapFont& font)
{
	font_ = &font;
	char_width_ = font_->GetCharWidth();
}


void BitmapString::SetText(const char* text)
{
	Clear();
	const char* p = text;
	while (*p != '\0')
	{
		AppendChar(*p);
		++p;
	}
}


void BitmapString::SetText(const std::string& text)
{
	SetText(text.c_str());
}


const char* BitmapString::GetText() const
{
	return chars_.c_str();
}


void BitmapString::AppendChar(char character)
{
	sf::Sprite sprite;
	sprite.SetImage(font_->GetImage());
	sprite.SetSubRect(font_->GetCharRect(character));
	sprite.SetColor(GetColor());

	size_t length = bitmaps_.size();
	if (length > 0)
	{
		sprite.SetX(length * char_width_);
	}
	bitmaps_.push_back(sprite);
	chars_ += character;
}


void BitmapString::InsertChar(char character, int position)
{
	position = GetRealPosition(position);

	sf::Sprite sprite;
	sprite.SetImage(font_->GetImage());
	sprite.SetSubRect(font_->GetCharRect(character));
	sprite.SetColor(GetColor());
	sprite.SetX(position * char_width_);

	chars_.insert(position, 1, character);
	bitmaps_.insert(bitmaps_.begin() + position, sprite);
	ComputePosition(position + 1);
}


void BitmapString::RemoveChar(int position)
{
	if (chars_.empty())
	{
		return;
	}

	position = GetRealPosition(position);
	if (position > (int) chars_.size() - 1)
	{
		position = chars_.size() - 1;
	}

	chars_.erase(position, 1);
	bitmaps_.erase(bitmaps_.begin() + position);
	ComputePosition(position);
}


char BitmapString::GetCharAt(int position) const
{
	return chars_[GetRealPosition(position)];
}


void BitmapString::SetFont(const BitmapFont& font)
{
	if (&font != font_)
	{
		font_ = &font;
		char_width_ = font.GetCharWidth();
		for (size_t i = 0; i < bitmaps_.size(); ++i)
		{
			sf::Sprite& sprite = bitmaps_[i];
			sprite.SetX(i * char_width_);
			sprite.SetSubRect(font_->GetCharRect(chars_[i]));
			sprite.SetImage(font_->GetImage());
		}
	}
}


const BitmapFont& BitmapString::GetFont() const
{
	return *font_;
}


void BitmapString::Clear()
{
	bitmaps_.clear();
	chars_.clear();
}


int BitmapString::Length() const
{
	return chars_.size();
}


void BitmapString::SetColor(const sf::Color& color)
{
	Drawable::SetColor(color);
	for (SpriteVec::iterator it = bitmaps_.begin(); it != bitmaps_.end(); ++it)
	{
		it->SetColor(color);
	}
}


void BitmapString::Render(sf::RenderTarget& target) const
{
	for (SpriteVec::const_iterator it = bitmaps_.begin(); it != bitmaps_.end(); ++it)
	{
		target.Draw(*it);
	}
}


int BitmapString::GetRealPosition(int position) const
{
	if (position < 0)
	{
		return chars_.size() + position;
	}
	return position;
}


void BitmapString::ComputePosition(int from)
{
	for (size_t i = from; i < bitmaps_.size(); ++i)
	{
		bitmaps_[i].SetX(i * char_width_);
	}
}

