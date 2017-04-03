#include "stdafx.h"
#include "PGEditorInstance.h"
//
//#include "AssetManager.h"
//
//
//#include "PGTree.h"
//
//
//
//#include "String.h"
//#include "Texture.h"

//
//class Particle {
//public:
//	r32 life;
//	v3 possition;
//	v3 velocity;
//	Particle() {
//		life = 0;
//		possition = v3(0.f);
//		velocity = v3(0.f);
//	}
//	virtual ~Particle() {
//
//	}
//};w
//class ParticleEffect {
//public:
//	//We need a shader
//	//We need a VAO
//	Buffer<Particle> *particle_data;
//	ParticleEffect(int max_particle) {
//		particle_data = new Buffer<Particle>(max_particle);
//	}
//	virtual ~ParticleEffect() {
//		delete(particle_data);
//	}
//	virtual void ParticleEffect::Update() {
//		Particle * particle = particle_data->At(0);
//		int cpt = 0;
//		r32* lifes = &particle->life;
//		while (cpt < particle_data->count) {
//			printf("%f", *lifes);
//			lifes += sizeof(Particle);
//			cpt++;
//		}
//	}
//	virtual void ParticleEffect::Render() {
//
//	}
//};
//class ParticleManager {
//public:
//	List <ParticleEffect> *effect_list;
//	int max_active_effect; //?
//	ParticleManager() {
//		effect_list = new List <ParticleEffect>();
//	}
//	~ParticleManager() {
//		delete(effect_list);
//	}
//};





int main(int argc, char **argv)
{
	//ParticleManager * manager_test = new ParticleManager();
	//ParticleEffect* effect_Test = new ParticleEffect(100);
	//manager_test->effect_list->Add(effect_Test);

	//effect_Test->Update();

	
	//_sleep(10000);

	PGEditorInstance* main_instance = new PGEditorInstance();
			main_instance->Build();
			main_instance->Start();
		delete(main_instance);


	return 0;
}

