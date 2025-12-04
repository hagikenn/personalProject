#include "MapChip.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void MapChip::Initialize() {
	fileName = "Resources/mapchip.csv";

	CreateStageObjectes();
	CreateStageWorldTransform();

	blockModel = std::unique_ptr<Model>(Model::CreateFromOBJ("cube"));
}

void MapChip::CreateStageObjectes() {
	std::ifstream file(fileName);
	if (!file) {
		std::cerr << "ファイルを開けませんでした。" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		stageBlocks_.push_back(std::vector<StageData>());
		int lineNumber = static_cast<int>(stageBlocks_.size()) - 1;
		std::stringstream ss(line);
		std::string cell;

		while (std::getline(ss, cell, ',')) {
			int value = std::stoi(cell);
			stageBlocks_[lineNumber].push_back(static_cast<StageData>(value));
		}
	}
	maxMapSize.x = static_cast<int>(stageBlocks_[0].size()) * BlockSize;
	maxMapSize.y = static_cast<int>(stageBlocks_.size()) * BlockSize;
}

void MapChip::CreateStageWorldTransform() {
	for (size_t y = 0; y < stageBlocks_.size(); ++y) {
		stageworldtransforms_.push_back(std::vector<WorldTransform*>());
		for (size_t x = 0; x < stageBlocks_[y].size(); ++x) {
			if (stageBlocks_[y][x] == StageData::none) {
				stageworldtransforms_[y].push_back(nullptr);
			} else {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransform->translation_ = {(BlockSize * 0.5f) + (BlockSize * x), (BlockSize * 0.5f) + (BlockSize * (stageBlocks_.size() - 1 - y)), 0.0f};
				worldTransform->UpdateMatrix();
				stageworldtransforms_[y].push_back(worldTransform);
			}
		}
	}
}

void MapChip::Update() {

}

void MapChip::Draw(const Camera* camera) {
	int y = 0; // 行のインデックスを初期化
	for (const auto& line : stageworldtransforms_) {
		int x = 0; // 列のインデックスを初期化
		for (const auto& worldTransform : line) {
			if (worldTransform != nullptr) {
				// cameraはポインタなので参照渡しに変換
				blockModel->Draw(*worldTransform, *camera);
			}
			x++;
		}
		y++;
	}
}