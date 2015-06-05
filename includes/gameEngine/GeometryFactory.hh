//
// GeometryFactory.hh for CPP_COMBERMAN in /home/Jamais/cpp_bomberman
//
// Made by Jamais
// Login   <Jamais@epitech.net>
//
// Started on  Sun May 24 05:21:40 2015 Jamais
// Last update Wed Jun  3 20:07:49 2015 Jamais
//

#ifndef				___GEOMETRY_FACTORY_HH___
# define			___GEOMETRY_FACTORY_HH___

# include			"graphics.hh"
# include			"Geometric.hh"

class				GeometryFactory
{
public:
  enum	eGeometry
    {
      RIGHT_PLANE = 0,
      LEFT_PLANE,
      UP_PLANE,
      DOWN_PLANE,
      FRONT_PLANE,
      BACK_PLANE,
      CUBE
    };


private:
  std::map<eGeometry, gdl::Geometry* >	_figures;

private:
  gdl::Geometry*		createDownPlane() const;
  gdl::Geometry*		createUpPlane() const;
  gdl::Geometry*		createRightPlane() const;
  gdl::Geometry*		createLeftPlane() const;
  gdl::Geometry*		createFrontPlane() const;
  gdl::Geometry*		createBackPlane() const;
  gdl::Geometry*		createCube() const;

public:
  GeometryFactory();

public:
  ~GeometryFactory();

public:
  gdl::Geometry&		getGeometry(eGeometry const& type);

};

#endif				/* !___GEOMETRY_FACTORY_HH___ */