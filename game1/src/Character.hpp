#include <SFML/Graphics.hpp>

class Character {
public:
    Character(int x_, int y_, int tileSizeX_, int tileSizeY_, const sf::Texture& texture, const sf::Vector2f& pos);
    void draw(sf::RenderTarget& rt) const;
    void setDirection(const sf::Vector2f& dir);
    void update(float dt);
    sf::Sprite getSprite();
private:
    int x_; // x: x coordinate of sprite on texture png
    int y_; // y: y coordinate of sprite on texture png
    int tileSizeX_; // tileSizeX: Size of tile in x direction
    int tileSizeY_; // tileSizeY: Size of tile in y direction

	static constexpr float speed_ = 100.0f;
	sf::Vector2f pos_;
	sf::Vector2f vel_ = {0.0f,0.0f};
	sf::Sprite sprite_;

};