#include<Oak.h>

class Sandox :public Oak::Application {
public:
	Sandox() {

	}
	
	~Sandox() {

	}
};

Oak::Application* Oak::CreateApplication() {
	return new Sandox();
}