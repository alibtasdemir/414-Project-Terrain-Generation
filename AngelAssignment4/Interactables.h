#include <Angel_commons/Angel.h>
#include <vector>
#include "TerrainMesh.h"


class Interactable
{
public:
	float radius;

	vec3 position;
	vec3 rotation;
	mat4 transform = mat4(1);

	vec3 velocity;

	Interactable();
	void UpdateTransform();
	
	void UpdatePhysics();
	bool Raycast(vec3 origin, vec3 direction);
};



//std::vector<Interactable*> interactables = std::vector<Interactable*>();



//Interactable* selectedInteractable;

void SelectInteractable(vec3 camPos, vec3 camLook);
void MoveSelectedInteractable(char input);