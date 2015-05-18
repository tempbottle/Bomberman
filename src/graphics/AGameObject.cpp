//
// AGameObject.cpp for CPP_BOMBERMAN in /home/Jamais/cpp_bomberman
//
// Made by Jamais
// Login   <Jamais@epitech.net>
//
// Started on  Sat May 16 20:52:10 2015 Jamais
// Last update Sat May 16 22:13:18 2015 Jamais
//

#include	"AGameObject.hh"

AGameObject::AGameObject() : _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{}

AGameObject::AGameObject(glm::vec3 const& position) : _rotation(0, 0, 0), _scale(1, 1, 1)
{
  _position = position;
}

AGameObject::AGameObject(glm::vec3 const& position, glm::vec3 const& rotation, glm::vec3 const& scale)
{
  _position = position;
  _rotation = rotation;
  _scale = scale;
}

AGameObject::AGameObject(AGameObject const& model)
{
  _position = model.getPosition();
  _rotation = model.getRotation();
  _scale = model.getScale();
}

AGameObject&	AGameObject::operator=(AGameObject const& model)
{
  _position = model.getPosition();
  _rotation = model.getRotation();
  _scale = model.getScale();
  return (*this);
}

AGameObject::~AGameObject() {}

void		AGameObject::setTexture(UNUSED gdl::Texture const& texture) {}

bool		AGameObject::initialize() { return true; }

void		AGameObject::update(UNUSED gdl::Clock const& clock, UNUSED gdl::Input &input)
{}

void		AGameObject::translate(glm::vec3 const& translation)
{
  _position += translation;
}

void		AGameObject::rotate(glm::vec3 const& axis, float angle)
{
  _rotation += axis * angle;
}

void		AGameObject::scale(glm::vec3 const& scale)
{
  _scale *= scale;
}

glm::vec3      	AGameObject::getPosition() const
{
  return _position;
}

glm::vec3	AGameObject::getRotation() const
{
  return _rotation;
}

glm::vec3	AGameObject::getScale() const
{
  return _scale;
}

void		AGameObject::setPosition(glm::vec3 const& position)
{
  _position = position;
}

void		AGameObject::setRotation(glm::vec3 const& rotation)
{
  _rotation = rotation;
}

void		AGameObject::setScale(glm::vec3 const& scale)
{
  _scale = scale;
}

glm::mat4	AGameObject::getTransformation() const
{
  glm::mat4	transform(1);

  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  transform = glm::translate(transform, _position);
  transform = glm::scale(transform, _scale);
  return transform;
}