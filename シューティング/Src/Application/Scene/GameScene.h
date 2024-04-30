#pragma once

//class Player;
class BaseObject;

class GameScene
{
public:
	GameScene(){}
	~GameScene() { Release(); }	//破棄時にRelease

	void PreUpdate();	//更新の前処理
	void Update();		//更新
	void Draw();		//描画
	void Init();		//初期化

	//オブジェクトリストを取得
	std::vector<std::shared_ptr<BaseObject>> GetObjList() { return m_objList; }

	void AddObjectList(std::shared_ptr<BaseObject> _obj) { m_objList.push_back(_obj); }

private:
	void Release();		//終了処理	※外部から呼ばれたくないのでprivate
		
	//Player* m_player = nullptr;						//派生クラス
	//BaseObject* m_player = nullptr;					//基底クラス
	//std::shared_ptr<Player> m_player = nullptr;		//スマートポインタ
	//std::shared_ptr<BaseObject> m_player = nullptr;	//スマートポインタ
	//std::shared_ptr<BaseObject> m_enemy = nullptr;	//スマートポインタ

	//全オブジェクトを可変長配列で管理
	std::vector<std::shared_ptr<BaseObject>> m_objList;	//スマートポインタ
};