#include <Angel_commons/Angel.h>
#include <vector>


class Interactable
{
public:
	float radius;

	vec3 position;
	vec3 rotation;
	mat4 transform = mat4(1);

	Interactable();
	void UpdateTransform();

	bool Raycast(vec3 origin, vec3 direction);
	/*    WATCH HERE
	Interactable() {
		interactables.push_back(this);
	}
	*/
};



//std::vector<Interactable*> interactables = std::vector<Interactable*>();



//Interactable* selectedInteractable;

void SelectInteractable(vec3 camPos, vec3 camLook);
void MoveSelectedInteractable(char input);