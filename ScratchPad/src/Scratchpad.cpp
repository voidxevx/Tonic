#include <iostream>

#include <xenon.h>

struct messageComponent
{
	std::string message;
};

struct volumeComponent
{
	unsigned int volume;
};

class MessageSystem : public xenon::SystemInterface
{
public:
	MessageSystem(XenonArchetype set)
		: xenon::SystemInterface(set)
	{

	}

	~MessageSystem()
	{

	}

	virtual void OnSystemUpdate(xenon::registry* reg, XenonID entity) override
	{
		messageComponent* msg = reg->GetComponent<messageComponent>(entity);
		volumeComponent* vol = reg->GetComponent<volumeComponent>(entity);
		if (vol)
			std::cout << "[" << vol->volume << "] " << msg->message << std::endl;
		else
			std::cout << msg->message << std::endl;
	}
};

int main()
{
	xenon::registry* registry = new xenon::registry(32, 1, 2);
	registry->RegisterComponent<messageComponent>();
	registry->RegisterComponent<volumeComponent>();

	registry->RegisterArchetype<MessageSystem, messageComponent>();

	XenonID ent = registry->CreateEntity();
	registry->SetTickEnabled(ent);
	registry->AddComponent(ent, new messageComponent{ "Hello, world!" });
	registry->AddComponent(ent, new volumeComponent{ 2 });


	registry->UpdateSystems();

	return 0;
}