#include "Particle.h"
#include "MyMath.h"
#include <cassert>

void Particle::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
}

void Particle::Update() {

	// ワールドトランスフォームの更新
	WorldTransformUpdate(worldTransform_);
}

void Particle::Draw(const Camera& camera) { model_->Draw(worldTransform_, camera); }