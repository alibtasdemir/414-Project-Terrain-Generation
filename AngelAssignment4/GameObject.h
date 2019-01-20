/*
#include <vector>


class GameObject;
class Component;

class Component {
public:
	GameObject* owner;
};
class GameObject {
public:
	vec3 position;
	vec3 rotation;
	mat4 transform = mat4(1);

	std::vector<Component*> components = std::vector<Component*>();

	Component* AddComponent(Component* component) {
		components.push_back(component);
	}
	static void DestroyComponent(Component* component) {
		GameObject* owner = component->owner;
		std::vector<Component*> vector = owner->components;
		std::vector<Component*>::iterator position = std::find(vector.begin(), vector.end(), component);
		
		if (position != vector.end())
			vector.erase(position);

		free(component);
	}
};
*/