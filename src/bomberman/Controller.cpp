//
// Controller.cpp for Controller in /home/jibb/rendu/cpp_bomberman
//
// Made by Jean-Baptiste Grégoire
// Login   <jibb@epitech.net>
//
// Started on  Sun May  3 16:38:09 2015 Jean-Baptiste Grégoire
// Last update Tue May  5 20:00:52 2015 Jean-Baptiste Grégoire
//

#include "Controller.hh"

Controller::Controller() : _id(0), _fd(0), _isPlugged(false)
{
  for (uint32_t id = 1; id < 11; ++id)
  {
	  std::stringstream	tmp;
	  tmp << "/dev/input/js";
	  tmp << id;
	  std::cout << tmp.str() << std::endl;
	  _fd = open(tmp.str().c_str(), O_RDONLY | O_NONBLOCK);
	  if (_fd != -1)
	  {
	  	flock(_fd, LOCK_EX);
  		_ctrlerFile.assign(tmp.str());
  	  	_isPlugged = true;
		_id = id;
		break;
	  }
  }
	bzero(&_ctrler, sizeof(t_controller));
}

void		Controller::controllerUpdate()
{
	std::vector<t_controller> v;
  	int 	ret(0);

	_state.clear();
	if (_isPlugged == false && stat(_ctrlerFile.c_str(), &_statBuf) == 0)
    {
		flock(_fd, LOCK_UN);
     	close(_fd);
     	_fd = open(_ctrlerFile.c_str(), O_RDONLY | O_NONBLOCK);
    	if (_fd != -1)
		{
	  		flock(_fd, LOCK_EX);
	  		_isPlugged = true;
		}
    }
    if (_isPlugged == true)
    {
		while ((ret = read(_fd, reinterpret_cast<char *>(&_ctrler), sizeof(t_controller))) > 0)
			v.push_back(_ctrler);
	}
	if (ret == -1 && (errno ^ EAGAIN) != 0)
		_isPlugged = false;
	// erase all double event
	if (_isPlugged == true && !v.empty())
	{
		for (auto it = v.end() - 1; it >= v.begin(); --it)
		{
			auto s = it - 1;
			while (s >= v.begin())
			{
				if (s->type == it->type && s->number == it->number)
					s = v.erase(s);
				else
					--s;
			}
		}
		for (auto it = v.begin(); it != v.end(); ++it)
		{
			bomber::Event tmp;
			qualifyEvent(&(*it), tmp);
			_state.push_back(tmp);
		}
	}
}

bool		Controller::handleEvent(bomber::Event &event, bomber::Event::KeyID key)
{
	if (!_isPlugged)
		return (false);
	for (auto it = _state.begin(); it != _state.end(); ++it)
	{
		if ((*it).key == key)
		{
			event = *it;
			return (true);
		}
	}
	return (false);
}

void		Controller::qualifyEvent(t_controller *ctrler, bomber::Event &event)
{
    if (ctrler->type == JOYSTICK)
	event.type = bomber::Event::JoystickMove;
      else
	{
	  if (ctrler->value == 1)
	    event.type = bomber::Event::KeyPressed;
	  else
	    event.type = bomber::Event::KeyReleased;
	}
      switch (ctrler->number)
	{
	case 0:
	  if (event.type == bomber::Event::JoystickMove)
	    event.key = (ctrler->value > 0 ? bomber::Event::JoyMiddleRight : bomber::Event::JoyMiddleLeft);
	  else
	    event.key = bomber::Event::XboxY;
	  break;
	case 1:
	  if (event.type == bomber::Event::JoystickMove)
	    event.key = (ctrler->value > 0 ? bomber::Event::JoyMiddleDown : bomber::Event::JoyMiddleUp);
	  else
	    event.key = bomber::Event::XboxB;
	  break;
	case 2:
	  if (event.type == bomber::Event::JoystickMove)
	    event.key = (ctrler->value > 0 ? bomber::Event::JoyRightRight : bomber::Event::JoyRightLeft);
	  else
	    event.key = bomber::Event::XboxA;
	  break;
	case 3: event.key  = (event.type == bomber::Event::JoystickMove ? bomber::Event::TriggerLB : bomber::Event::XboxX); break;
	case 4: event.key = (event.type == bomber::Event::JoystickMove ? bomber::Event::TriggerRB : bomber::Event::TriggerLT); break;
	case 5:
	  if (event.type == bomber::Event::JoystickMove)
	    event.key = (ctrler->value > 0 ? bomber::Event::JoyRightDown : bomber::Event::JoyRightUp);
	  else
	    event.key = bomber::Event::TriggerRT;
	  break;
	case 6: event.key = (ctrler->value > 0 ? bomber::Event::JoyLeftRight : bomber::Event::JoyLeftLeft); break;
	case 7: event.key = (ctrler->value > 0 ? bomber::Event::JoyLeftDown : bomber::Event::JoyLeftUp); break;
	case 8: event.key = bomber::Event::Start; break;
	case 9: event.key = bomber::Event::Select; break;
	case 10: event.key = bomber::Event::Start; break;
	case 11: event.key = bomber::Event::Undifined; break;
	case 12: event.key = bomber::Event::Power; break;
	case 13: event.key = bomber::Event::Undifined; break;
	default: event.key = bomber::Event::Undifined; break;
	}
  event.value = ctrler->value;
}

bool		Controller::plugged() const
{
  return (_isPlugged);
}

Controller::~Controller()
{
	flock(_fd, LOCK_UN);
	close(_fd);
}
