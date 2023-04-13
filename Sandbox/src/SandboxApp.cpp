#include "Hazel.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox() {};
	~Sandbox() {};

private:
	int id = 0;

};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}