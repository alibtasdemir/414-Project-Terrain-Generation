#include <Angel_commons/Angel.h>
#include <vector>


class Interactable
{
public:
	vec3 center;
	float radius;
	vec3 position;
	vec3 rotation;
	mat4 transform = mat4(1);

	void UpdateTransform() {
		transform = Translate(position) * RotateZ(rotation.z) * RotateY(rotation.y) * RotateX(rotation.x);
	}
	bool Raycast(vec3 origin, vec3 direction) {
		vec3 E0 = origin;
		vec3 E1 = origin + direction;

		vec3 C = center;

		vec3 D = C - E0;
		vec3 E = E1 - E0;

		float e2 = dot(E, E); //E.Dot(E);
		float ed = dot(E, D); //E.Dot(D);

		float t = ed / e2;

		if (t < 0.0f) t = 0.0f; else if (t > 1.0f) t = 1.0f;

		vec3 closestPoint = E0 + E * t;

		float distance = length(center - closestPoint);
		if (distance < radius) {
			return true;
		}
		else {
			return false;
		}
	}
};

std::vector<Interactable*> interactables = std::vector<Interactable*>();

Interactable* selectedInteractable = NULL;

void SelectInteractable(vec3 camPos, vec3 camLook);
void MoveSelectedInteractable(char input);