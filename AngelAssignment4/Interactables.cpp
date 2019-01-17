#include "Interactables.h"

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
		default:
			break;
	}
}
