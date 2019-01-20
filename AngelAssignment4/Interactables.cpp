#include "Interactables.h"

//interactables = std::vector<Interactable*>();
void Interactable::UpdateTransform() {
	transform = Translate(position) * RotateZ(rotation.z) * RotateY(rotation.y) * RotateX(rotation.x);
}
bool Interactable::Raycast(vec3 origin, vec3 direction) {
	vec3 E0 = origin;
	vec3 E1 = origin + direction;

	vec3 C = position;

	vec3 D = C - E0;
	vec3 E = E1 - E0;

	float e2 = dot(E, E); //E.Dot(E);
	float ed = dot(E, D); //E.Dot(D);

	float t = ed / e2;

	if (t < 0.0f) t = 0.0f; else if (t > 1.0f) t = 1.0f;

	vec3 closestPoint = E0 + E * t;

	float distance = length(position - closestPoint);
	if (distance < radius) {
		return true;
	}
	else {
		return false;
	}
}
std::vector<Interactable*> interactables = std::vector<Interactable*>();
Interactable* selectedInteractable = NULL;

Interactable::Interactable() {
	interactables.push_back(this);
	std::cout << "interactable list updated" << std::endl;
}

void SelectInteractable(vec3 camPos, vec3 camLook)
{
	for (int i = 0; i < interactables.size(); i++) {
		Interactable* element = interactables[i];
		if (element->Raycast(camPos, camLook) == true) {
			selectedInteractable = element;
			return;
		}
	}
}

void MoveSelectedInteractable(char input)
{
	float move = 1;
	float rotate = 0.1f;
	if (selectedInteractable == NULL) { return; }
	switch (input)
	{
	case 'r':// right
		selectedInteractable->position += vec3(1, 0, 0) * move;
		selectedInteractable->UpdateTransform();
		break;
	case 'f':// left
		selectedInteractable->position += vec3(-1, 0, 0) * move;
		selectedInteractable->UpdateTransform();
		break;
	case 't':// up
		selectedInteractable->position += vec3(0, 1, 0) * move;
		selectedInteractable->UpdateTransform();
		break;
	case 'g':// down
		selectedInteractable->position += vec3(0, -1, 0) * move;
		selectedInteractable->UpdateTransform();
		break;
	case 'y':// forward
		selectedInteractable->position += vec3(0, 0, 1) * move;
		selectedInteractable->UpdateTransform();
		break;
	case 'h':// back
		selectedInteractable->position += vec3(0, 0, -1) * move;
		selectedInteractable->UpdateTransform();
		break;

		//rotations
	case 'u':// right
		selectedInteractable->rotation += vec3(1, 0, 0) * move;
		selectedInteractable->UpdateTransform();
		break;
	case 'j':// left
		selectedInteractable->rotation += vec3(-1, 0, 0) * move;
		selectedInteractable->UpdateTransform();
		break;
	case '�':// up
		selectedInteractable->rotation += vec3(0, 1, 0) * move;
		selectedInteractable->UpdateTransform();
		break;
	case 'k':// down
		selectedInteractable->rotation += vec3(0, -1, 0) * move;
		selectedInteractable->UpdateTransform();
		break;
	case 'o':// forward
		selectedInteractable->rotation += vec3(0, 0, 1) * move;
		selectedInteractable->UpdateTransform();
		break;
	case 'l':// back
		selectedInteractable->rotation += vec3(0, 0, -1) * move;
		selectedInteractable->UpdateTransform();
		break;


		default:
			break;
	}
}
