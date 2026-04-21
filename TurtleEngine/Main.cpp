#include "PrecompiledHeader.h"
#include "Engine/Engine.h"

int main()
{
	Engine* engine = Engine::GetInstance();
	engine->Initialize(TEXT("Turtle Engine"), 900, 500);
	engine->Run();

	SafeDelete(engine);
}