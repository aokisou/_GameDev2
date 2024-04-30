#include "GameScene.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"
#include <vector>

void GameScene::PreUpdate()
{
	//Updateの前の更新処理
	//オブジェクトのリストを更新しておく

	//イテレータとは…コンテナクラス用のポインタ(のようなもの)
	//コンテナを先頭から末尾まで辿る際に使用
	//イテレータ作成 ベタ書き
	//std::vector<std::shared_ptr<BaseObject>>::iterator it = m_objList.begin();
	//イテレータ作成 auto版
	//ユーザが定義したものは何かわからない可能性があるため全てautoはダメ
	auto it = m_objList.begin();
	while (it != m_objList.end())//end() 最後の要素の一個後ろを返す
	{
		//オブジェクトの有効チェック
		if (!(*it)->GetAlive())
		{
			//無効なオブジェクトをリストから削除
			it = m_objList.erase(it);
		}
		else
		{
			//次の要素へイテレータを進める
			it++;
		}
	}
	//↑の後に有効なオブジェクトだけのリストになっている
}

void GameScene::Update()
{
	if (rand() % 100 < 3)
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		enemy->SetPos({ 640.f,360.f });
		enemy->SetMove({ -2.f,-2.f,0.f });
		m_objList.push_back(enemy);
	}

	//m_player->Update();
	//m_enemy->Update();

	//全オブジェクトの更新関数を一括で呼ぶ
	//for (auto& obj : m_objList)
	//{
	//	obj->Update();
	//}
 
	//for (std::shared_ptr<BaseObject> i : m_objList)
	//{
	//	i->Update();
	//}

	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Update();
	}
}

void GameScene::Draw()
{
	//m_player->Draw();
	//m_enemy->Draw();
	
	//全オブジェクトの描画関数を一括で呼ぶ
	//範囲ベースfor
	//for (auto& obj : m_objList)
	//{
	//	obj->Draw();
	//}

	//for (std::shared_ptr<BaseObject> i : m_objList)
	//{
	//	i->Draw();
	//}

	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Draw();
	}
}

void GameScene::Init()
{
	//m_player = new Player;
	//m_player->SetOwner(this);
	//m_player = std::make_shared<Player>();
	//m_enemy = std::make_shared<Enemy>();
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->SetOwner(this);
	m_objList.push_back(player);
	std::shared_ptr<Enemy> enemy;
	for (int i = 0; i < 10; i++)
	{
		enemy = std::make_shared<Enemy>();
		enemy->SetPos({ i * 128.f - 640.f, 360.f });
		//enemy->SetMove({ 0.f,-1.f,0.f });
		m_objList.push_back(enemy);
	}
}

void GameScene::Release()
{
	//delete m_player;
}