#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;
class MapChip {
public:
	enum class StageData {
		none,
		block
	};

	void Initialize();
	void Update();
	void Draw(const Camera* camera);

	void SetOrigin(const Vector2& origin) { originOffset_ = origin; }
	Vector2 GetMaxMapSize() const { return maxMapSize; }

private:
	void CreateStageObjectes();
	void CreateStageWorldTransform();

	std::string fileName;

	std::vector<std::vector<StageData>> stageBlocks_;
	std::vector<std::vector<WorldTransform*>> stageworldtransforms_;

	std::unique_ptr<Model> blockModel;

	Vector2 maxMapSize;

	Vector2 originOffset_{0.0f, 0.0f};

	static inline const float BlockSize = 2.0f;
};
