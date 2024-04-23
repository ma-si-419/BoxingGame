#pragma once
#include "SceneBase.h"
#include <memory>

class CharacterBase;
class SceneGame : public SceneBase
{
public:
	SceneGame(SceneManager& sceneManager, DataManager& dataManager);
	~SceneGame();
	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//�I������
	void End();
private:
	
	std::shared_ptr<CharacterBase> m_pPlayer;

};

